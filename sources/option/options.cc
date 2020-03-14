#include <iostream>
#include <cmath>
#include "options.hpp"
#include "stat/math.h"


// default constructor
Option::Option() 
    : S_(110.0), K_(100.0), r_(0.06), vol_(0.2), t_(1.0), exercise_('E'), type_('C') 
    {}


// overloaded constructor
Option::Option(double S, double K, double r, double vol, double t, char exercise, char type)
    : S_(S), K_(K), r_(r), vol_(vol), t_(t), exercise_(exercise), type_(type)
    {}

// Option: data attributes
double Option::UnderlyingPrice() {
    return S_;
}

double Option::StrikePrice() {
    return K_;
}

double Option::RiskfreeRate() {
    return r_;
}

double Option::Volatility() {
    return vol_;
}

double Option::Maturity() {
    return t_;
}

double Option::Exercise() {
    return exercise_;
}

double Option::Type() {
    return type_;
}


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

double Option::ExerciseValue(double CurrentPrice) {
    if (type_ == 'C') 
        return max(CurrentPrice - K_, 0.0);
    if (type_ == 'P') 
        return max(K_ - CurrentPrice, 0.0);
}


void GenericOptions::set_engine(const OptionPricingEngine* pricing_eng)
{
    _pricing_eng = const_cast<OptionPricingEngine *>(pricing_eng);
}


