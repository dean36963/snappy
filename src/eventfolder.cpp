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
    QString upThree = QString("..").append(QDir::separator()).append("..").append(QDir::separator()).append("..");
    bool canChange = dir.cd(upThree);
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

QList<QString> EventFolder::getPhotos(QDir dir) {
    QList<QString> photos = QList<QString>();
        dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);
        QDirIterator it(dir);
        while(it.hasNext()) {
            QString file = it.next();
            if(isValidPhotoName(file)) {
                photos.append(it.filePath());
            }
        }
    return photos;
}

QList<QString> EventFolder::getEventSubdirectories(QDir dir) {
    QList<QString> eventsFound = QList<QString>();
    dir.setFilter(QDir::NoDotAndDotDot|QDir::Dirs);
    QDirIterator it(dir);
    while(it.hasNext()) {
        QDir subDir(it.next());
        if(isValidEventFolderPath(subDir)) {
            eventsFound.append(subDir.absolutePath());
        } else {
            eventsFound.append(getEventSubdirectories(subDir));
        }
    }
    return eventsFound;
}

bool EventFolder::isValidPhotoName(QString path) {
    QStringList parts = path.split('.');
    QString extension = parts.last();
    //TODO I'm sure more formats will work!
    if(extension.toUpper()=="JPG") {
        return true;
    }
    return false;
}
