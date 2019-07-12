#include <iostream>
#include "matrix.h"

int main() {
    std::vector< std::vector<double> > vec1 = {{1.0, 0.0}, {2.0, 1.0}}; 
    Matrix mat1(vec1);
    std::cout << mat1.ncol() << std::endl;
    mat1.print();
    std::vector< std::vector<double> > vec2 = {{1.0, 0.0}, {2.0, 1.0}}; 
    Matrix mat2(vec2);
    Matrix product = mat1 * mat2;
    std::cout << product.ncol() << "  " << product.nrow() << std::endl;
    std::cout << product(0, 0) << "  " << product(0, 1) << std::endl;
    std::cout << product(1, 0) << "  " << product(1, 1) << std::endl;
    return 0;
}

