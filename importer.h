#ifndef IMPORTER_H
#define IMPORTER_H

#include <QList>
#include <QString>
#include <QWidget>
#include <QFileDialog>
#include "applicationmodel.h"

class Importer
{
public:
    Importer();
    ~Importer();
    void importPhotosFromFolder(QString path, QWidget parent);
    void importPhotos(QWidget *parent);
private:
    int importSuccess;
    int importFail;
    int importGuessed;
    int importDuplicatesIgnored;
    QList<QString> guessedFiles;
    QList<QString> failedFiles;
    void initialiseSummary();
};

#endif // IMPORTER_H
