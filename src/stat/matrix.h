#pragma once
#include <stdexcept>
#include <vector>

template <typename T>
class Matrix {
    public:
        Matrix(size_t rows, size_t cols): rows_(rows), cols_(cols);
        Matrix(std::vector<std::vector<T>> m): rows_(m.size()), cols_(m[0].size());
        Matrix(const Matrix<T>& m), rows_(m.nrow()), cols_(m.cols());
        ~Matrix();

        size_t nrow();
        size_t ncol();
        T& operator() (size_t row, size_t col);
        Matrix<T> operator+ (Matrix<T>& left, Matrix<T>& right);
        Matrix<T> operator- (Matrix<T>& left, Matrix<T>& right);
        Matrix<T> operator* (Matrix<T>& left, Matrix<T>& right);
        Matrix<T> operator/ (Matrix<T>& left, Matrix<T>& right);
        Matrix<T> operator+= (Matrix<T>& another);
        Matrix<T> operator-= (Matrix<T>& another);
        Matrix<T> operator*= (Matrix<T>& another);
        Matrix<T> operator/= (Matrix<T>& another);
        Matrix<T> operator= (std::vector<std::vector<T>>);
        Matrix& operator= (const Matrix<T>& m);

        Matrix<T> inv();
        Matrix<T> transpose();
        bool isSquare();
        T det();
    private:
        unsigned rows_, cols_;
        double* data_;
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    if (rows == 0 || cols == 0)
        throw std::out_of_range("Matrix constructor has 0 size.");
    data_ = new double[rows * cols];
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] data_;
}

template <typename T>
T& Matrix<T>::operator() (size_t row, size_t col) {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Matrix subscript out of bounds.");
    return data_[cols_*row+col];
}
