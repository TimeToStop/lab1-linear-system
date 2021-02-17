#include "fileloaddialog.h"
#include "ui_fileloaddialog.h"

FileLoadDialog::FileLoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileLoadDialog)
{
    ui->setupUi(this);
}

FileLoadDialog::~FileLoadDialog()
{
    delete ui;
}
