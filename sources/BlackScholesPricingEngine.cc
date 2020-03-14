#include "BlackScholesPricingEngine.hpp"
#include "stat/distribution.h"
#include <cmath>


double BlackScholesPricingEngine::d1()
{
    double num = log(_pto->s0/_pto->k) + (_pto->rf + 0.5*pow(_pto->vol, 2))*_pto->tau;
    double denom = _pto->vol * sqrt(_pto->tau);
    double res = num / denom;
    return res;
}

double BlackScholesPricingEngine::d2()
{
    double res = d1() - _pto->vol * sqrt(_pto->tau);
    return res;
}

double BlackScholesPricingEngine::value(const GenericOptions* pto = nullptr)
{
    if (pto != nullptr)
        _pto = pto;
    double res;
    double df = exp(-_pto->rf*_pto->tau);
    Normal normal_dist;
    if (_pto->type == 'C')
        res = _pto->s0*normal_dist.cdf(d1()) - _pto->k*df*normal_dist.cdf(d2());
    else
        res = _pto->k*df*normal_dist.cdf(-d2()) - _pto->s0*normal_dist.cdf(-d1());
    return res;
}

double BlackScholesPricingEngine::implied_vol(double mkt_price)
{
    const int MAX_INTERATIONS = 1000;
    const double ACCURACY = 1.0e-5;
    const double HIGH_VALUE = 1.0e10;
    const double ERROR = -1.0e40;

    double sigma_low = 0.00001;
    double sigma_high = 0.3;
    // Check for arbitrage violation
    _pto->vol = sigma_low;
    if (mkt_price < value()) return 0.0;

    _pto->vol = sigma_high;
    double price = value();
    while (price < mkt_price){
        sigma_high = 2*sigma_high;
        _pto->vol = sigma_high;
        price = value();
        if (sigma_high > HIGH_VALUE)
            return ERROR;
    }

    for (int i=0; i < MAX_INTERATIONS; i++){
        double new_sigma = (sigma_low+sigma_high)*0.5;
        _pto->vol = new_sigma;
        if (fabs(value() - mkt_price) < ACCURACY) return new_sigma;
        if (value() - mkt_price < 0) sigma_low=new_sigma; 
        else sigma_high=new_sigma;
    }
    return ERROR;
}

double BlackScholesPricingEngine::delta()
{
    double res; 
    Normal normal_dist;
    if (_pto->type == 'C')
        res = normal_dist.cdf(d1());
    else
        res = normal_dist.cdf(d1()) - 1;
    return res;
}

double BlackScholesPricingEngine::gamma()
{
    Normal normal_dist;
    double res = normal_dist.pdf(d1()) / (_pto->s0*_pto->vol*sqrt(_pto->tau));
    return res;
}

double BlackScholesPricingEngine::theta()
{
    double res;
    double df = exp(-_pto->rf * _pto->tau);
    Normal normal_dist;
    if (_pto->type == 'C')
        res = _pto->s0*normal_dist.pdf(d1())*0.5*_pto->vol/sqrt(_pto->tau) - _pto->rf*_pto->k*df*normal_dist.cdf(d2());
    else
        res = _pto->s0*normal_dist.pdf(d1())*0.5*_pto->vol/sqrt(_pto->tau) + _pto->rf*_pto->k*df*normal_dist.cdf(-d2());
    return res;
}

double BlackScholesPricingEngine::vega()
{
    Normal normal_dist;
    double res = _pto->s0*sqrt(_pto->tau)*normal_dist.pdf(d1());
    return res;
}

double BlackScholesPricingEngine::rho()
{
    double res;
    Normal normal_dist;
    if (_pto->type == 'C')
        res = _pto->s0*_pto->tau*exp(-_pto->rf*_pto->tau)*normal_dist.cdf(d2());
    else 
        res = -_pto->s0*_pto->tau*exp(-_pto->rf*_pto->tau)*normal_dist.cdf(-d2());
    return res;
}

double BlackScholesPricingEngine::lambda()
{
    double res = delta() * _pto->s0 / value();
    return res;
}

double BlackScholesPricingEngine::vanna()
{
    double res = vega() / _pto->s0 * (1 - d1()/(_pto->vol*sqrt(_pto->tau)));
    return res;
}

double BlackScholesPricingEngine::volga()
{
    double res = vega()*d1()*d2()/_pto->vol;
    return res;
}

double BlackScholesPricingEngine::color()
{
    return 0.0;
}

double BlackScholesPricingEngine::speed()
{
    return 0.0;
}

double BlackScholesPricingEngine::ultima()
{
    double dd1 = d1();
    double dd2 = d2();
    double term = dd1*dd2*(1-dd1*dd2) + pow(dd1, 2) + pow(dd2, 2);
    double res = -vega()/pow(_pto->vol, 2)*term;
    return res;
}
