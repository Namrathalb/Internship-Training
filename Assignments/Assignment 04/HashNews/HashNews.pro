#-------------------------------------------------
#
# Project created by QtCreator 2020-11-26 T13:21:41
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HashNews
TEMPLATE = app

CONFIG += openssl-linked

RC_ICONS = icontag.ico

SOURCES += main.cpp\
        CpuUsage.cpp \
        dialog.cpp \
        logfile.cpp \
        mainwindow.cpp \
        mywebenginepage.cpp

HEADERS  += mainwindow.h \
    CpuUsage.h \
    dialog.h \
    logfile.h \
    mywebenginepage.h

FORMS    += \
    mainwindow.ui \
    dialog.ui

RESOURCES += \
    loadimg.qrc

DESTDIR += ../ExeFolder
