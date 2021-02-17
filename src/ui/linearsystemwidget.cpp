#include "linearsystemwidget.h"
#include "ui_linearsystemwidget.h"

LinearSystemWidget::LinearSystemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinearSystemWidget)
{
    ui->setupUi(this);
}

LinearSystemWidget::~LinearSystemWidget()
{
    delete ui;
}
