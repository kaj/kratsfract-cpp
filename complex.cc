#include "complex.hh"
#include <algorithm>

std::ostream& operator << (std::ostream& out, Complex c) {
  return out << c.real << '+' << c.imag << 'i';
}

Transform::Transform(int width, int height, double scale)
  : center(0), w(width), h(height), scale(scale)
{
  init();
}

void Transform::set_source_size(int width, int height) {
  w = width;
  h = height;
  init();
}

void Transform::set_center(Complex c, double scale_factor) {
  this->center = c;
  this->scale *= scale_factor;
  init();
}

void Transform::init() {
  s = scale / (std::min(w, h) / 2);
  dx = s * w / 2 - center.get_real();
  dy = s * h / 2 + center.get_imag();
  /*
  std::cout << "Initialized transform " << center << " " << scale
	    << " => " << s << " " << dx << " " << dy
	    << std::endl;
  */
}

int julia(Complex z, Complex c, int max_i) {
  for (int i = 0; i < max_i; ++i) {
    if (z.abs2() > 4) {
      return i;
    } else {
      z = z.sqr() + c;
    }
  }
  return 0;
}
