#pragma once

// using namespace std;


class Option{
public:
    enum Exercise {European = 'E', American = 'A'};
    enum Type {Call = 'C', Put = 'P'};

    Option();
    Option(double S, double K, double r, double vol, double t, char exercise, char type);
    void UpdateExercise(char new_exercise);
    void UpdateType(char new_type);
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
    char exercise_;
    char type_;
};

