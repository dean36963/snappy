#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new MainWidget();
    setCentralWidget(mainWidget);

    checkForFirstTimeRunning();
}

MainWindow::~MainWindow()
{
    delete mainWidget;
}

void MainWindow::checkForFirstTimeRunning() {
    //TODO this needs to actually be done!!!
    cout << "Config dir: " << ApplicationModel::getApplicationModel()->getMainConfigFile() <<endl;
}
