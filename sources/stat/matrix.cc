#include "matrix.h"
#include <iostream>


Matrix::Matrix(int rows, int cols)
{
    nrows = rows;
    rows_ = rows;
    ncols = cols;
    cols_ = cols;
    data = new double* [rows];
    for (int i=0; i<rows; i++) 
        data[i] = new double[cols];
}

// Matrix::Matrix(double **arr)
// {
//     nrows = arr.size();
// }

Matrix::~Matrix()
{
    for (int i=0; i<nrows; i++)
        delete [] data[i];
    delete [] data;
}


Matrix::Matrix(Matrix& rhs) 
{
    rows_ = rhs.nrows;
    cols_ = rhs.ncols;
    for (int i=0; i<rhs.nrows; i++) {
        for (int j=0; j<rhs.ncols; j++) {
            data[i][j] = rhs(i, j);
        }
    }   
    // data_ = rhs.data_;
}

RowVector Matrix::Row(int idx) {
    RowVector IndexedRow(data[idx]);
    return IndexedRow;
}

ColumnVector Matrix::Column(int idx) {
    ColumnVector IndexedColumn(nrows);
    for (int i=0; i<nrows; i++)
        IndexedColumn.data[i] = data[i][idx];
    return IndexedColumn;
}


Matrix Matrix::operator= (Matrix& rhs) {
    if (this != &rhs) // avoid self-assignment
    {
        for (int i=0; i<rhs.nrows; i++) {
            for (int j=0; j<rhs.ncols; j++) {
                this->data[i][j] = rhs(i, j);
            }
        }
    }
    return *this;
}

double Matrix::operator() (int row, int col) {
    return data[row][col];
}

Matrix Matrix::operator+ (Matrix& right) {
    Matrix out(nrows, ncols);
    for (int i=0; i < nrows; i++) {
        for (int j=0; j < cols_; j++) {
            out.data[i][j] = data[i][j] + right(i, j);
        }
    }
    return out; 
}

// Matrix Matrix::operator+ (double constant) {
//     std::vector< std::vector<double> > out_data(data_);
//     for (int i=0; i < rows_; i++) {
//         for (int j=0; j < cols_; j++) {
//             out_data[i][j] += constant;
//         }
//     }
//     Matrix out(out_data);
//     return out; 
// }

// Matrix Matrix::operator- (Matrix& right) {
//     std::vector< std::vector<double> > out_data(data_);
//     for (int i=0; i < rows_; i++) {
//         for (int j=0; j < cols_; j++) {
//             out_data[i][j] -= right(i, j);
//         }
//     }
//     Matrix out(out_data);
//     return out; 
// }

// Matrix Matrix::operator+ (double constant) {
//     std::vector< std::vector<double> > out_data(data_);
//     for (int i=0; i < rows_; i++) {
//         for (int j=0; j < cols_; j++) {
//             out_data[i][j] -= constant;
//         }
//     }
//     Matrix out(out_data);
//     return out; 
// }

Matrix Matrix::operator* (Matrix& mat) {
    Matrix out(nrows, mat.ncols);
    // std::cout << "for k:" << cols_ << std::endl;
    // std::vector< std::vector<double> > out_vector(rows_, std::vector<double>(mat.ncol(), 0.0));
    for (int i=0; i < nrows; i++) {
        for (int j=0; j < mat.ncols; j++) {
            double tmpSum = 0.0;
            for (int k=0; k < ncols; k++) {
                tmpSum += (data[i][k] * mat(k, j));
            }
            out.data[i][j] = tmpSum;
        }
    }
    return out;
}

Matrix Matrix::operator* (MatrixVector& right) {
    if (ncols != right.size)
        throw "Incompatible number of dimension!";
    Matrix out(nrows, 1);
    for (int i=0; i < nrows; i++) {
        double tmpSum = 0.0;
        for (int j=0; j < right.size; j++) {
            tmpSum += data[i][j] * right(j);
            }
        out.data[i][0] = tmpSum;
    }
    return out;
}


// Matrix Matrix::operator* (double constant) {
//     std::vector< std::vector<double> > out_data(data_);
//     for (int i=0; i < rows_; i++) {
//         for (int j=0; j < cols_; j++) {
//             out_data[i][j] *= constant;
//         }
//     }
//     Matrix out(out_data);
//     return out; 
// }

Matrix Matrix::transpose() {
    Matrix out(ncols, nrows);
    for (int i=0; i < ncols; i++) {
        for (int j=0; j < nrows; j++) {
            out.data[i][j] = data[j][i];
        }
    }
    return out; 
}

Matrix Matrix::inverse()
{   
    if (!isSquare())
        throw "Inverse is only defined for a square matrix";
    int MatrixSize = ncols;
    // Gauss-Jordan elimination
    Matrix InvertedMatrix(MatrixSize, MatrixSize);
    return InvertedMatrix;
}

void Matrix::print() {
    for (int i=0; i < ncols; i++) {
        for (int j=0; j < nrows; j++) {
            std::cout << data[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}


bool Matrix::isSquare()
{
    return nrows == ncols;
}

bool Matrix::isSymmetric()
{
    if (!isSquare()) return false;
    for (int i=0; i<nrows; i++) {
        for (int j=i+1; j<ncols; j++) {
            if (data[i][j] != data[j][i]) return false;
        }
    }
    return true;
}

bool Matrix::isUpper()
{
    if (!isSquare())
        throw "Non-square matrix not allowed";
    for (int i=0; i<nrows; i++) {
        for (int j=0; j<i; j++) {
            if (data[i][j] != 0.0) return false;
        }
    }
    return true;
}

bool Matrix::isLower()
{
    if (!isSquare())
        throw "Non-square matrix not allowed";
    for (int i=0; i<nrows; i++) {
        for (int j=i+1; j<ncols; j++) {
            if (data[i][j] != 0) return false;
        }
    }
    return true;
}


MatrixVector::MatrixVector(int n) {
    size = n;
    data = new double [size];
}

MatrixVector::MatrixVector(double arr[]) {
    size = sizeof(arr)/sizeof(*arr);
    data = new double [size];
    for (int i=0; i<size; i++) 
        data[i] = arr[i];
}

MatrixVector::~MatrixVector() {
    delete [] data;
}

double MatrixVector::operator() (int idx) {
    return data[idx];
}


RowVector ColumnVector::transpose() {
    RowVector Transposed(data);
    return Transposed;
}

double RowVector::operator* (ColumnVector right) {
    double ScalarProduct = 0.0;
    for (int i=0; i<size; i++) 
        ScalarProduct += this->data[i]*right.data[i];
    return ScalarProduct;
}

Matrix RowVector::operator* (Matrix right) {
    Matrix Multiplied(1, right.ncols);
    for (int i=0; i<right.ncols; i++) {
        double tempSum = 0.0;
        for (int j=0; j<size; j++) 
            tempSum += data[j]*right.data[j][i];
        Multiplied.data[0][i] = tempSum;
    }
    return Multiplied;
}

ColumnVector RowVector::transpose() {
    ColumnVector Transposed(data);
    return Transposed;
}

Matrix ColumnVector::operator* (RowVector right) {
    Matrix Multiplied(size, right.size);
    for (int i=0; i<size; i++) {
        for (int j=0; j<right.size; j++)
            Multiplied.data[i][j] = data[i]*right.data[j];
    }
    return Multiplied;
}

Matrix ColumnVector::operator* (Matrix right) {
    if (right.nrows != 1) 
        throw "Incompatible matrix dimensions!";
    Matrix Multiplied(size, right.ncols);
    for (int i=0; i<size; i++) {
        for (int j=0; j<right.ncols; j++)
            Multiplied.data[i][j] = data[i]*right.data[0][j];
    }
    return Multiplied;
}
