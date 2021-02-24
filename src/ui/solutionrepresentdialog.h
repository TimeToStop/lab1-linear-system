#ifndef SOLUTIONREPRESENTDIALOG_H
#define SOLUTIONREPRESENTDIALOG_H

#include "../core/linearsystemsolution.h"

#include <QDialog>
#include <QFile>

enum class FileType : int
{
    NO_TYPE = 0,
    HTML = 1,
    PDF = 2,
    LAST_TYPE
};

namespace Ui {
class SolutionRepresentDialog;
}

class SolutionRepresentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolutionRepresentDialog(const LinearSystemSolution& solution, QWidget *parent = nullptr);
    virtual ~SolutionRepresentDialog();

public slots:
    void fileTypeSelected(int index);
    void saveAs();

private:
    void saveHtmlFile(QFile& file);
    void savePdfFile(QFile& file);

private:
    FileType _selected;
    QString _html;

private:
    Ui::SolutionRepresentDialog *ui;
};

#endif // SOLUTIONREPRESENTDIALOG_H
