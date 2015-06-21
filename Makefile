SRC	= main.cc complex.cc fractal.cc

OBJS	= $(SRC:.cc=.o)
CPPFLAGS = -Wall -O4 -std=c++11 $(shell pkg-config --cflags gtkmm-3.0)
LDLIBS = $(shell pkg-config --libs gtkmm-3.0)

all: kratsfract

kratsfract: $(OBJS)
	c++ -o $@ $(OBJS) $(LDLIBS)

main.o: main.cc complex.hh fractal.hh
complex.o: complex.cc complex.hh
fractal.o: fractal.cc fractal.hh complex.hh
