#pragma once
#include "distribution.h"
#include <cstdlib>
#include <ctime>

class random {
    public:
        static double uniform(double a=0, double b=1);
        static double normal(double mean=0, double variance=1);
};

