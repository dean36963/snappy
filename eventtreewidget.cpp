#include "eventtreewidget.h"

EventTreeWidget::EventTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    addTopLevelItems(libraryModel->getTreeItems());
    setHeaderHidden(true);
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(onSelectionChange()));
    setSortingEnabled(true);
}

EventTreeWidget::~EventTreeWidget()
{

}

void EventTreeWidget::onSelectionChange() {
    ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(currentItem());
    expandItem(currentItem());
}
