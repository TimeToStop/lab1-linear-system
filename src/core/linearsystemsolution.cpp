#include "linearsystemsolution.h"

LinearSystemSolution::LinearSystemSolution(
        Status solved,
        const DoubleMatrix& init_matrix,
        const DoubleVector& init_vector,
        double c,
        const DoubleMatrix& matrix_c,
        const DoubleVector& vector_d,
        const QList<SolutionStep>& steps
):
    _solved(solved),
    _init_matrix(init_matrix),
    _init_vector(init_vector),
    _c(c),
    _matrix_c(matrix_c),
    _vector_d(vector_d),
    _steps(steps)
{
}

LinearSystemSolution::LinearSystemSolution(const LinearSystemSolution &other):
    _solved(other._solved),
    _init_matrix(other._init_matrix),
    _init_vector(other._init_vector),
    _c(other._c),
    _matrix_c(other._matrix_c),
    _vector_d(other._vector_d),
    _steps(other._steps)
{
}

LinearSystemSolution::~LinearSystemSolution()
{
}

Status LinearSystemSolution::solved() const
{
    return _solved;
}

const DoubleMatrix& LinearSystemSolution::initMatrix() const
{
    return _init_matrix;
}

const DoubleVector& LinearSystemSolution::initVector() const
{
    return _init_vector;
}

double LinearSystemSolution::c() const
{
    return _c;
}

const DoubleMatrix& LinearSystemSolution::matrixC() const
{
    return _matrix_c;
}

const DoubleVector& LinearSystemSolution::vectorD() const
{
    return _vector_d;
}

const QList<SolutionStep>& LinearSystemSolution::steps() const
{
    return _steps;
}
