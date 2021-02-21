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
                         const QList<SolutionStep>& steps
    );

    LinearSystemSolution(const LinearSystemSolution& other);
    ~LinearSystemSolution();

    Status solved() const;
    int maxNumberOfIteration() const;
    double targetAccuracy() const;
    const DoubleMatrix& initMatrix() const;
    const DoubleVector& initVector() const;
    double c() const;
    const DoubleMatrix& matrixC() const;
    const DoubleVector& vectorD() const;
    const QList<SolutionStep>& steps() const;

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
};

#endif // LINEARSYSTEMSOLUTION_H
