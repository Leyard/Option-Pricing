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
    static double mean(std::vector<double>& dataset);
    static double variance(std::vector<double>& dataset);
    static double covariance(std::vector<double>& dataset1, std::vector<double>& dataset2);
    static double correlation(std::vector<double>& dataset1, std::vector<double>& dataset2);
    static double box_muller(double mu = 0, double sigma = 1);
<<<<<<< HEAD

=======
>>>>>>> 0746138df6fe69b5832ec97b20dc6dadac256a7f
    class LM{
    public:
        LM();
        LM(const std::vector<double>& y, const std::vector<double>& x);
        double Slope();
        double Intercept();
        std::vector<double> Fitted();
        std::vector<double> Residuals();
    private:
        std::vector<double> y_;
        std::vector<double> x_;
        int n;
    };

<<<<<<< HEAD
    class GLM{
    public:
        GLM();
        GLM(const std::vector<double>& y, const std::vector<double>& x, bool include_mean = true);
    private:
        std::vector<double> y_;
        std::vector<double> x_;
        int n;
        int p;
    };


    class Matrix{
    public:
        std::vector<double> sum(std::vector<double>& mat1, std::vector<double>& mat2);
        std::vector<double> multiply(std::vector<double>& mat1, std::vector<double>& mat2);
        std::vector<double> transpose(std::vector<double>& mat);
        std::vector<double> inverse(std::vector<double>& mat);
    };

    static std::vector<double> MCMC(int n);

=======
>>>>>>> 0746138df6fe69b5832ec97b20dc6dadac256a7f
};

