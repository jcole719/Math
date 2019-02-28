#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

#include <iostream>
using namespace std;

template<class T> class Vector;
template<class U> Vector<U> operator * (Matrix<U> m, Vector<U> v);

template<class T> class Vector
{
public:
    Vector():
    vec() {}
    Vector(int dim):
    vec(dim,T()) {}
    Vector(vector<T> v):
    vec(v) {}
    Vector(const Vector<T> &v):
    vec(v.vec) {}
    
    inline int getDimension() {return vec.size();}
    inline T getVal(int pos) {return vec[pos];}
    inline void setVal(int pos, T val) {vec[pos] = val;}
    
    // Overload operators
    Vector<T> operator - ();
    Vector<T> operator + (Vector<T> v2);
    Vector<T> operator - (Vector<T> v2);
    template<class U> friend Vector<U> operator * (Matrix<U> m, Vector<U> v);
    inline T& operator [] (int pos) {return vec[pos];}
    
    T dot(Vector<T> v2);
    Vector<T> cross(Vector<T> v2);
    
    void print();
    
private:
    vector<T> vec;
};

#endif //VECTOR_H
