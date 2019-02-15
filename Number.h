#ifndef NUMB_H
#define NUMB_H

#include <iostream>
#include <cmath>

using namespace std;

class Number
{
public:
    Number(double real = 0.0, double imaginary = 0.0);
    Number(const Number &number);
    
    inline void setNumber(double r = 0.0, double i = 0.0) {real = r; imaginary = i;}
    inline double getReal() const {return real;}
    inline double getImaginary() const {return imaginary;}
    inline double magnitude() {return sqrt(pow(real,2) + pow(imaginary,2));}
    inline Number conjugate() {return Number(real,-imaginary);}
    
    // Overload operators
    Number operator - ();
    Number operator + (Number n2);
    Number operator - (Number n2);
    Number operator * (Number n2);
    Number operator / (Number n2);
    Number& operator += (Number n2);
    bool operator == (Number n2);
    bool operator != (Number n2);
    
    Number inverse();
    void print();
    
private:
    double real;
    double imaginary;
    
};

#endif //NUMB_H
