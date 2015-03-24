#-------------------------------------------------
#
# Project created by QtCreator 2014-12-14T16:02:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snappy
TEMPLATE = app

LIBS += -lexif

SOURCES += main.cpp\
        mainwindow.cpp \
    applicationmodel.cpp \
    mainwidget.cpp \
    librarymodel.cpp \
    eventfolder.cpp \
    importer.cpp \
    photoarea.cpp \
    notifier.cpp \
    eventtreewidget.cpp

HEADERS  += mainwindow.h \
    applicationmodel.h \
    mainwidget.h \
    librarymodel.h \
    eventfolder.h \
    importer.h \
    photoarea.h \
    notifier.h \
    eventtreewidget.h

RESOURCES = application.qrc
