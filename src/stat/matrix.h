#pragma once
#include <stdexcept>
// #include <vector>


class Matrix {
    public:
        // Matrix();
        Matrix(int rows, int cols);
        // Matrix(double **arr);
        ~Matrix();
        // Matrix(int rows, int cols): rows_(rows), cols_(cols) {};
        // Matrix(std::vector< std::vector<double> >& m): rows_(m.size()), cols_(m[0].size()), data_(m) {}
        // no semicolon needed to end a member initializer list
        Matrix(const Matrix& rhs);
        Matrix operator= (Matrix& mat);

        int nrows;
        int ncols;
        double **data;
        // std::vector< std::vector<double> > data();
        double operator() (int row, int col);
        Matrix operator+ (Matrix& right);
        // Matrix operator+ (double constant);
        Matrix operator- (Matrix& right);
        // Matrix operator- (double constant);
        Matrix operator* (Matrix& right);
        // Matrix operator* (double constant);
        Matrix operator/ (Matrix& right);
        Matrix operator+= (Matrix& another);
        Matrix operator-= (Matrix& another);
        Matrix operator*= (Matrix& another);
        Matrix operator/= (Matrix& another);
        // Matrix operator= (std::vector< std::vector<double> >& vector);

        Matrix inverse();
        Matrix transpose();
        bool isSquare();
        double det();

        void print();
        bool isSquare();
        bool isSymmetric();
        bool isDefinite();
        bool isUpper();
        bool isLower();

    private:
        int rows_;
        int cols_;
        // std::vector< std::vector<double> >& data_;
};

