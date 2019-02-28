#include "Matrix.h"

template<class T> Matrix<T>::Matrix(int i, int j)
{
    matrix = vector< vector<T> >(i,vector<T>(j,T()));
    n = i;
    m = j;
}

template<class T> Matrix<T>::Matrix(const Matrix<T> &mat)
{
    n = mat.n;
    m = mat.m;
    matrix = vector< vector<T> >(n,vector<T>(m,T()));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            setNumber(i,j,mat.matrix[i][j]);
        }
    }
}

template<class T> Matrix<T>::Matrix(vector< vector<T> > mat)
{
    this->n = mat.size();
    this->m = mat[0].size();
    matrix = vector< vector<T> >(n,vector<T>(m,T()));
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[i].size(); j++) {
            matrix[i][j] = mat[i][j];
        }
    }
}

template<class T> Matrix<T> Matrix<T>::operator - ()
{
    Matrix<T> result(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(i,j,-matrix[i][j]);
        }
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::operator + (Matrix<T> m2)
{
    if (n != m2.getN() || m != m2.getM()) {
        return Matrix<T>(0,0);
    }
    Matrix<T> result(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(i,j,matrix[i][j]+m2.getNumber(i,j));
        }
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::operator - (Matrix<T> m2)
{
    if (n != m2.getN() || m != m2.getM()) {
        return Matrix<T>(0,0);
    }
    Matrix<T> result(n,m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(i,j,matrix[i][j]-m2.getNumber(i,j));
        }
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::operator * (Matrix<T> m2)
{
    if (n != m2.getM() || m != m2.getN()) {
        return Matrix<T>(0,0);
    }
    return slow_multiply(*this,m2);
}

template<class U> Matrix<U> operator * (U n1, Matrix<U> m2)
{
    return m2 * n1;
}

template<class T> Matrix<T> Matrix<T>::operator * (T n2)
{
    Matrix<T> result = *this;
    for (int i = 0; i < getN(); i++) {
        for (int j = 0; j < getM(); j++) {
            result.setNumber(i,j,n2*getNumber(i,j));
        }
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::operator / (Matrix<T> m2)
{
    if (n != m2.getN() || m != m2.getM() || n != m) {
        return Matrix<T>(0,0);
    }
    return (*this)*m2.inverse();
}

template<class T> Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> result(m,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result.setNumber(j,i,matrix[i][j]);
        }
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::getMinor(int row, int col)
{
    Matrix<T> result(n-1,m-1);
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

template<class T> T Matrix<T>::determinant()
{
    return determinant(*this);
}

template<class T> T Matrix<T>::determinant(Matrix<T> mat)
{
    T result;
    int k = mat.getN();
    if (k != mat.getM()) {
        return T();
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

template<class T> Matrix<T> Matrix<T>::inverse()
{
    T zero;
    T det = determinant();
    if (det == zero) {
        return Matrix<T>(0,0);
    }
    Matrix<T> minors(n,m);
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
    return minors.transpose()*det.inverse();
}

template<class T> Matrix<T> Matrix<T>::slow_multiply(Matrix<T> a, Matrix<T> b)
{
    int n = a.getN();
    int m = a.getM();
    Matrix<T> result(n,b.getM());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b.getM(); j++) {
            for (int k = 0; k < m; k++) {
                result.setNumber(i,j,result.getNumber(i,j) + (a.getNumber(i,k) * b.getNumber(k,j)));
            }
        }
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::swapRow(int r1, int r2)
{
    Matrix<T> result = *this;
    result.setRow(r1,getRow(r2));
    result.setRow(r2,getRow(r1));
    return result;
}

template<class T> Matrix<T> Matrix<T>::rowNumMult(int row, T num)
{
    Matrix<T> result = *this;
    for (int i = 0; i < m; i++) {
        result.setNumber(row,i,num * getNumber(row,i));
    }
    return result;
}

template<class T> Matrix<T> Matrix<T>::rowRowMult(int r1, int r2, T mult)
{
    Matrix<T> result = *this;
    for (int i = 0; i < m; i++) {
        result.setNumber(r1,i,getNumber(r1,i) + mult * getNumber(r2,i));
    }
    return result;
}

template<class T> bool Matrix<T>::isREForm(Matrix<T> m)
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

template<class T> void Matrix<T>::print()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j].print();
            cout << ' ';
        }
        cout << '\n';
    }
}
