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

void Importer::importPhotosFromFolder(QString path, QWidget parent) {

}

void Importer::importPhotos(QWidget *parent) {
    QString caption = QString::fromUtf8("Select a folder to import from");
    QString importDir = QFileDialog::getExistingDirectory(parent,caption);
    //,ApplicationModel::getApplicationModel()->getHomeDirectory());

}
