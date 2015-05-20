#include "photoarea.h"

PhotoArea::PhotoArea(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout();

    listArea = new ThumbnailView(this);

    label = new QLabel(this);
    label->setText("Welcome");
    label->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    label->setMinimumWidth(500);

    thumbSizeSlider = new QSlider(Qt::Horizontal,this);
    thumbSizeSlider->setMinimum(100);
    thumbSizeSlider->setMaximum(200);
    thumbSizeSlider->setMaximumWidth(200);
    thumbSizeSlider->setMinimumWidth(200);
    thumbSizeSlider->connect(thumbSizeSlider,SIGNAL(valueChanged(int)),listArea,SLOT(thumbSizeChanged(int)));
    if(ApplicationModel::getApplicationModel()->getProperties()->hasProperty(QString("preferred.thumbsize"))) {
        QString preferred = ApplicationModel::getApplicationModel()->getProperties()->getPropertyValue((QString("preferred.thumbsize")));
        thumbSizeSlider->setValue(preferred.toInt());
        listArea->thumbSizeChanged(thumbSizeSlider->value());
    }

    largePhotoView = NULL;

    layout->addWidget(listArea,0,0,1,2);
    layout->addWidget(label,1,0);
    layout->addWidget(thumbSizeSlider,1,1);
    setLayout(layout);

    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    connect(model,SIGNAL(eventPathChanged(QString,SELECTION_TYPE)),this,SLOT(eventChanged()));
    connect(listArea,SIGNAL(photoDoubleClicked(QString)),this,SLOT(showFullPhoto(QString)));
}

PhotoArea::~PhotoArea()
{
    delete layout;
    delete label;
    delete listArea;
    delete thumbSizeSlider;
}


void PhotoArea::eventChanged() {
    QString path = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    label->setText(path);
    showThumbs();
}

void PhotoArea::showFullPhoto(QString photoPath) {
    layout->removeWidget(listArea);
    layout->removeWidget(label);
    layout->removeWidget(thumbSizeSlider);
    listArea->hide();
    label->hide();
    thumbSizeSlider->hide();

    largePhotoView = new LargePhotoView(photoPath,this,listArea);
    layout->addWidget(largePhotoView,1,1);
    connect(largePhotoView,SIGNAL(disposed()),this,SLOT(largePhotoViewDisposed()));
}

void PhotoArea::addMenuItems(QMenuBar *) {
    //Not needed atm
}

void PhotoArea::showThumbs() {
    if(largePhotoView!=NULL) {
        layout->removeWidget(largePhotoView);
        delete largePhotoView;
        largePhotoView = NULL;
    }
    layout->addWidget(listArea,0,0,1,2);
    layout->addWidget(label,1,0);
    layout->addWidget(thumbSizeSlider,1,1);
    listArea->show();
    label->show();
    thumbSizeSlider->show();
    listArea->setFocus();
    listArea->refocus();
}


void PhotoArea::eventActivated(QTreeWidgetItem *, int) {
    showThumbs();
}

void PhotoArea::largePhotoViewDisposed() {
    largePhotoView = NULL;
    showThumbs();
}
