#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <iostream>
#include <QStandardPaths>
#include <QDir>
#include <string>

#include "librarymodel.h"

class ApplicationModel
{
protected:
    ApplicationModel();
public:
    static ApplicationModel* getApplicationModel();
    std::string getConfigDir();
    std::string getMainConfigFile();
    std::string getLibraryDirectory();
    QString getHomeDirectory();
    QString appendPath(std::string path1, std::string path2);
    LibraryModel *getLibraryModel();

private:
    static ApplicationModel *instance;
    LibraryModel *libModel;
};

#endif // APPLICATIONMODEL_H
