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
    QString newPath = QDir::toNativeSeparators(containingDir.absolutePath().append(QDir::separator())
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

bool LibraryUtils::mergeEvents(QString newName, QList<QString> eventPathList) {
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    if(eventPathList.size()<=1) {
        //can't merge one event!
        return false;
    }

    QDate earliestDate = QDate();

    QListIterator<QString> eventPaths(eventPathList);
    while(eventPaths.hasNext()) {
        QString eventPath = eventPaths.next();
        QDate date = libraryModel->getEventDateTime(eventPath);
        if(earliestDate.isNull() || date <= earliestDate) {
           earliestDate = date;
        }
    }

    QString newEventPath(Importer::getDirToImportTo(QDateTime(earliestDate)));
    newEventPath.append("_");
    newEventPath.append(newName);

    QDir newEventDir = QDir(newEventPath);
    if(newEventDir.exists() && !eventPathList.contains(newEventPath)) {
        //Can't merge into an existing folder that you didn't intend to merge.
        return false;
    } else if (!newEventDir.exists()) {
        bool newDir = newEventDir.mkpath(newEventPath);
        if(!newDir) {
            cout << "Can't create directory to merge event." << endl;
            return false;
        }
    }

    eventPaths.toFront();
    while(eventPaths.hasNext()) {
        QString eventPath = eventPaths.next();
        QListIterator<QString> photosInEvent(libraryModel->getPhotosFromPath(eventPath));
        while(photosInEvent.hasNext()) {
            QString photoPath = photosInEvent.next();
            QFileInfo photoFile(photoPath);
            QString destinationFile(newEventPath+QDir::separator()+photoFile.fileName());
            bool didItWork = QFile::rename(photoPath,destinationFile);
            if(!didItWork) {
                cout << "Cannot move file: " << photoPath.toStdString() << endl;
            }
        }
    }

    libraryModel->libraryHasChanged();
    return true;
}

void LibraryUtils::renameEventWithPrompt(QString eventPath,QWidget *parent) {
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    QFileInfo info(eventPath);
    QString userInput = info.fileName();
    if(libraryModel->isNamedEvent(eventPath)) {
        userInput = libraryModel->getFriendlyEventName(eventPath);
    }
    QString errorMessage("Select a new name for the event.");
    bool ok = false;
    bool valid = false;
    do {

        userInput = QInputDialog::getText(parent,"Rename Event",errorMessage,
                                                  QLineEdit::Normal,userInput,&ok);
        info.setFile(info.dir().absolutePath().append(QDir::separator()).append(userInput));
        valid = isValidInput(info,userInput,&errorMessage);
    } while (ok && !valid);
    if(ok) {
        LibraryUtils::renameEvent(eventPath,info.fileName());
    }
}

bool LibraryUtils::isValidInput(QFileInfo info, QString userInput, QString *errorMessage) {
    errorMessage->clear();
    if(!LibraryUtils::validName(userInput)) {
        errorMessage->append("Not a valid name. Use alpha-numeric characters, spaces, underscores and dashes only.");
        return false;
    }
    if(info.exists()) {
        errorMessage->append("Event already exists. Use a unique event name.");
        return false;
    }
    return true;
}

