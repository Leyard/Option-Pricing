#include "BlackScholesPricingEngine.hpp"
#include "stat/distribution.h"
#include <cmath>


double BlackScholesPricingEngine::Value() {
    double d1 = (log(option_.UnderlyingPrice()/option_.StrikePrice()) + (option_.RiskfreeRate() + pow(option_.Volatility(), 2))*option_.Maturity()) / (option_.Volatility()*sqrt(option_.Maturity()));
    double d2 = d1 - option_.Volatility()*sqrt(option_.Maturity());
    double value;
    double df = exp(-option_.RiskfreeRate()*option_.Maturity());
    Normal normal_dist;
    if (option_.Type() == 'C')
        value = option_.UnderlyingPrice()*normal_dist.CumulativeDensityFunction(d1) - option_.StrikePrice()*df*normal_dist.CumulativeDensityFunction(d2);
    else
        value = option_.StrikePrice()*df*normal_dist.CumulativeDensityFunction(-d2) - option_.UnderlyingPrice()*normal_dist.CumulativeDensityFunction(-d1);
    return value;
}

double BlackScholesPricingEngine::ImpliedVolatility(double MarketPrice) {
    const int MAX_INTERATIONS = 1000;
    const double ACCURACY = 1.0e-5;
    const double HIGH_VALUE = 1.0e10;
    const double ERROR = -1.0e40;

    double sigma_low = 0.00001;
    double sigma_high = 0.3;
    // Check for arbitrage violation
    option_.UpdateVol(sigma_low);
    if (MarketPrice < Value()) return 0.0;

    option_.UpdateVol(sigma_high);
    double price = Value();
    while (price < MarketPrice){
        sigma_high = 2*sigma_high;
        option_.UpdateVol(sigma_high);
        price = Value();
        if (sigma_high > HIGH_VALUE) return ERROR;
    }

    for (int i=0; i < MAX_INTERATIONS; i++){
        double new_sigma = (sigma_low+sigma_high)*0.5;
        option_.UpdateVol(new_sigma);
        if (fabs(Value()-MarketPrice) < ACCURACY) return new_sigma;
        if (Value()-MarketPrice < 0) sigma_low=new_sigma; 
        else sigma_high=new_sigma;
    }
    return ERROR;
}

double BlackScholesPricingEngine::Delta() {
    double d1 = (log(option_.UnderlyingPrice()/option_.StrikePrice()) + (option_.RiskfreeRate() + pow(option_.Volatility(), 2))*option_.Maturity()) / (option_.Volatility()*sqrt(option_.Maturity()));
    double delta; 
    Normal normal_dist;
    if (option_.Type() == 'C')
        delta = normal_dist.CumulativeDensityFunction(d1);
    else
        delta = normal_dist.CumulativeDensityFunction(d1) - 1;
    return delta;
}


double BlackScholesPricingEngine::Gamma() {
    double d1 = (log(option_.UnderlyingPrice()/option_.StrikePrice()) + (option_.RiskfreeRate() + pow(option_.Volatility(), 2))*option_.Maturity()) / (option_.Volatility()*sqrt(option_.Maturity()));
    Normal normal_dist;
    double gamma = normal_dist.ProbabilityDensityFunction(d1) / (option_.UnderlyingPrice()*option_.Volatility()*sqrt(option_.Maturity()));
    return gamma;
}

double BlackScholesPricingEngine::Theta() {
    double d1 = (log(option_.UnderlyingPrice()/option_.StrikePrice()) + (option_.RiskfreeRate() + pow(option_.Volatility(), 2))*option_.Maturity()) / (option_.Volatility()*sqrt(option_.Maturity()));
    double d2 = d1 - option_.Volatility()*sqrt(option_.Maturity());
    double theta;
    double df = exp(-option_.RiskfreeRate()*option_.Maturity());
    Normal normal_dist;
    if (option_.Type() == 'C')
        theta = option_.UnderlyingPrice()*normal_dist.ProbabilityDensityFunction(d1)*0.5*option_.Volatility()/sqrt(option_.Maturity()) - option_.RiskfreeRate()*option_.StrikePrice()*df*normal_dist.CumulativeDensityFunction(d2);
    else
        theta = option_.UnderlyingPrice()*normal_dist.ProbabilityDensityFunction(d1)*0.5*option_.Volatility()/sqrt(option_.Maturity()) + option_.RiskfreeRate()*option_.StrikePrice()*df*normal_dist.CumulativeDensityFunction(-d2);
    return theta;
}

double BlackScholesPricingEngine::Vega() {
    double d1 = (log(option_.UnderlyingPrice()/option_.StrikePrice()) + (option_.RiskfreeRate() + pow(option_.Volatility(), 2))*option_.Maturity()) / (option_.Volatility()*sqrt(option_.Maturity()));
    Normal normal_dist;
    double vega = option_.UnderlyingPrice()*sqrt(option_.Maturity())*normal_dist.ProbabilityDensityFunction(d1);
    return vega;
}

double BlackScholesPricingEngine::Rho() {
    double d1 = (log(option_.UnderlyingPrice()/option_.StrikePrice()) + (option_.RiskfreeRate() + pow(option_.Volatility(), 2))*option_.Maturity()) / (option_.Volatility()*sqrt(option_.Maturity()));
    double d2 = d1 - option_.Volatility()*sqrt(option_.Maturity());
    double rho;
    Normal normal_dist;
    if (option_.Type() == 'C')
        rho = option_.StrikePrice()*option_.Maturity()*exp(-option_.RiskfreeRate()*option_.Maturity())*normal_dist.CumulativeDensityFunction(d2);
    else 
        rho = -option_.StrikePrice()*option_.Maturity()*exp(-option_.RiskfreeRate()*option_.Maturity())*normal_dist.CumulativeDensityFunction(-d2);
    return rho;
}

