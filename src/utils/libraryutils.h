#ifndef LIBRARYUTILS_H
#define LIBRARYUTILS_H

#include <iostream>

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QRegularExpression>
#include <QInputDialog>
#include <QList>
#include <QDateTime>

#include "src/model/applicationmodel.h"
#include "src/model/librarymodel.h"
#include "src/utils/importer.h"

using namespace std;

class LibraryUtils : public QObject
{
    Q_OBJECT
public:
    explicit LibraryUtils(QObject *parent = 0);
    static bool renameEvent(QString eventPath, QString newName);
    static bool validName(QString name);
    static bool mergeEvents(QString newName, QList<QString> eventPaths);
    static bool getEarliestEventDate(QList<QString> eventPaths);
    static void renameEventWithPrompt(QString eventPath, QWidget *parent);
    static bool isValidInput(QFileInfo info, QString userInput, QString *errorMessage);

signals:

public slots:
};

#endif // LIBRARYUTILS_H
