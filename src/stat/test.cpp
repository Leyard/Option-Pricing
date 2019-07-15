#include <iostream>
#include "matrix.h"

int main() {
    std::cout << "Starting " << std::endl;
    Matrix mat1(2, 2);
    mat1.data[0][0] = 1.0;
    mat1.data[0][1] = 0.0;
    mat1.data[1][0] = 2.0;
    mat1.data[1][1] = 1.0; 
    std::cout << mat1.ncols << std::endl;
    // mat1.print();
    Matrix mat2(2, 2);
    mat2.data[0][0] = 1.0;
    mat2.data[0][1] = 0.0;
    mat2.data[1][0] = 2.0;
    mat2.data[1][1] = 1.0; 
    Matrix product = mat1 * mat2;
    std::cout << product.ncols << "  " << product.nrows << std::endl;
    std::cout << "this is result" << std::endl;
    std::cout << product(0, 0) << "  " << product(0, 1) << std::endl;
    std::cout << product(1, 0) << "  " << product(1, 1) << std::endl;
    return 0;
}

