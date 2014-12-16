#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new MainWidget();
    setCentralWidget(mainWidget);

    setupMenus();
    //checkForFirstTimeRunning();
}

MainWindow::~MainWindow()
{
    delete mainWidget;
    delete importer;
    delete importAction;
}

void MainWindow::checkForFirstTimeRunning() {
    //TODO this needs to actually be done!!!
    cout << "Config dir: " << ApplicationModel::getApplicationModel()->getMainConfigFile() <<endl;
}

void MainWindow::setupMenus() {
    QMenuBar* menu = menuBar();
    QMenu* fileMenu = menu->addMenu("&File");

    importer = new Importer();
    importAction = new QAction(QIcon(":/icons/folder.svg"),"Import photos from folder",this);
    importAction->setIconVisibleInMenu(true);
    importAction->setShortcut(QKeySequence("Ctrl+I"));
    fileMenu->addAction(importAction);

    menu->setNativeMenuBar(false);
    menu->show();
}
