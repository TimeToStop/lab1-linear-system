#ifndef LINEARSYSTEMSERVICE_H
#define LINEARSYSTEMSERVICE_H

#include <QObject>

#include <QVector>

using DoubleMatrix =

class LinearSystemService : public QObject
{
    Q_OBJECT
public:
    explicit LinearSystemService(QObject *parent = nullptr);
    virtual ~LinearSystemService();

    void setSize(int size);
    void setMaxNumberOfIteration(int number);
    void setAccuracy(double accuracy);
    void setMatrixValue(int i, int j, double value);
    void setRightValue(int i, double value);

    int size() const;
    int maxNumberOfIteration() const;
    double accuracy() const;
    double matrixValue(int i, int j) const;
    double rightValue(int i) const;

signals:

private:
    int _size;
    int _max_number_of_iteration;
    double _accuracy;

};

#endif // LINEARSYSTEMSERVICE_H
