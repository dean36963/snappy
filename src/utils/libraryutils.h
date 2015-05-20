#ifndef LIBRARYUTILS_H
#define LIBRARYUTILS_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QRegExp>

#include "src/model/applicationmodel.h"
#include "src/model/librarymodel.h"

class LibraryUtils : public QObject
{
    Q_OBJECT
public:
    explicit LibraryUtils(QObject *parent = 0);
    static bool renameEvent(QString eventPath, QString newName);
    static bool validName(QString name);

signals:

public slots:
};

#endif // LIBRARYUTILS_H
