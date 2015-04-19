#include "eventtreewidget.h"

EventTreeWidget::EventTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    addTopLevelItems(libraryModel->getTreeItems());
    setHeaderHidden(true);
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(onSelectionChange()));
    connect(libraryModel,SIGNAL(libraryChanged()),this,SLOT(onLibraryChange()));
    connect(libraryModel,SIGNAL(eventPathChanged(QString,SELECTION_TYPE)),this,SLOT(onEventChanged()));
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(onItemClicked(QTreeWidgetItem*,int)));
    setSortingEnabled(true);
}

EventTreeWidget::~EventTreeWidget()
{

}

void EventTreeWidget::onSelectionChange() {
    ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(currentItem());
}

void EventTreeWidget::onLibraryChange() {
    clear();
    LibraryModel* libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    addTopLevelItems(libraryModel->getTreeItems());
}

void EventTreeWidget::onItemClicked(QTreeWidgetItem * item, int) {
    QString event = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    if(item->text(0)!=event) {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(item);
    }
    expandItem(item);
}

void EventTreeWidget::onEventChanged() {
    expandItem(currentItem());
}
