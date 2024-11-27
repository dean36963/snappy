#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QMatrix2x2>
#include <QDateTime>
#include <QFileInfo>
#include <QRegularExpression>
#include <QTransform>

#include <iostream>

#include <exiv2/exiv2.hpp>

using namespace std;

class ImageUtils
{
public:
    ImageUtils();
    ~ImageUtils();
    static QTransform getImageRotation(QString imagePath);
    static QDateTime getImageDate(QString imagePath);
    static QDateTime getImageDateExiv2(QString imagePath);
    static QDateTime getDateTimeFromFilename(QString fileName);
    static void printImageMetadata(QString imagePath);
};

#endif // IMAGEUTILS_H
