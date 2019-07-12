#pragma once
#include "options.hpp"


// An abstract base class of OptionPricingEngine
class OptionPricingEngine {
public:
    OptionPricingEngine();
    OptionPricingEngine(Option& option) : option_(option) {};
    double Value();
    double ImpliedVolatility(double MarketPrice);
    double ExerciseValue(double S);
private:
    Option& option_;
};

