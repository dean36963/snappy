#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    photoArea = new PhotoArea(this);

    //TODO replace this tree with a custom tree
    tree = new EventTreeWidget(this);

    layout->addWidget(tree,0,0);
    layout->addWidget(photoArea,0,1);

    setLayout(layout);
}

MainWidget::~MainWidget() {
    delete layout;
    delete photoArea;
}
