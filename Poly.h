#ifndef POLY_H
#define POLY_H

#include "Number.h"
#include "Vector.cpp"

#include <iostream>
using namespace std;

class Poly
{
public:
    Poly(vector<Number> p);
    Poly(Vector<Number> p);
    Poly(const Poly &p):
    poly(p.poly) {}
    
    inline Number getCoefficient(int i) {return poly[i];}
    inline void setCoefficient(int i, Number num) {poly[i] = num;}
    
    // Overload operators
    Poly operator - ();
    Poly operator + (Poly p2);
    Poly operator - (Poly p2);
    Poly operator * (Poly p2);
    friend Poly operator * (Number n, Poly p);
    Poly operator / (Poly p2);
    
    void print(char var);
    
private:
    Vector<Number> poly;
};
#endif //POLY_H
