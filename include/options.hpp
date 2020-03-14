#pragma once

#include "OptionPricingEngine.hpp"
#include "greeks.hpp"


class GenericOptions
{
public:
    enum Exercise {European = 'E', American = 'A'};
    enum Type {Call = 'C', Put = 'P'};

    GenericOptions();
    GenericOptions(double S, double K, double r, double vol, double t, Exercise exercise, Type type) : s0(S), k(K), rf(r), tau(t), vol(vol), exercise(exercise), type(type) {}
    double& s0;
    double& k;
    double& rf;
    double& tau;
    double& vol;
    Exercise& exercise;
    Type& type;

    double exercise_price();
    virtual double exercise_value();
    double current_time();
    void set_engine(OptionPricingEngine* pricing_eng);
    OptionPricingEngine* get_engine();
    Greeks greeks();

private:
    OptionPricingEngine* _pricing_eng = nullptr;
};

// class Option{
// public:
//     enum Exercise {European = 'E', American = 'A'};
//     enum Type {Call = 'C', Put = 'P'};

//     Option();
//     Option(double S, double K, double r, double vol, double t, Exercise exercise, Type type);
//     double UnderlyingPrice();
//     double StrikePrice();
//     double RiskfreeRate();
//     double Volatility();
//     double Maturity();
//     double Exercise();
//     double Type();

//     void UpdateExercise(char new_exercise);
//     void UpdateType(char new_type);
//     void UpdateUnderlying(double new_underlying);
//     void UpdateStrike(double new_stike);
//     void UpdateRate(double new_rate);
//     void UpdateVol(double new_vol);
//     void UpdateTime(double new_time);

//     double ExerciseValue(double CurrentPrice);

//     double ImpliedVol(double market);
//     double Delta();
//     double Gamma();
//     double Theta();
//     double Vega();
//     double Rho();
// private:
//     double S_;
//     double K_;
//     double r_;
//     double vol_;
//     double t_;
//     char exercise_;
//     char type_;
// };

