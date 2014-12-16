#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <iostream>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

#include "librarymodel.h"
#include "applicationmodel.h"
#include "eventfolder.h"

using namespace std;

class LibraryModel
{
public:
    LibraryModel();
private:
    void populateModel();
};

#endif // LIBRARYMODEL_H
