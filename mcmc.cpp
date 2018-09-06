#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
// #include "func.h"
#include "options.h"
// #include "options.cpp"

#define PI 3.14159265358979323846

int main(){
    std::cout << "hello, test for mcmc!!" << std::endl;
    // std::cout << inv_cdf(0.5) << std::endl;
    // std::cout << rand() % 2 << std::endl;
    // std::cout << normal_rand() << std::endl;
    // std::cout << box_muller() << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    std::ofstream outClientFile;
    outClientFile.open("write.txt", std::ofstream::out);
    outClientFile << "This is the first line. \n";
    outClientFile << "There is another line. \n";
    outClientFile.close();
    std::cout << "---------------------------------------" << std::endl;
    // char buffer[256];
    // char *bufferPtr = &buffer;
    double buffer;
    // std::vector<std::string> inFile;
    std::vector<double> inFile;
    std::ifstream inClientFile;
    inClientFile.open("norm.csv", std::ifstream::in);
    if(!inClientFile){
        std::cerr << "Fail to open the file." << std::endl;
        exit(1);
    }
    /*
    while(!inClientFile.eof()){
        inClientFile.getline(buffer, 100);
        inFile.push_back(buffer);
        std::cout << buffer << std::endl;
    }
    */
    while(inClientFile >> buffer){
        inFile.push_back(buffer);
        std::cout << buffer << std::endl;
    }
    inClientFile.close();
    std::cout << inFile[0] << std::endl << inFile.size() << std::endl;
    // std::cout << "mean: " << mean(&inFile) << std::endl;
    // std::cout << "sd: " << sqrt(variance(&inFile)) << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    Option call(110, 100, 0.05, 0.2, 1);
    std::cout << "Price is: " << call.Value() << std::endl;
    call.UpdateVol(0.3);
    std::cout << "New price is: " << call.Value() << std::endl;

    std::cout << "Vol of a $30: " << call.ImpliedVol(30) << std::endl;

    std::cout << "Delta is: " << call.Delta() << std::endl;
    std::cout << "Gamma is: " << call.Gamma() << std::endl;
    std::cout << "Theta is: " << call.Theta() << std::endl;
    std::cout << "Vega is: " << call.Vega() << std::endl;
    std::cout << "Rho is: " << call.Rho() << std::endl;
    return 0;
}

