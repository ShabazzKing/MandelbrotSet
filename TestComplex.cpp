#include <iostream>
#include <numbers>
#include "libcomplex/Complex.hpp"

int main()
{
    using std::cout;
    using std::endl;
    using std::cin;
    cout << "Program testujący liczby zespolone.\n";
    Complex z1, z2, z3;
    z3.setMode(Complex::POL);
    long double d;
    cout << "Podaj pierwszą liczbę z1.\n";
    cin >> z1;
    cout << "Podaj drugą liczbę z2.\n";
    cin >> z2;
    cout << "Podaj trzecią liczbę z3.\n";
    cin >> z3;
    cout << "Podaj liczbę rzeczywistą d.\n";
    cin >> d;
    cout << "Re(z1) = " << z1.Re() << endl;
    cout << "Im(z1) = " << z1.Im() << endl;
    cout << "|z1| = " << z1.Abs() << endl;
    cout << "Arg(z1) = " << z1.Arg() << endl;
    cout << "z1 + z2 = " << z1 + z2 << endl;
    cout << "z1 - z2 = " << z1 - z2 << endl;
    cout << "z1 * z2 = " << z1 * z2 << endl;
    cout << "z1 / z2 = " << z1 / z2 << endl;
    cout << "z3 = " << z3 << endl;
    z3 *= (z1 + z2);
    cout << "z3 po modyfikacji (z3 *= z1 + z2): " << z3 << endl;
    z3.setMode(Complex::RECT);
    cout << "Czyli " << z3 << endl;
    cout << "z1^7 = " << Power(z1, 7) << endl;
    cout << "z1^(-7) = " << Power(z1, -7) << endl;
    cout << "Pierwszy pierwiastek 7 stopnia z z1 = " << Root(z1, 7, 0) << endl;
    cout << "Drugi pierwiastek 7 stopnia z z1 = " << Root(z1, 7, 1) << endl;
    cout << "e^z1 = " << Exp(std::numbers::e_v<long double>, z1) << endl;
    cout << "7^z1 = " << Exp(7, z1) << endl;
    return 0;
}
