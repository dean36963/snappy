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
    QColor greyIsh(42,42,42);
    QPalette pal(palette());
    pal.setColor(QPalette::Background,greyIsh);
    setAutoFillBackground(true);
    setPalette(pal);
    show();
    setImage(parent->size());

    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    connect(model,SIGNAL(selectedPhotoChanged(QString)),this,SLOT(pictureChanged(QString)));
}

LargePhotoView::~LargePhotoView()
{
    delete label;
    delete layout;
}

void LargePhotoView::setImage(QSize size) {
    QMatrix rotation = ImageUtils::getImageRotation(photoPath);
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

void LargePhotoView::pictureChanged(QString newPic) {
    if(newPic=="") {
        return;
    }
    this->photoPath = newPic;
    setImage(parent->size());
}
