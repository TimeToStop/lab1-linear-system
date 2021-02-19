#include "linearsystemservice.h"

#include <stdexcept>

#include <QDebug>

#include "../utils/utils.h"

LinearSystemService LinearSystemService::_global;

const int LinearSystemService::_min_matrix_size = 2;
const int LinearSystemService::_max_matrix_size = 20;

const int LinearSystemService::_initial_size = _min_matrix_size;
const double LinearSystemService::_initial_accuracy = 0.1;
const int LinearSystemService::_initial_max_number_of_itearation = 10;

LinearSystemService::LinearSystemService(QObject *parent):
    QObject(parent),
    _size(_initial_size),
    _max_number_of_iteration(_initial_max_number_of_itearation),
    _accuracy(_initial_accuracy),
    _matrix(_initial_size, DoubleVector(_initial_size, 0)),
    _vector(_initial_size, 0)
{
}

LinearSystemService::~LinearSystemService()
{
}

void LinearSystemService::setSize(int size)
{
    if (size == _size) return;

    if (size < _min_matrix_size || size > _max_matrix_size)
    {
        throw std::runtime_error("Size of matrix is not valid");
    }

    int min_size = std::min(_size, size);
    DoubleMatrix matrix(size, DoubleVector(size, 0));
    DoubleVector vector(size, 0);

    for(int i = 0; i < min_size; i++)
    {
        for(int j = 0; j < min_size; j++)
        {
            matrix[i][j] = _matrix[i][j];
        }

        vector[i] = _vector[i];
    }

    _size = size;
    _matrix = matrix;
    _vector = vector;

    emit sizeChanged(size);
}

void LinearSystemService::setMaxNumberOfIteration(int number)
{
    if (_max_number_of_iteration != number) return;
    _max_number_of_iteration = number;
    emit maxNumberOfIterationChanged(number);
}

void LinearSystemService::setAccuracy(double accuracy)
{
    if (::nearlyEqual(accuracy, _accuracy)) return;
    _accuracy = accuracy;
    emit accuracyChanged(accuracy);
}

void LinearSystemService::setMatrixValue(int i, int j, double value)
{
    if (::nearlyEqual(value, _matrix[i][j])) return;
    _matrix[i][j] = value;
    emit matrixValueChanged(i, j, value);
}

void LinearSystemService::setRightValue(int i, double value)
{
    if (::nearlyEqual(value, _vector[i])) return;
    _vector[i] = value;
    emit rightValueChanged(i, value);
}

int LinearSystemService::size() const
{
    return _size;
}

int LinearSystemService::maxNumberOfIteration() const
{
    return _max_number_of_iteration;
}

double LinearSystemService::accuracy() const
{
    return _accuracy;
}

double LinearSystemService::matrixValue(int i, int j) const
{
    return _matrix[i][j];
}

double LinearSystemService::rightValue(int i) const
{
    return _vector[i];
}

LinearSystemService* LinearSystemService::global()
{
    return &_global;
}
