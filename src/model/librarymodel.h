#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QList>
#include <QListIterator>
#include <QTreeWidgetItem>

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
    QList<QString> *getPhotosFromPath(QString path);
    void setSelectedEventPath(QString selectedEventPath);
    void setSelectedEventPath(QTreeWidgetItem *selectedEventPath);
    void setSelectedPhotoPath(QString selectedPhoto);
    QString getSelectedPhotoPath();
private:
    void populateModel();
    void getContainingFolders();
    void createTreeItems();
    bool isYearItem(QString path);
    bool isMonthItem(QString path);
    bool isEventItem(QString path);
    QTreeWidgetItem* addTreeItem(QString folder);

    QString libraryPath;
    QList<QString> eventFolders;
    QList<QString> containingFolders;
    QList<QTreeWidgetItem*> treeItems;
    QMap<QString, QTreeWidgetItem*> pathToItemMap;
    QString selectedEventPath;
    QString selectedPhoto;

signals:
    void selectedPhotoChanged(QString selectedPhoto);
    void eventPathChanged(QString eventPath);
};

#endif // LIBRARYMODEL_H
