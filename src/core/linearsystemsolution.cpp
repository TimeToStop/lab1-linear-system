#include "linearsystemsolution.h"

#include <QTextStream>

#include <QDebug>

QString LinearSystemSolution::_html_pattern =
    "<div>"
    "   <div align=\"center\">Solution</div>"
    "   <div>"
    "       <div>Status %1</div>"
    "       <div>Iterations %2 out of %3</div>"
    "       <div>Accuracy %4 out of %5</div>"
    "       <div>Initial system:</div>"
    "       <div>%6</div>"
    "       <div>Initial vector:</div>"
    "       <div>%7</div>"
    "   </div>"
    "   <div>"
    "       %8"
    "   </div>"
    "</div>"
;

QString LinearSystemSolution::_step_pattern =
    "<div>"
    "   <div align=\"center\"> Step №%1</div>"
    "   <div>%2</div>"
    "   <div>Epsilon:</div>"
    "   <div>%3</div>"
    "   <div>e = max(%4) = %5</div>"
    "</div>"
;

LinearSystemSolution::LinearSystemSolution(
        Status solved,
        int max_number_of_iteartion,
        double accuracy,
        const DoubleMatrix& init_matrix,
        const DoubleVector& init_vector,
        double c,
        const DoubleMatrix& matrix_c,
        const DoubleVector& vector_d,
        const QList<SolutionStep>& steps,
        const DoubleVector& answer
):
    _solved(solved),
    _max_number_of_iteartion(max_number_of_iteartion),
    _target_accuracy(accuracy),
    _init_matrix(init_matrix),
    _init_vector(init_vector),
    _c(c),
    _matrix_c(matrix_c),
    _vector_d(vector_d),
    _steps(steps),
    _answer(answer)
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
    _steps(other._steps),
    _answer(other._answer)
{
}

LinearSystemSolution::~LinearSystemSolution()
{
}

QString LinearSystemSolution::toHTML() const
{
    int n = _init_matrix.size();
    QString solution_status;

    switch(_solved)
    {
    case Status::SOLVED:
        solution_status = "SOLVED";
        break;
    case Status::DIVERGES:
        solution_status = "DIVERGES";
        break;
    case Status::NO_DOMINANCE:
        solution_status = "NO DOMINANCE";
        break;
    }

    QString initial_system;
    QTextStream s_initial_system(&initial_system);

    for(int i = 0; i < n; i++)
    {
        s_initial_system << "<div>";
        for(int j = 0; j + 1 < n; j++)
        {
            s_initial_system << _init_matrix[i][j] << " * x" << j + 1 << " +";
        }

        s_initial_system << _init_matrix[i][n - 1] << " * x" << n << " = " << _init_vector[i];
        s_initial_system << "</div>";
    }

    s_initial_system.flush();

    QString initial_vector;
    QTextStream s_initial_vector(&initial_vector);

    for(int i = 0; i < n; i++)
    {
        s_initial_vector << "<div>x" << i + 1 << " = " << _vector_d[i] << "</div>";
    }

    s_initial_vector.flush();

    QString steps;

    int number = 1;

    for(const SolutionStep& step : _steps)
    {
        QString epsilon;
        QString max;
        QString step_calculation;
        QString max_epsilon;

        QTextStream s_epsilon(&epsilon);
        QTextStream s_calculation(&step_calculation);

        for(int i = 0; i < n; i++)
        {
            s_calculation << "<div>";

            // Calculation
            s_calculation << "x" << i + 1 << " = ";

            for(int j = 0; j < n; j++)
            {
                s_calculation << _matrix_c[i][j] << " * " << step.prev()[j] << " + ";
            }

            s_calculation << _vector_d[i] << " = " << step.x()[i];

            // Epsilon
            s_epsilon << "<div>";
            s_epsilon << "|x" << i + 1 << " - x" << i + 1 << "| = |"
                        << step.x()[i] << " - " << step.prev()[i]
                           << "| = " << step.epsilons()[i];
            s_epsilon << "</div>";
            max += QString::number(step.epsilons()[i]) + ",";

            s_calculation << "</div>";
        }

        max.chop(1);

        max_epsilon = QString::number(step.epsilon());
        max_epsilon += (step.epsilon() < _target_accuracy ? " < " : " > ");
        max_epsilon += QString::number(_target_accuracy);

        s_epsilon.flush();
        s_calculation.flush();

        steps += _step_pattern.arg(QString::number(number++),
                                   step_calculation, epsilon, max,
                                   max_epsilon
        );
    }

    return _html_pattern.arg(
                solution_status,
                QString::number(_steps.size()),
                QString::number(_max_number_of_iteartion),
                "0",
                QString::number(_target_accuracy),
                initial_system,
                initial_vector,
                steps
    );
}
