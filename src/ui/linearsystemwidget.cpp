#include "linearsystemwidget.h"
#include "ui_linearsystemwidget.h"

#include "doublelineedit.h"

LinearSystemWidget::LinearSystemWidget(QWidget *parent) :
    QWidget(parent),
    _widgets(),
    ui(new Ui::LinearSystemWidget)
{
    ui->setupUi(this);
}

LinearSystemWidget::~LinearSystemWidget()
{
    delete ui;
}

void LinearSystemWidget::setMatrixSize(int n)
{
    for(QWidget* widget : _widgets)
    {
        ui->layout->removeWidget(widget);
        delete widget;
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            DoubleLineEdit* edit = new DoubleLineEdit(this);
            connect(edit, &DoubleLineEdit::valueEdited,
            [] (double value)
            {

            });
        }
    }
}
