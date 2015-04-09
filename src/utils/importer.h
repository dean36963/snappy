#ifndef IMPORTER_H
#define IMPORTER_H

#include <QList>
#include <QFile>
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <QDirIterator>
#include <QListIterator>
#include <QProgressDialog>
#include <QDateTime>
#include <Qt>
#include <QApplication>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QRegExp>

#include "src/model/applicationmodel.h"
#include "src/utils/imageutils.h"

#include <unistd.h>
#include <iostream>
#include <sstream>
#include <libexif/exif-data.h>
#include <libexif/exif-byte-order.h>
#include <libexif/exif-data-type.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-log.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>
#include <libexif/exif-mnote-data.h>
#include <libexif/exif-mem.h>

using namespace std;
using namespace Qt;

class Importer
{
public:
    Importer();
    ~Importer();
    int importPhotosFromFolder(QString path, QWidget *parent);
    bool importPhotos(QWidget *parent);
    static void createThumbnail(QString origFile);
private:
    int importSuccess;
    int importFail;
    int importGuessed;
    int importDuplicatesIgnored;
    QList<QString> guessedFiles;
    QList<QString> failedFiles;
    void initialiseSummary();
    void importPhoto(QString filePath);
    QList<QString> findFiles(QString path);
    QProgressDialog *createProgressDialog(QWidget *parent,int files);
    void updateProgressDialog(QProgressDialog *dialog,int index);
    QString getPathToImportTo(QDateTime dateTime, QString filename);
    QString getDirToImportTo(QDateTime dateTime);
    QString padInt(int i);
    bool isDuplicate(QString file1, QString file2);
    void showImportSummary(QWidget *parent);
    void safeCopy(QString from, QString to);
};

#endif // IMPORTER_H
