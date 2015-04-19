#ifndef EVENTFOLDER_H
#define EVENTFOLDER_H

#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <iostream>
#include <QList>

#include <iostream>

using namespace std;

/*
 * EventFolder represents a folder that contains photos.
 * It should be contained below a year folder and a month folder.
 * It can be named or can be a day of month.
*/

class EventFolder
{
public:
    EventFolder(QString libFolder);
    bool isValidEventFolderPath(QDir dir);
    bool containsPhotos(QDir dir);
    bool isCorrectDepth(QDir dir);
    bool isValidPhotoName(QString path);
    QList<QString> getPhotos(QDir dir);
    QList<QString> getEventSubdirectories(QDir dir);
private:
    QString libFolder;
};

#endif // EVENTFOLDER_H
