#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include "applicationmodel.h"
#include "mainwidget.h"

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
};

#endif // MAINWINDOW_H
