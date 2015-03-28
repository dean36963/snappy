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
    eventtreewidget.cpp \
    thumbnailwidget.cpp \
    thumbnailview.cpp \
    persistedproperties.cpp \
    largephotoview.cpp \
    setupwizard.cpp \
    librarywizardpage.cpp \
    imageutils.cpp

HEADERS  += mainwindow.h \
    applicationmodel.h \
    mainwidget.h \
    librarymodel.h \
    eventfolder.h \
    importer.h \
    photoarea.h \
    eventtreewidget.h \
    thumbnailwidget.h \
    thumbnailview.h \
    persistedproperties.h \
    largephotoview.h \
    setupwizard.h \
    librarywizardpage.h \
    imageutils.h

RESOURCES = application.qrc
