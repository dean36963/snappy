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

    connect(tree,SIGNAL(itemActivated(QTreeWidgetItem*,int)),photoArea,SLOT(eventActivated(QTreeWidgetItem*,int)));

    setLayout(layout);
}

MainWidget::~MainWidget() {
    delete layout;
    delete photoArea;
    delete tree;
}

void MainWidget::addMenuItems(QMenuBar *menu) {
    photoArea->addMenuItems(menu);
}
