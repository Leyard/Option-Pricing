#pragma once
#include <vector>
// #include <cmath>


class StatUtility{
public:
    static double normal_pdf(double x, double mu = 0, double sigma = 1);
    static double normal_cdf(double x, double mu = 0, double sigma = 1);
    static double inv_cdf(double quantile, double mu = 0, double sigma = 1);
    static double uniform_rand(double a = 0, double b = 1);
    static double normal_rand(double mu = 0, double sigma = 1);
    static double mean(std::vector<double>* dataset);
    static double variance(std::vector<double>* dataset);
    static double box_muller(double mu = 0, double sigma = 1);
};

