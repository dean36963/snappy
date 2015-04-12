#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QMatrix>
#include <QDateTime>
#include <QFileInfo>
#include <QRegExp>

#include <string>
#include <iostream>
#include <exiv2/exiv2.hpp>

using namespace std;

class ImageUtils
{
public:
    ImageUtils();
    ~ImageUtils();
    static QMatrix getImageRotation(QString imagePath);
    static QDateTime getImageDate(QString imagePath);
    static QDateTime getImageDateExiv2(QString imagePath);
    static QDateTime getDateTimeFromFilename(QString fileName);
    static void printImageMetadata(QString imagePath);
};

#endif // IMAGEUTILS_H
