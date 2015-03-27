#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <iostream>
#include <QStandardPaths>
#include <QDir>
#include <string>
#include <QSize>

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
    QSize *getPreferredThumbnailSize();
    void setPreferredThumbnailSize(QSize *thumbnailSize);

private:
    static ApplicationModel *instance;
    LibraryModel *libModel;
    QSize *preferredThumbnailSize;

};

#endif // APPLICATIONMODEL_H
