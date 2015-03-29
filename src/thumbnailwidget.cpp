#include "thumbnailwidget.h"

ThumbnailWidget::ThumbnailWidget(QString photoPath, QWidget *parent, int w, int h) : QWidget(parent)
{
    this->photoPath = photoPath;
    layout = new QGridLayout();
    label = new QLabel(this);
    layout->addWidget(label);
    width = w;
    height = h;
    setImage();
    label->setAlignment(Qt::AlignCenter);
    label->setMinimumSize(width,height);

    setLayout(layout);
}

ThumbnailWidget::~ThumbnailWidget()
{
    delete layout;
    delete label;
}


void ThumbnailWidget::setImage() {
    if(!ifThumbExists()) {
        Importer::createThumbnail(photoPath);
    }
    QMatrix rotation = ImageUtils::getImageRotation(photoPath);
    QImage icon(getThumbPath());
    icon = icon.transformed(rotation);
    QSize size(width,height);
    label->setPixmap(QPixmap::fromImage(icon).scaled(size,Qt::KeepAspectRatio));
}

QString ThumbnailWidget::getThumbPath() {
    QFileInfo mainPhotoInfo(photoPath);
    return mainPhotoInfo.dir().absolutePath().append("/.thumbnails/").append(mainPhotoInfo.fileName());
}

bool ThumbnailWidget::ifThumbExists() {
    QFileInfo thumb(getThumbPath());
    if(thumb.exists() && thumb.isFile()) {
        return true;
    }
    return false;
}

void ThumbnailWidget::changeSize(int w, int h) {
    width = w;
    height = h;
    label->setMinimumSize(width,height);
    setImage();
}

QString ThumbnailWidget::getType() {
    return QString("Photo");
}
