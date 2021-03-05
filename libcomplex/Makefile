CXX = g++
CFLAGS = -std=c++20 -Wall -pedantic -shared -fPIC
LIBNAME = Complex
LIB = lib$(LIBNAME).so

.PHONY: all clean

all: $(LIB)

$(LIB): $(LIBNAME).cpp $(LIBNAME).hpp
	$(CXX) $< $(CFLAGS) -o ../$@

clean:
	rm -f ../$(LIB)
