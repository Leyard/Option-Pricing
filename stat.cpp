#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include "stat.h"
#define PI 3.14159265358979323846



double StatUtility::normal_pdf(double x, double mu, double sigma){
    return 1/(sqrt(2*PI*sigma*sigma))*exp((-(x-mu)*(x-mu))/(2*sigma*sigma));
}


double StatUtility::normal_cdf(double x, double mu, double sigma){
    x = (x-mu)/sigma;

    // Constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);

    double t = 1.0 / (1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}


double StatUtility::inv_cdf(double quantile, double mu, double sigma){
    // Using the Beasley-Springer-Moro algorithm in Glasserman[2004]
    double a[4] = {2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637};
    double b[4] = {-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833};
    double c[9] = {0.3374754822726147, 0.9761690190917186, 0.1607979714918209,
                    0.0276438810333863, 0.0038405729373609, 0.0003951896511919, 
                    0.0000321767881768, 0.0000002888167364, 0.0000003960315187};

    quantile = (quantile - mu)/sigma;

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
        return -1.0*inv_cdf(1-quantile);
    }
}


double StatUtility::uniform_rand(double a, double b){
    // srand(time(0));
    return double(rand())/RAND_MAX * (b-a) + a;
}


double StatUtility::normal_rand(double mu, double sigma){
    return inv_cdf(uniform_rand());
}


double StatUtility::mean(std::vector<double>& dataset){
    std::vector<double>::iterator iter;
    double sum = 0;
    for(iter=dataset.begin(); iter!=dataset.end(); iter++){
        sum += *iter;
    }
    return sum/dataset.size();
}


double StatUtility::variance(std::vector<double>& dataset){
    std::vector<double>::iterator iter;
    double mu = mean(dataset);
    double sum = 0.0;
    for(iter=dataset.begin(); iter!=dataset.end(); iter++){
        sum += ((*iter)-mu) * ((*iter)-mu);
    }
    return sum/dataset.size();
}


double StatUtility::covariance(std::vector<double>& dataset1, std::vector<double>& dataset2){
    double mu_x = mean(dataset1);
    double mu_y = mean(dataset2);
    double co_sum = 0.0;
    int n = dataset1.size();
    for (int i=0; i<n; i++){
        co_sum += (dataset1[i]-mu_x)*(dataset2[i]-mu_y);
    }
    return co_sum/n;
}


double StatUtility::correlation(std::vector<double>& dataset1, std::vector<double>& dataset2){
    return covariance(dataset1, dataset2)/sqrt(variance(dataset1)*variance(dataset2));
}




double StatUtility::box_muller(double mu, double sigma){
    double u1 = uniform_rand();
    double u2 = uniform_rand();

    double x1 = sqrt(-2*log(u1)) * cos(2*PI*u2);
    // double x2 = sqrt(-2*log(u1)) * sin(2*PI*u2);

    return x1*sigma + mu;
}



StatUtility::LM::LM(const std::vector<double>& y, const std::vector<double>& x){
    if (!(x.size() == y.size())){
        throw("Input vectors should of the same length!\n");
    }
    y_ = y;
    x_ = x;
    n = y.size();
}


double StatUtility::LM::Slope(){
    double slope = StatUtility::covariance(x_, y_)/StatUtility::variance(x_);
    return slope;
}


double StatUtility::LM::Intercept(){
    double intercept = StatUtility::mean(y_) - Slope()*StatUtility::mean(x_);
    return intercept;
}


std::vector<double> StatUtility::LM::Fitted(){
    std::vector<double> fitted;
    for (int i=0; i<n; i++){
        double fitted_y = Intercept() + Slope()*x_[i];
        fitted.push_back(fitted_y);
    }
    return fitted;
}


std::vector<double> StatUtility::LM::Residuals(){
    std::vector<double> residuals;
    for (int i=0; i<n; i++){
        residuals.push_back(y_[i] - Fitted()[i]);
    }
    return residuals;
}

<<<<<<< HEAD

StatUtility::GLM::GLM(const std::vector<double>& y, const std::vector<double>& x, bool include_mean){
    y_ = y;
    x_ = x;
    n = y.size();
    p = x.size();
}


std::vector<double> StatUtility::MCMC(int n){
    double init = 0;
    std::vector<double> samples;
    for (int i=0; i<n; i++) {
        double next = normal_rand(init);
        double acceptance = normal_pdf(next) / normal_pdf(init);
        if(uniform_rand() > acceptance){
            samples.push_back(next);
            init = next;
        } 
        else
            samples.push_back(init);
    }
    return samples;
}

=======
>>>>>>> 0746138df6fe69b5832ec97b20dc6dadac256a7f
