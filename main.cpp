
#include <iostream>

#include "Vector.h"
#include "Matrix.h"
#include "Poly.h"

using namespace std;

int main(int argc, char* argv[])
{
    Poly p1({Number(1.0,1.0),Number(0.0,1.0)});
    Poly p2({Number(1.0,0.0),Number(1.0,0.0)});
    p1.print("x");
    p2.print("x");
    Poly p3 = p1 * p2;
    p3.print("x");
    
    return 0;
}
