#pragma once
#include "options.hpp"


// An abstract base class of OptionPricingEngine
class OptionPricingEngine {
public:
    OptionPricingEngine();
    // OptionPricingEngine(Option& option) : option_(option) {};
    OptionPricingEngine(GenericOptions* pto);
    double Value();
    virtual double value() = 0;
    double ImpliedVolatility(double MarketPrice);
    double ExerciseValue(double S);
    virtual double implied_vol(double mkt_price) = 0;

    virtual double delta() = 0;
    virtual double gamma() = 0;
    virtual double vega() = 0;
    virtual double theta() = 0;
    virtual double rho() = 0;

    virtual double lambda() = 0;
    virtual double epsilon() = 0;

    virtual double vanna() = 0;
    virtual double volga() = 0;
    virtual double charm() = 0; // a.k.a delta decay
    virtual double veta() = 0;
    virtual double vera() = 0;

    virtual double speed() = 0;
    virtual double zomma() = 0;
    virtual double color() = 0;
    virtual double ultima() = 0;

private:
    Option& option_;
};

