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
    QString importArea = getPathToImportTo(datetime,filePath);
    if(isDuplicate(filePath,importArea)) {
        importDuplicatesIgnored++;
    } else {
        //safe copy needed as we could still have the filename existing
        //where we are copying to.
        cout << "Would import to " << importArea.toStdString() << endl;
    }
}

QString Importer::getPathToImportTo(QDateTime dateTime, QString filepath) {
    ApplicationModel *a = ApplicationModel::getApplicationModel();
    QFileInfo info = QFileInfo(filepath);
    QString libPath = QString::fromLocal8Bit(a->getLibraryDirectory().c_str());
    QString dayString = padInt(dateTime.date().day());
    QString monthString = padInt(dateTime.date().month());
    QString pathToImportTo = libPath.append("/").append(dayString).append("/")
            .append(monthString).append("/").append(info.fileName());
    return pathToImportTo;
}

QString Importer::padInt(int i) {
    QString pad = QString::fromLocal8Bit("0");
    QString padded = QString::number(i);
    if(padded.length()==1) {
        padded.insert(0,pad);
    }
    return padded;
}

bool Importer::isDuplicate(QString file1, QString file2) {
    QFile f1(file1);
    QFile f2(file2);
    if(!f1.exists() || !f2.exists()) {
        return false;
    }
    f1.open(QFile::ReadOnly);
    f2.open(QFile::ReadOnly);
    QString h1 = QString(QCryptographicHash::hash(f1.readAll(),QCryptographicHash::Md5));
    QString h2 = QString(QCryptographicHash::hash(f2.readAll(),QCryptographicHash::Md5));
    return h1.compare(h1,h2) == 0;
}
