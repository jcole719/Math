#include <iostream>
#include "Matrix.h"
using namespace std;

int main(int argc, char* argv[])
{
    Matrix m({{Number(2.0,1.0),Number(1.0,2.0)},{Number(1.0,0.0),Number(0.0,1.0)}});
    m.print();
    Matrix n = m;
    n.print();
    m = m / n;
    m.print();
    cout << '\n';
    return 0;
}
