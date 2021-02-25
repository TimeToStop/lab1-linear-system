#include "linearsystemparser.h"

#include "parseexception.h"

#include <QString>
#include <QRegularExpression>
#include <QTextStream>

LinearSystemParser::LinearSystemParser(QFile* file)
{
    QTextStream stream(file);
    QString str = stream.readAll();
    QStringList list = str.split(QRegularExpression("[\r\n\t ]+"), Qt::SkipEmptyParts);

    try
    {
        parse(list.toVector());
    }
    catch (ParseException& e)
    {
        _has_error = true;
        _error = e.message();
    }
}

LinearSystemParser::~LinearSystemParser()
{
}

bool LinearSystemParser::hasError() const
{
    return _has_error;
}

QString LinearSystemParser::error() const
{
    return _error;
}

int LinearSystemParser::n() const
{
    return _n;
}

double LinearSystemParser::accuracy() const
{
    return _accuracy;
}

int LinearSystemParser::maxNumberOfIterations() const
{
    return _max_number_of_iterations;
}

const DoubleMatrix &LinearSystemParser::matrix() const
{
    return _matrix;
}

const DoubleVector &LinearSystemParser::vector() const
{
    return _vector;
}

void LinearSystemParser::parse(const QVector<QString>& list)
{
    bool ok = true;
    if (list.size() < 3) throw ParseException("File contains too few data");

    _n = list[0].toInt(&ok);
    _matrix = DoubleMatrix(_n, DoubleVector(_n, 0));
    _vector = DoubleVector(_n, 0);

    if (!ok) throw ParseException("N is not an int value");

    _accuracy = list[1].toDouble(&ok);

    if (!ok) throw ParseException("Accuracy is not a double value");

    _max_number_of_iterations = list[2].toInt(&ok);

    if (!ok) throw ParseException("Max number of iteration is not an int value");

    if ( list.size() != 3 + _n * (_n + 1)) throw ParseException("Matrix is not copatible with size of it");

    int index = 3;

    for(int i = 0; i < _n; i++)
    {
        for (int j = 0; j < _n; j++)
        {
            _matrix[i][j] = list[index++].toDouble(&ok);

            if (!ok) throw ParseException("Matrix value is not a double value");
        }

        _vector[i] = list[index++].toDouble(&ok);

        if (!ok) throw ParseException("Matrix value is not a double value");
    }
}
