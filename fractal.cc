#include "fractal.hh"

int Mandelbrot::calc(Complex z) {
  return julia(0, z, maxiter);
}

Julia::Julia(Complex c, int maxiter) : Fractal(maxiter), c(c) { }

int Julia::calc(Complex z) {
  return julia(z, c, maxiter);
}

