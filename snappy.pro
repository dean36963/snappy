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

SOURCES += src/utils/imageutils.cpp \
    src/utils/importer.cpp \
    src/utils/persistedproperties.cpp \
    src/model/applicationmodel.cpp \
    src/model/librarymodel.cpp \
    src/wizards/librarywizardpage.cpp \
    src/wizards/setupwizard.cpp \
    src/eventfolder.cpp \
    src/eventtreewidget.cpp \
    src/main.cpp \
    src/mainwidget.cpp \
    src/mainwindow.cpp \
    src/photoarea.cpp \
    src/thumbnailview.cpp \
    src/thumbnailwidget.cpp \
    src/largephotowidget.cpp \
    src/largephotoview.cpp

HEADERS  += src/utils/imageutils.h \
    src/utils/importer.h \
    src/utils/persistedproperties.h \
    src/model/applicationmodel.h \
    src/model/librarymodel.h \
    src/wizards/librarywizardpage.h \
    src/wizards/setupwizard.h \
    src/eventfolder.h \
    src/eventtreewidget.h \
    src/mainwidget.h \
    src/mainwindow.h \
    src/photoarea.h \
    src/thumbnailview.h \
    src/thumbnailwidget.h \
    src/largephotowidget.h \
    src/largephotoview.h

RESOURCES = application.qrc
