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
        std::cout << "file: " << (info.absoluteFilePath()+info.fileName()).toStdString() << " has suffix: " << suffix.toStdString() <<std::endl;
    }
    std::cout << containsPhotos <<std::endl;
    return containsPhotos;
}

bool EventFolder::isCorrectDepth(QDir dir) {
    std::string libDir = libFolder.toStdString();
    bool canChange = dir.cd("../..");
    if(!canChange) {
        std::cout << "cannot change to ../.." <<std::endl;
        return false;
    }
    std::string backTwo = dir.absolutePath().toStdString();
    if(libDir==backTwo) {
        return true;
    } else {
        std::cout << backTwo <<std::endl;
        return false;
    }
}
