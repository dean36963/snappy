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

int Importer::importPhotosFromFolder(QString path, QWidget *parent) {
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
    showImportSummary(parent);
    return importSuccess;
}

bool Importer::importPhotos(QWidget *parent) {
    QString caption = QString::fromUtf8("Select a folder to import from");
    QString importDir = QFileDialog::getExistingDirectory(parent,caption,ApplicationModel::getApplicationModel()->getHomeDirectory());
    if(importDir=="") {
        return false;
    }
    int numPhotosImported = importPhotosFromFolder(importDir,parent);
    if(numPhotosImported > 0) {
        return true;
    }
    return false;
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
    ExifContent* content = NULL;
    ExifEntry* entry = NULL;
    if(exifData!=NULL) {
        content = *exifData->ifd;
        entry = exif_content_get_entry(content,EXIF_TAG_DATE_TIME);
    }

    QDateTime dateTime;

    if(entry==NULL) {
        cerr << "Cannot find tag on " << filePath.toStdString() << endl;
        //Attempt to parse date from filename. IMG_20140812_143012.jpg for example;
        dateTime = getDateTimeFromFilename(filePath);
        if(dateTime == QDateTime()) {
            //Final resort is creation date from filesystem
            QFileInfo fInfo(filePath);
            dateTime = fInfo.created();
            importGuessed++;
            guessedFiles.append(filePath);
        }

    } else {
        string dateStringStd = string((const char*)entry->data);
        QString dateString = QString::fromLocal8Bit(dateStringStd.c_str());
        dateTime = QDateTime::fromString(dateString,ISODate);
    }
    QString importArea = getDirToImportTo(dateTime);
    QString importFile = getPathToImportTo(dateTime,filePath);
    if(isDuplicate(filePath,importFile)) {
        importDuplicatesIgnored++;
    } else {
        safeCopy(filePath,importArea);
        importSuccess++;
    }
}

QString Importer::getPathToImportTo(QDateTime dateTime, QString filepath) {
    QString dirToImportTo = getDirToImportTo(dateTime);
    QFileInfo info(filepath);
    return dirToImportTo.append("/").append(info.fileName());
}

QString Importer::getDirToImportTo(QDateTime dateTime) {
    ApplicationModel *a = ApplicationModel::getApplicationModel();
    QString libPath = a->getLibraryDirectory();
    QString dayString = padInt(dateTime.date().day());
    QString monthString = padInt(dateTime.date().month());
    QString yearString = QString::number(dateTime.date().year());
    QString pathToImportTo = libPath.append("/").append(yearString).append("/")
            .append(monthString).append("/").append(dayString);
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
    if(!f1.exists()) {
        return false;
    }
    if (!f2.exists()) {
        return false;
    }
    f1.open(QFile::ReadOnly);
    f2.open(QFile::ReadOnly);
    QString h1 = QString(QCryptographicHash::hash(f1.readAll(),QCryptographicHash::Md5));
    QString h2 = QString(QCryptographicHash::hash(f2.readAll(),QCryptographicHash::Md5));
    return h1.compare(h1,h2) == 0;
}

void Importer::showImportSummary(QWidget *parent) {
    QMessageBox messageBox(parent);
    QString txt = QString::fromLocal8Bit("Imported ").append(QString::number(importSuccess)).append(" photos successfully.");
    txt.append("\nFailed to import ").append(QString::number(importFail)).append(" photos.");
    txt.append("\nIgnored ").append(QString::number(importDuplicatesIgnored)).append(" duplicate photos.");
    QString details = QString::fromLocal8Bit("");
    if(importFail>0) {
        details.append("Failed to import:\n");
        QListIterator<QString> iter(failedFiles);
        while(iter.hasNext()) {
            QString file = iter.next();
            details.append(file).append("\n");
        }
    }
    if(importGuessed>0) {
        details.append("\nGuessed dates from timestamps (instead of EXIF metadata) for:");
        QListIterator<QString> iter(guessedFiles);
        while(iter.hasNext()) {
            QString file = iter.next();
            details.append(file).append("\n");
        }
    }
    messageBox.setText(txt);
    if(!details.isEmpty()) {
        messageBox.setDetailedText(details);
    }
    messageBox.setWindowTitle(QString::fromLocal8Bit("Import Summary"));
    messageBox.exec();
}

QDateTime Importer::getDateTimeFromFilename(QString fileName) {
    QString dateTimeRegExpStr = QString::fromLocal8Bit("\\d{8}_\\d{6}");
    QRegExp dateTimeRegExp(dateTimeRegExpStr);
    int startPos = dateTimeRegExp.indexIn(fileName);
    if(startPos==-1) {
        return QDateTime();
    }
    QString dateStr = fileName.mid(startPos,dateTimeRegExp.matchedLength());
    cout << "Guessed date <" << dateStr.toStdString() << "> from file: " << fileName.toStdString()<< endl;
    return QDateTime::fromString(dateStr,"yyyyMMdd_HHmmss");
}

void Importer::safeCopy(QString from, QString to) {
    QDir dir(to);
    if(!dir.exists()) {
        cout << "Making dir: " << dir.absolutePath().toStdString() << endl;
        dir.mkpath(dir.absolutePath());
    }
    int duplicateName=1;
    QFileInfo old(from);
    to.append("/").append(old.fileName());
    QString toNew(to);
    while(true) {
        QFile f(toNew);
        if(!f.exists()) {
            break;
        }
        duplicateName++;
        QFileInfo toInfo(to);
        toNew = toInfo.baseName().append("_").append(QString::number(duplicateName)).append(toInfo.completeSuffix());
    }
    QFile::copy(from,toNew);
    createThumbnail(toNew);
    cout << "Copied " << from.toStdString() << " to " << toNew.toStdString() << endl;
}

void Importer::createThumbnail(QString origFile) {
    QFileInfo origInfo(origFile);
    QDir thumbnailDir(origInfo.absoluteDir().absolutePath().append("/.thumbnails"));
    if(!thumbnailDir.exists()) {
        thumbnailDir.mkdir(thumbnailDir.absolutePath());
    }
    QImage origImage(origFile);
    QImage thumbImage = origImage.scaled(200,200,KeepAspectRatio);
    QString thumbFile = thumbnailDir.absolutePath().append("/").append(origInfo.fileName());
    thumbImage.save(thumbFile);
}
