#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <QAction>
#include <QIcon>
#include <QMenuBar>
#include "applicationmodel.h"
#include "mainwidget.h"
#include "importer.h"

using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    MainWidget *mainWidget;
    void checkForFirstTimeRunning();
    void setupMenus();
    Importer* importer;
    QAction *importAction;
};

#endif // MAINWINDOW_H
