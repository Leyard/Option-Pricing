#pragma once
#include "options.hpp"
#include "OptionPricingEngine.hpp"


class BlackScholesPricingEngine: public OptionPricingEngine {
    public:
        BlackScholesPricingEngine(Option& option): option_(option) {};
        double Value();
        double ImpliedVolatility(double MarketPrice);
        double Delta();
        double Gamma();
        double Theta();
        double Vega();
        double Rho();
    private:
        Option& option_;
};


