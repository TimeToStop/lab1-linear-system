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

    QString filePath() const;

private:
    void validateFilePath(const QString& filepath);

public slots:
    void selectFile();
    void filePathChanged(const QString&);

private:
    QString _filepath;

private:
    Ui::FileLoadDialog *ui;
};

#endif // FILELOADDIALOG_H
