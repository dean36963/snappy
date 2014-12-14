#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <iostream>
#include <QStandardPaths>
#include <QDir>
#include <string>

using namespace std;

class ApplicationModel
{
protected:
    ApplicationModel();
public:
    static ApplicationModel* getApplicationModel();
    std::string getConfigDir();
    std::string getMainConfigFile();
    QString appendPath(std::string path1, std::string path2);

private:
    static ApplicationModel *instance;
};

#endif // APPLICATIONMODEL_H
