#include "Matrix.h"

Matrix::Matrix(int i, int j)
{
    matrix = vector< vector<Number> >(i,vector<Number>(j,Number()));
    n = i;
    m = j;
}

Matrix::Matrix(const Matrix &mat)
{
    n = mat.n;
    m = mat.m;
    matrix = vector< vector<Number> >(n,vector<Number>(m,Number()));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            setNumber(i,j,mat.matrix[i][j]);
        }
    }
}

Matrix::Matrix(vector< vector<Number> > mat)
{
    this->n = mat.size();
    this->m = mat[0].size();
    matrix = vector< vector<Number> >(n,vector<Number>(m,Number()));
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            matrix[i][j] = mat[i][j];
        }
    }
}

Matrix Matrix::operator - ()
{
    Matrix result(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(i,j,-matrix[i][j]);
        }
    }
    return result;
}

Matrix Matrix::operator + (Matrix m2)
{
    if (n != m2.getN() || m != m2.getM()) {
        return Matrix(0,0);
    }
    Matrix result(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(i,j,matrix[i][j]+m2.getNumber(i,j));
        }
    }
    return result;
}

Matrix Matrix::operator - (Matrix m2)
{
    if (n != m2.getN() || m != m2.getM()) {
        return Matrix(0,0);
    }
    Matrix result(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(i,j,matrix[i][j]-m2.getNumber(i,j));
        }
    }
    return result;
}

Matrix Matrix::operator * (Matrix m2)
{
    if (n != m2.getM() || m != m2.getN()) {
        return Matrix(0,0);
    }
    return slow_multiply(*this,m2);
}

Matrix Matrix::operator / (Matrix m2)
{
    if (n != m2.getN() || m != m2.getM() || n != m) {
        return Matrix(0,0);
    }
    return (*this)*m2.inverse();
}

Matrix Matrix::multiplyByNumber(Number n)
{
    Matrix result = *this;
    for (int i = 0; i < getN(); i++) {
        for (int j = 0; j < getM(); j++) {
            result.setNumber(i,j,n*getNumber(i,j));
        }
    }
    return result;
}

Matrix Matrix::transpose()
{
    Matrix result(m,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(j,i,matrix[i][j]);
        }
    }
    return result;
}

Matrix Matrix::getMinor(int row, int col)
{
    Matrix result(n-1,m-1);
    int rr = 0;
    for (int i = 0; i < n; i++) {
        int rc = 0;
        for (int j = 0; j < m; j++) {
            if (i != row && j != col) {
                result.setNumber(rr,rc,getNumber(i,j));
                rc++;
            }
            if (rc == n - 1) {
                rc = 0;
                rr++;
            }
        }
    }
    return result;
}

Number Matrix::determinant()
{
    return determinant(*this);
}

Number Matrix::determinant(Matrix mat)
{
    Number result;
    int k = mat.getN();
    if (k != mat.getM()) {
        return Number();
    }
    Number sign(1.0,0.0);
    if (k == 1) {
        return mat.getNumber(0,0);
    }
    else {
        for (int i = 0; i < k; i++) {
            Matrix temp = mat.getMinor(0,i);
            result += sign*mat.getNumber(0,i)*determinant(temp);
            sign = -sign;
        }
    }
    return result;
}

Matrix Matrix::inverse()
{
    Number zero;
    Number det = determinant();
    if (det == zero) {
        return Matrix(0,0);
    }
    Matrix minors(n,m);
    Number sign(1.0,0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 != 0) {
                sign = Number(-1.0,0.0);
            }
            else {
                sign = Number(1.0,0.0);
            }
            minors.setNumber(i,j,sign*determinant(getMinor(i,j)));
        }
    }
    return minors.transpose().multiplyByNumber(det.inverse());
}

Matrix Matrix::slow_multiply(Matrix a, Matrix b)
{
    int n = a.getN();
    int m = a.getM();
    Matrix result(n,b.getM());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b.getM(); j++) {
            for (int k = 0; k < m; k++) {
                result.setNumber(i,j,result.getNumber(i,j) + (a.getNumber(i,k) * b.getNumber(k,j)));
            }
        }
    }
    return result;
}

Matrix Matrix::swapRow(int r1, int r2)
{
    Matrix result = *this;
    result.setRow(r1,getRow(r2));
    result.setRow(r2,getRow(r1));
    return result;
}

Matrix Matrix::rowNumMult(int row, Number num)
{
    Matrix result = *this;
    for (int i = 0; i < m; i++) {
        result.setNumber(row,i,num * getNumber(row,i));
    }
    return result;
}

Matrix Matrix::rowRowMult(int r1, int r2, Number mult)
{
    Matrix result = *this;
    for (int i = 0; i < m; i++) {
        result.setNumber(r1,i,getNumber(r1,i) + mult * getNumber(r2,i));
    }
    return result;
}

bool Matrix::isREForm(Matrix m)
{
    int pivot = -1;
    Number zero(0.0,0.0);
    bool isZero = false;
    for (int i = 0; i < m.getN(); i++) {
        bool pivotSet = false;
        bool notZero = false;
        for (int j = 0; j < m.getM(); i++) {
            if (m.getNumber(i,j) != zero) {
                if (pivot < j) {
                    if (!pivotSet) {
                        pivot = j;
                        pivotSet = true;
                    }
                }
                else {
                    return false;
                }
            }
            if (m.getNumber(i,j) != zero) {
                notZero = true;
                if (isZero == true) {
                    return false;
                }
            }
        }
        if (!notZero) {
            isZero = true;
        }
    }
    return true;
}

Matrix Matrix::identity(int n)
{
    Matrix result(n,n);
    for (int i = 0; i < n; i++) {
        result.setNumber(i,i,Number(1.0,0.0));
    }
    return result;
}

void Matrix::print()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j].print();
            cout << ' ';
        }
        cout << '\n';
    }
}
