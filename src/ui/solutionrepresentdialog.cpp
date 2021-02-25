#include "solutionrepresentdialog.h"
#include "ui_solutionrepresentdialog.h"

#include <QPrinter>
#include <QFileDialog>
#include <QMessageBox>

SolutionRepresentDialog::SolutionRepresentDialog(const LinearSystemSolution& solution, QWidget *parent) :
    QDialog(parent),
    _selected(FileType::HTML),
    _html(solution.toHTML()),
    ui(new Ui::SolutionRepresentDialog)
{
    ui->setupUi(this);

    ui->browser->setHtml(_html);

    ui->type->addItem("HTML", (int)FileType::HTML);
    ui->type->addItem("PDF", (int)FileType::PDF);

    connect(ui->type, &QComboBox::currentIndexChanged, this, &SolutionRepresentDialog::fileTypeSelected);
    connect(ui->save, &QPushButton::clicked, this, &SolutionRepresentDialog::saveAs);
    connect(ui->close, &QPushButton::clicked, this, &QDialog::accept);
}

SolutionRepresentDialog::~SolutionRepresentDialog()
{
    delete ui;
}

void SolutionRepresentDialog::fileTypeSelected(int index)
{
    if (index >= 0)
    {
        int value = ui->type->itemData(index).toInt();

        if ((int)FileType::NO_TYPE < value && value < (int)FileType::LAST_TYPE)
        {
            _selected = (FileType)value;
        }
        else
        {
            QMessageBox::critical(this, "Error", "Invalid file type selected");
        }
    }
}

void SolutionRepresentDialog::saveAs()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save");

    if (filepath != "")
    {
        QFile file(filepath);

        if (file.open(QIODevice::WriteOnly))
        {
            switch (_selected)
            {
            case FileType::HTML:
                saveHtmlFile(file);
                break;
            case FileType::PDF:
                savePdfFile(file);
                break;
            default:
                break;
            }

            file.flush();
            file.close();

            QMessageBox::information(this, "Save", "File written corectly");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Unable to open file: " + filepath);
        }
    }
}

void SolutionRepresentDialog::saveHtmlFile(QFile& file)
{
    file.write(_html.toUtf8());
}

void SolutionRepresentDialog::savePdfFile(QFile& file)
{
    QTextDocument document;
    document.setHtml(_html);

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(file.fileName());
    printer.setPageMargins(QMarginsF(0, 0, 0, 0));

    document.print(&printer);
}

