#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex
{
public:
    enum Mode { RECT, POL };
private:
    long double x;
    long double y;
    long double radius;
    long double angle;
    Mode mode;
    void set_x();
    void set_y();
    void set_radius();
    void set_angle();
public:
    class ZeroDivision {};
    Complex(long double = 0.0L, long double = 0.0L, Mode = RECT);
    void setMode(Mode);
    friend std::ostream & operator<<(std::ostream &, const Complex &);
    friend std::istream & operator>>(std::istream &, Complex &);
    long double Re() const;
    long double Im() const;
    long double Abs() const;
    long double Arg() const;
    const Complex operator-() const;
    const Complex conjg() const;
    const Complex operator+(const Complex &) const;
    const Complex operator+(long double) const;
    friend const Complex operator+(long double, const Complex &);
    const Complex operator-(const Complex &) const;
    const Complex operator-(long double) const;
    friend const Complex operator-(long double, const Complex &);
    const Complex operator*(const Complex &) const;
    const Complex operator*(long double) const;
    friend const Complex operator*(long double, const Complex &);
    const Complex operator/(const Complex &) const;
    const Complex operator/(long double) const;
    friend const Complex operator/(long double, const Complex &);
    const Complex & operator+=(const Complex &);
    const Complex & operator+=(long double);
    const Complex & operator-=(const Complex &);
    const Complex & operator-=(long double);
    const Complex & operator*=(const Complex &);
    const Complex & operator*=(long double);
    const Complex & operator/=(const Complex &);
    const Complex & operator/=(long double);
    bool operator==(const Complex &) const;
    bool operator!=(const Complex &) const;
    // TODO Rzeczywista potęga liczby zespolonej
    friend const Complex Power(const Complex &, long long);
    friend const Complex Root(const Complex &, long long, long long);
    friend const Complex Exp(long double, const Complex &);
};

#endif
