#pragma once
#include <cmath>
#include <vector>
#include "OptionPricingEngine.hpp"
#include "stat/distribution.h"
#include "stat/random.hpp"
#include "stat/matrix.h"



class LongstaffSchwartzPricingEngine: public OptionPricingEngine {
    public:
        double Value(unsigned Steps, unsigned NumPath);
    private:
        Option& option_;
};