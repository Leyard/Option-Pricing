#include "options.hpp"


class Greeks
{
public:
    Greeks();
    Greeks(const GenericOptions* pto) : _pto(const_cast<GenericOptions *>(pto)) {}

    double delta();
    double gamma();
    double theta();
    double vega();
    double rho();

    double vanna();
    double volga();

private:
    GenericOptions* _pto;
};