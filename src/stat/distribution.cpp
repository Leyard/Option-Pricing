#include "distribution.h"
#include <cmath>
#include <stdexcept>

#define PI 3.14159265358979

double Normal::ProbabilityDensityFunction(double x) {
    return 1/(sqrt(2*PI)*sigma_)*exp(-(x-mean_)*(x-mean_)/(2*sigma_*sigma_));
}

double Normal::CumulativeDensityFunction(double x) {
    x = (x-mean_)/sigma_;

    // Constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    int sign = x < 0 ? -1:1;
    x = fabs(x)/sqrt(2.0);

    double t = 1.0 / (1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}


double Normal::InverseCumulativeDensityFunction(double quantile) {
    // if (quantile < 0 || quantile > 1) 
    //     throw std::invalid_argument("Invalid quantile arguement");
    
    // Using the Beasley-Springer-Moro algorithm in Glasserman[2004]
    double a[4] = {2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637};
    double b[4] = {-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833};
    double c[9] = {0.3374754822726147, 0.9761690190917186, 0.1607979714918209,
                    0.0276438810333863, 0.0038405729373609, 0.0003951896511919, 
                    0.0000321767881768, 0.0000002888167364, 0.0000003960315187};

    quantile = (quantile - mean_)/sigma_;

    if(quantile >= 0.5 && quantile <= 0.92){
        double num = 0.0;
        double denom = 1.0;
        for (int i=0; i<4; i++){
            num += a[i] * pow((quantile - 0.5), 2*i + 1);
            denom += b[i] * pow((quantile - 0.5), 2*i);
        }
        return num/denom;
    }
    else if(quantile > 0.92 && quantile < 1){
        double num = 0.0;
        for (int i=0; i<9; i++){
            num += c[i] * pow((log(-log(1-quantile))), i);
        }
        return num;
    }
    else{
        return -1.0*InverseCumulativeDensityFunction(1-quantile);
    }
}

double Poisson::pdf(unsigned x) {
    unsigned fac = 1;
    unsigned y = x;
    if (y > 0) {while(y > 0) {fac *= y; y--;}}
    return exp(-lambda_)*pow(lambda_, x)/fac;
}

