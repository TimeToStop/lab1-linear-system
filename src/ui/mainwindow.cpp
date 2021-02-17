#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
}

void MainWindow::calculate()
{
}

void MainWindow::exit()
{
}

