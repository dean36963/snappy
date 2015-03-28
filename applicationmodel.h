#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <iostream>
#include <QStandardPaths>
#include <QDir>
#include <string>
#include <QSize>

#include "librarymodel.h"
#include "persistedproperties.h"

class ApplicationModel
{
protected:
    ApplicationModel();
    ~ApplicationModel();
public:
    static ApplicationModel* getApplicationModel();
    static void deleteModel();
    QString getConfigDir();
    QString getMainConfigFile();
    std::string getLibraryDirectory();
    QString getHomeDirectory();
    QString appendPath(std::string path1, std::string path2);
    LibraryModel *getLibraryModel();
    QSize *getPreferredThumbnailSize();
    void setPreferredThumbnailSize(QSize *thumbnailSize);
    PersistedProperties *getProperties();

private:
    static ApplicationModel *instance;
    LibraryModel *libModel;
    QSize *preferredThumbnailSize;
    PersistedProperties *properties;

};

#endif // APPLICATIONMODEL_H
