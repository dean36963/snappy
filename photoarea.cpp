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
}
