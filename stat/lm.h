#pragma once
#include <vector>

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
