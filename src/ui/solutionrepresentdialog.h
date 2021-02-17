#ifndef SOLUTIONREPRESENTDIALOG_H
#define SOLUTIONREPRESENTDIALOG_H

#include <QDialog>

namespace Ui {
class SolutionRepresentDialog;
}

class SolutionRepresentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolutionRepresentDialog(QWidget *parent = nullptr);
    virtual ~SolutionRepresentDialog();

private:
    Ui::SolutionRepresentDialog *ui;
};

#endif // SOLUTIONREPRESENTDIALOG_H
