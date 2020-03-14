#include "options.hpp"


class AsianOption
{
public:
    AsianOption();
    AsianOption(const AsianOption& opt);
    ~AsianOption();
};

class BarrierOption
{
public:
    BarrierOption();
    BarrierOption(const BarrierOption& opt);
    ~BarrierOption();

    double barrier();
};
