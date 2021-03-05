#include <iostream>
#include <cmath>
#include <cstdlib>
#include <numbers>
#include "Complex.hpp"

Complex::Complex(long double a, long double b, Mode m)
{
    mode = m;
    if (mode == RECT)
    {
        x = a;
        y = b;
        set_radius();
        set_angle();
    }
    else
    {
        radius = a;
        if (radius == 0.0L)
            angle = 0.0L;
        else
            angle = b;
        set_x();
        set_y();
    }
}

void Complex::set_x()
{
    x = radius * std::cos(angle);
}

void Complex::set_y()
{
    y = radius * std::sin(angle);
}

void Complex::set_radius()
{
    radius = std::sqrt(x * x + y * y);
}

void Complex::set_angle()
{
    if (x == 0.0L && y == 0.0L)
        angle = 0.0L;
    else
        angle = std::atan2(y, x);
}

void Complex::setMode(Mode m)
{
    mode = m;
}

std::ostream & operator<<(std::ostream & os, const Complex & z)
{
    if (z.mode == Complex::RECT)
        os << z.x << (z.y >= 0.0L ? " + " : " - ") << (z.y >= 0.0L ? z.y : -z.y) << "i";
    else
        os << z.radius << ", " << z.angle << " rad";
    return os;
}

std::istream & operator>>(std::istream & is, Complex & z)
{
    if (z.mode == Complex::RECT)
    {
        std::cout << "Re(z): ";
        is >> z.x;
        std::cout << "Im(z): ";
        is >> z.y;
        z.set_radius();
        z.set_angle();
    }
    else
    {
        long double temp;
        std::cout << "Moduł: ";
        is >> z.radius;
        std::cout << "Argument: ";
        is >> temp;
        if (z.radius == 0.0L)
            z.angle = 0.0L;
        else
            z.angle = temp;
        z.set_x();
        z.set_y();
    }
    return is;
}

long double Complex::Re() const
{
    return x;
}

long double Complex::Im() const
{
    return y;
}

long double Complex::Abs() const
{
    return radius;
}

long double Complex::Arg() const
{
    return angle;
}

const Complex Complex::operator-() const
{
    return Complex(-x, -y);
}

const Complex Complex::conjg() const
{
    return Complex(x, -y);
}

const Complex Complex::operator+(const Complex & z) const
{
    return Complex(x + z.x, y + z.y);
}

const Complex Complex::operator+(long double d) const
{
    return Complex(x + d, y);
}

const Complex operator+(long double d, const Complex & z)
{
    return z + d;
}

const Complex Complex::operator-(const Complex & z) const
{
    return Complex(x - z.x, y - z.y);
}

const Complex Complex::operator-(long double d) const
{
    return Complex(x - d, y);
}

const Complex operator-(long double d, const Complex & z)
{
    return -z + d;
}

const Complex Complex::operator*(const Complex & z) const
{
    return Complex(x * z.x - y * z.y, x * z.y + y * z.x);
}

const Complex Complex::operator*(long double d) const
{
    return Complex(x * d, y * d);
}

const Complex operator*(long double d, const Complex & z)
{
    return z * d;
}

const Complex Complex::operator/(const Complex & z) const
{
    if (z.x == 0.0L && z.y == 0.0L)
        throw ZeroDivision();
    long double denominator = z.x * z.x + z.y * z.y;
    return Complex((x * z.x + y * z.y) / denominator, (y * z.x - x * z.y) / denominator);
}

const Complex Complex::operator/(long double d) const
{
    if (d == 0.0L)
        throw ZeroDivision();
    return *this * (1 / d);
}

const Complex operator/(long double d, const Complex & z)
{
    if (z.x == 0.0L && z.y == 0.0L)
        throw Complex::ZeroDivision();
    Complex temp(1.0L, 0.0L);
    return d * (temp / z);
}

const Complex & Complex::operator+=(const Complex & z)
{
    x += z.x;
    y += z.y;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator+=(long double d)
{
    x += d;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator-=(const Complex & z)
{
    x -= z.x;
    y -= z.y;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator-=(long double d)
{
    x -= d;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator*=(const Complex & z)
{
    long double temp = x * z.x - y * z.y;
    y = x * z.y + y * z.x;
    x = temp;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator*=(long double d)
{
    x *= d;
    y *= d;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator/=(const Complex & z)
{
    if (z.x == 0.0L && z.y == 0.0L)
        throw ZeroDivision();
    long double denominator = z.x * z.x + z.y * z.y;
    long double temp = (x * z.x + y * z.y) / denominator;
    y = (y * z.x - x * z.y) / denominator;
    x = temp;
    set_radius();
    set_angle();
    return *this;
}

const Complex & Complex::operator/=(long double d)
{
    if (d == 0.0L)
        throw ZeroDivision();
    x /= d;
    y /= d;
    set_radius();
    set_angle();
    return *this;
}

bool Complex::operator==(const Complex & z) const
{
    return x == z.x && y == z.y;
}

bool Complex::operator!=(const Complex & z) const
{
    return ! (*this == z);
}

long double power(long double base, long long exp)
{
    long double result = 1.0L;
    if (exp >= 0LL)
        for (long long i = 0LL; i < exp; i++)
            result *= base;
    else
    {
        if (base == 0.0L)
            throw Complex::ZeroDivision();
        for (long long i = 0LL; i < std::abs(exp); i++)
            result /= base;
    }
    return result;
}

const Complex Power(const Complex & z, long long exp)
{
    long double x = power(z.Abs(), exp) * std::cos(exp * z.Arg());
    long double y = power(z.Abs(), exp) * std::sin(exp * z.Arg());
    return Complex(x, y);
}

const Complex Root(const Complex & z, long long deg, long long k)
{
    if (deg == 0LL)
        throw Complex::ZeroDivision();
    long double x = std::pow(z.Abs(), 1 / deg) * 
                    std::cos((z.Arg() + 2 * k * std::numbers::pi_v<long double>) / deg);
    long double y = std::pow(z.Abs(), 1 / deg) * 
                    std::sin((z.Arg() + 2 * k * std::numbers::pi_v<long double>) / deg);
    return Complex(x, y);
}

unsigned factorial(unsigned n)
{
    unsigned result = 1;
    if (n ==0)
        return result;
    for (unsigned i = 1; i < n; i++)
        result *= result + 1;
    return result;
}

const Complex Exp(long double base, const Complex & arg)
{
    if (base != std::numbers::e_v<long double>)
        return Exp(std::numbers::e_v<long double>, arg * std::log(base));
    Complex result;
    for (unsigned i = 0; i < 25; i++)
        result += Power(arg, i) / (long double) factorial(i);
    return result;
}
