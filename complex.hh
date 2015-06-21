#ifndef __COMPLEX_HH
#define __COMPLEX_HH
#include <iostream>

class Complex {
public:
  Complex(double re, double im = 0) : real(re), imag(im) {}
  double abs2() const {
    return real * real + imag * imag;
  }
  Complex sqr() const {
    return Complex(real * real - imag * imag, 2 * real * imag);
  }
  Complex operator + (Complex x) const {
    return Complex(real + x.real, imag + x.imag);
  }

  double get_real() const { return real; }
  double get_imag() const { return imag; }

private:
  double real, imag;
  friend std::ostream& operator << (std::ostream& out, Complex c);
};


class Transform {
public:
  Transform(int width, int height, double scale);
  void set_source_size(int width, int height);
  void set_center(Complex c, double scale_factor = 1);

  Complex operator () (int x, int y) const {
    return Complex(s * x - dx, -(s * y - dy));
  }
private:
  void init();

  Complex center;
  int w, h;
  double scale, s, dx, dy;
};

int julia(Complex z, Complex c, int max_i);

#endif
