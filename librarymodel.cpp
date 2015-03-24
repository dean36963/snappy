#include "librarymodel.h"

LibraryModel::LibraryModel(QString path)
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
                cout << "Other dir: " << eventDir.absolutePath().toStdString() << endl;
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
    if(isYearItem(folder)) {
        if(!treeItems.contains(item)) {
            treeItems.append(item);
            return item;
        }
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


QList<QTreeWidgetItem*> LibraryModel::getTreeItems() {
    return treeItems;
}

