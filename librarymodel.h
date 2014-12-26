#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

#include "eventfolder.h"

using namespace std;

class LibraryModel
{
public:
    LibraryModel(QString path);
    ~LibraryModel();
private:
    void populateModel(QString path);
};

#endif // LIBRARYMODEL_H
