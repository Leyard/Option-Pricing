#pragma once
#include <vector>

class GLM {
public:
    GLM(const std::vector<std::vector <double>>& dataset) {
        dataset_ = dataset;
    };
    std::vector<double> coefficients();
    std::vector<double> fitted();
    std::vector<double> residuals();
private:
    std::vector<std::vector <double>> dataset_;
}