#ifndef IMPORTER_H
#define IMPORTER_H

#include <QList>
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include <QDirIterator>
#include <QListIterator>
#include <QProgressDialog>
#include "applicationmodel.h"

#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

class Importer
{
public:
    Importer();
    ~Importer();
    void importPhotosFromFolder(QString path, QWidget *parent);
    void importPhotos(QWidget *parent);
private:
    int importSuccess;
    int importFail;
    int importGuessed;
    int importDuplicatesIgnored;
    QList<QString> guessedFiles;
    QList<QString> failedFiles;
    void initialiseSummary();
    QList<QString> findFiles(QString path);
    QProgressDialog *createProgressDialog(QWidget *parent,int files);
    void updateProgressDialog(QProgressDialog *dialog,int index);
};

#endif // IMPORTER_H
