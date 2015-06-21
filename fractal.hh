#include "complex.hh"

class Fractal {
public:
  Fractal(int m) : maxiter(m) {}
  virtual int calc(Complex c) = 0;
protected:
  int maxiter;
};

class Mandelbrot : public Fractal {
public:
  Mandelbrot(int maxiter) : Fractal(maxiter) { }
  int calc(Complex z);
};

class Julia : public Fractal {
public:
  Julia(Complex c, int maxiter);

  int calc(Complex z);
private:
  Complex c;
};

