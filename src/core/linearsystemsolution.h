#ifndef LINEARSYSTEMSOLUTION_H
#define LINEARSYSTEMSOLUTION_H

#include "linearsystemservice.h"
#include "solutionstep.h"

enum class Status
{
    SOLVED,
    NO_DOMINANCE,
    DIVERGES
};

class LinearSystemSolution
{
public:
    LinearSystemSolution(Status solved,
                         int max_number_of_iteartion,
                         double accuracy,
                         const DoubleMatrix& init_matrix,
                         const DoubleVector& init_vector,
                         double c,
                         const DoubleMatrix& matrix_c,
                         const DoubleVector& vector_d,
                         const QList<SolutionStep>& steps,
                         const DoubleVector& answer
    );

    LinearSystemSolution(const LinearSystemSolution& other);
    ~LinearSystemSolution();

    QString statusAsString() const;
    QString toHTML() const;

private:
    Status _solved;
    int _max_number_of_iteartion;
    double _target_accuracy;
    DoubleMatrix _init_matrix;
    DoubleVector _init_vector;
    double _c;
    DoubleMatrix _matrix_c;
    DoubleVector _vector_d;
    QList<SolutionStep> _steps;
    DoubleVector _answer;
};

#endif // LINEARSYSTEMSOLUTION_H
