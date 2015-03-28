#include "persistedproperties.h"

PersistedProperties::PersistedProperties(QString savePath)
{
    this->savePath = savePath;
    map = new QMap<QString,QString>();
    readProperties();
}

PersistedProperties::~PersistedProperties()
{
    saveProperties();
    delete map;
}

void PersistedProperties::setProperty(QString property,QString value) {
    (*map)[property] = value;
}

bool PersistedProperties::hasProperty(QString property) {
    if(map->contains(property)) {
        return true;
    }
    return false;
}

QString PersistedProperties::getPropertyValue(QString property) {
    return (*map)[property];
}

void PersistedProperties::saveProperties() {
    QFile file(savePath);
    if (file.open(QFile::WriteOnly)) {
        QListIterator<QString> it = map->keys();
        while(it.hasNext()) {
            QString key = it.next();
            QString value = (*map)[key];
            QString line = key + "=" + value + "\n";
            file.write(line.toLocal8Bit());
        }
    } else {
        cerr << "Error persisting preferences." << endl;
    }
    file.close();
}

void PersistedProperties::readProperties() {
    QFile file(savePath);
    if (file.open(QFile::ReadOnly)) {
        char buf[1024];
        qint64 lineLength = file.readLine(buf, sizeof(buf));
        if (lineLength != -1) {
            QString line(buf);
            QStringList keyValue = line.split(QRegularExpression("="));
            if(keyValue.size()==2) {
                (*map)[keyValue.at(0)] = keyValue.at(1);
                //cout << "Read in: " << keyValue.at(0).toStdString() << " equals: " << keyValue.at(1).toStdString() << endl;
            }
        }
    } else {
        cerr << "Couldn't restore preferences." << endl;
    }
    file.close();
}
