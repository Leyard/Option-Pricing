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


Matrix::Matrix(const Matrix& rhs) 
{
    rows_ = rhs.rows_;
    cols_ = rhs.rows_;
    // data_ = rhs.data_;
}


Matrix Matrix::operator= (Matrix& rhs) {
    Matrix out(rhs.nrows, rhs.ncols);
    for (int i=0; i<rhs.nrows; i++)
    {
        for (int j=0; j<rhs.ncols; j++) 
        {
            out.data[i][j] = rhs(i, j);
        }
    }
    return out;
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
