#ifndef LINEARSYSTEMSERVICE_H
#define LINEARSYSTEMSERVICE_H

#include <QObject>

#include <QVector>

using DoubleVector = QVector<double>;
using DoubleMatrix = QVector<QVector<double>>;

class LinearSystemService : public QObject
{
    Q_OBJECT

private:
    explicit LinearSystemService(QObject* parent = nullptr);
    virtual ~LinearSystemService();

public:
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
    void sizeChanged(int size);
    void maxNumberOfIterationChanged(int number);
    void accuracyChanged(double accuracy);
    void matrixValueChanged(int i, int j, double value);
    void rightValueChanged(int i, double value);

private:
    static LinearSystemService _global;

public:
    static LinearSystemService* global();

    static const int _min_matrix_size;
    static const int _max_matrix_size;

    static const int _initial_size;
    static const double _initial_accuracy;
    static const int _initial_max_number_of_itearation;

private:
    int _size;
    int _max_number_of_iteration;
    double _accuracy;
    DoubleMatrix _matrix;
    DoubleVector _vector;
};

#endif // LINEARSYSTEMSERVICE_H
