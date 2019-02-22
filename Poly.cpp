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
