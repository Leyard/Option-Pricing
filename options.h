#pragma once

// using namespace std;


class Option{
public:
    enum Exercise {European, American};
    enum Type {Call, Put};

    Option();
    Option(double S, double K, double r, double vol, double t);
    void UpdateUnderlying(double new_underlying);
    void UpdateStrike(double new_stike);
    void UpdateRate(double new_rate);
    void UpdateVol(double new_vol);
    void UpdateTime(double new_time);
    double BlackScholesPrice();
    double BaroneAdesiWhaleyPrice();
    double LongstaffSchwartzPrice();
    double ImpliedVol(double market);
    double Delta();
    double Gamma();
    double Theta();
    double Vega();
    double Rho();
private:
    double S_;
    double K_;
    double r_;
    double vol_;
    double t_;
};

