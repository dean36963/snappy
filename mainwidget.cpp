#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout();
    button = new QPushButton("TEST");

    //TODO replace this tree with a custom tree
    tree = new QTreeWidget();
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    tree->addTopLevelItems(libraryModel->getTreeItems());

    layout->addWidget(tree,0,0);
    layout->addWidget(button,0,1);

    setLayout(layout);
}

MainWidget::~MainWidget() {
    delete layout;
    delete button;
    //for(int i=0; i<tree->topLevelItemCount();i++) {
    //    delete tree->topLevelItem(i);
    //}
    //tree->clear();
    //delete tree;
}
