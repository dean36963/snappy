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
    static QString getDirToImportTo(QDateTime dateTime);
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
    static QString padInt(int i);
    bool isDuplicate(QString file1, QString file2);
    void showImportSummary(QWidget *parent);
    void safeCopy(QString from, QString to);
};

#endif // IMPORTER_H
