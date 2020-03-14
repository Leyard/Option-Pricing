#pragma once
#include "options.hpp"
#include "OptionPricingEngine.hpp"


class BlackScholesPricingEngine: public OptionPricingEngine
{
public:
    BlackScholesPricingEngine();
    BlackScholesPricingEngine(const GenericOptions* pto) : _pto(pto) {}
    // BlackScholesPricingEngine(Option& option) : option_(option) {}
    double d1();
    double d2();
    double value(const GenericOptions* pto = nullptr);

    double implied_vol(double mkt_price);

    double delta();
    double gamma();
    double theta();
    double vega();
    double rho();

    double lambda();
    
    double vanna();
    double volga();

    double color();
    double speed();
    double ultima();

private:
    // Option& option_;
    const GenericOptions* _pto;
};


