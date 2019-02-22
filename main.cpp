
#include <iostream>

#include "Vector.h"
#include "Matrix.h"

using namespace std;

int main(int argc, char* argv[])
{
    Matrix m({{Number(2.0,1.0),Number(1.0,2.0)},{Number(1.0,0.0),Number(0.0,1.0)}});
    m.print();
    Vector<Number> v({Number(2.0,1.0),Number(1.0,2.0)});
    //v.print();
    //v = m * v;
    //v.print();
    return 0;
}
