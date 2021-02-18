#ifndef LINEARSYSTEMCALCULATOR_H
#define LINEARSYSTEMCALCULATOR_H

#include "linearsystem.h"
#include "linearsystemsolution.h"

class LinearSystemCalculator
{
public:
    LinearSystemCalculator();
    ~LinearSystemCalculator();

    LinearSystemSolution calculate();
};

#endif // LINEARSYSTEMCALCULATOR_H
