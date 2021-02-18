#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exitdialog.h"
#include "fileloaddialog.h"

#include "../utils/linearsystemparser.h"

#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connections
    connect(ui->accuracy, &QLineEdit::textChanged, this, &MainWindow::accuracyChanged);
    connect(ui->matrix_size, &QComboBox::currentIndexChanged, this, &MainWindow::sizeOfMatrixChanged);
    connect(ui->calculate, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(ui->max_iteration_number, &QLineEdit::textChanged, this, &MainWindow::maxNumberOfIterationChanged);
    connect(ui->load_file, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::exit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sizeOfMatrixChanged(int index)
{
}

void MainWindow::accuracyChanged(const QString& value)
{
}

void MainWindow::maxNumberOfIterationChanged(const QString& value)
{
}

void MainWindow::loadFile()
{
    FileLoadDialog d(this);

    if(d.exec() == QDialog::Accepted)
    {
        QFile file = d.filePath();

        if(file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();
            LinearSystemParser p(data);
            //TODO: implement this
            file.close();
        }
        else
        {
            QMessageBox::critical(this, "Error", "File is not readable");
        }
    }
}

void MainWindow::calculate()
{
}

void MainWindow::exit()
{
    ExitDialog d(this);

    if (d.exec() == QDialog::Accepted)
    {
        QApplication::quit();
    }
}

