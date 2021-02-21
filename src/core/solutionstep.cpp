#include "solutionstep.h"

SolutionStep::SolutionStep(
        int step_number,
        double epsilon,
        const DoubleVector& x,
        const DoubleVector& prev,
        const DoubleVector& epsilons
):
    _step_number(step_number),
    _epsilon(epsilon),
    _x(x),
    _prev(prev),
    _epsilons(epsilons)
{
}

SolutionStep::SolutionStep(const SolutionStep& other):
    _step_number(other._step_number),
    _epsilon(other._epsilon),
    _x(other._x),
    _prev(other._prev),
    _epsilons(other._epsilons)
{
}

SolutionStep::~SolutionStep()
{
}

int SolutionStep::stepNumber() const
{
    return _step_number;
}

double SolutionStep::epsilon() const
{
    return _epsilon;
}

const DoubleVector& SolutionStep::x() const
{
    return _x;
}

const DoubleVector& SolutionStep::prev() const
{
    return _prev;
}

const DoubleVector& SolutionStep::epsilons() const
{
    return _epsilons;
}
