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
        Matrix(Matrix& rhs);
        Matrix operator= (Matrix& mat);

        int nrows;
        int ncols;
        RowVector Row(int idx);
        ColumnVector Column(int idx);

        double **data;
        // std::vector< std::vector<double> > data();
        double operator() (int row, int col);
        Matrix operator+ (Matrix& right);
        // Matrix operator+ (double constant);
        Matrix operator- (Matrix& right);
        // Matrix operator- (double constant);
        Matrix operator* (Matrix& right);
        Matrix operator* (MatrixVector& right);
        // Matrix operator* (double constant);
        Matrix operator/ (Matrix& right);
        Matrix operator+= (Matrix& another);
        Matrix operator-= (Matrix& another);
        Matrix operator*= (Matrix& another);
        Matrix operator/= (Matrix& another);
        // Matrix operator= (std::vector< std::vector<double> >& vector);

        Matrix inverse();
        Matrix transpose();
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


class MatrixVector {
    public:
        MatrixVector();
        MatrixVector(int n);
        MatrixVector(double arr[]);
        ~MatrixVector();
        int size;
        double* data;
        double operator() (int idx);
        MatrixVector transpose();
    private:
        // double _data [];
};




class RowVector: public MatrixVector {
    public:
        RowVector();
        RowVector(int n);
        RowVector(double arr[]);
        ColumnVector transpose();
        double operator* (ColumnVector right);
        Matrix operator* (Matrix right);
};

class ColumnVector: public MatrixVector {
    public:
        ColumnVector();
        ColumnVector(int n);
        ColumnVector(double arr[]);
        RowVector transpose();
        Matrix operator* (RowVector right);
        Matrix operator* (Matrix right);
};
