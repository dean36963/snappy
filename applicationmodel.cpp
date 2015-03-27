#include "applicationmodel.h"

ApplicationModel *ApplicationModel::instance = NULL;

ApplicationModel::ApplicationModel()
{
    preferredThumbnailSize = new QSize(200,200);
    libModel=NULL;
}

ApplicationModel *ApplicationModel::getApplicationModel() {
    if(!instance) {
        instance = new ApplicationModel();
    }
    return instance;
}

std::string ApplicationModel::getConfigDir() {
    std::string mainConfigPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).toStdString();
    return appendPath(mainConfigPath,"snappy").toStdString();
}

std::string ApplicationModel::getMainConfigFile() {
    return appendPath(getConfigDir(),"config").toStdString();
}

QString ApplicationModel::appendPath(std::string path1, std::string path2)
{
    QString qPath1 = QString::fromUtf8(path1.c_str());
    QString qPath2 = QString::fromUtf8(path2.c_str());
    QString separator = QString(QDir::separator());
    return QDir::cleanPath(qPath1 + separator + qPath2);
}

std::string ApplicationModel::getLibraryDirectory() {
    //TODO get actual config
    std::string photoPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation).toStdString();
    return appendPath(photoPath,"snappyPhotos").toStdString();
}

QString ApplicationModel::getHomeDirectory() {
    return QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
}

LibraryModel *ApplicationModel::getLibraryModel() {
    if(libModel==NULL) {
        QString rootDirPath = QString::fromUtf8(ApplicationModel::getApplicationModel()->getLibraryDirectory().c_str());
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
