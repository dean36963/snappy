#include "largephotoview.h"

LargePhotoView::LargePhotoView(QString path, QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    photoWidget = new LargePhotoWidget(path,this);
    layout->addWidget(photoWidget,1,0);

    toolbar = new QToolBar("",this);
    layout->addWidget(toolbar,2,0);
    setLayout(layout);

    toolbar->addAction(QIcon::fromTheme("folder"),"Open in file manager",this,SLOT(openInFileManager()));
    toolbar->addAction(QIcon::fromTheme("object-rotate-left"),"Rotate anti-clockwise",this,SLOT(rotatePhotoAntiClockwise()));
    toolbar->addAction(QIcon::fromTheme("object-rotate-right"),"Rotate clockwise",this,SLOT(rotatePhotoClockwise()));
}

LargePhotoView::~LargePhotoView()
{
    delete photoWidget;
    delete layout;
    delete toolbar;
}


void LargePhotoView::openInFileManager() {
    QString photoPath = photoWidget->getImagePath();
    QFileInfo info(photoPath);
    QDir containingDir = info.dir();

    QDesktopServices::openUrl("file://"+containingDir.absolutePath());
}

void LargePhotoView::rotatePhotoAntiClockwise() {
    rotatePhoto(-90);
}

void LargePhotoView::rotatePhotoClockwise() {
    rotatePhoto(90);
}

void LargePhotoView::rotatePhoto(int rotation) {
    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    QImage image = QImage(model->getSelectedPhotoPath());
    QMatrix currentRotation = ImageUtils::getImageRotation(model->getSelectedPhotoPath());
    QImage currentImage = image.transformed(currentRotation,Qt::SmoothTransformation);

    QMatrix antiClockwise = QMatrix();
    antiClockwise.rotate(rotation);

    QImage antiClockwiseImage = currentImage.transformed(antiClockwise,Qt::SmoothTransformation);
    antiClockwiseImage.save(model->getSelectedPhotoPath());
    model->setSelectedPhotoPath(model->getSelectedPhotoPath());
}

