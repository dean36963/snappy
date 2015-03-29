#ifndef PERSISTEDPROPERTIES_H
#define PERSISTEDPROPERTIES_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QDir>
#include <QRegularExpression>

#include <iostream>

using namespace std;

class PersistedProperties
{
public:
    PersistedProperties(QString savePath);
    ~PersistedProperties();
    void setProperty(QString property,QString value);
    bool hasProperty(QString property);
    QString getPropertyValue(QString property);
    void saveProperties();
    void setSaveOnExit(bool saveOnExit);
private:
    QString savePath;
    QMap<QString,QString> *map;
    void readProperties();
    bool saveOnExit;
};

#endif // PERSISTEDPROPERTIES_H
