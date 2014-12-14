#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    button = new QPushButton("TEST");
    tree = new QTreeWidget();

    layout->addWidget(tree,0,0);
    layout->addWidget(button,0,1);

    setLayout(layout);
}

MainWidget::~MainWidget() {
    delete layout;
    delete button;
    delete tree;
}
