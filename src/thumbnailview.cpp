#include "thumbnailview.h"



ThumbnailView::ThumbnailView(QWidget *parent) : QListWidget(parent)
{
    setViewMode(QListWidget::IconMode);
    setDragEnabled(false);
    setResizeMode(QListView::Adjust);
    QColor greyIsh(42,42,42);
    QPalette pal(palette());
    pal.setColor(QPalette::Background,greyIsh);
    viewport()->setAutoFillBackground(false);
    setAutoFillBackground(true);
    setPalette(pal);
    show();
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    connect(model,SIGNAL(selectedPhotoChanged(QString)),this,SLOT(photoChanged(QString)));
    connect(model,SIGNAL(eventPathChanged(QString,SELECTION_TYPE)),this,SLOT(refresh()));
    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(this,SIGNAL(itemSelectionChanged()),this,SLOT(updateActionContext()));

    setSortingEnabled(true);
    initActions();
}

ThumbnailView::~ThumbnailView()
{

}

void ThumbnailView::refresh() {
    startProgress();
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    LibraryModel::SELECTION_TYPE type = libraryModel->getSelectedEventType();
    QList<QString> photos = libraryModel->getPhotosFromPath(libraryModel->getSelectedEventPath());
    clear();
    if(type==LibraryModel::FOLDER_VIEW) {
        refreshWithPhotos(photos);
    } else if(type==LibraryModel::EVENT_VIEW) {
        if(libraryModel->isEventItem(libraryModel->getSelectedEventPath())) {
            refreshWithPhotos(photos);
        } else {
            QList<QString> events = libraryModel->getEventsUnderPath(libraryModel->getSelectedEventPath());
            refreshWithEvents(events);
        }
    }
    endProgress();
}

void ThumbnailView::startProgress() {
    event = new QEventLoop(this);
    event->processEvents();
}
void ThumbnailView::endProgress() {
    if(event!=NULL) {
        delete event;
        event = NULL;
    } else {
    }
}

QSize ThumbnailView::sizeHint() const {
    return QSize(600,400);
}

void ThumbnailView::thumbSizeChanged(int newValue) {
    QSize *size = new QSize(newValue,newValue);
    ApplicationModel::getApplicationModel()->setPreferredThumbnailSize(size);

    QList<QListWidgetItem*> allItems = findItems("*",Qt::MatchWildcard);
    QListIterator<QListWidgetItem*> it(allItems);
    while(it.hasNext()) {
        QListWidgetItem * thisItem = it.next();
        thisItem->setSizeHint(*size);
        ThumbnailWidget *thisItemWidget = (ThumbnailWidget*) itemWidget(thisItem);
        thisItemWidget->changeSize(0.8*newValue,0.8*newValue);
    }
    doItemsLayout();
    ApplicationModel::getApplicationModel()->getProperties()->setProperty(QString("preferred.thumbsize"),QString::number(newValue));
}

void ThumbnailView::itemDoubleClicked(QListWidgetItem *item) {
    ThumbnailWidget *widget = (ThumbnailWidget*) itemWidget(item);
    if(widget->getType()=="Photo") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(item->data(RolesEnums::PHOTO_PATH_PROPERTY).toString());
        emit photoDoubleClicked(item->data(RolesEnums::PHOTO_PATH_PROPERTY).toString());
    } else if(widget->getType()=="Event") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(item->text());
    }
}

QString ThumbnailView::getNextPhoto(QString photo) {
    QDateTime dateTime = ImageUtils::getImageDate(photo);
    ImageUtils::getImageDateExiv2(photo);
    QList<QListWidgetItem*> foundItems = findItems(dateTime.toString(),Qt::MatchExactly);
    if(foundItems.size()>0) {
        QListWidgetItem* foundItem = foundItems.first();
        QModelIndex index = indexFromItem(foundItem);
        QModelIndex next = index.sibling(index.row()+1,index.column());
        if(next.isValid()) {
            return itemFromIndex(next)->data(RolesEnums::PHOTO_PATH_PROPERTY).toString();
        }
    }
    return NULL;
}
QString ThumbnailView::getPreviousPhoto(QString photo) {
    QDateTime dateTime = ImageUtils::getImageDate(photo);
    QList<QListWidgetItem*> foundItems = findItems(dateTime.toString(),Qt::MatchExactly);
    if(foundItems.size()>0) {
        QListWidgetItem* foundItem = foundItems.first();
        QModelIndex index = indexFromItem(foundItem);
        QModelIndex next = index.sibling(index.row()-1,index.column());
        if(next.isValid()) {
            return itemFromIndex(next)->data(RolesEnums::PHOTO_PATH_PROPERTY).toString();
        }
    }
    return NULL;
}

void ThumbnailView::photoChanged(QString newPhoto) {
    setSelectionMode(QAbstractItemView::SingleSelection);
    for(int i=0; i<count(); i++) {
        QListWidgetItem *localItem = item(i);
        if(localItem->data(RolesEnums::PHOTO_PATH_PROPERTY).toString()==newPhoto) {
            setItemSelected(localItem,true);
            setCurrentItem(localItem);
            scrollTo(indexFromItem(localItem));
            break;
        }
    }
}

void ThumbnailView::keyPressEvent(QKeyEvent *event) {
    if(event->key()==Qt::Key_Return) {
        if(selectedItems().length()==1) {
            QListWidgetItem * first = selectedItems().first();
            itemDoubleClicked(first);
        }
    } else {
        QListWidget::keyPressEvent(event);
    }
}

void ThumbnailView::refreshWithEvents(QList<QString> events) {
    QListIterator<QString> it(events);
    QSize size = *ApplicationModel::getApplicationModel()->getPreferredThumbnailSize();
    int i=1;
    int refreshAfterThisManyEvents= 20;
    while(it.hasNext()) {
        QString path = it.next();
        ThumbnailWidget *widget = new ThumbnailWidget(path,this,(int)(size.width()*0.8),(int)(size.height()*0.8));
        widget->setAutoFillBackground(false);
        QListWidgetItem *item = new QListWidgetItem();
        QFont f = QFont();
        f.setPointSize(1);
        item->setFont(f);
        item->setSizeHint(size);
        item->setText(path);
        item->setBackgroundColor(QColor(42,42,42));
        item->setData(RolesEnums::PHOTO_OR_EVENT_PROPERTY,QVariant(RolesEnums::EVENT));
        item->setData(RolesEnums::EVENT_PATH_PROPERTY,QVariant(path));
        addItem(item);
        setItemWidget(item,widget);
        if(i % refreshAfterThisManyEvents == 0) {
            if(event!=NULL) {
                event->processEvents();
            }
        }
        i++;
    }
    //Show recent events first
    sortItems(Qt::DescendingOrder);
}

void ThumbnailView::refreshWithPhotos(QList<QString> photos) {
    QListIterator<QString> it(photos);
    QSize size = *ApplicationModel::getApplicationModel()->getPreferredThumbnailSize();
    int i=1;
    int refreshAfterThisManyPhotos = 20;
    while(it.hasNext()) {
        QString path = it.next();
        ThumbnailWidget *widget = new ThumbnailWidget(path,this,(int)(size.width()*0.8),(int)(size.height()*0.8));
        widget->setAutoFillBackground(false);
        QListWidgetItem *item = new QListWidgetItem();
        QFont f = QFont();
        f.setPointSize(1);
        item->setFont(f);
        item->setSizeHint(size);
        QDateTime time = ImageUtils::getImageDate(path);
        item->setText(time.toString());
        item->setData(RolesEnums::PHOTO_PATH_PROPERTY,QVariant(path));
        item->setData(RolesEnums::PHOTO_OR_EVENT_PROPERTY,QVariant(RolesEnums::PHOTO));
        item->setBackgroundColor(QColor(42,42,42));
        if(findItems(item->text(),Qt::MatchExactly).size()==0) {
            addItem(item);
            setItemWidget(item,widget);
        } else {
            delete widget;
            delete item;
        }
        if(i % refreshAfterThisManyPhotos == 0) {
            if(event!=NULL) {
                event->processEvents();
            }
        }
        i++;
    }
    //Show photos in order of date taken
    sortItems(Qt::AscendingOrder);
}

void ThumbnailView::initActions() {
    actions = QList<AbstractThumbAction*>();
    actions.append(new EditPhotoAction(this));
    actions.append(new MergeEventsAction(this));

    setContextMenuPolicy(Qt::ActionsContextMenu);
    QListIterator<AbstractThumbAction*> it(actions);
    while(it.hasNext()) {
        AbstractThumbAction* action = it.next();
        addAction((QAction*)action);
    }
}

void ThumbnailView::refocus() {
    setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void ThumbnailView::updateActionContext() {
    QListIterator<AbstractThumbAction*> it(actions);
    while(it.hasNext()) {
        AbstractThumbAction * action = it.next();
        if(isActionVisible(action)) {
            action->setItems(selectedItems());
            addAction((QAction*)action);
        } else {
            removeAction((QAction*)action);
        }
    }
}

bool ThumbnailView::isActionVisible(AbstractThumbAction *action) {
    QList<QListWidgetItem*> items = selectedItems();
    int actionRole = ((QAction*)action)->data().toInt();
    QListIterator<QListWidgetItem*> it(items);
    while(it.hasNext()) {
        QListWidgetItem* item = it.next();
        int thumbType = item->data(RolesEnums::PHOTO_OR_EVENT_PROPERTY).toInt();
        if(thumbType==RolesEnums::PHOTO) {
            if(items.size()==1
                        && actionRole==RolesEnums::SINGLE_PHOTO) {
                    return true;
            } else if(items.size()>1
                        && actionRole==RolesEnums::MULTIPLE_PHOTOS) {
                    return true;
            }
            if(actionRole==RolesEnums::ANY_PHOTOS) {
                return true;
            }
        } else if(thumbType==RolesEnums::EVENT) {
            if(items.size()==1
                        && actionRole==RolesEnums::SINGLE_EVENT) {
                    return true;
            } else if(items.size()>1
                        && actionRole==RolesEnums::MULTIPLE_EVENTS) {
                    return true;
            }
            if(actionRole==RolesEnums::ANY_EVENTS) {
                return true;
            }
        }
    }
    return false;
}

