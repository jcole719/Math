#include "Vector.h"

Vector Vector::operator - ()
{
    int n = getDimension();
    Vector result(n);
    for (int i = 0; i < n; i++) {
        result.setNumber(i,-vec[i]);
    }
    return result;
}

Vector Vector::operator + (Vector v2)
{
    int n = getDimension();
    Vector result(n);
    if (n != v2.getDimension()) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result.setNumber(i,vec[i] + v2.getNumber(i));
    }
    return result;
}

Vector Vector::operator - (Vector v2)
{
    int n = getDimension();
    Vector result(n);
    if (n != v2.getDimension()) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result.setNumber(i,vec[i] - v2.getNumber(i));
    }
    return result;
}

Vector operator * (Matrix m, Vector v)
{
    Vector result(v.getDimension());
    if (v.getDimension() != m.getM()) {
        return result;
    }
    for (int i = 0; i < m.getN(); i++) {
        Number temp;
        for (int j = 0; j < m.getM(); j++) {
            temp += m.getNumber(i,j)*v.getNumber(j);
        }
        result.setNumber(i,temp);
    }
    return result;
}

Number Vector::dot(Vector v2)
{
    int n = getDimension();
    Number result;
    if (n != v2.getDimension()) {
        return result;
    }
    for (int i = 0; i < n; i++) {
        result += vec[i] * v2.getNumber(i);
    }
    return result;
}
    

void Vector::print()
{
    for (auto n : vec) {
        n.print();
        cout << " ";
    }
    cout << '\n';
}
