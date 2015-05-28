#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QList>
#include <QListIterator>
#include <QTreeWidgetItem>
#include <QRegExp>
#include <QDate>

#include "src/eventfolder.h"

using namespace std;

class LibraryModel : public QObject
{
    Q_OBJECT
public:
    LibraryModel(QString path);
    ~LibraryModel();
    QList<QTreeWidgetItem*> getTreeItems();
    QString getSelectedEventPath();
    QList<QString> getPhotosFromPath(QString path);
    QList<QString> getEventsUnderPath(QString path);
    void setSelectedEventPath(QString selectedEventPath);
    void setSelectedEventPath(QTreeWidgetItem *selectedEventPath);
    void setSelectedPhotoPath(QString selectedPhoto);
    QString getSelectedPhotoPath();
    void libraryHasChanged();
    void libraryPathChanged(QString libraryPath);
    QString getFriendlyEventName(QString eventPath);
    bool isNamedEvent(QString path);
    QString getEventDate(QString path);
    QDate getEventDateTime(QString path);

    bool isEventItem(QString path);



    enum SELECTION_TYPE {
        FOLDER_VIEW,EVENT_VIEW
    };
    SELECTION_TYPE getSelectedEventType();

private:
    void populateModel();
    void getContainingFolders();
    bool isYearItem(QString path);
    bool isMonthItem(QString path);

    void createFolderItems();
    void createEventItems();
    QTreeWidgetItem *createEventFromFolderItem(QTreeWidgetItem *folderItem);

    QString libraryPath;
    QList<QTreeWidgetItem*> treeItems;
    QString selectedEventPath;
    QString selectedPhoto;
    QTreeWidgetItem* rootFolderWidgetItem;
    QTreeWidgetItem* rootEventWidgetItem;
    QList<QTreeWidgetItem *> createFolderItems(QString path);
    SELECTION_TYPE selectedType;

    static const int TREE_ITEM_PATH;
    static const int TREE_ITEM_TYPE;

signals:
    void selectedPhotoChanged(QString selectedPhoto);
    void eventPathChanged(QString eventPath,SELECTION_TYPE eventOrFolder);
    void libraryChanged();
};

#endif // LIBRARYMODEL_H
