#include "largephotoview.h"

LargePhotoView::LargePhotoView(QString path, QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    photoWidget = new LargePhotoWidget(path,this);
    layout->addWidget(photoWidget,1,0);

    toolbar = new QToolBar("",this);
    layout->addWidget(toolbar,2,0);
    setLayout(layout);

    toolbar->addAction(QIcon::fromTheme("folder"),"Open in file manager",this,SLOT(openInFileManager()));
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
