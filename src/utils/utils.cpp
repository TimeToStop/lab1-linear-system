#include "utils.h"
#include <limits>
#include <math.h>

bool nearlyEqual(double a, double b)
{
    double m = std::max<double>(std::abs(a), std::abs(b));
    m = std::max<double>(1.0, m);
    return std::fabs(a - b) <= std::numeric_limits<double>::epsilon() *  m;
}
