#pragma once
#include "OptionPricingEngine.hpp"
#include <vector>
#include "stat/math.h"


class TrinomialTreePricingModel: public OptionPricingEngine {
    public:
        double Value(unsigned Steps);
    private:
        Option& option_;
};


double TrinomialTreePricingModel::Value(unsigned Steps) {
    double h = option_.Maturity() / Steps; // step-size
    double u = exp(option_.Volatility()*sqrt(h));
    double d = 1/u;
    double pu = pow((exp(option_.RiskfreeRate()*h) - d) / (u - d), 2);
    double pd = pow((u - exp(option_.RiskfreeRate()*h)) / (u - d), 2);
    double pm = 1 - pu - pd;
    double df = exp(-option_.RiskfreeRate()*h);

    std::vector< std::vector< std::pair<double, double> > > Tree;
    Tree.resize(Steps+1);
    for (unsigned i=0; i <= Steps; i++) {
        Tree[i].resize(2*i+1);
        for (unsigned j=0; j < 2*i+1; j++) {
            double Price = option_.UnderlyingPrice()*pow(u, -i+j);
            Tree[i][j].first = Price;
            double OptionValue = option_.ExerciseValue(option_.UnderlyingPrice());
            Tree[i][j].second = OptionValue;
        }
    }

    for (unsigned i=Steps-1; i>=0; i--) {
        for (unsigned j=0; j < 2*i+1; j++) {
            double DiscountedFutureValue = df*(pu*Tree[i+1][j].second + pm*Tree[i+1][j+1].second + pd*Tree[i+1][j+2].second);
            if (option_.Exercise() == 'A') Tree[i][j].second = max(Tree[i][j].second-DiscountedFutureValue, 0.0);
            else Tree[i][j].second = DiscountedFutureValue;
        }
    }
    return Tree[0][0].second;
}
