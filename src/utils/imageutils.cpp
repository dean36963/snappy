#include "imageutils.h"

ImageUtils::ImageUtils()
{

}

ImageUtils::~ImageUtils()
{

}

QMatrix ImageUtils::getImageRotation(QString imagePath) {
    QMatrix rotation = QMatrix();
    ExifData* exifData = exif_data_new_from_file(imagePath.toStdString().c_str());
    if(exifData!=NULL) {
        ExifContent* content = *exifData->ifd;
        ExifEntry* entry = exif_content_get_entry(content,EXIF_TAG_ORIENTATION);
        if(entry!=NULL) {
            std::string orientation = std::string((const char*)entry->data);
            if(orientation=="Rotated 90 CCW") {
                rotation.rotate(90);
            } else if(orientation=="Rotated 90 CW") {
                rotation.rotate(-90);
            } else if(orientation=="Rotated 180") {
                rotation.rotate(180);
            }
        }
        delete exifData;
        delete content;
        delete entry;
    }
    return rotation;
}

QDateTime ImageUtils::getImageDate(QString imagePath) {
    ExifData* exifData = exif_data_new_from_file(imagePath.toStdString().c_str());
    ExifContent* content = NULL;
    ExifEntry* entry = NULL;
    if(exifData!=NULL) {
        content = *exifData->ifd;
        entry = exif_content_get_entry(content,EXIF_TAG_DATE_TIME);
    }

    QDateTime dateTime;

    if(entry==NULL) {
        //Attempt to parse date from filename. IMG_20140812_143012.jpg for example;
        dateTime = getDateTimeFromFilename(imagePath);
        if(dateTime == QDateTime()) {
            QFileInfo fInfo(imagePath);
            dateTime = fInfo.created();
        }
    } else {
        string dateStringStd = string((const char*)entry->data);
        QString dateString = QString::fromLocal8Bit(dateStringStd.c_str());
        dateTime = QDateTime::fromString(dateString,Qt::ISODate);
    }
    return dateTime;
}

QDateTime ImageUtils::getDateTimeFromFilename(QString fileName) {
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
