#ifndef LINEARSYSTEMWIDGET_H
#define LINEARSYSTEMWIDGET_H

#include <QWidget>

namespace Ui {
class LinearSystemWidget;
}

class LinearSystemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinearSystemWidget(QWidget *parent = nullptr);
    virtual ~LinearSystemWidget();

    void setMatrixSize(int n);

private:
    QList<QWidget*> _widgets;

private:
    Ui::LinearSystemWidget *ui;
};

#endif // LINEARSYSTEMWIDGET_H
