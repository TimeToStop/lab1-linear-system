#include "exitdialog.h"
#include "ui_exitdialog.h"

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);

    connect(ui->yes, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->no,  &QPushButton::clicked, this, &QDialog::reject);
}

ExitDialog::~ExitDialog()
{
    delete ui;
}
