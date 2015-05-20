#include "eventtreewidget.h"

const int EventTreeWidget::ACTION_CONTEXT_ROLE = 57;

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
    initActions();
}

EventTreeWidget::~EventTreeWidget()
{
    QListIterator<QAction*> it(actions);
    while(it.hasNext()) {
        QAction* action = it.next();
        delete action;
    }
}

void EventTreeWidget::onSelectionChange() {
    ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(currentItem());
    changeActionContext();
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

void EventTreeWidget::changeActionContext() {
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    LibraryModel::SELECTION_TYPE currentType = libraryModel->getSelectedEventType();

    RolesEnums::ActionContext actionContext;
    if(currentType==LibraryModel::EVENT_VIEW &&
            libraryModel->isEventItem(libraryModel->getSelectedEventPath())) {
        actionContext = RolesEnums::EVENTS_ONLY;
    } else if(currentType==LibraryModel::FOLDER_VIEW) {
        actionContext = RolesEnums::FOLDERS_ONLY;
    }
    QListIterator<QAction*> it(actions);
    while(it.hasNext()) {
        QAction * action = it.next();
        if(action->data().toInt()==actionContext ||
                action->data().toInt()==RolesEnums::ALL) {
            addAction(action);
        } else {
            removeAction(action);
        }
    }
}

void EventTreeWidget::initActions() {
    actions = QList<QAction*>();
    actions.append(new OpenInFolderAction());
    actions.append(new RenameEventAction());
    setContextMenuPolicy(Qt::ActionsContextMenu);
}
