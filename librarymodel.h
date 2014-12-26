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

using namespace std;

class LibraryModel
{
public:
    LibraryModel(QString path);
    ~LibraryModel();
    QList<QTreeWidgetItem*> getTreeItems();
private:
    void populateModel();
    void getContainingFolders();
    void createTreeItems();
    bool isRootItem(QString path);
    QString libraryPath;
    QList<QString> eventFolders;
    QList<QString> containingFolders;
    QList<QTreeWidgetItem*> treeItems;
};

#endif // LIBRARYMODEL_H
