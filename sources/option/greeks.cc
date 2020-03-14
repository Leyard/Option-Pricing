#include "../include/greeks.hpp"


double Greeks::delta()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->delta();
}

double Greeks::gamma()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->gamma();
}

double Greeks::theta()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->theta();
}

double Greeks::vega()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->vega();
}

double Greeks::rho()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->rho();
}

double Greeks::vanna()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->vanna();
}

double Greeks::volga()
{
    OptionPricingEngine* eng = _pto->get_engine();
    return eng->volga();
}
