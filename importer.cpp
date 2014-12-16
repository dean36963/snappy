#include "importer.h"

Importer::Importer()
{
}

Importer::~Importer() {

}

void Importer::initialiseSummary() {
    importSuccess = 0;
    importFail = 0;
    importGuessed = 0;
    importDuplicatesIgnored =0;
    guessedFiles = QList<QString>();
    failedFiles = QList<QString>();
}

void Importer::importPhotosFromFolder(QString path, QWidget *parent) {
    initialiseSummary();
    QList<QString> photoList = findFiles(path);
    cout << "Got " << photoList.size() << " photos" << endl;
}

void Importer::importPhotos(QWidget *parent) {
    QString caption = QString::fromUtf8("Select a folder to import from");
    QString importDir = QFileDialog::getExistingDirectory(parent,caption,ApplicationModel::getApplicationModel()->getHomeDirectory());
    if(importDir=="") {
        return;
    }
    importPhotosFromFolder(importDir,parent);
}

QList<QString> Importer::findFiles(QString path) {
    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot|QDir::Files);
    QDirIterator iter(dir,QDirIterator::Subdirectories);
    QList<QString> photos = QList<QString>();
    while(iter.hasNext()) {
        iter.next();
        QFileInfo info = iter.fileInfo();
        if(info.completeSuffix().toLower() == QString::fromUtf8("jpg")) {
            photos.append(iter.filePath());
        }
    }
    return photos;
}
