#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exitdialog.h"
#include "fileloaddialog.h"

#include "../utils/linearsystemparser.h"
#include "../core/linearsystemservice.h"

#include <QFile>
#include <QMessageBox>

#include <QDoubleValidator>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connections
    connect(ui->accuracy, &QLineEdit::textChanged, this, &MainWindow::accuracyChanged);
    connect(ui->matrix_size, &QComboBox::currentIndexChanged, this, &MainWindow::sizeOfMatrixChanged, Qt::ConnectionType::DirectConnection);
    connect(ui->calculate, &QPushButton::clicked, this, &MainWindow::calculate);
    connect(ui->max_iteration_number, &QLineEdit::textChanged, this, &MainWindow::maxNumberOfIterationChanged);
    connect(ui->load_file, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->exit, &QPushButton::clicked, this, &MainWindow::exit);


    ui->mainframe->setMatrixSize(LinearSystemService::_initial_size);

    // Range of matrix size
    for(int i = LinearSystemService::_min_matrix_size;
            i <= LinearSystemService::_max_matrix_size; i++)
    {
        ui->matrix_size->addItem(QString::number(i), i);
    }

    ui->max_iteration_number->setText(QString::number(LinearSystemService::_initial_max_number_of_itearation));
    ui->accuracy->setText(QString::number(LinearSystemService::_initial_accuracy));

    // Validators
    // TODO: magic value
    ui->accuracy->setValidator(new QDoubleValidator());
    ui->max_iteration_number->setValidator(new QIntValidator(1, 9999999));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sizeOfMatrixChanged(int index)
{
    if (index >= 0)
    {
        int value = ui->matrix_size->itemData(index).toInt();
        LinearSystemService::global()->setSize(value);
    }
}

void MainWindow::accuracyChanged(const QString& text)
{    
    bool ok = true;
    double value = text.toDouble(&ok);

    if(!ok)
    {
        QMessageBox::critical(this, "Error", "Unable to parce as double value");
    }
    else
    {
        LinearSystemService::global()->setAccuracy(value);
    }
}

void MainWindow::maxNumberOfIterationChanged(const QString& text)
{
    bool ok = true;
    int value = text.toInt(&ok);

    if(!ok)
    {
        QMessageBox::critical(this, "Error", "Unable to parse as int value");
    }
    else
    {
        LinearSystemService::global()->setMaxNumberOfIteration(value);
    }
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

