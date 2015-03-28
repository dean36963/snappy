#include "largephotoview.h"

#include <libexif/exif-data.h>
#include <libexif/exif-byte-order.h>
#include <libexif/exif-data-type.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-log.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>
#include <libexif/exif-mnote-data.h>
#include <libexif/exif-mem.h>

LargePhotoView::LargePhotoView(QString photoPath, QWidget *parent) : QWidget(parent)
{
    this->photoPath = photoPath;
    this->parent = parent;
    label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    label->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    layout = new QGridLayout(this);
    layout->addWidget(label);
    setImage(parent->size());
}

LargePhotoView::~LargePhotoView()
{
    delete label;
    delete layout;
}

void LargePhotoView::setImage(QSize size) {
    QMatrix rotation = QMatrix();
    ExifData* exifData = exif_data_new_from_file(photoPath.toStdString().c_str());
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
    QImage icon(photoPath);
    icon = icon.transformed(rotation);
    label->setPixmap(QPixmap::fromImage(icon).scaled(size,Qt::KeepAspectRatio));
}

void LargePhotoView::resizeEvent(QResizeEvent *) {
    int w = label->width();
    int h = label->height();
    QImage image(photoPath);
    label->setPixmap(QPixmap::fromImage(image.scaled(w,h,Qt::KeepAspectRatio)));
    label->setMinimumSize(200,200);
}
