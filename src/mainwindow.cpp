#include "mainwindow.h"

const QString MainWindow::WINDOW_HEIGHT_PROPERTY = "window.height";
const QString MainWindow::WINDOW_WIDTH_PROPERTY = "window.width";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    quit = false;
    checkForFirstTimeRunning();

    if(!quit) {
        mainWidget = new MainWidget();
        setCentralWidget(mainWidget);
        restoreSize();

        setupMenus();
    }
}

MainWindow::~MainWindow()
{
    if(!quit) {
        saveSize();
        delete mainWidget;
        delete importer;
        delete importAction;
        delete quitAction;
        delete settingsAction;
    }

    //Final should be settings
    ApplicationModel::deleteModel();
}

void MainWindow::checkForFirstTimeRunning() {
    QString libraryPath = ApplicationModel::getApplicationModel()->getLibraryDirectory();
    QFileInfo libraryDir(libraryPath);
    if(libraryPath=="" || !libraryDir.exists() || !libraryDir.isDir()) {
        SetupWizard* wiz = new SetupWizard(this);
        if(wiz->exec()==QWizard::Accepted) {
            cout << "Saving library location as: " << ApplicationModel::getApplicationModel()->getLibraryDirectory().toStdString() << endl;
            ApplicationModel::getApplicationModel()->setLibraryDirectory(wiz->getLibraryPath());
        } else {
            cerr << "Library not set. Quitting..." << endl;
            quit = true;
            ApplicationModel::getApplicationModel()->getProperties()->setSaveOnExit(false);
        }
    }
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

    QMenu* settingsMenu = menu->addMenu("&Settings");

    settingsAction = new QAction(QIcon::fromTheme("emblem-system"),"Settings",this);
    settingsAction->setIconVisibleInMenu(true);
    connect(settingsAction,SIGNAL(triggered()),this,SLOT(settingsClicked()));

    settingsMenu->addAction(settingsAction);


    menu->setNativeMenuBar(true);

    mainWidget->addMenuItems(menu);

    menu->show();
}

void MainWindow::importClicked() {
    if(importer->importPhotos(this)) {
        ApplicationModel::getApplicationModel()->getLibraryModel()->libraryHasChanged();
    }
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

bool MainWindow::hasQuit() {
    return quit;
}

void MainWindow::settingsClicked() {
    SetupWizard* wiz = new SetupWizard(this);
    if(wiz->exec()==QWizard::Accepted) {
        cout << "Saving library location as: " << ApplicationModel::getApplicationModel()->getLibraryDirectory().toStdString() << endl;
        ApplicationModel::getApplicationModel()->setLibraryDirectory(wiz->getLibraryPath());
    }
}
