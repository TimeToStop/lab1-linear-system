#include "solutionrepresentdialog.h"
#include "ui_solutionrepresentdialog.h"

SolutionRepresentDialog::SolutionRepresentDialog(const LinearSystemSolution& solution, QWidget *parent) :
    QDialog(parent),
    _html(solution.toHTML()),
    ui(new Ui::SolutionRepresentDialog)
{
    ui->setupUi(this);

    connect(ui->close, &QPushButton::clicked, this, &QDialog::accept);

    ui->browser->setHtml(_html);

    qDebug() << _html;
}

SolutionRepresentDialog::~SolutionRepresentDialog()
{
    delete ui;
}

