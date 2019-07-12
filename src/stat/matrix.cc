#include "matrix.h"
#include <iostream>


int Matrix::ncol() {
    return cols_;
}

int Matrix::nrow() {
    return rows_;
}

std::vector< std::vector<double> > Matrix::data() {
    return data_;
}

Matrix::Matrix(const Matrix& rhs) : data_(rhs.data_) {
    rows_ = rhs.rows_;
    cols_ = rhs.rows_;
    // data_ = rhs.data_;
}


Matrix Matrix::operator= (Matrix& rhs) {
    Matrix mat(rhs.data());
    return mat;
}

double Matrix::operator() (int row, int col) {
    return data_[row][col];
}

Matrix Matrix::operator+ (Matrix& right) {
    std::vector< std::vector<double> > out_data(data_);
    for (int i=0; i < rows_; i++) {
        for (int j=0; j < cols_; j++) {
            out_data[i][j] += out_data[i][j] + right(i, j);
        }
    }
    Matrix out(out_data);
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

Matrix Matrix::operator- (Matrix& right) {
    std::vector< std::vector<double> > out_data(data_);
    for (int i=0; i < rows_; i++) {
        for (int j=0; j < cols_; j++) {
            out_data[i][j] -= right(i, j);
        }
    }
    Matrix out(out_data);
    return out; 
}

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
    std::vector< std::vector<double> > out_vector(rows_, std::vector<double>(mat.ncol(), 0.0));
    for (int i=0; i < rows_; i++) {
        for (int j=0; j < mat.ncol(); j++) {
            for (int k=0; k < cols_; k++) {
                out_vector[i][j] = out_vector[i][j] + data_[i][k] * mat(k, j);
            }
        }
    }
    std::cout << out_vector[0][0] << out_vector[0][1] << std::endl;
    std::cout << out_vector[1][0] << out_vector[1][1] << std::endl;
    Matrix out(out_vector);
    std::cout << out(0, 0) << out(0, 1) << std::endl;
    std::cout << out(1, 0) << out(1, 1) << std::endl;
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
    std::vector< std::vector<double> > out_data;
    out_data.resize(cols_);
    for (int i=0; i < cols_; i++) {
        out_data[i].resize(rows_);
        for (int j=0; j < rows_; j++) {
            out_data[i][j] = data_[j][i];
        }
    }
    Matrix out(out_data);
    return out; 
}

void Matrix::print() {
    for (int i=0; i < cols_; i++) {
        for (int j=0; j < rows_; j++) {
            std::cout << data_[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
