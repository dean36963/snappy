#include "eventfolder.h"

EventFolder::EventFolder(QString libFolder)
{
    this->libFolder = libFolder;
}

bool EventFolder::isValidEventFolderPath(QDir dir) {
    return containsPhotos(dir) && isCorrectDepth(dir);
}

bool EventFolder::containsPhotos(QDir dir) {
    QDirIterator it(dir);
    dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);
    bool containsPhotos = false;
    while(it.hasNext()) {
        it.next();
        QFileInfo info = it.fileInfo();
        QString suffix = info.completeSuffix();
        //TODO, something better here. im sure there is
        //a supported formats enum, but cant find it
        if(suffix.toLower().compare("jpg")==0) {
            containsPhotos=true;
            break;
        }
    }
    return containsPhotos;
}

bool EventFolder::isCorrectDepth(QDir dir) {
    std::string libDir = libFolder.toStdString();
    bool canChange = dir.cd("../../..");
    if(!canChange) {
        return false;
    }
    std::string backTwo = dir.absolutePath().toStdString();
    if(libDir==backTwo) {
        return true;
    } else {
        return false;
    }
}
