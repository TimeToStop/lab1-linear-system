#ifndef FILELOADDIALOG_H
#define FILELOADDIALOG_H

#include <QDialog>

namespace Ui {
class FileLoadDialog;
}

class FileLoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileLoadDialog(QWidget *parent = nullptr);
    virtual ~FileLoadDialog();

private:
    Ui::FileLoadDialog *ui;
};

#endif // FILELOADDIALOG_H
