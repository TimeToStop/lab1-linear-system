#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

public slots:
    void sizeOfMatrixChanged(int index);
    void accuracyChanged(const QString& text);
    void maxNumberOfIterationChanged(const QString& text);
    void loadFile();
    void calculate();
    void exit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
