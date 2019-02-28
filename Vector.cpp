#include "Vector.h"

template<class T> Vector<T> Vector<T>::operator - ()
{
    int n = getDimension();
    Vector<T> result(n);
    for (int i = 0; i < n; i++) {
        result.setVal(i,-vec[i]);
    }
    return result;
}

template<class T> Vector<T> Vector<T>::operator + (Vector<T> v2)
{
    int n = getDimension();
    Vector<T> result(n);
    if (n != v2.getDimension()) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result.setVal(i,vec[i] + v2.getNumber(i));
    }
    return result;
}

template<class T> Vector<T> Vector<T>::operator - (Vector<T> v2)
{
    int n = getDimension();
    Vector<T> result(n);
    if (n != v2.getDimension()) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result.setVal(i,vec[i] - v2.getVal(i));
    }
    return result;
}

template<class U> Vector<U> operator * (Matrix<U> m, Vector<U> v)
{
    Vector<U> result(v.getDimension());
    if (v.getDimension() != m.getM()) {
        return result;
    }
    for (int i = 0; i < m.getN(); i++) {
        U temp;
        for (int j = 0; j < m.getM(); j++) {
            temp += m.getNumber(i,j)*v.getVal(j);
        }
        result.setVal(i,temp);
    }
    return result;
}

template<class T> T Vector<T>::dot(Vector<T> v2)
{
    int n = getDimension();
    T result;
    if (n != v2.getDimension()) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result += vec[i] * v2.getVal(i);
    }
    return result;
}
    

template<class T> void Vector<T>::print()
{
    for (auto n : vec) {
        cout << n << " ";
    }
    cout << '\n';
}
