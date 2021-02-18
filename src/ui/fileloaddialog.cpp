#include "fileloaddialog.h"
#include "ui_fileloaddialog.h"

#include <QFileInfo>
#include <QFileDialog>

#include <QMessageBox>

FileLoadDialog::FileLoadDialog(QWidget *parent) :
    QDialog(parent),
    _filepath(),
    ui(new Ui::FileLoadDialog)
{
    ui->setupUi(this);

    connect(ui->load, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->exit, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->filepath, &QLineEdit::textChanged, this, &FileLoadDialog::filePathChanged);
    connect(ui->select_file, &QPushButton::clicked, this, &FileLoadDialog::selectFile);
}

FileLoadDialog::~FileLoadDialog()
{
    delete ui;
}

QString FileLoadDialog::filePath() const
{
    return _filepath;
}

void FileLoadDialog::validateFilePath(const QString& filepath)
{
    QFileInfo info(filepath);

    if(info.isReadable())
    {
        _filepath = filepath;
        ui->load->setEnabled(true);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Unable to read file: " + filepath);
        _filepath = "";
        ui->load->setEnabled(false);
    }
}

void FileLoadDialog::selectFile()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Linear System");
    ui->filepath->setText(filepath);
    validateFilePath(filepath);
}

void FileLoadDialog::filePathChanged(const QString& text)
{
   validateFilePath(text);
}
