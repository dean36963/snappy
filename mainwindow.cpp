#include "mainwindow.h"

const QString MainWindow::WINDOW_HEIGHT_PROPERTY = "window.height";
const QString MainWindow::WINDOW_WIDTH_PROPERTY = "window.width";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new MainWidget();
    setCentralWidget(mainWidget);
    restoreSize();

    setupMenus();
    //checkForFirstTimeRunning();
}

MainWindow::~MainWindow()
{
    saveSize();
    delete mainWidget;
    delete importer;
    delete importAction;
    delete quitAction;

    //Final should be settings
    ApplicationModel::deleteModel();
}

void MainWindow::checkForFirstTimeRunning() {
    //TODO this needs to actually be done!!!
    //cout << "Config dir: " << ApplicationModel::getApplicationModel()->getMainConfigFile() <<endl;
}

void MainWindow::setupMenus() {
    QMenuBar* menu = menuBar();
    QMenu* fileMenu = menu->addMenu("&File");

    importer = new Importer();
    importAction = new QAction(QIcon::fromTheme("folder"),"Import photos from folder",this);
    importAction->setIconVisibleInMenu(true);
    importAction->setShortcut(QKeySequence("Ctrl+I"));
    QObject::connect(importAction,SIGNAL(triggered()),this,SLOT(importClicked()));
    fileMenu->addAction(importAction);

    fileMenu->addSeparator();

    quitAction = new QAction(QIcon::fromTheme("application-exit"),"Quit",this);
    quitAction->setIconVisibleInMenu(true);
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(quitAction,SIGNAL(triggered()),this,SLOT(quitClicked()));
    fileMenu->addAction(quitAction);

    menu->setNativeMenuBar(false);

    mainWidget->addMenuItems(menu);

    menu->show();
}

void MainWindow::importClicked() {
    importer->importPhotos(this);
}

void MainWindow::quitClicked() {
    QApplication::quit();
}

void MainWindow::restoreSize() {
    PersistedProperties *props = ApplicationModel::getApplicationModel()->getProperties();
    if(props->hasProperty(WINDOW_WIDTH_PROPERTY) && props->hasProperty(WINDOW_HEIGHT_PROPERTY)) {
        QString widthProperty = props->getPropertyValue(WINDOW_WIDTH_PROPERTY);
        QString heightProperty = props->getPropertyValue(WINDOW_HEIGHT_PROPERTY);
        resize(widthProperty.toInt(),heightProperty.toInt());
    }
}

void MainWindow::saveSize() {
    ApplicationModel::getApplicationModel()->getProperties()->setProperty(WINDOW_WIDTH_PROPERTY,QString::number(size().width()));
    ApplicationModel::getApplicationModel()->getProperties()->setProperty(WINDOW_HEIGHT_PROPERTY,QString::number(size().height()));
}
