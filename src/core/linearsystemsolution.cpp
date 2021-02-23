#include "linearsystemsolution.h"

#include "../utils/htmlwriter.h"

//QString LinearSystemSolution::_html_pattern =
//    "<!DOCTYPE html><html><head><title>Solution</title></head><body>"
//    "<div style=\"margin : 0 10px\">"
//    "   <div align=\"center\">Solution</div>"
//    "   <div>"
//    "       <div>Status %1</div>"
//    "       <div>Iterations %2 out of %3</div>"
//    "       <div>Accuracy %4 out of %5</div>"
//    "       <div>Initial system:</div>"
//    "       <div style=\"margin : 0 10px\">%6</div>"
//    "       <div>Initial vector:</div>"
//    "       <div style=\"margin : 0 10px\">%7</div>"
//    "       <div>Answer:</div>"
//    "       <div style=\"margin : 0 10px\">%8</div>"
//    "   </div>"
//    "   <div>"
//    "       %9"
//    "   </div>"
//    "</div>"
//    "</body></html>"
//;

//QString LinearSystemSolution::_step_pattern =
//    "<div>"
//    "   <div align=\"center\">Step №%1</div>"
//    "   <div>Calculation:</div>"
//    "   <div style=\"margin : 0 10px\">%2</div>"
//    "   <div>Epsilon:</div>"
//    "   <div style=\"margin : 0 10px\">%3</div>"
//    "   <div>e = max(%4) = %5 </div>"
//    "</div>"
//;

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
        w.writeDivElement();

        int i = 1;

        for(const double& x : _answer)
        {
            w.writeParagraph("x" + QString::number(i++) + " = " + QString::number(x));
        }

        w.writeEndElement();
    }
    else
    {
        w.writeParagraph("Answer - NO DOMINANCE");
    }

    w.writeEndElement();

    w.writeParagraph(QStringLiteral("Diagonal dominance = %1").arg(_c));

    w.writeParagraph("Initial matrix: ");

    w.writeDivElement();

    for(const DoubleVector& row : _init_matrix)
    {
        QString text;

        for(const double& value : row)
        {
            text += QString::number(value) + " ";
        }

        w.writeParagraph(text);
    }

    w.writeEndElement();

    w.writeEndElement();
    return w.toHtml();
}
