#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T15:45:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleApp-VersionControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    updatedialog.cpp

HEADERS  += mainwindow.h \
    updatedialog.h

FORMS    += mainwindow.ui \
    updatedialog.ui

QT += network

