#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QMatrix>
#include <QPixmap>
#include <QFileInfo>
#include <QDir>

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

#include "importer.h"

using namespace std;

class ThumbnailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThumbnailWidget(QString photoPath, QWidget *parent = 0, int w = 80, int h = 80);
    ~ThumbnailWidget();

private:
    QString photoPath;
    QGridLayout *layout;
    QLabel *label;

    void setImage();
    QString getThumbPath();
    bool ifThumbExists();
    int width,height;

signals:

public slots:
};

#endif // THUMBNAILWIDGET_H
