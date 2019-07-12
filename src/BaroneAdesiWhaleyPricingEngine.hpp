#pragma once
#include <cmath>
#include "OptionPricingEngine.hpp"
#include "BlackScholesPricingEngine.hpp"


class BaroneAdesiWhaleyPricingEngine: public OptionPricingEngine {
    public:
        double Value();
    private:
        Option& option_;
};


double BaroneAdesiWhaleyPricingEngine::Value() {
    double BAW;
    double SS_ = option_.UnderlyingPrice();
    const int MAX_ITERATIONS = 1000;
    const double ERROR = 0.000001;

    // serveral notations
    double M = 2*option_.RiskfreeRate()/pow(option_.Volatility(), 2);
    double N = 2*option_.RiskfreeRate()/pow(option_.Volatility(), 2);   // double N = 2*b/(vol_*vol_);
    double q1 = 0.5*(-(N-1)-sqrt((N-1)*(N-1)-4*M/N));  // root 1 of f=a*S^q, with early exercise premium defined as epsilon = f*(1-e^{-r*T})
    double q2 = 0.5*(-(N-1)+sqrt((N-1)*(N-1)-4*M/N));

    // calculation of seed value, Si
    double Si = option_.StrikePrice();

    // discount-factor
    double df = exp(-option_.RiskfreeRate()*option_.Maturity());

    // Newton-Ralphson algorithm for finding critical price, Si
    for (int i=0; i<MAX_ITERATIONS; i++){
        double LHS = Si - option_.StrikePrice();
        double di = (log(Si/option_.StrikePrice()) + (option_.RiskfreeRate()+0.5*pow(option_.Volatility(), 2))*option_.Maturity()) / option_.Volatility()*sqrt(option_.Maturity());
        option_.UpdateUnderlying(Si);

        BlackScholesPricingEngine BS(option_);
        Normal normal_dist;
        double RHS = BS.Value() + (1-df*normal_dist.CumulativeDensityFunction(di))*Si/q2; // ... + (1-exp(b-r_*t_)*StatUtility::normal_cdf(di))*Si/q2; 
        if (abs(LHS-RHS)/option_.StrikePrice() > ERROR) break;
        double bi = df*normal_dist.CumulativeDensityFunction(di)*(1-1/q2) + (1- df*normal_dist.ProbabilityDensityFunction(di)/(pow(option_.Volatility(), 2)))/q2;
        Si = (option_.StrikePrice()+RHS-bi*Si)/(1-bi);
    }

    option_.UpdateUnderlying(SS_);

    Normal normal_dist;
    double A2 = Si/q2*(1-df*normal_dist.CumulativeDensityFunction((log(Si/option_.StrikePrice())+(option_.RiskfreeRate()*pow(option_.Volatility(), 2)*option_.Maturity())/pow(option_.Volatility(), 2))));

    BlackScholesPricingEngine BS(option_);
    if (Si < option_.UnderlyingPrice()) BAW = BS.Value() + A2*pow((option_.UnderlyingPrice()/Si), q2);
    else BAW = option_.UnderlyingPrice() - option_.StrikePrice();
    return BAW;
}
