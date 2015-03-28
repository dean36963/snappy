#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

#include <QMatrix>
#include <libexif/exif-data.h>
#include <libexif/exif-byte-order.h>
#include <libexif/exif-data-type.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-log.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>
#include <libexif/exif-mnote-data.h>
#include <libexif/exif-mem.h>


class ImageUtils
{
public:
    ImageUtils();
    ~ImageUtils();
    static QMatrix getImageRotation(QString imagePath);
};

#endif // IMAGEUTILS_H
