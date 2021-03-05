CXX = g++
CFLAGS = -std=c++20 -Wall -pedantic -L. -lComplex -Wl,-rpath=.
LIBFLAGS = -std=c++20 -Wall -pedantic -shared -fPIC
PROG1 = TestComplex
PROG2 = Mandelbrot
LIB = Complex

.PHONY: all clean

all: $(PROG1) $(PROG2)

$(PROG1): $(PROG1).cpp libcomplex/$(LIB).hpp lib$(LIB).so
	$(CXX) $< $(CFLAGS) -o $@

$(PROG2): $(PROG2).cpp libcomplex/$(LIB).hpp lib$(LIB).so
	$(CXX) $< $(CFLAGS) `libpng-config --cflags --ldflags` -o $@

lib$(LIB).so: libcomplex/$(LIB).cpp libcomplex/$(LIB).hpp
	$(CXX) $< $(LIBFLAGS) -o $@

clean:
	rm -f $(PROG1) $(PROG2)
