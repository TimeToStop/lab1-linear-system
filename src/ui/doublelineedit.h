#ifndef DOUBLELINEEDIT_H
#define DOUBLELINEEDIT_H

#include <QLineEdit>

class DoubleLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit DoubleLineEdit(double value = 0, QWidget* parent = nullptr);
    virtual ~DoubleLineEdit();

    void setValue(double value);

signals:
    void valueEdited(double value);

public slots:
    void onValueEdited(const QString&);

private:
    double _previous_value;
};

#endif // DOUBLELINEEDIT_H
