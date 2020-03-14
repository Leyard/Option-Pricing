#include "../include/VannaVolgaPricingEngine.hpp"

#include "../include/BlackScholesPricingEngine.hpp"
#include <vector>


double VannaVolgaPricingEngine::value(const GenericOptions* pto = nullptr)
{
    if (pto == nullptr && _pto == nullptr)
        return 0.0;
    BlackScholesPricingEngine bs_engine(_pto);
    double bs_price = bs_engine.Value();
    double bs_vega = bs_engine.Vega();
    return 1.0;
}