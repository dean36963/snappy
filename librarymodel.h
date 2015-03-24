#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QList>
#include <QListIterator>
#include <QTreeWidgetItem>

#include "eventfolder.h"
#include "notifier.h"

using namespace std;

class LibraryModel
{
public:
    LibraryModel(QString path);
    ~LibraryModel();
    QList<QTreeWidgetItem*> getTreeItems();
    Notifier *getNotifier();
    QString getSelectedEventPath();
    void setSelectedEventPath(QString selectedEventPath);
    void setSelectedEventPath(QTreeWidgetItem *selectedEventPath);
private:
    void populateModel();
    void getContainingFolders();
    void createTreeItems();
    bool isYearItem(QString path);
    bool isMonthItem(QString path);
    QTreeWidgetItem* addTreeItem(QString folder);

    QString libraryPath;
    QList<QString> eventFolders;
    QList<QString> containingFolders;
    QList<QTreeWidgetItem*> treeItems;
    QMap<QString, QTreeWidgetItem*> pathToItemMap;
    Notifier *notifier;
    QString selectedEventPath;
};

#endif // LIBRARYMODEL_H
