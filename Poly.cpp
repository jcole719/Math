#include "Poly.h"

Poly::Poly(vector<Number> p)
{
    int size = (int) pow(2,ceil(log2(p.size())));
    poly = Vector<Number>(size);
    for (int i = 0; i < p.size(); i++) {
        poly[i] = p[i];
    }
}

Poly::Poly(Vector<Number> p)
{
    poly = p;
}

Poly Poly::operator - ()
{
    Poly result(-this->poly);
    return result;
}

Poly Poly::operator + (Poly p2)
{
    Poly result(poly);
    for (int i = 0; i < poly.getDimension(); i++) {
        result.setCoefficient(i,poly[i] + p2.getCoefficient(i));
    }
    return result;
}

Poly Poly::operator - (Poly p2)
{
    Poly result(poly);
    for (int i = 0; i < poly.getDimension(); i++) {
        result.setCoefficient(i,poly[i] - p2.getCoefficient(i));
    }
    return result;
}

Poly Poly::operator * (Poly p2)
{
    int n = this->getDegree();
    if (n < p2.getDegree()) {
        n = p2.getDegree();
    }
    Vector<Number> p0 = fill(*this,2*n);
    Vector<Number> p1 = fill(p2,2*n);
    p0 = fft(p0);
    p1 = fft(p1);
    Vector<Number> result = point_mult(p0,p1);
    return Poly(fft(result));
}

Vector<Number> Poly::fill(Poly p, int size)
{
    Vector<Number> result(size);
    for (int i = 0; i < p.getDegree(); i++) {
        result[i] = p.getCoefficient(i);
    }
    return result;
}

Vector<Number> Poly::fft(Vector<Number> p)
{
    int n = p.getDimension();
    if (n == 1) {
        return p;
    }
    double arg = 8.0*atan(1.0)/((double) n);
    Number omega_n(cos(arg),sin(arg));
    Number omega(1.0,0.0);
    Vector<Number> p0 = split('e',p);
    Vector<Number> p1 = split('o',p);
    Vector<Number> y0 = fft(p0);
    Vector<Number> y1 = fft(p1);
    Vector<Number> result(n);
    for (int i = 0; i < n/2; i++) {
        result[i] = y0[i] + omega*y1[i];
        result[i + n/2] = y0[i] - omega*y1[i];
        omega = omega*omega_n;
    }
    return result;
}

Vector<Number> Poly::split(char s, Vector<Number> p)
{
    int n = p.getDimension()/2 - 1;
    Vector<Number> result(n);
    int count = 0; 
    for (int i = 0; i < p.getDimension(); i++) {
        if (s == 'e' && i%2 == 0) {
            result[count] = p[i];
            count++;
        }
        else if (s == 'o' && i%2 != 0) {
            result[count] = p[i];
            count++;
        }
    }
    return result;
}

Vector<Number> Poly::point_mult(Vector<Number> p1, Vector<Number> p2)
{
    Vector<Number> result(p1.getDimension());
    for (int i = 0; i < p1.getDimension(); i++) {
            result[i] = p1[i] * p2[i];
    }
    return result;
}

Poly operator * (Number n, Poly p)
{
    Poly result(p);
    for (int i = 0; i < p.getDegree(); i++) {
        result.setCoefficient(i,n * p.getCoefficient(i));
    }
    return result;
}
