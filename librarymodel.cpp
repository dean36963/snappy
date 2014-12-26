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
    QListIterator<QString> containingFoldersIt(containingFolders);
    while(containingFoldersIt.hasNext()) {
        QString folder = containingFoldersIt.next();
        QFileInfo dir(folder);
        if(isRootItem(folder)) {
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0,dir.baseName());
            treeItems.append(item);
        }
    }
}

bool LibraryModel::isRootItem(QString path) {
    QDir dir(path);
    dir.cd("..");
    if(dir.absolutePath()==libraryPath) {
        return true;
    } else {
        return false;
    }
}


QList<QTreeWidgetItem*> LibraryModel::getTreeItems() {
    return treeItems;
}
