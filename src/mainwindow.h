#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <QAction>
#include <QIcon>
#include <QMenuBar>

#include "src/model/applicationmodel.h"
#include "src/mainwidget.h"
#include "src/utils/importer.h"
#include "src/utils/persistedproperties.h"
#include "src/wizards/setupwizard.h"

using namespace std;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool hasQuit();
private:
    MainWidget *mainWidget;
    void checkForFirstTimeRunning();
    void setupMenus();
    void saveSize();
    void restoreSize();
    Importer* importer;
    QAction *importAction;
    QAction *quitAction;
    QAction *settingsAction;
    static const QString WINDOW_HEIGHT_PROPERTY;
    static const QString WINDOW_WIDTH_PROPERTY;
    bool quit;
public slots:
    void importClicked();
    void quitClicked();
    void settingsClicked();
};

#endif // MAINWINDOW_H
