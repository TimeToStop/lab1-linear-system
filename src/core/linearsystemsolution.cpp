#include "linearsystemsolution.h"

#include <QTextStream>

LinearSystemSolution::LinearSystemSolution(
        Status solved,
        int max_number_of_iteartion,
        double accuracy,
        const DoubleMatrix& init_matrix,
        const DoubleVector& init_vector,
        double c,
        const DoubleMatrix& matrix_c,
        const DoubleVector& vector_d,
        const QList<SolutionStep>& steps
):
    _solved(solved),
    _max_number_of_iteartion(max_number_of_iteartion),
    _target_accuracy(accuracy),
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
    _max_number_of_iteartion(other._max_number_of_iteartion),
    _target_accuracy(other._target_accuracy),
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

int LinearSystemSolution::maxNumberOfIteration() const
{
    return _max_number_of_iteartion;
}

double LinearSystemSolution::targetAccuracy() const
{
    return _target_accuracy;
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

QString LinearSystemSolution::toHTML() const
{
    QString html;
    QTextStream s(&html);

    s << "<div align=center>Solution</div>";
    s << "<div>Status = ";

    switch (_solved)
    {
    case Status::SOLVED:
        s << "SOLVED";
        break;
    case Status::DIVERGES:
        s << "DIVERGES";
        break;
    case Status::NO_DOMINANCE:
        s << "NO_DOMINANCE";
        break;
    default:
        break;
    }

    s << "</div>";

    s << "<div>Max Iteration = " << _max_number_of_iteartion << "</div>";
    s << "<div>Iteration = " << _steps.size() << "</div>";
    s << "<div>Target accuracy = " << _target_accuracy << "</div>";
    s << "<div>Initial system:</div>";

    s << "<div>";

    int n = _init_matrix.size();

    for(int i = 0; i < n; i++)
    {
        s << "<div>";

        for(int j = 0; j + 1 < n; j++)
        {
            s << _init_matrix[i][j] << " * x" << j + 1 << " + ";
        }

         s << _init_matrix[i][n - 1] << " * x" << n << " = " << _init_vector[i];
         s << "</div>";
    }

    s << "</div>";

    // Solution
    int number = 1;

    s << "<div>";

    for(const SolutionStep& step : _steps)
    {
        s << "<div>";

        s << "<div>Step №" << number++ << "</div>";
        s << "<div>";

        int n = _init_matrix.size();

        for(int i = 0; i < n; i++)
        {
            s << "<div>";
            s << "x" << i + 1 << " = ";

            for(int j = 0; j < n; j++)
            {
                s << _matrix_c[i][j] << " * " << step.prev()[j] << " + ";
            }

             s << _vector_d[i] << " = " << step.x()[i];
             s << "</div>";
        }

        s << "</div>";

        s << "<div><div>Epsilon:</div><div>";

        for(int i = 0; i < n; i++)
        {
            s << "<div>";
            s << "|x" << i + 1 << " - x" << i + 1 << "| = |"
                        << step.x()[i] << " - " << step.prev()[i] << " | = "
                        << step.epsilons()[i];
            s << "</div>";
        }
        s << "</div>";

        s << "<div>";
        s << "e = max(";

        for(int i = 0; i + 1 < n; i++)
        {
            s << step.epsilons()[i] << ", ";
        }

        s << step.epsilons()[n - 1] << ") = " << step.epsilon();

        s << (step.epsilon() < _target_accuracy ? " < " : " > ") << _target_accuracy;

        s << "</div>";

        s << "</div>";
        s << "</div>";
    }

    s << "</div>";

    s << "<div><div> Conclusion </div><div>";

    switch (_solved)
    {
    case Status::SOLVED:
        s << "Target accuracy was reached";
        break;
    case Status::DIVERGES:
        s << "Target accuracy was not reached";
        break;
    case Status::NO_DOMINANCE:
        s << "Calculated dominance is not less than 1";
        break;
    default:
        break;
    }

    s << "</div>";
    s << "</div>";

    s.flush();
    return html;
}
