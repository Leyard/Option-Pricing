#pragma once
#include "OptionPricingEngine.hpp"
#include "BlackScholesPricingEngine.hpp"
#include <vector>
#include "stat/math.h"


class VannaVolgaPricingEngine: public OptionPricingEngine
{
public:
    VannaVolgaPricingEngine();
    ~VannaVolgaPricingEngine();
    VannaVolgaPricingEngine(const GenericOptions* pto) : _pto(pto) {}
    double value(const GenericOptions* pto);

private:
    const GenericOptions* _pto = nullptr;
};


