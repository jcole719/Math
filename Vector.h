#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"
#include "Number.h"

#include <iostream>
using namespace std;

class Vector
{
public:
    Vector(int dim):
    vec(dim,Number()) {}
    Vector(vector<Number> v):
    vec(v) {}
    Vector(const Vector &v):
    vec(v.vec) {}
    
    inline int getDimension() {return vec.size();}
    inline Number getNumber(int pos) {return vec[pos];}
    inline void setNumber(int pos, Number num) {vec[pos] = num;}
    
    // Overload operators
    Vector operator - ();
    Vector operator + (Vector v2);
    Vector operator - (Vector v2);
    friend Vector operator * (Matrix m, Vector v);
    
    Number dot(Vector v);
    Vector cross(Vector v);
    
    void print();
    
private:
    vector<Number> vec;
};

#endif //VECTOR_H
