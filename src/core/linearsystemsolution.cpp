#include "linearsystemsolution.h"

#include "../utils/htmlwriter.h"

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

QString LinearSystemSolution::statusAsString() const
{
    switch (_solved)
    {
    case Status::SOLVED:
        return "SOLVED";
    case Status::DIVERGES:
        return "DIVERGES";
    case Status::NO_DOMINANCE:
        return "NO DOMINANCE";
    }
}

QString LinearSystemSolution::toHTML() const
{
    HtmlWriter w;
    w.writeDivElement("margin: 0 10px");

    w.writeParagraph("Solution", "text-align : center");

    w.writeDivElement("Overview: ");
    w.writeParagraph(QStringLiteral("Status = %1").arg(statusAsString()));

    if (_solved != Status::NO_DOMINANCE)
    {
        w.writeParagraph(QStringLiteral("Answer") + (_solved == Status::DIVERGES ? " - DIVERGES" : ":"));
        w.writeDivElement("margin: 0 10px");

        int i = 1;

        for(const double& x : _answer)
        {
            w.writeParagraph("x<sub>" + QString::number(i++) + "</sub> = " + QString::number(x));
        }

        w.writeEndElement();
    }
    else
    {
        w.writeParagraph("Answer - NO DOMINANCE");
    }

    w.writeEndElement();

    w.writeParagraph(QStringLiteral("Diagonal dominance = %1").arg(_c));

    w.writeParagraph("Input system: ");

    w.writeDivElement("margin: 0 10px");

    const int n = _init_matrix.size();

    for(int i = 0; i < n; i++)
    {
        QString text;

        for(int j = 0; j + 1 < n; j++)
        {
            text += QString::number(_init_matrix[i][j]) + " * x<sub>" + QString::number(j + 1) + "</sub> + ";
        }

        text += QString::number(_init_matrix[i][n - 1]) + " * x<sub>" + QString::number(n) + "</sub> = " + QString::number(_init_vector[i]);

        w.writeParagraph(text);
    }

    w.writeEndElement();

    if (_solved != Status::NO_DOMINANCE)
    {
        w.writeDivElement();

        w.writeParagraph("New system: ");

        w.writeDivElement("margin: 0 10px");

        for(int i = 0; i < n; i++)
        {
            QString text = "x<sub>" + QString::number(i + 1) + "</sub> = ";

            for(int j = 0; j < n; j++)
            {
                text += QString::number(_matrix_c[i][j]) + " * x<sub>" + QString::number(j + 1) + "</sub> + ";
            }

            text += QString::number(_vector_d[i]);

            w.writeParagraph(text);
        }

        w.writeEndElement();

        w.writeEndElement();

        w.writeDivElement();

        w.writeParagraph("Initial vector:");

        w.writeDivElement("margin: 0 10px");

        for(int i = 0; i < n; i++)
        {
            QString text;
            text = "x<sub>" + QString::number(i + 1) + "</sub><sup>0</sup> = " + QString::number(_vector_d[i]);
            w.writeParagraph(text);
        }

        w.writeEndElement();

        w.writeEndElement();

        // Steps
        w.writeDivElement();

        int index = 1;
        int iteration_number = 1;

        for(const SolutionStep& step : _steps)
        {
            w.writeDivElement();

            w.writeParagraph("Step №" + QString::number(index++), "text-align: center");

            w.writeDivElement();

            for(int i = 0; i < n; i++)
            {
                QString text;
                text = "x<sub>" + QString::number(i + 1) + "</sub><sup>"
                        + QString::number(iteration_number) + "</sup> = ";

                for(int j = 0; j < n; j++)
                {
                    text += QString::number(_matrix_c[i][j])
                            + " * " + QString::number(step.prev()[j])
                            + " + ";
                }

                text += QString::number(_vector_d[i])
                        + " = " + QString::number(step.x()[i]);

                text += " e = |x<sub>"
                        + QString::number(i + 1)
                     + "</sub><sup>" + QString::number(iteration_number) + "</sup>"
                     + " - x<sub>" + QString::number(i + 1) + "</sub><sup>"
                     + QString::number(iteration_number - 1) + "</sup>| = |"
                     + QString::number(step.x()[i]) + " - " + QString::number(step.prev()[i]) + "| = "
                     + QString::number(step.epsilons()[i]);

                w.writeParagraph(text);
            }

            QString text = "e = max(";

            for(int i = 0; i + 1 < n; i++)
            {
                text += QString::number(step.epsilons()[i]) + ", ";
            }

            text += QString::number(step.epsilons()[n - 1]) + ") = " + QString::number(step.epsilon());
            text += (step.epsilon() < _target_accuracy ? " &lt; " : " &gt; ") + QString::number(_target_accuracy);

            w.writeParagraph(text);

            w.writeEndElement();
            w.writeEndElement();
        }

        w.writeEndElement();
    }

    w.writeEndElement();
    return w.toHtml();
}
