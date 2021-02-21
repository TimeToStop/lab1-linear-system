#ifndef SOLUTIONREPRESENTDIALOG_H
#define SOLUTIONREPRESENTDIALOG_H

#include "../core/linearsystemsolution.h"

#include <QDialog>

namespace Ui {
class SolutionRepresentDialog;
}

class SolutionRepresentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolutionRepresentDialog(const LinearSystemSolution& solution, QWidget *parent = nullptr);
    virtual ~SolutionRepresentDialog();

private:
    Ui::SolutionRepresentDialog *ui;
};

#endif // SOLUTIONREPRESENTDIALOG_H
