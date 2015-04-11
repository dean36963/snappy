#include "largephotowidget.h"

#include <libexif/exif-data.h>
#include <libexif/exif-byte-order.h>
#include <libexif/exif-data-type.h>
#include <libexif/exif-ifd.h>
#include <libexif/exif-log.h>
#include <libexif/exif-tag.h>
#include <libexif/exif-content.h>
#include <libexif/exif-mnote-data.h>
#include <libexif/exif-mem.h>

LargePhotoWidget::LargePhotoWidget(QString photoPath, QWidget *parent) : QWidget(parent)
{
    this->photoPath = photoPath;
    this->parent = parent;
    image=NULL;
    zoomArea=NULL;
    zoomLevel=1.0;
    label = new QLabel(this);
    setImage(parent->size());
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
    resetZoom();

    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    connect(model,SIGNAL(selectedPhotoChanged(QString)),this,SLOT(pictureChanged(QString)));
}

LargePhotoWidget::~LargePhotoWidget()
{
    delete label;
    delete layout;
    delete image;
    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    disconnect(model,SIGNAL(selectedPhotoChanged(QString)),this,SLOT(pictureChanged(QString)));
}

void LargePhotoWidget::setImage(QSize size) {
    QMatrix rotation = ImageUtils::getImageRotation(photoPath);
    QImage rawImage(photoPath);
    rawImage = rawImage.transformed(rotation);
    QPixmap pixmap = QPixmap::fromImage(rawImage).scaled(size,Qt::KeepAspectRatio);
    label->setPixmap(pixmap);
    image = new QImage(rawImage);
}

void LargePhotoWidget::resizeEvent(QResizeEvent *) {
    int w = label->width();
    int h = label->height();
    if(image==NULL) {
        cout << "Resize event before image is read" << endl;
        setImage(QSize(w,h));
    }
    QImage icon(*image);
    label->setPixmap(QPixmap::fromImage(icon).scaled(w,h,Qt::KeepAspectRatio));
    label->setMinimumSize(200,200);
    resetZoom();
}

void LargePhotoWidget::pictureChanged(QString newPic) {
    if(newPic=="") {
        return;
    }
    this->photoPath = newPic;
    setImage(parent->size());
    resetZoom();
}

void LargePhotoWidget::wheelEvent(QWheelEvent *e) {
    if(e->delta() > 0) {
        increaseZoom();
    } else {
        decreaseZoom();
    }
    QWidget::wheelEvent(e);
}

void LargePhotoWidget::resetZoom() {
    checkZoom();
    zoomArea = new QRect(0,0,label->size().width(),label->size().height());
    zoomLevel = 1.0;
}

void LargePhotoWidget::checkZoom() {
    if(zoomArea!=NULL) {
        delete zoomArea;
    }
}

void LargePhotoWidget::increaseZoom() {
    zoomLevel += 0.1*zoomLevel;
    if(zoomLevel>10.0) zoomLevel=10.0;
    drawZoomedState();
}

void LargePhotoWidget::decreaseZoom() {
    zoomLevel -= 0.1*zoomLevel;
    if(zoomLevel<1.0) zoomLevel=1.0;
    drawZoomedState();
}


void LargePhotoWidget::drawZoomedState() {
    int w = label->width();
    int h = label->height();

    QSize newSize(zoomLevel*w,zoomLevel*h);
    QImage scaledImage = image->scaled(newSize,Qt::KeepAspectRatio);

    QRect imageSizeNow(0,0,scaledImage.size().width(),scaledImage.size().height());
    QPoint midPointOfImage = getMidPoint(imageSizeNow);
    QRect zoomArea(midPointOfImage.x()-0.5*w,midPointOfImage.y()-0.5*h,
                   w,h);

    cout << "Image size is: " << scaledImage.size().width() << "," << scaledImage.size().height() << endl;
    QImage scaledCroppedImage = scaledImage.copy(zoomArea);
    label->setPixmap(QPixmap::fromImage(scaledCroppedImage));
}

QPoint LargePhotoWidget::getMidPoint(QRect input) {
    int x1=0,y1=0,x2=0,y2=0;
    input.getCoords(&x1,&y1,&x2,&y2);
    int midX = 0.5*(x1+x2);
    int midY = 0.5*(y1+y2);
    return QPoint(midX,midY);
}

QString LargePhotoWidget::getImagePath() {
    return photoPath;
}
