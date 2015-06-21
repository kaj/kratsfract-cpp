#include <gtkmm.h>
#include <iostream>
#include "complex.hh"
#include <chrono>
#include "fractal.hh"

class FractalWidget : public Gtk::DrawingArea {
public:
  FractalWidget();
protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  virtual bool on_button_clicked(GdkEventButton* event);
private:
  Fractal* fractal;
  Transform p2c;
};

FractalWidget::FractalWidget()
  : p2c(800, 600, 1.2)
{
  add_events(Gdk::BUTTON_PRESS_MASK); // | Gdk::BUTTON_RELEASE_MASK
  signal_button_press_event().connect(
    sigc::mem_fun(*this, &FractalWidget::on_button_clicked));

  p2c.set_center(Complex(-.5));
  fractal = new Mandelbrot(1024);
}

bool FractalWidget::on_button_clicked(GdkEventButton* event) {
  Complex c = p2c(event->x, event->y);
  std::cout << "Button " << event->button << " was clicked at " << c << std::endl;
  switch (event->button) {
  case 1:
    p2c.set_center(c, 0.5);
    break;
  case 2:
    p2c = Transform(800, 600, 1.2);
    fractal = new Julia(c, 255);
    break;
  case 3:
    p2c.set_center(c, 2);
    break;
  }
  queue_draw();
  return true;
}

class Palette {
public:
  Palette(int n) : n_colors(n) {}

  void put(int c, guint8* p) {
    *p++ = char(c % 255);
    *p++ = char(c % 255);
    *p++ = char(c * 255 / n_colors);
  }
private:
  int n_colors;
};

bool FractalWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Glib::RefPtr<Gdk::Pixbuf> image =
    Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 8, get_width(), get_height());
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  p2c.set_source_size(image->get_width(), image->get_height());
  // Complex c(-0.75, 0.14);
  // Complex zero(0);
  int rowstride = image->get_rowstride();

  Palette palette(fractal->get_maxiter());
  guint8* data = image->get_pixels();
  for (int y = 0; y < image->get_height(); ++y) {
    for (int x = 0; x < image->get_width(); ++x) { 
      palette.put(fractal->calc(p2c(x, y)),
		  &data[rowstride * y + 3*x]);
    }
  }

  std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

  std::cout << "Rendered " << image->get_width() << 'x' << image->get_height()
	    << " fractal in "
	    << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
	    << " ms." << std::endl;
  
  Gdk::Cairo::set_source_pixbuf(cr, image, 0, 0);
  cr->rectangle(0, 0, image->get_width(), image->get_height());
  cr->fill();
  return true;
}

class MainWindow : public Gtk::Window {

public:
  MainWindow();
  virtual ~MainWindow();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  FractalWidget fractal;
};

MainWindow::MainWindow()
{
  int bw = 0;
  set_border_width(bw);
  set_default_size(800 + 2*bw, 600 + 2*bw);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  //m_button.signal_clicked().connect(sigc::mem_fun(*this,
  //             &MainWindow::on_button_clicked));

  add(fractal);
  fractal.show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  MainWindow window;

  return app->run(window);
}
