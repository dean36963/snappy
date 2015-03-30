#include "librarymodel.h"

LibraryModel::LibraryModel(QString path) : QObject()
{
    libraryPath = path;
    eventFolders = QList<QString>();
    containingFolders = QList<QString>();
    treeItems = QList<QTreeWidgetItem*>();
    populateModel();
}

LibraryModel::~LibraryModel() {
    QListIterator<QTreeWidgetItem*> iter(treeItems);
    while(iter.hasNext()) {
        QTreeWidgetItem* item = iter.next();
        if(item!=NULL) {
            delete item;
        }
    }
    treeItems.clear();
}

void LibraryModel::populateModel() {
    pathToItemMap.clear();
    treeItems.clear();
    containingFolders.clear();
    eventFolders.clear();
    QDir rootDir = QDir(libraryPath);
    rootDir.setFilter(QDir::NoDotAndDotDot|QDir::Dirs);
    if(!rootDir.exists()) {
        cout << "Library path doesn't exist, creating..." << endl;
        if(!rootDir.mkdir(libraryPath)) {
            cerr << "Could not create library path." <<endl;
            return;
        }
    }
    QDirIterator dirIter(rootDir,QDirIterator::Subdirectories);
    while(dirIter.hasNext()) {
        dirIter.next();
        QFileInfo info(dirIter.filePath());
        EventFolder ev(libraryPath);
        if(ev.isValidEventFolderPath(info.absoluteFilePath())) {
            cout << info.absoluteFilePath().toStdString() << " is an event folder" <<endl;
            eventFolders.append(info.absoluteFilePath());
        }
    }
    getContainingFolders();
    createTreeItems();
}

void LibraryModel::getContainingFolders() {
    QListIterator<QString> events(eventFolders);
    while(events.hasNext()) {
        QString event = events.next();
        QDir eventDir(event);
        while(true) {
            eventDir.cd("..");
            if(eventDir.absolutePath()==libraryPath) {
                break;
            } else if(containingFolders.contains(eventDir.absolutePath())) {
               //We have already done the next folders too.
               break;
            } else {
                containingFolders.append(eventDir.absolutePath());
            }
        }
    }
}

void LibraryModel::createTreeItems() {
    QListIterator<QString> eventFoldersIt(eventFolders);
    while(eventFoldersIt.hasNext()) {
        QString folder = eventFoldersIt.next();
        addTreeItem(folder);
    }
}

QTreeWidgetItem* LibraryModel::addTreeItem(QString folder) {
    QFileInfo dirInfo(folder);
    QTreeWidgetItem *item;
    if(pathToItemMap.keys().contains(folder)) {
        item = pathToItemMap.value(folder);
        return item;
    } else {
        item = new QTreeWidgetItem();
        pathToItemMap[folder] = item;
    }
    item->setText(0,dirInfo.baseName());
    if(isEventItem(folder)) {
        item->setIcon(0,QIcon::fromTheme("folder-images"));
    } else {
        item->setIcon(0,QIcon::fromTheme("folder"));
    }
    if(isYearItem(folder)) {
        treeItems.append(item);
        return item;
    } else {
        QDir dir(folder);
        dir.cd("..");
        QTreeWidgetItem *subItem = addTreeItem(dir.absolutePath());
        subItem->addChild(item);
        return item;
    }
}

bool LibraryModel::isYearItem(QString path) {
    QDir dir(path);
    dir.cd("..");
    if(dir.absolutePath()==libraryPath) {
        return true;
    } else {
        return false;
    }
}

bool LibraryModel::isMonthItem(QString path) {
    QDir dir(path);
    dir.cd("../..");
    if(dir.absolutePath()==libraryPath) {
        return true;
    } else {
        return false;
    }
}

bool LibraryModel::isEventItem(QString path) {
    EventFolder ev(libraryPath);
    QDir pathDir(path);
    if(ev.isValidEventFolderPath(pathDir)) {
        return true;
    } else {
        return false;
    }
}


QList<QTreeWidgetItem*> LibraryModel::getTreeItems() {
    return treeItems;
}

QString LibraryModel::getSelectedEventPath() {
    return selectedEventPath;
}

void LibraryModel::setSelectedEventPath(QString selectedEventPath) {
    this->selectedEventPath = selectedEventPath;
    emit eventPathChanged(selectedEventPath);
}

void LibraryModel::setSelectedEventPath(QTreeWidgetItem *item) {
    selectedEventPath = pathToItemMap.key(item);
    emit eventPathChanged(selectedEventPath);
}

QList<QString> LibraryModel::getPhotosFromPath(QString path) {
    EventFolder ev(libraryPath);
    QDir pathDir(path);
    if(ev.isValidEventFolderPath(pathDir)) {
        return ev.getPhotos(pathDir);
    }
    return QList<QString>();
}

QList<QString> LibraryModel::getEventsUnderPath(QString path) {
    EventFolder ev(libraryPath);
    QDir pathDir(path);
    return ev.getEventSubdirectories(pathDir);
}

void LibraryModel::setSelectedPhotoPath(QString selectedPhoto) {
    this->selectedPhoto = selectedPhoto;
    emit selectedPhotoChanged(selectedPhoto);
}

QString LibraryModel::getSelectedPhotoPath() {
    return selectedPhoto;
}

void LibraryModel::libraryHasChanged() {
    populateModel();
    emit libraryChanged();
}

QString LibraryModel::getFriendlyEventName(QString eventPath) {
    EventFolder ev(libraryPath);
    QDir eventDir(eventPath);
    if(!ev.isValidEventFolderPath(eventDir)) {
        return "";
    }
    QString eventName = eventDir.dirName();
    eventDir.cdUp();
    QString monthName = eventDir.dirName();
    eventDir.cdUp();
    QString yearName = eventDir.dirName();
    return eventName.append("/").append(monthName).append("/").append(yearName);
}
