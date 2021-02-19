#include "linearsystemwidget.h"
#include "ui_linearsystemwidget.h"

#include "doublelineedit.h"

#include "../core/linearsystemservice.h"

#include <QLabel>

LinearSystemWidget::LinearSystemWidget(QWidget *parent) :
    QWidget(parent),
    _widgets(),
    ui(new Ui::LinearSystemWidget)
{
    ui->setupUi(this);

    connect(LinearSystemService::global(), &LinearSystemService::sizeChanged,
    [=](int size)
    {
        setMatrixSize(size);
    });
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

    _widgets.clear();

    for(int i = 0; i < n; i++)
    {
        int k = 0;

        for(int j = 0; j < n; j++)
        {
            DoubleLineEdit* edit = new DoubleLineEdit(
                        LinearSystemService::global()->matrixValue(i, j),
                        this
            );

            connect(edit, &DoubleLineEdit::valueEdited,
            [=] (double value)
            {
                LinearSystemService::global()->setMatrixValue(i, j, value);
            });

            connect(LinearSystemService::global(), &LinearSystemService::matrixValueChanged,
            [=] (int _i, int _j, double value)
            {
                if(i == _i && j == _j)
                {
                    edit->setValue(value);
                }
            });

            ui->layout->addWidget(edit, i, k++);
            _widgets.append(edit);

            QLabel* label = new QLabel("x" + QString::number(j + 1), this);
            ui->layout->addWidget(label, i, k++);
            _widgets.append(label);
        }

        QLabel* equal = new QLabel("=", this);
        ui->layout->addWidget(equal, i, k++);
        _widgets.append(equal);

        DoubleLineEdit* edit = new  DoubleLineEdit(
                    LinearSystemService::global()->rightValue(i),
                    this
        );

        connect(edit, &DoubleLineEdit::valueEdited,
        [=] (double value)
        {
            LinearSystemService::global()->setRightValue(i, value);
        });

        connect(LinearSystemService::global(), &LinearSystemService::rightValueChanged,
        [=] (int _i, double value)
        {
            if(i == _i)
            {
                edit->setValue(value);
            }
        });

        ui->layout->addWidget(edit, i, k++);
        _widgets.append(edit);
    }
}
