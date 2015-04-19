#include "librarymodel.h"

const int LibraryModel::TREE_ITEM_PATH = 55;
const int LibraryModel::TREE_ITEM_TYPE = 56;

LibraryModel::LibraryModel(QString path) : QObject()
{
    libraryPath = path;
    treeItems = QList<QTreeWidgetItem*>();
    rootEventWidgetItem = NULL;
    rootFolderWidgetItem = NULL;
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
    treeItems.clear();
    if(rootEventWidgetItem==NULL) {
        delete rootEventWidgetItem;
        rootEventWidgetItem = NULL;
    }
    if(rootFolderWidgetItem==NULL) {
        delete rootFolderWidgetItem;
        rootFolderWidgetItem = NULL;
    }

    QDir rootDir = QDir(libraryPath);
    if(!rootDir.exists()) {
        cout << "Library path doesn't exist, creating..." << endl;
        if(!rootDir.mkdir(libraryPath)) {
            cerr << "Could not create library path." <<endl;
            return;
        }
    }

    createFolderItems();
    createEventItems();
}

bool LibraryModel::isYearItem(QString path) {
    QDir dir(path);
    QFileInfo info(dir.absolutePath());
    dir.cd("..");
    if(dir.absolutePath()!=libraryPath) {
        return false;
    }
    QRegExp yearPattern("\\d{4}");
    if(yearPattern.exactMatch(info.baseName())) {
        return true;
    } else {
        return false;
    }
}

bool LibraryModel::isMonthItem(QString path) {
    QDir dir(path);
    QFileInfo info(dir.absolutePath());
    dir.cd("../..");
    if(dir.absolutePath()!=libraryPath) {
        return false;
    }
    QRegExp monthPattern("\\d{2}");
    if(monthPattern.exactMatch(info.baseName())) {
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

LibraryModel::SELECTION_TYPE LibraryModel::getSelectedEventType() {
    return selectedType;
}

void LibraryModel::setSelectedEventPath(QString selectedEventPath) {
    this->selectedEventPath = selectedEventPath;
    EventFolder ev(libraryPath);
    SELECTION_TYPE type;
    if(ev.isValidEventFolderPath(selectedEventPath)) {
        type = EVENT_VIEW;
    } else {
        type = FOLDER_VIEW;
    }
    emit eventPathChanged(selectedEventPath,type);
}

void LibraryModel::setSelectedEventPath(QTreeWidgetItem *item) {
    if(item->data(0,TREE_ITEM_TYPE).toInt()==0) {
        selectedType = FOLDER_VIEW;
    } else {
        selectedType = EVENT_VIEW;
    }
    setSelectedEventPath(item->data(0,TREE_ITEM_PATH).toString());
}

QList<QString> LibraryModel::getPhotosFromPath(QString path) {
    EventFolder ev(libraryPath);
    QDir pathDir(path);
    return ev.getPhotos(pathDir);
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

void LibraryModel::libraryPathChanged(QString libraryPath) {
    this->libraryPath = libraryPath;
    libraryHasChanged();
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

void LibraryModel::createFolderItems() {
    rootFolderWidgetItem = new QTreeWidgetItem();
    rootFolderWidgetItem->setText(0,"Folders");
    rootFolderWidgetItem->setIcon(0,QIcon::fromTheme("folder"));
    rootFolderWidgetItem->setData(0,TREE_ITEM_PATH,QVariant(libraryPath));
    rootFolderWidgetItem->addChildren(createFolderItems(libraryPath));
    treeItems.append(rootFolderWidgetItem);
}

QList<QTreeWidgetItem*> LibraryModel::createFolderItems(QString path) {
    QList<QTreeWidgetItem*> items = QList<QTreeWidgetItem*>();
    QDir thisDir = QDir(path);
    thisDir.setFilter(QDir::NoDotAndDotDot|QDir::Dirs);
    QDirIterator folderIterator(thisDir);
    while(folderIterator.hasNext()) {
        QDir dir = folderIterator.next();
        cout << dir.absolutePath().toStdString() << endl;
        QTreeWidgetItem* dirItem = new QTreeWidgetItem();
        dirItem->setText(0,dir.dirName());
        dirItem->setData(0,TREE_ITEM_PATH,dir.absolutePath());
        QList<QTreeWidgetItem*> subDirs = createFolderItems(dir.absolutePath());
        EventFolder ev(libraryPath);
        if(ev.containsPhotos(dir) && subDirs.length()>0) {
            dirItem->setIcon(0,QIcon::fromTheme("folder-images"));
        } else if(ev.containsPhotos(dir)) {
            dirItem->setIcon(0,QIcon::fromTheme("folder-images"));
        } else {
            dirItem->setIcon(0,QIcon::fromTheme("folder"));
        }
        dirItem->setData(0,TREE_ITEM_TYPE,FOLDER_VIEW);
        dirItem->addChildren(subDirs);
        items.append(dirItem);
    }
    return items;
}

void LibraryModel::createEventItems() {
    //Traverse the folders and work out events that way.
    rootEventWidgetItem = new QTreeWidgetItem();
    rootEventWidgetItem->setText(0,"Events");
    rootEventWidgetItem->setIcon(0,QIcon::fromTheme("image-x-generic"));
    rootEventWidgetItem->setData(0,TREE_ITEM_PATH,QVariant(libraryPath));
    rootEventWidgetItem->setData(0,TREE_ITEM_TYPE,EVENT_VIEW);

    treeItems.append(rootEventWidgetItem);

    for(int yearIndex=0; yearIndex<rootFolderWidgetItem->childCount();yearIndex++) {
        QTreeWidgetItem *yearItem = rootFolderWidgetItem->child(yearIndex);
        if(!isYearItem(yearItem->data(0,TREE_ITEM_PATH).toString())) {
            continue;
        }
        QTreeWidgetItem *eventYearItem = createEventFromFolderItem(yearItem);
        for(int monthIndex=0; monthIndex<yearItem->childCount();monthIndex++) {
            QTreeWidgetItem *monthItem = yearItem->child(monthIndex);
            if(!isMonthItem(monthItem->data(0,TREE_ITEM_PATH).toString())) {
                continue;
            }
            QTreeWidgetItem *eventMonthItem = createEventFromFolderItem(monthItem);
            for(int dateIndex=0; dateIndex<monthItem->childCount();dateIndex++) {
                QTreeWidgetItem *dateItem = monthItem->child(dateIndex);
                if(!isEventItem(dateItem->data(0,TREE_ITEM_PATH).toString())) {
                    continue;
                }
                QTreeWidgetItem *eventDateItem = createEventFromFolderItem(dateItem);
                eventDateItem->setIcon(0,QIcon::fromTheme("folder-images"));
                eventMonthItem->addChild(eventDateItem);
            }
            if(eventMonthItem->childCount()>0) {
                eventYearItem->addChild(eventMonthItem);
            }
        }
        if(eventYearItem->childCount()>0) {
            rootEventWidgetItem->addChild(eventYearItem);
        }
    }
}

QTreeWidgetItem *LibraryModel::createEventFromFolderItem(QTreeWidgetItem *folderItem) {
    QTreeWidgetItem *newItem = new QTreeWidgetItem();
    newItem->setText(0,folderItem->text(0));
    newItem->setData(0,TREE_ITEM_PATH,folderItem->data(0,TREE_ITEM_PATH));
    newItem->setData(0,TREE_ITEM_TYPE,QVariant(EVENT_VIEW));
    newItem->setIcon(0,QIcon::fromTheme("folder"));
    return newItem;
}
