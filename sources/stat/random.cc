#include "random.hpp"
#include "distribution.h"

double random::uniform(double a=0, double b=1) {
    return double(rand())/RAND_MAX * (b-a) + a;
}

double random::normal(double mean=0, double variance=1) {
    Normal normal_dist(mean, variance);
    return normal_dist.InverseCumulativeDensityFunction(uniform_rand());
}

