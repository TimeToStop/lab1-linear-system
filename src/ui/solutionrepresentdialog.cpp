#include "solutionrepresentdialog.h"
#include "ui_solutionrepresentdialog.h"

SolutionRepresentDialog::SolutionRepresentDialog(const LinearSystemSolution& solution, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolutionRepresentDialog)
{
    ui->setupUi(this);

    connect(ui->close, &QPushButton::clicked, this, &QDialog::accept);
}

SolutionRepresentDialog::~SolutionRepresentDialog()
{
    delete ui;
}
