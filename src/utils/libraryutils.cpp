#include "libraryutils.h"

LibraryUtils::LibraryUtils(QObject *parent) : QObject(parent) {

}

bool LibraryUtils::renameEvent(QString eventPath, QString newName) {
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    if(!libraryModel->isEventItem(eventPath)) {
        return false;
    }
    if(!validName(newName)) {
        return false;
    }
    QFileInfo info(eventPath);
    QString oldName = info.fileName();
    if(libraryModel->isNamedEvent(eventPath)) {
        oldName = libraryModel->getEventDate(eventPath);
    }
    QDir containingDir = info.dir();
    QString newPath = QDir::toNativeSeparators(containingDir.absolutePath().append("/")
                    .append(oldName).append("_").append(newName));
    QFileInfo newDirInfo(newPath);
    if(newDirInfo.exists()) {
        return false;
    } else {
        QDir dir;
        if(!dir.rename(eventPath,newPath)) {
            return false;
        }
    }

    libraryModel->libraryHasChanged();

    return true;
}

bool LibraryUtils::validName(QString name) {
    QRegExp namePattern("[A-Za-z0-9_ -]*");
    if(namePattern.exactMatch(name)) {
        return true;
    } else {
        return false;
    }
}
