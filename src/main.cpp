#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon("../resources/icon.png");
    MainWindow w;
    a.setWindowIcon(icon);
    w.show();
    return a.exec();
}
