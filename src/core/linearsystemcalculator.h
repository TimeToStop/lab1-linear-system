#ifndef LINEARSYSTEMCALCULATOR_H
#define LINEARSYSTEMCALCULATOR_H

#include "linearsystemservice.h"
#include "linearsystemsolution.h"

class LinearSystemCalculator
{
public:
    LinearSystemCalculator() = delete;
    ~LinearSystemCalculator() = delete;

    static LinearSystemSolution calculate(int n, double accuracy, int max_number_of_iteration, const DoubleMatrix& matrix, const DoubleVector& right);

private:
    static double dominance(const DoubleMatrix& matrix);
};

#endif // LINEARSYSTEMCALCULATOR_H
