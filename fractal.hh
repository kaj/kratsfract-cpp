#include "complex.hh"

class Fractal {
public:
  Fractal(int m) : maxiter(m) {}
  virtual int calc(Complex c) const = 0;

  int get_maxiter() const { return maxiter; }
protected:
  int maxiter;
};

class Mandelbrot : public Fractal {
public:
  Mandelbrot(int maxiter) : Fractal(maxiter) { }
  int calc(Complex z) const;
};

class Julia : public Fractal {
public:
  Julia(Complex c, int maxiter);

  int calc(Complex z) const;
private:
  Complex c;
};

