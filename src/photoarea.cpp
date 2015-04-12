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

    layout->addWidget(listArea,0,0,1,2);
    layout->addWidget(label,1,0);
    layout->addWidget(thumbSizeSlider,1,1);
    setLayout(layout);

    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    connect(model,SIGNAL(eventPathChanged(QString)),this,SLOT(eventChanged()));

    connect(listArea,SIGNAL(photoDoubleClicked(QString)),this,SLOT(showFullPhoto(QString)));
}

PhotoArea::~PhotoArea()
{
    delete layout;
    delete label;
    delete listArea;
    delete thumbSizeSlider;
    delete backAction;
}


void PhotoArea::eventChanged() {
    QString path = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    label->setText(path);
    if(backAction->isEnabled()) {
        showThumbs();
    }
}

void PhotoArea::showFullPhoto(QString photoPath) {
    layout->removeWidget(listArea);
    layout->removeWidget(label);
    layout->removeWidget(thumbSizeSlider);
    listArea->hide();
    label->hide();
    thumbSizeSlider->hide();

    largePhotoView = new LargePhotoView(photoPath,this);
    layout->addWidget(largePhotoView,1,1);

    backAction->setEnabled(true);
    nextAction->setEnabled(true);
    prevAction->setEnabled(true);
}

void PhotoArea::addMenuItems(QMenuBar *menu) {
    QMenu *navMenu = menu->addMenu("Navigation");

    //Add navigation Items

    backAction = new QAction(QIcon::fromTheme("go-up"),"Back",this);
    backAction->setShortcut(QKeySequence("Escape"));
    navMenu->addAction(backAction);
    backAction->setEnabled(false);
    connect(backAction,SIGNAL(triggered()),this,SLOT(showThumbs()));

    navMenu->addSeparator();

    nextAction = new QAction(QIcon::fromTheme("go-next"),"Next",this);
    nextAction->setShortcut(QKeySequence("Right"));
    navMenu->addAction(nextAction);
    nextAction->setEnabled(false);
    connect(nextAction,SIGNAL(triggered()),this,SLOT(nextPhoto()));

    prevAction = new QAction(QIcon::fromTheme("go-previous"),"Previous",this);
    prevAction->setShortcut(QKeySequence("Left"));
    navMenu->addAction(prevAction);
    prevAction->setEnabled(false);
    connect(prevAction,SIGNAL(triggered()),this,SLOT(prevPhoto()));
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

    backAction->setEnabled(false);
    nextAction->setEnabled(false);
    prevAction->setEnabled(false);
}


void PhotoArea::eventActivated(QTreeWidgetItem *, int) {
    if(backAction->isEnabled()) {
        showThumbs();
    }
}

void PhotoArea::nextPhoto() {
    QString nextPhoto = listArea->getNextPhoto(ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedPhotoPath());
    if(nextPhoto!="") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(nextPhoto);
    }
}


void PhotoArea::prevPhoto() {
    QString prevPhoto = listArea->getPreviousPhoto(ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedPhotoPath());
    if(prevPhoto!="") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(prevPhoto);
    }
}
