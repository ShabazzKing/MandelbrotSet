#include <iostream>
#include <cstdlib>
#include <vector>
#include <png++/png.hpp>
#include "libcomplex/Complex.hpp"

void makePicture(const char *, unsigned long, unsigned long);

bool Mandelbrot(unsigned long, unsigned long, unsigned long, unsigned long);

Complex MandelbrotFunction(const Complex &, const Complex &);

template <typename T>
T min(T a, T b)
{
    return a < b ? a : b;
}

int main(int argc, char ** argv)
{
    if (argc != 4)
    {
        std::cout << "Użycie programu:\n";
        std::cout << "Mandelbrot plik szerokość wysokość\n";
        return 0;
    }
    unsigned long width = (unsigned long) std::atol(argv[2]);
    unsigned long height = (unsigned long) std::atol(argv[3]);
    makePicture(argv[1], width, height);
    return 0;
}

void makePicture(const char * file, unsigned long width, unsigned long height)
{
    std::vector<std::vector<bool>> pixels;
    for (unsigned long i = 0; i < height; i++)
    {
        pixels.push_back(std::vector<bool>());
        for (unsigned long j = 0; j < width; j++)
        {
            std::cout << "Obliczam piksel nr (" << i + 1 << ", " << j + 1 << ")\n";
            pixels[i].push_back(Mandelbrot(i, j, height, width));
        }
    }
    png::image<png::rgb_pixel> image(width, height);
    for (png::uint_32 i = 0; i < image.get_height(); i++)
        for (png::uint_32 j = 0; j < image.get_width(); j++)
            if (pixels[i][j])
                image[i][j] = png::rgb_pixel(0, 0, 0);
            else
                image[i][j] = png::rgb_pixel(255, 255, 255);
    image.write(file);
}

bool Mandelbrot(unsigned long i, unsigned long j, unsigned long h, unsigned long w)
{
    const unsigned baseSideSize = 5;
    long double x = (long double) (j + 1) * baseSideSize / min(w, h) - baseSideSize / 2.0L;
    long double y = baseSideSize / 2.0L - (long double) (i + 1) * baseSideSize / min(w, h);
    Complex c(x, y), z;
    unsigned counter = 0;
    do
    {
        z = MandelbrotFunction(c, z);
        counter++;
    }
    while (z.Abs() < 2.0L && counter <= 1000);
    if (counter > 1000)
        return true;
    return false;
}

Complex MandelbrotFunction(const Complex & c, const Complex & z)
{
    return Power(z, 2) + c;
}
