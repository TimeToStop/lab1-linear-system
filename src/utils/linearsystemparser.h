#ifndef LINEARSYSTEMPARSER_H
#define LINEARSYSTEMPARSER_H

#include "../core/linearsystemservice.h"
#include <QFile>

class LinearSystemParser
{
public:
    LinearSystemParser(QFile* file);
    ~LinearSystemParser();

    bool hasError() const;
    QString error() const;

    int n() const;
    double accuracy() const;
    int maxNumberOfIterations() const;
    const DoubleMatrix& matrix() const;
    const DoubleVector& vector() const;

private:
    void parse(const QVector<QString>& list);

private:
    QFile* _file;

    int _n;
    double _accuracy;
    int _max_number_of_iterations;
    DoubleMatrix _matrix;
    DoubleVector _vector;

    bool _has_error;
    QString _error;
};

#endif // LINEARSYSTEMPARSER_H
