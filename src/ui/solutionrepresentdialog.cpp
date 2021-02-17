#include "solutionrepresentdialog.h"
#include "ui_solutionrepresentdialog.h"

SolutionRepresentDialog::SolutionRepresentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolutionRepresentDialog)
{
    ui->setupUi(this);
}

SolutionRepresentDialog::~SolutionRepresentDialog()
{
    delete ui;
}
