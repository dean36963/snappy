#include "eventtreewidget.h"

EventTreeWidget::EventTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    addTopLevelItems(libraryModel->getTreeItems());
    setHeaderHidden(true);
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(onSelectionChange()));
    connect(libraryModel,SIGNAL(libraryChanged()),this,SLOT(onLibraryChange()));
    setSortingEnabled(true);
}

EventTreeWidget::~EventTreeWidget()
{

}

void EventTreeWidget::onSelectionChange() {
    ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(currentItem());
    expandItem(currentItem());
}

void EventTreeWidget::onLibraryChange() {
    clear();
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    addTopLevelItems(libraryModel->getTreeItems());
}
