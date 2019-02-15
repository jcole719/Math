#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include "Number.h"

using namespace std;

class Matrix
{
public:
    Matrix(int i, int j);
    Matrix(const Matrix &m);
    Matrix(vector< vector<Number> > m);
    
    inline int getN() {return n;}
    inline int getM() {return m;}
    inline Number getNumber(int i, int j) {return matrix[i][j];}
    inline vector<Number> getRow(int i) {return matrix[i];}
    inline void setNumber(int i, int j, Number num) {matrix[i][j] = num;}
    inline void setRow(int i, vector<Number> row) {matrix[i] = row;}
    
    // Overload operators
    Matrix operator - ();
    Matrix operator + (Matrix n2);
    Matrix operator - (Matrix n2);
    Matrix operator * (Matrix n2);
    Matrix operator / (Matrix n2);
    
    Matrix multiplyByNumber(Number n);
    Matrix transpose();
    Matrix getMinor(int row, int col);
    Number determinant();
    Number determinant(Matrix m);
    Matrix inverse();
    Matrix slow_multiply(Matrix a, Matrix b);
    
    // Row operations, etc.
    Matrix swapRow(int r1, int r2);
    Matrix rowNumMult(int row, Number num);
    Matrix rowRowMult(int r1, int r2, Number mult);
    bool isREForm(Matrix m);
    
    // Special matrices
    static Matrix identity(int n);
    
    void print();
    
private:
    vector< vector<Number> > matrix;
    int n;
    int m;
    
};

#endif //MATRIX_H
    
