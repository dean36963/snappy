#include "imageutils.h"

ImageUtils::ImageUtils()
{

}

ImageUtils::~ImageUtils()
{

}

QTransform ImageUtils::getImageRotation(QString imagePath) {
    QTransform rotation = QTransform();

    Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(std::move(imagePath.toStdString().c_str()));
    if(image.get() == 0) {
        return rotation;
    }
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        return rotation;
    }
    QString value;
    Exiv2::ExifKey dateTimeKey("Exif.Image.DateTime");
    Exiv2::ExifData::iterator pos = exifData.findKey(dateTimeKey);
    if(pos != exifData.end()) {
        std::stringstream ss;
        ss << pos->value();
        std::string s = ss.str();
        value = QString::fromStdString(s);
    }

    if(value=="3") {
        rotation.rotate(180);
    } else if(value=="6") {
        rotation.rotate(90);
    } else if(value=="8") {
        rotation.rotate(-90);
    }
    return rotation;
}

QDateTime ImageUtils::getImageDate(QString imagePath) {
    QDateTime dateTime = getImageDateExiv2(imagePath);
    if(dateTime == QDateTime()) {
        dateTime = getDateTimeFromFilename(imagePath);
    }
    if(dateTime == QDateTime()) {
        QFileInfo fInfo(imagePath);
        dateTime = fInfo.created();
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

QDateTime ImageUtils::getImageDateExiv2(QString imagePath) {
    QDateTime dateTime;
    Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(std::move(imagePath.toStdString().c_str()));
    if(image.get() == 0) {
        return dateTime;
    }
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        return dateTime;
    }

    QString dateString;
    Exiv2::ExifKey dateTimeKey("Exif.Image.DateTime");
    Exiv2::ExifData::iterator pos = exifData.findKey(dateTimeKey);
    if(pos != exifData.end()) {
        std::stringstream ss;
        ss << pos->value();
        std::string s = ss.str();
        dateString = QString::fromStdString(s);
    }
    dateTime = QDateTime::fromString(dateString,Qt::ISODate);

    return dateTime;
}

void ImageUtils::printImageMetadata(QString imagePath) {
    Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(std::move(imagePath.toStdString().c_str()));
    if(image.get() == 0) {
        return;
    }
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        return;
    }
    Exiv2::ExifData::const_iterator end = exifData.end();
    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
        const char* tn = i->typeName();
        std::cout << std::setw(44) << std::setfill(' ') << std::left
                  << i->key() << " "
                  << "0x" << std::setw(4) << std::setfill('0') << std::right
                  << std::hex << i->tag() << " "
                  << std::setw(9) << std::setfill(' ') << std::left
                  << (tn ? tn : "Unknown") << " "
                  << std::dec << std::setw(3)
                  << std::setfill(' ') << std::right
                  << i->count() << "  "
                  << std::dec << i->value()
                  << "\n";
    }
}
