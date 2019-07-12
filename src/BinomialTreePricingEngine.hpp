#pragma once
#include <cmath>
#include <vector>
#include "OptionPricingEngine.hpp"
#include "stat/math.h"
#include "options.h"


class BinomialTreePricingEngine: public OptionPricingEngine {
    public:
        BinomialTreePricingEngine(Option& option): option_(option) {};
        double Value(unsigned Steps);
    private:
        Option& option_;
};


double BinomialTreePricingEngine::Value(unsigned Steps) {
    double h = option_.Maturity() / Steps; // step-size
    double u = exp(option_.Volatility()*sqrt(h));
    double d = 1/u;
    double pu = (exp(option_.RiskfreeRate()*h) - d) / (u - d);
    double pd = 1 - pu;
    double df = exp(-option_.RiskfreeRate()*h);

    std::vector< std::vector< std::pair<double, double> > > Tree;
    Tree.resize(Steps+1);
    for (unsigned i=0; i <= Steps; i++) {
        Tree[i].resize(i+1);
        for (unsigned j=0; j <= i; j++) {
            double Price = option_.UnderlyingPrice()*pow(u, -i+2*j);
            Tree[i][j].first = Price;
            double OptionValue = option_.ExerciseValue(option_.UnderlyingPrice());
            Tree[i][j].second = OptionValue;
        }
    }

    for (unsigned i=Steps-1; i>=0; i--) {
        for (unsigned j=0; j<=i; j++) {
            double DiscountedFutureValue = df*(pu*Tree[i+1][j].second + pd*Tree[i+1][j+1].second);
            if (option_.Exercise() == 'A') Tree[i][j].second = max(Tree[i][j].second-DiscountedFutureValue, 0.0);
            else Tree[i][j].second = DiscountedFutureValue;
        }
    }
    return Tree[0][0].second;
}

