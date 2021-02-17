#ifndef DOUBLELINEEDIT_H
#define DOUBLELINEEDIT_H

#include <QLineEdit>

class DoubleLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit DoubleLineEdit(QWidget* parent = nullptr);
    virtual ~DoubleLineEdit();

signals:
    void valueEdited(double value);

public slots:
    void onValueEdited(const QString&);
};

#endif // DOUBLELINEEDIT_H
