QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/core/linearsystemcalculator.cpp \
    src/core/linearsystemservice.cpp \
    src/core/linearsystemsolution.cpp \
    src/core/solutionstep.cpp \
    src/main.cpp \
    src/ui/doublelineedit.cpp \
    src/ui/exitdialog.cpp \
    src/ui/fileloaddialog.cpp \
    src/ui/linearsystemwidget.cpp \
    src/ui/mainwindow.cpp \
    src/ui/solutionrepresentdialog.cpp \
    src/utils/doublevalidator.cpp \
    src/utils/htmlwriter.cpp \
    src/utils/linearsystemparser.cpp \
    src/utils/parseexception.cpp \
    src/utils/utils.cpp

HEADERS += \
    src/core/linearsystemcalculator.h \
    src/core/linearsystemservice.h \
    src/core/linearsystemsolution.h \
    src/core/solutionstep.h \
    src/ui/doublelineedit.h \
    src/ui/exitdialog.h \
    src/ui/fileloaddialog.h \
    src/ui/linearsystemwidget.h \
    src/ui/mainwindow.h \
    src/ui/solutionrepresentdialog.h \
    src/utils/doublevalidator.h \
    src/utils/htmlwriter.h \
    src/utils/linearsystemparser.h \
    src/utils/parseexception.h \
    src/utils/utils.h

FORMS += \
    src/ui/exitdialog.ui \
    src/ui/fileloaddialog.ui \
    src/ui/linearsystemwidget.ui \
    src/ui/mainwindow.ui \
    src/ui/solutionrepresentdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
