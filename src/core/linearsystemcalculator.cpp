#include "linearsystemcalculator.h"

LinearSystemSolution LinearSystemCalculator::calculate(int n, double accuracy, int max_number_of_iteration, const DoubleMatrix &matrix, const DoubleVector &right)
{
    // Diagonal Dominance
    DoubleVector vector_d = right;
    DoubleMatrix matrix_c = matrix;

    for(int i = 0; i < n; i++)
    {
        double q = matrix_c[i][i];

        for(int j = 0; j < n; j++)
        {
            matrix_c[i][j] /= -q;
        }

        matrix_c[i][i] = 0;
        vector_d[i] /= q;
    }

    double c = dominance(matrix_c);
    Status status;
    DoubleVector answer;
    QList<SolutionStep> steps;

    if (c < 1)
    {
        double max_epsilon = 0;
        DoubleVector epsilon = vector_d;
        DoubleVector temp = vector_d;
        DoubleVector current = vector_d;

        for(int i = 0; i < max_number_of_iteration; i++)
        {
            max_epsilon = -1;

            for(int i = 0; i < n; i++)
            {
                double summ = vector_d[i];

                for(int j = 0; j < n; j++)
                {
                    summ += matrix_c[i][j] * current[j];
                }

                temp[i] = summ;
                epsilon[i] = std::abs(temp[i] - current[i]);
                max_epsilon = std::max(max_epsilon, epsilon[i]);
            }

            steps.append(SolutionStep(i + 1, max_epsilon, temp, current, epsilon));
            current = temp;

            if (max_epsilon < accuracy)
            {
                answer = current;
                break;
            }
        }

        status = max_epsilon < accuracy ? Status::SOLVED : Status::DIVERGES;
    }
    else
    {
        status = Status::NO_DOMINANCE;
    }

    return LinearSystemSolution(
                status,
                max_number_of_iteration,
                accuracy,
                matrix,
                right,
                c,
                matrix_c,
                vector_d,
                steps,
                answer
    );
}

double LinearSystemCalculator::dominance(const DoubleMatrix& matrix)
{
    double c = 0;

    for(const DoubleVector& vector : matrix)
    {
        for(double value : vector)
        {
            c += value * value;
        }
    }

    return sqrt(c);
}
