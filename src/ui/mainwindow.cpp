#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "exitdialog.h"
#include "fileloaddialog.h"
#include "solutionrepresentdialog.h"

#include "../utils/doublevalidator.h"

#include "../utils/linearsystemparser.h"
#include "../core/linearsystemservice.h"
#include "../core/linearsystemcalculator.h"

#include <QFile>
#include <QMessageBox>

#include <QDoubleValidator>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    DoubleValidator* validator = new DoubleValidator(this);
    validator->setBottom(0);
    ui->accuracy->setValidator(validator);
    ui->max_iteration_number->setValidator(new QIntValidator(1, 9999999, this));


    // Connections
    connect(ui->accuracy, &QLineEdit::textEdited, this, &MainWindow::accuracyChanged);
    connect(ui->matrix_size, &QComboBox::currentIndexChanged, this, &MainWindow::sizeOfMatrixChanged, Qt::ConnectionType::DirectConnection);
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
    if (index >= 0)
    {
        int value = ui->matrix_size->itemData(index).toInt();
        LinearSystemService::global()->setSize(value);
        ui->mainframe->setMatrixSize(value);
    }
}

void MainWindow::accuracyChanged(const QString& text)
{    
    if (text.isEmpty()) return;
    if (text.size() > 0 && text.toLower() == "e") return;

    QString new_text = text;
    new_text.replace(',', '.');

    bool ok = true;
    double value = new_text.toDouble(&ok);

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
    if (text.isEmpty()) return;

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
            LinearSystemParser p(&file);
            file.close();

            if (!p.hasError())
            {
                LinearSystemSolution s = LinearSystemCalculator::calculate(
                                p.n(),
                                p.accuracy(),
                                p.maxNumberOfIterations(),
                                p.matrix(),
                                p.vector()
                            );

                SolutionRepresentDialog d(s, this);

                d.exec();
            }
            else
            {
                QMessageBox::critical(this, "Error", p.error());
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "File is not readable");
        }
    }
}

void MainWindow::calculate()
{
    LinearSystemSolution s = LinearSystemCalculator::calculate(
        LinearSystemService::global()->size(),
        LinearSystemService::global()->accuracy(),
        LinearSystemService::global()->maxNumberOfIteration(),
        LinearSystemService::global()->matrix(),
        LinearSystemService::global()->rightVector()
    );

    SolutionRepresentDialog d(s, this);
    d.exec();
}

void MainWindow::exit()
{
    ExitDialog d(this);

    if (d.exec() == QDialog::Accepted)
    {
        QApplication::quit();
    }
}

