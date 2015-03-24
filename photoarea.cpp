#include "photoarea.h"

PhotoArea::PhotoArea(QWidget *parent) : QWidget(parent)
{
    layout = new QGridLayout();
    label = new QLabel(this);
    label->setText("TEST");
    label->setAlignment(Qt::AlignCenter);
    label->setMinimumHeight(500);
    label->setMinimumWidth(500);
    layout->addWidget(label,0,0);
    setLayout(layout);

    Notifier *notifier = ApplicationModel::getApplicationModel()->getLibraryModel()->getNotifier();
    notifier->connect(notifier,SIGNAL(triggered()),this,SLOT(eventChanged()));
}

PhotoArea::~PhotoArea()
{
    delete layout;
}


void PhotoArea::eventChanged() {
    QString path = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    label->setText(path);
}
