#pragma once
#include <vector>

class Distribution {
    public:
        double pdf(double x);
        double cdf(double x);
        double inv_cdf(double quantile);
        double Moments(unsigned order);
    };


class Normal: public Distribution {
    public: 
        Normal(double mean=0, double sigma=1): mean_(mean), sigma_(sigma) {};
        double pdf(double x);
        double cdf(double x);
        double inv_cdf(double quantile);
        double Moments(unsigned order);
    private:
        double mean_, sigma_;
};


class Uniform: public Distribution {
    public:
        Uniform(double a=0, double b=1): a_(a), b_(b) {};
        double pdf(double x);
        double cdf(double x);
        double inv_cdf(double quantile);
        double Moments(unsigned order);
    private:
        double a_, b_;
};


class Poisson: public Distribution {
    public:
        Poisson(double lambda): lambda_(lambda) {};
        double pdf(unsigned x);
        double cdf(unsigned x);
        double moment(unsigned order);
    private:
        double lambda_;
};


double normal_pdf(double x, double mu = 0, double sigma = 1);
double normal_cdf(double x, double mu = 0, double sigma = 1);
double inv_cdf(double quantile, double mu = 0, double sigma = 1);
double uniform_rand(double a = 0, double b = 1);
double normal_rand(double mu = 0, double sigma = 1);
