#include "thumbnailview.h"

const int ThumbnailView::PHOTO_PATH_PROPERTY = 50;

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
    setSelectionMode(QAbstractItemView::MultiSelection);

    LibraryModel *model = ApplicationModel::getApplicationModel()->getLibraryModel();
    connect(model,SIGNAL(selectedPhotoChanged(QString)),this,SLOT(photoChanged(QString)));
    connect(model,SIGNAL(eventPathChanged(QString)),this,SLOT(refresh()));
    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(this,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemClicked(QListWidgetItem*)));

    setSortingEnabled(true);
}

ThumbnailView::~ThumbnailView()
{

}

void ThumbnailView::refresh() {
    startProgress();
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    QList<QString> photos = libraryModel->getPhotosFromPath(libraryModel->getSelectedEventPath());
    clear();
    if(photos.empty()) {
        QList<QString> events = libraryModel->getEventsUnderPath(libraryModel->getSelectedEventPath());
        refreshWithEvents(events);
    } else {
        refreshWithPhotos(photos);
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
    setSelectionMode(QAbstractItemView::SingleSelection);
    ThumbnailWidget *widget = (ThumbnailWidget*) itemWidget(item);
    if(widget->getType()=="Photo") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(item->data(PHOTO_PATH_PROPERTY).toString());
        emit photoDoubleClicked(item->data(PHOTO_PATH_PROPERTY).toString());
    } else if(widget->getType()=="Event") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedEventPath(item->text());
    }
}

QString ThumbnailView::getNextPhoto(QString photo) {
    QDateTime dateTime = ImageUtils::getDateTimeFromFilename(photo);
    QList<QListWidgetItem*> foundItems = findItems(dateTime.toString(),Qt::MatchExactly);
    if(foundItems.size()>0) {
        QListWidgetItem* foundItem = foundItems.first();
        QModelIndex index = indexFromItem(foundItem);
        QModelIndex next = index.sibling(index.row()+1,index.column());
        if(next.isValid()) {
            return itemFromIndex(next)->data(PHOTO_PATH_PROPERTY).toString();
        }
    }
    return NULL;
}
QString ThumbnailView::getPreviousPhoto(QString photo) {
    QDateTime dateTime = ImageUtils::getDateTimeFromFilename(photo);
    QList<QListWidgetItem*> foundItems = findItems(dateTime.toString(),Qt::MatchExactly);
    if(foundItems.size()>0) {
        QListWidgetItem* foundItem = foundItems.first();
        QModelIndex index = indexFromItem(foundItem);
        QModelIndex next = index.sibling(index.row()-1,index.column());
        if(next.isValid()) {
            return itemFromIndex(next)->data(PHOTO_PATH_PROPERTY).toString();
        }
    }
    return NULL;
}

void ThumbnailView::photoChanged(QString newPhoto) {
    for(int i=0; i<count(); i++) {
        QListWidgetItem *localItem = item(i);
        if(localItem->data(PHOTO_PATH_PROPERTY).toString()==newPhoto) {
            setItemSelected(localItem,true);
            setCurrentItem(localItem);
            scrollTo(indexFromItem(localItem));
            break;
        }
    }
}

void ThumbnailView::keyPressEvent(QKeyEvent *event) {
    setSelectionMode(QAbstractItemView::SingleSelection);
    if(event->key()==Qt::Key_Return) {
        if(selectedItems().length()==1) {
            QListWidgetItem * first = selectedItems().first();
            itemDoubleClicked(first);
        }
    } else {
        QListWidget::keyPressEvent(event);
    }
}

void ThumbnailView::mousePressEvent(QMouseEvent * event) {
    setSelectionMode(QAbstractItemView::MultiSelection);
    mouseModifiers = event->modifiers();
    QListWidget::mousePressEvent(event);
}

void ThumbnailView::itemClicked(QListWidgetItem* item) {
    if(mouseModifiers == Qt::ControlModifier) {
    } else {
        QListIterator<QListWidgetItem*> currentSelectedItems = selectedItems();
        while(currentSelectedItems.hasNext()) {
            QListWidgetItem* selectedItem = currentSelectedItems.next();
            setItemSelected(selectedItem,false);
        }
        setItemSelected(item,true);
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
        item->setData(PHOTO_PATH_PROPERTY,QVariant(path));
        item->setBackgroundColor(QColor(42,42,42));
        if(findItems(item->text(),Qt::MatchExactly).size()==0) {
            addItem(item);
        }
        setItemWidget(item,widget);
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
