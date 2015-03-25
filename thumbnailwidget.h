#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QMatrix>
#include <QPixmap>

#include <string>

#include <libexif/exif-data.h>
#include <libexif/exif-byte-order.h>
#include <libexif/exif-data-type.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-log.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>
#include <libexif/exif-mnote-data.h>
#include <libexif/exif-mem.h>

class ThumbnailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThumbnailWidget(QString photoPath, QWidget *parent = 0);
    ~ThumbnailWidget();

private:
    QString photoPath;
    QGridLayout *layout;
    QLabel *label;

    void setImage();

signals:

public slots:
};

#endif // THUMBNAILWIDGET_H
