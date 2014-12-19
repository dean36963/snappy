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
    QProgressDialog *dialog = createProgressDialog(parent,photoList.size());
    QListIterator<QString> it(photoList);
    int i=1;
    while(it.hasNext()) {
        if(dialog->wasCanceled()) {
            //TODO do some undo process
            break;
        }
        QString photoPath = it.next();
        importPhoto(photoPath);
        updateProgressDialog(dialog,i);
        i++;
    }
    dialog->close();
    delete dialog;
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

QProgressDialog* Importer::createProgressDialog(QWidget *parent, int files) {
    QProgressDialog* dialog = new QProgressDialog(parent);
    dialog->setWindowModality(Qt::WindowModal);
    dialog->setWindowTitle("Importing");
    dialog->setMaximum(files);
    updateProgressDialog(dialog,1);
    dialog->show();
    return dialog;
}

void Importer::updateProgressDialog(QProgressDialog *dialog, int index) {
    stringstream ss;
    ss << "Importing " << index << " of " << dialog->maximum();
    QString label = QString::fromLocal8Bit(ss.str().c_str());
    dialog->setLabelText(label);
    dialog->setValue(index);
    QApplication::processEvents();
}

void Importer::importPhoto(QString filePath) {
    ExifData* exifData = exif_data_new_from_file(filePath.toStdString().c_str());
    ExifContent* content = *exifData->ifd;
    ExifEntry* entry = exif_content_get_entry(content,EXIF_TAG_DATE_TIME);
    string dateStringStd = string((const char*)entry->data);
    QString dateString = QString::fromLocal8Bit(dateStringStd.c_str());
    QDateTime datetime = QDateTime::fromString(dateString,ISODate);
    cout << entry->data << " Datetime: " << datetime.toString().toStdString() << " datestring std " << dateStringStd << " datestring: " << dateString.toStdString() << endl;
}
