#include "photoarea.h"

PhotoArea::PhotoArea(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout();

    listArea = new ThumbnailView(this);
//    listArea->setViewMode(QListWidget::IconMode);
//    listArea->setDragEnabled(false);
//    //TODO this is just testing atm
//    QListWidgetItem *test = new QListWidgetItem();
//    QSize size(100,100);
//    test->setSizeHint(size);
//    test->setText("TEST!");
//    photoWidget = new ThumbnailWidget("/home/dean/Pictures/snappyPhotos/2013/08/26/20130826_164942.jpg",this);


//    listArea->addItem(test);
//    listArea->setItemWidget(test,photoWidget);
//    listArea->addItem("TEST2");


    label = new QLabel(this);
    label->setText("Welcome");
    label->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    label->setMinimumWidth(500);

    layout->addWidget(listArea,0,0);
    layout->addWidget(label,1,0);
    setLayout(layout);

    Notifier *notifier = ApplicationModel::getApplicationModel()->getLibraryModel()->getNotifier();
    notifier->connect(notifier,SIGNAL(triggered()),this,SLOT(eventChanged()));
}

PhotoArea::~PhotoArea()
{
    delete layout;
    delete label;
}


void PhotoArea::eventChanged() {
    QString path = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    label->setText(path);
}
