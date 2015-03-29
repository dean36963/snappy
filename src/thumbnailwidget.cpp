#include "thumbnailwidget.h"

ThumbnailWidget::ThumbnailWidget(QString photoPath, QWidget *parent, int w, int h) : QWidget(parent)
{
    this->photoPath = photoPath;
    layout = new QGridLayout();
    label = new QLabel(this);
    layout->addWidget(label);
    width = w;
    height = h;
    setType();
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
    if(type=="Photo") {
        if(!ifThumbExists()) {
            Importer::createThumbnail(photoPath);
        }
        QMatrix rotation = ImageUtils::getImageRotation(photoPath);
        QImage icon(getThumbPath(photoPath));
        icon = icon.transformed(rotation);
        QSize size(width,height);
        label->setPixmap(QPixmap::fromImage(icon).scaled(size,Qt::KeepAspectRatio));
    } else if(type=="Event") {
        QList<QString> photos = ApplicationModel::getApplicationModel()->getLibraryModel()->getPhotosFromPath(photoPath);
        if(!photos.isEmpty()) {
            QMatrix rotation = ImageUtils::getImageRotation(photos.first());
            QImage icon(getThumbPath(photos.first()));
            icon = icon.transformed(rotation);
            QSize size(width,height);
            label->setPixmap(roundCorners(icon,size));
        }
    }
}

QPixmap ThumbnailWidget::roundCorners(QImage icon,QSize size) {
    QImage maskImage(":/res/eventMask.png");
    maskImage = maskImage.scaled(size,Qt::IgnoreAspectRatio);
    icon = icon.scaled(maskImage.size(),Qt::KeepAspectRatioByExpanding);
//    cout << "Mask size: <" << maskImage.size().width() << "," << maskImage.size().height() << "> "
//         << " and icon size: <" << icon.size().width() << "," << icon.size().height() << "> " << endl;
    QRect properSize = QRect(0,0,maskImage.size().width(),maskImage.size().height());
    icon = icon.copy(properSize);
    icon.setAlphaChannel(maskImage.alphaChannel());
    return QPixmap::fromImage(icon);
}

QString ThumbnailWidget::getThumbPath(QString path) {
    QFileInfo mainPhotoInfo(path);
    return mainPhotoInfo.dir().absolutePath().append("/.thumbnails/").append(mainPhotoInfo.fileName());
}

bool ThumbnailWidget::ifThumbExists() {
    QFileInfo thumb(getThumbPath(photoPath));
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
    return type;
}

void ThumbnailWidget::setType() {
    EventFolder ev(ApplicationModel::getApplicationModel()->getLibraryDirectory());
    if(ifPhotoExists()) {
        type = QString("Photo");
    }
    QDir dir(photoPath);
    if(ev.isValidEventFolderPath(dir)) {
        type = QString("Event");
    }
}

bool ThumbnailWidget::ifPhotoExists() {
    QFileInfo photo(photoPath);
    if(photo.exists() && photo.isFile()) {
        return true;
    }
    return false;
}
