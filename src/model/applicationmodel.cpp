#include "applicationmodel.h"

const QString ApplicationModel::LIBRARY_PATH_PROPERTY = "library.path";

ApplicationModel *ApplicationModel::instance = NULL;

ApplicationModel::ApplicationModel() : QObject(0)
{
    preferredThumbnailSize = new QSize(100,100);
    libModel=NULL;
    properties = new PersistedProperties(getMainConfigFile());
}

ApplicationModel::~ApplicationModel() {
    delete properties;
}

ApplicationModel *ApplicationModel::getApplicationModel() {
    if(!instance) {
        instance = new ApplicationModel();
    }
    return instance;
}

QString ApplicationModel::getConfigDir() {
    std::string mainConfigPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).toStdString();
    QString path = appendPath(mainConfigPath,"snappy");
    QDir dir(path);
    if(!dir.exists()) {
        dir.mkdir(dir.absolutePath());
    }
    return path;
}

QString ApplicationModel::getMainConfigFile() {
    return appendPath(getConfigDir().toStdString(),"config");
}

QString ApplicationModel::appendPath(std::string path1, std::string path2)
{
    QString qPath1 = QString::fromUtf8(path1.c_str());
    QString qPath2 = QString::fromUtf8(path2.c_str());
    QString separator = QString(QDir::separator());
    return QDir::cleanPath(qPath1 + separator + qPath2);
}

QString ApplicationModel::getLibraryDirectory() {
    if(!properties->hasProperty(LIBRARY_PATH_PROPERTY)) {
        return NULL;
    } else {
        return properties->getPropertyValue(LIBRARY_PATH_PROPERTY);
    }
}

QString ApplicationModel::getHomeDirectory() {
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

LibraryModel *ApplicationModel::getLibraryModel() {
    if(libModel==NULL) {
        QString rootDirPath = ApplicationModel::getApplicationModel()->getLibraryDirectory();
        libModel = new LibraryModel(rootDirPath);
    }
    return libModel;
}

QSize *ApplicationModel::getPreferredThumbnailSize() {
    return preferredThumbnailSize;
}

void ApplicationModel::setPreferredThumbnailSize(QSize *thumbnailSize) {
    delete preferredThumbnailSize;
    preferredThumbnailSize = thumbnailSize;
}

PersistedProperties *ApplicationModel::getProperties() {
    return properties;
}

void ApplicationModel::deleteModel() {
    delete instance;
}

void ApplicationModel::setLibraryDirectory(QString libraryDirectory) {
    properties->setProperty(LIBRARY_PATH_PROPERTY,libraryDirectory);
    properties->saveProperties();
    getLibraryModel()->libraryPathChanged(libraryDirectory);
}

void ApplicationModel::requestFullscreen(QWidget* widget) {
    emit widgetRequestedFullscreen(widget);
}
