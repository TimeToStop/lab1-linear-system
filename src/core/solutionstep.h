#ifndef SOLUTIONSTEP_H
#define SOLUTIONSTEP_H

#include "linearsystemservice.h"

class SolutionStep
{
public:
    SolutionStep(int step_number, double epsilon, const DoubleVector& x, const DoubleVector& prev, const DoubleVector& epsilons);
    SolutionStep(const SolutionStep& other);
    ~SolutionStep();

    int stepNumber() const;
    double epsilon() const;
    const DoubleVector& x() const;
    const DoubleVector& prev() const;
    const DoubleVector& epsilons() const;

private:
    int _step_number;
    double _epsilon;
    DoubleVector _x;
    DoubleVector _prev;
    DoubleVector _epsilons;
};

#endif // SOLUTIONSTEP_H
