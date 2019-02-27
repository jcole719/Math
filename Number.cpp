#include "Number.h"

Number::Number(double real, double imaginary)
{
    setNumber(real,imaginary);
}

Number::Number(Number const &number)
{
    real = number.real;
    imaginary = number.imaginary;
}

Number Number::operator - ()
{
    return Number(-real,-imaginary);
}

Number Number::operator + (Number n2)
{
    return Number(real + n2.getReal(),imaginary + n2.getImaginary());
}

Number Number::operator - (Number n2)
{
    return *this + (-n2);
}

Number Number::operator * (Number n2)
{
    double r = real*n2.getReal() - imaginary*n2.getImaginary();
    double i = real*n2.getImaginary() + imaginary*n2.getReal();
    return Number(r,i);
}

Number Number::operator / (Number n2)
{
    return *this * n2.inverse();
}

Number& Number::operator += (Number n2)
{
    *this = *this + n2;
    return *this;
}

bool Number::operator == (Number n2)
{
    if (real == n2.getReal() && imaginary == n2.getImaginary()) {
        return true;
    }
    return false;
}

bool Number::operator != (Number n2)
{
    if (*this == n2) {
        return false;
    }
    return true;
}

ostream & operator << (ostream &out, Number &n)
{
    out << '(';
    if (n.real != 0.0) {
        out << n.real;
    }
    if (n.real != 0.0 && n.imaginary != 0.0) {
        out << '+';
    }
    if (n.imaginary != 0.0) {
        out << n.imaginary << 'i';
    }
    out << ')';
}

Number Number::inverse()
{
    double mag_square = pow(magnitude(),2);
    Number result = conjugate();
    result.setNumber(result.getReal()/mag_square,result.getImaginary()/mag_square);
    return result;
}

void Number::print()
{
    cout << '(';
    if (real != 0.0) {
        cout << real;
    }
    if (real != 0.0 && imaginary != 0.0) {
        cout << '+';
    }
    if (imaginary != 0.0) {
        cout << imaginary << 'i';
    }
    cout << ')';
}

string Number::toString()
{
    string result = "(";
    if (real != 0.0) {
        result = result + to_string(real);
    }
    if (real != 0.0 && imaginary != 0.0) {
        result = result + "+";
    }
    if (imaginary != 0.0) {
        result = result + to_string(imaginary) + "i";
    }
    result = result + ")";
    return result;
}
