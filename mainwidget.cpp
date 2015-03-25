#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();

    photoArea = new PhotoArea(this);
    tree = new EventTreeWidget(this);

    layout->addWidget(tree,0,0);
    layout->addWidget(photoArea,0,1);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,3);

    setLayout(layout);
}

MainWidget::~MainWidget() {
    delete layout;
    delete photoArea;
}
