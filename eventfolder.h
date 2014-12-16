#ifndef EVENTFOLDER_H
#define EVENTFOLDER_H

#include <QDirIterator>
#include <QDir>
#include <QFileInfo>
#include <iostream>

#include "applicationmodel.h"

/*
 * EventFolder represents a folder that contains photos.
 * It should be contained below a year folder and a month folder.
 * It can be named or can be a day of month.
*/

class EventFolder
{
public:
    EventFolder();
    static bool isValidEventFolderPath(QDir dir);
    static bool containsPhotos(QDir dir);
    static bool isCorrectDepth(QDir dir);
};

#endif // EVENTFOLDER_H
