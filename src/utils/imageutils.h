#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QMatrix>
#include <QDateTime>
#include <QFileInfo>
#include <QRegExp>

#include <string>
#include <iostream>

#include <libexif/exif-data.h>
#include <libexif/exif-byte-order.h>
#include <libexif/exif-data-type.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-log.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>
#include <libexif/exif-mnote-data.h>
#include <libexif/exif-mem.h>

using namespace std;

class ImageUtils
{
public:
    ImageUtils();
    ~ImageUtils();
    static QMatrix getImageRotation(QString imagePath);
    static QDateTime getImageDate(QString imagePath);
    static QDateTime getDateTimeFromFilename(QString fileName);
};

#endif // IMAGEUTILS_H
