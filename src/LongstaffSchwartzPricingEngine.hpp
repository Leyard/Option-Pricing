#pragma once
#include <cmath>
#include <vector>
#include "OptionPricingEngine.hpp"
#include "stat/distribution.h"
#include "stat/random.hpp"



class LongstaffSchwartzPricingEngine: public OptionPricingEngine {
    public:
        double Value(unsigned Steps, unsigned NumPath);
    private:
        Option& option_;
};


double LongstaffSchwartzPricingEngine::Value(unsigned Steps, unsigned NumPath) {
    double dt = option_.Maturity() / Steps;
    double init_price = option_.UnderlyingPrice();
    double df = exp(-option_.RiskfreeRate()*dt);

    std::vector< std::vector<double> > paths;
    paths.resize(NumPath);
    for (unsigned i=0; i < NumPath; i++) {
        paths[i].push_back(option_.UnderlyingPrice());
        for (unsigned j=1; j < Steps; j++) {
            double deviate = random::normal((option_.RiskfreeRate()-0.5*pow(option_.Volatility(), 2))*dt, pow(option_.Volatility(), 2)*dt);
            paths[i].push_back(paths[i][j-1]*exp(deviate));
            paths[i][j] = option_.ExerciseValue(paths[i][j]);
        }
    }
    

    double OptionValue;
    return OptionValue;
}
