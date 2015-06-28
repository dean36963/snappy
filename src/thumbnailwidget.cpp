#include "thumbnailwidget.h"

ThumbnailWidget::ThumbnailWidget(QString photoPath, QWidget *parent, int w, int h) : QWidget(parent)
{
    this->photoPath = photoPath;
    layout = new QGridLayout();
    thumbnail = new QLabel(this);
    layout->addWidget(thumbnail,0,0);
    width = w;
    height = h;
    setType();
    setImage();
    setDetailLabel();
    thumbnail->setAlignment(Qt::AlignCenter);
    thumbnail->setMinimumSize(width,height);
    detailLabel = NULL;

    setLayout(layout);
}

ThumbnailWidget::~ThumbnailWidget()
{
    delete layout;
    delete thumbnail;
    if(detailLabel!=NULL) {
        delete detailLabel;
    }
}

void ThumbnailWidget::setDetailLabel() {
    if(type=="Photo") {
        return;
    } else if (type=="Event") {
        detailLabel = new QLabel();
        LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
        detailLabel->setText(model->getFriendlyEventName(photoPath));
        detailLabel->setAlignment(Qt::AlignCenter);
        QPalette pal = detailLabel->palette();
        pal.setColor(QPalette::Text,QColor(255,255,255));
        detailLabel->setPalette(pal);
        layout->addWidget(detailLabel,1,0);
    }
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
        thumbnail->setPixmap(QPixmap::fromImage(icon).scaled(size,Qt::KeepAspectRatio));
    } else if(type=="Event") {
        QList<QString> photos = ApplicationModel::getApplicationModel()->getLibraryModel()->getPhotosFromPath(photoPath);
        if(!photos.isEmpty()) {
            QMatrix rotation = ImageUtils::getImageRotation(photos.first());
            QFile firstImageThumbnail(getThumbPath(photos.first()));
            if(!firstImageThumbnail.exists()) {
                Importer::createThumbnail(photos.first());
            }
            QImage icon(getThumbPath(photos.first()));
            icon = icon.transformed(rotation);
            QSize size(width,height);
            thumbnail->setPixmap(roundCorners(icon,size));
        } else {
            cout << "Cannot find photos for this event" << endl;
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
    return mainPhotoInfo.dir().absolutePath().append(QDir::separator()).append(".thumbnails").append(QDir::separator()).append(mainPhotoInfo.fileName());
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
    thumbnail->setMinimumSize(width,height);
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
