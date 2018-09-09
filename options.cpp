#include <iostream>
#include <cmath>
#include "stat.h"
#include "options.h"


// default constructor
Option::Option() 
    : S_(110.0), K_(100.0), r_(0.06), vol_(0.2), t_(1.0), exercise_('E'), type_('C') 
    {}


// overloaded constructor
Option::Option(double S, double K, double r, double vol, double t, char exercise, char type)
    : S_(S), K_(K), r_(r), vol_(vol), t_(t), exercise_(exercise), type_(type)
    {}


void Option::UpdateExercise(char new_exercise){
    exercise_ = new_exercise;
}

void Option::UpdateType(char new_type){
    type_ = new_type;
}

void Option::UpdateUnderlying(double new_underlying){
    S_ = new_underlying;
}

void Option::UpdateStrike(double new_strike){
    K_ = new_strike;
}

void Option::UpdateRate(double new_rate){
    r_ = new_rate;
}

void Option::UpdateVol(double new_vol){
    vol_ = new_vol;
}

void Option::UpdateTime(double new_time){
    t_ = new_time;
}


double Option::BlackScholesPrice(){
    double d1 = (log(S_/K_) + (r_+vol_*vol_)*t_) / (vol_*sqrt(t_));
    double d2 = d1 - vol_*sqrt(t_);
    double value;
    if (type_ == 'C')
        value = S_*StatUtility::normal_cdf(d1) - K_*exp(-r_*t_)*StatUtility::normal_cdf(d2);
    else
        value = K_*exp(-r_*t_)*StatUtility::normal_cdf(-d2) - S_*StatUtility::normal_cdf(-d1);
    return value;
}


double Option::ImpliedVol(double market){
    const int MAX_INTERATIONS = 1000;
    const double ACCURACY = 1.0e-5;
    const double HIGH_VALUE = 1.0e10;
    const double ERROR = -1.0e40;

    double sigma_low = 0.00001;
    double sigma_high = 0.3;
    // Check for arbitrage violation
    UpdateVol(sigma_low);
    if (market < BlackScholesPrice()) return 0.0;

    UpdateVol(sigma_high);
    double price = BlackScholesPrice();
    while (price < market){
        sigma_high = 2*sigma_high;
        UpdateVol(sigma_high);
        price = BlackScholesPrice();
        if (sigma_high > HIGH_VALUE) return ERROR;
    }

    for (int i=0; i < MAX_INTERATIONS; i++){
        double new_sigma = (sigma_low+sigma_high)*0.5;
        UpdateVol(new_sigma);
        if (fabs(BlackScholesPrice()-market) < ACCURACY) return new_sigma;
        if (BlackScholesPrice()-market < 0) sigma_low=new_sigma; 
        else sigma_high=new_sigma;
    }

    return ERROR;
}


double Option::Delta(){
    double d1 = (log(S_/K_) + (r_+vol_*vol_)*t_) / (vol_*sqrt(t_));
    double delta; 
    if (type_ == 'C')
        delta = StatUtility::normal_cdf(d1);
    else
        delta = StatUtility::normal_cdf(d1) - 1;
    return delta;
}


double Option::Gamma(){
    double d1 = (log(S_/K_) + (r_+vol_*vol_)*t_) / (vol_*sqrt(t_));
    double gamma = StatUtility::normal_pdf(d1) / (S_*vol_*sqrt(t_));
    return gamma;
}


double Option::Theta(){
    double d1 = (log(S_/K_) + (r_+vol_*vol_)*t_) / (vol_*sqrt(t_));
    double d2 = d1 - vol_*sqrt(t_);
    double theta;
    if (type_ == 'C')
        theta = S_*StatUtility::normal_pdf(d1)*0.5*vol_/sqrt(t_) - r_*K_*exp(-r_*t_)*StatUtility::normal_cdf(d2);
    else
        theta = S_*StatUtility::normal_pdf(d1)*0.5*vol_/sqrt(t_) + r_*K_*exp(-r_*t_)*StatUtility::normal_cdf(-d2);
    return theta;
}


double Option::Vega(){
    double d1 = (log(S_/K_) + (r_+vol_*vol_)*t_) / (vol_*sqrt(t_));
    double vega = S_*sqrt(t_)*StatUtility::normal_pdf(d1);
    return vega;
}


double Option::Rho(){
    double d1 = (log(S_/K_) + (r_+vol_*vol_)*t_) / (vol_*sqrt(t_));
    double d2 = d1 - vol_*sqrt(t_);
    double rho;
    if (type_ == 'C')
        rho = K_*t_*exp(-r_*t_)*StatUtility::normal_cdf(d2);
    else 
        rho = -K_*t_*exp(-r_*t_)*StatUtility::normal_cdf(-d2);
    return rho;
}

