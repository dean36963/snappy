#include "largephotoview.h"

LargePhotoView::LargePhotoView(QString path, QWidget *parent, ThumbnailView *listArea) : QWidget(parent) {
    layout = new QGridLayout(this);
    this->listArea = listArea;

    fullscreen = false;

    photoWidget = new LargePhotoWidget(path,this);
    layout->addWidget(photoWidget,1,0);

    toolbar = new QToolBar("",this);
    layout->addWidget(toolbar,2,0);
    setLayout(layout);

    QString shortCut("O");
    QAction *action = toolbar->addAction(QIcon::fromTheme("folder"),getShortcutLabel("Open in file manager",shortCut),
                                         this,SLOT(openInFileManager()));
    action->setShortcut(QKeySequence(shortCut));
    shortCut = QString("E");
    action = toolbar->addAction(QIcon::fromTheme("image-x-generic"),getShortcutLabel("Edit photo in other application",shortCut),
                                this,SLOT(editPhoto()));
    action->setShortcut(QKeySequence(shortCut));
    toolbar->addSeparator();
    shortCut = QString("Ctrl+Shift+R");
    action = toolbar->addAction(QIcon::fromTheme("object-rotate-left"),getShortcutLabel("Rotate anti-clockwise",shortCut),
                                this,SLOT(rotatePhotoAntiClockwise()));
    action->setShortcut(QKeySequence(shortCut));
    shortCut = QString("Ctrl+R");
    action = toolbar->addAction(QIcon::fromTheme("object-rotate-right"),getShortcutLabel("Rotate clockwise",shortCut),
                                this,SLOT(rotatePhotoClockwise()));
    action->setShortcut(QKeySequence(shortCut));

    toolbar->addSeparator();

    shortCut = QString("Escape");
    action = toolbar->addAction(QIcon::fromTheme("go-up"),getShortcutLabel("Back to event",shortCut),
                                this,SLOT(backAction()));
    action->setShortcut(QKeySequence(shortCut));

    shortCut = QString("Left");
    action = toolbar->addAction(QIcon::fromTheme("go-previous"),getShortcutLabel("Previous photo",shortCut),
                                this,SLOT(prevPhoto()));
    action->setShortcut(QKeySequence(shortCut));

    shortCut = QString("Right");
    action = toolbar->addAction(QIcon::fromTheme("go-next"),getShortcutLabel("Next photo",shortCut),
                                this,SLOT(nextPhoto()));
    action->setShortcut(QKeySequence(shortCut));

    toolbar->addSeparator();

    shortCut = QString("F11");
    action = toolbar->addAction(QIcon::fromTheme("view-fullscreen"),getShortcutLabel("Toggle Fullscreen",shortCut),this,SLOT(toggleFullscreen()));
    action->setShortcut(QKeySequence(shortCut));

    connect(photoWidget,SIGNAL(doubleClicked()),this,SLOT(toggleFullscreen()));

    setFocus();
}

LargePhotoView::~LargePhotoView()
{
    delete photoWidget;
    delete layout;
    delete toolbar;
    emit disposed();
}


void LargePhotoView::openInFileManager() {
    QString photoPath = photoWidget->getImagePath();
    QFileInfo info(photoPath);
    QDir containingDir = info.dir();

    QDesktopServices::openUrl("file://"+containingDir.absolutePath());
}

void LargePhotoView::editPhoto() {
    QString photoPath = photoWidget->getImagePath();
    QDesktopServices::openUrl("file://"+photoPath);
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
    Importer::createThumbnail(model->getSelectedPhotoPath());
}

void LargePhotoView::backAction() {
    //Need to either toggle fullscreen or delete
    if(fullscreen) {
        fullscreen = false;
        ApplicationModel::getApplicationModel()->requestFullscreen(NULL);
    } else {
        delete this;
    }
}

void LargePhotoView::prevPhoto() {
    QString prevPhoto = listArea->getPreviousPhoto(ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedPhotoPath());
    if(prevPhoto!="") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(prevPhoto);
    }
}

void LargePhotoView::nextPhoto() {
    QString nextPhoto = listArea->getNextPhoto(ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedPhotoPath());
    if(nextPhoto!="") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(nextPhoto);
    }
}

QString LargePhotoView::getShortcutLabel(QString tooltip, QString shortcut) {
    return tooltip.append(" (").append(shortcut).append(")");
}

void LargePhotoView::toggleFullscreen() {
    if(!fullscreen) {
        ApplicationModel::getApplicationModel()->requestFullscreen(this);
    } else {
        ApplicationModel::getApplicationModel()->requestFullscreen(this);
        emit restore();
    }
    fullscreen = !fullscreen;
}
