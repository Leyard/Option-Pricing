#pragma once
#include <vector>

class Distribution {
    public:
        float mean();
        float variance();
    };


double normal_pdf(double x, double mu = 0, double sigma = 1);
double normal_cdf(double x, double mu = 0, double sigma = 1);
double inv_cdf(double quantile, double mu = 0, double sigma = 1);
double uniform_rand(double a = 0, double b = 1);
double normal_rand(double mu = 0, double sigma = 1);
