#include "largephotowidget.h"

LargePhotoWidget::LargePhotoWidget(QString photoPath, QWidget *parent) : QWidget(parent)
{
    this->photoPath = photoPath;
    this->parent = parent;
    image=NULL;
    zoomArea=NULL;
    zoomLevel=1.0;
    lastPoint=NULL;
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
    if(lastPoint!=NULL) {
        delete lastPoint;
    }
    if(imageForPanning!=NULL) {
        delete imageForPanning;
    }
}

void LargePhotoWidget::setImage(QSize size) {
    QTransform rotation = ImageUtils::getImageRotation(photoPath);
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

void LargePhotoWidget::drawPannedState() {
    int w = label->width();
    int h = label->height();

    QSize newSize(zoomLevel*w,zoomLevel*h);
    if(imageForPanning==NULL) {
        imageForPanning = new QImage(image->scaled(newSize,Qt::KeepAspectRatio));
    }
    QImage scaledCroppedImage = imageForPanning->copy(*zoomArea);
    label->setPixmap(QPixmap::fromImage(scaledCroppedImage));
}

void LargePhotoWidget::drawZoomedState() {
    int w = label->width();
    int h = label->height();

    QSize newSize(zoomLevel*w,zoomLevel*h);
    QImage scaledImage = image->scaled(newSize,Qt::KeepAspectRatio);
    double oldWidth = 0.0;
    double oldHeight = 0.0;
    if(imageForPanning!=NULL) {
        oldWidth = imageForPanning->width();
        oldHeight = imageForPanning->height();
        delete imageForPanning;
    }
    imageForPanning = new QImage(image->scaled(newSize,Qt::KeepAspectRatio));
    double newWidth = imageForPanning->width();
    double newHeight = imageForPanning->height();


    QRect imageSizeNow(0,0,scaledImage.size().width(),scaledImage.size().height());
    QPoint midPointOfImage = getMidPoint(imageSizeNow);

    if(zoomArea==NULL || oldHeight == 0.0) {
        zoomArea = new QRect(midPointOfImage.x()-0.5*w,midPointOfImage.y()-0.5*h,w,h);
    } else {
        zoomArea->translate(0.5*(newWidth-oldWidth),0.5*(newHeight-oldHeight));
        zoomArea->setWidth(w);
        zoomArea->setHeight(h);
    }

    //Zoom in checks!
    if (zoomArea->width() > scaledImage.width()) {
        zoomArea->setLeft(0);
        zoomArea->setWidth(scaledImage.width());
    }
    if (zoomArea->height() > scaledImage.height()) {
        zoomArea->setTop(0);
        zoomArea->setHeight(scaledImage.height());
    }
    //Zoom out checks
    QRect imageRect = scaledImage.rect();
    if (zoomArea->bottom() > imageRect.bottom()) {
        double diff = zoomArea->bottom() - imageRect.bottom();
        zoomArea->setTop(zoomArea->top()-diff);
        zoomArea->setBottom(imageRect.bottom());
    }
    if (zoomArea->top() < imageRect.top()) {
        double diff = imageRect.top() - zoomArea->top();
        zoomArea->setBottom(zoomArea->bottom()+diff);
        zoomArea->setTop(imageRect.top());
    }
    if (zoomArea->right() > imageRect.right()) {
        double diff = zoomArea->right() - imageRect.right();
        zoomArea->setLeft(zoomArea->left()-diff);
        zoomArea->setRight(imageRect.right());
    }
    if (zoomArea->left() < imageRect.left()) {
        double diff = imageRect.left() - zoomArea->left();
        zoomArea->setRight(zoomArea->right()+diff);
        zoomArea->setLeft(imageRect.left());
    }

    QImage scaledCroppedImage = scaledImage.copy(*zoomArea);
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

void LargePhotoWidget::mouseMoveEvent(QMouseEvent * event) {
    if(zoomArea==NULL || zoomLevel==1.0) {
        return;
    }
    if(lastPoint!=NULL) {
        QPointF newPos = event->pos();
        double diffX = newPos.x()-lastPoint->x();
        double diffY = newPos.y()-lastPoint->y();
        if(isNewPanStateValid(diffX,diffY))
            zoomArea->translate(-diffX,-diffY);
        delete lastPoint;
    }
    lastPoint = new QPointF(event->pos());
    drawPannedState();
}

void LargePhotoWidget::mouseReleaseEvent(QMouseEvent *) {
    delete lastPoint;
    lastPoint=NULL;
}

bool LargePhotoWidget::isNewPanStateValid(double diffX, double diffY) {
    QRect newArea = QRect(*zoomArea);
    newArea.translate(-diffX,-diffY);
    if(imageForPanning->rect().contains(newArea)) {
        return true;
    } else {
        return false;
    }
}

void LargePhotoWidget::mouseDoubleClickEvent(QMouseEvent * event) {
    QWidget::mouseDoubleClickEvent(event);
    emit doubleClicked();
}
