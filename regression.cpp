#include <vector>
#include "stat.h"
#include "regression.h"

LM::LM(const std::vector<double>& y, const std::vector<double>& x){
    if (!(x.size() == y.size())){
        throw("Input vectors should of the same length!\n");
    }
    y_ = y;
    x_ = x;
    n = y.size();
}


double LM::Slope(){
    double slope = StatUtility::covariance(x_, y_)/StatUtility::variance(x_);
    return slope;
}


double LM::Intercept(){
    double intercept = StatUtility::mean(y_) - Slope()*StatUtility::mean(x_);
    return intercept;
}


std::vector<double> LM::Fitted(){
    std::vector<double> fitted;
    for (int i=0; i<n; i++){
        double fitted_y = Intercept() + Slope()*x_[i];
        fitted.push_back(fitted_y);
    }
    return fitted;
}


std::vector<double> LM::Residuals(){
    std::vector<double> residuals;
    for (int i=0; i<n; i++){
        residuals.push_back(y_[i] - Fitted()[i]);
    }
    return residuals;
}
