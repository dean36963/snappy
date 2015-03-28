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

    Notifier *notifier = ApplicationModel::getApplicationModel()->getLibraryModel()->getNotifier();
    notifier->connect(notifier,SIGNAL(triggered()),this,SLOT(eventChanged()));

    connect(listArea,SIGNAL(photoDoubleClicked(QString)),this,SLOT(showFullPhoto(QString)));
    //connect(listArea,SIGNAL(itemActivated(QListWidgetItem*)),this,SLOT(eventActivated(QListWidgetItem*)));
}

PhotoArea::~PhotoArea()
{
    delete layout;
    delete label;
    delete thumbSizeSlider;
}


void PhotoArea::eventChanged() {
    QString path = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    label->setText(path);

    cout << "Event chagned" << endl;

    if(backAction->isEnabled()) {
        showThumbs();
    }
}

void PhotoArea::showFullPhoto(QString photoPath) {
    cout << "Show a big copy of this: "<< photoPath.toStdString() << endl;
    layout->removeWidget(listArea);
    layout->removeWidget(label);
    layout->removeWidget(thumbSizeSlider);
    listArea->hide();
    label->hide();
    thumbSizeSlider->hide();

    largePhotoView = new LargePhotoView(photoPath,this);
    layout->addWidget(largePhotoView,1,1);

    backAction->setEnabled(true);
}

void PhotoArea::addMenuItems(QMenuBar *menu) {
    QMenu *navMenu = menu->addMenu("Navigation");

    //Add navigation Items
    backAction = new QAction("Back",this);
    backAction->setShortcut(QKeySequence("Escape"));
    navMenu->addAction(backAction);
    backAction->setEnabled(false);
    connect(backAction,SIGNAL(triggered()),this,SLOT(showThumbs()));
}

void PhotoArea::showThumbs() {
    if(largePhotoView!=NULL) {
        layout->removeWidget(largePhotoView);
        delete largePhotoView;
    }
    layout->addWidget(listArea,0,0,1,2);
    layout->addWidget(label,1,0);
    layout->addWidget(thumbSizeSlider,1,1);
    listArea->show();
    label->show();
    thumbSizeSlider->show();

    backAction->setEnabled(false);
}


void PhotoArea::eventActivated(QTreeWidgetItem *, int) {
    cout << "eventActivated" << endl;
    if(backAction->isEnabled()) {
        showThumbs();
    }
}
