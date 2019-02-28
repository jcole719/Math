#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include "Number.h"

#include <iostream>
using namespace std;

template<class T> class Matrix;
template<class U> Matrix<U> operator * (Number n1, Matrix<U> m2);

template<class T> class Matrix
{
public:
    Matrix(int i, int j);
    Matrix(const Matrix<T> &m);
    Matrix(vector< vector<T> > m);
    
    inline int getN() {return n;}
    inline int getM() {return m;}
    inline T getNumber(int i, int j) {return matrix[i][j];}
    inline vector<T> getRow(int i) {return matrix[i];}
    inline void setNumber(int i, int j, T num) {matrix[i][j] = num;}
    inline void setRow(int i, vector<T> row) {matrix[i] = row;}
    
    // Overload operators
    Matrix<T> operator - ();
    Matrix<T> operator + (Matrix<T> m2);
    Matrix<T> operator - (Matrix<T> m2);
    Matrix<T> operator * (Matrix<T> m2);
    template<class U> friend Matrix<U> operator * (U n1, Matrix<U> m2);
    Matrix<T> operator * (T n1);
    Matrix<T> operator / (Matrix<T> m2);
    
    Matrix<T> transpose();
    Matrix<T> getMinor(int row, int col);
    T determinant();
    T determinant(Matrix<T> m);
    Matrix<T> inverse();
    Matrix<T> slow_multiply(Matrix<T> a, Matrix<T> b);
    
    // Row operations, etc.
    Matrix<T> swapRow(int r1, int r2);
    Matrix<T> rowNumMult(int row, T num);
    Matrix<T> rowRowMult(int r1, int r2, T mult);
    bool isREForm(Matrix<T> m);
    
    // Special matrices
    static Matrix<T> identity(int n);
    
    void print();
    
private:
    vector< vector<T> > matrix;
    int n;
    int m;
    
};

#endif //MATRIX_H
