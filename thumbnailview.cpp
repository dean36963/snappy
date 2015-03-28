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
    //setSelectionMode(QAbstractItemView::MultiSelection);


    Notifier* notifier = ApplicationModel::getApplicationModel()->getLibraryModel()->getNotifier();
    notifier->connect(notifier,SIGNAL(triggered()),this,SLOT(refresh()));

    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
}

ThumbnailView::~ThumbnailView()
{

}

void ThumbnailView::refresh() {
    startProgress();
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    QList<QString> *photos = libraryModel->getPhotosFromPath(libraryModel->getSelectedEventPath());
    clear();
    if(photos==NULL) {
        delete photos;
        return;
    }
    QListIterator<QString> it(*photos);
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
        item->setText(path);
        addItem(item);
        setItemWidget(item,widget);
        if(i % refreshAfterThisManyPhotos == 0) {
            event->processEvents();
        }
        i++;
    }
    delete photos;
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
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    QList<QString> *photos = libraryModel->getPhotosFromPath(libraryModel->getSelectedEventPath());
    QListIterator<QString> it(*photos);
    int i=0;
    while(it.hasNext()) {
        it.next();
        QListWidgetItem *localItem = item(i);
        localItem->setSizeHint(*size);
        ThumbnailWidget *localItemWidget = (ThumbnailWidget*) itemWidget(localItem);
        localItemWidget->changeSize(0.8*newValue,0.8*newValue);
        i++;
    }
    doItemsLayout();
    ApplicationModel::getApplicationModel()->getProperties()->setProperty(QString("preferred.thumbsize"),QString::number(newValue));
    delete photos;
}

void ThumbnailView::itemDoubleClicked(QListWidgetItem *item) {
    ThumbnailWidget *widget = (ThumbnailWidget*) itemWidget(item);
    if(widget->getType()=="Photo") {
        ApplicationModel::getApplicationModel()->getLibraryModel()->setSelectedPhotoPath(item->text());
        emit photoDoubleClicked(item->text());
    } else if(widget->getType()=="Event") {
        //TODO currently I haven't got a thumbnail widget for events so this wont trigger
        //but eventually will.
    }
}

QString ThumbnailView::getNextPhoto(QString photo) {
    for(int i=0; i<count(); i++) {
        QListWidgetItem *localItem = item(i);
        if(localItem->text()==photo && (i+1)<count()) {
            return item(i+1)->text();
        }
    }
    return NULL;
}
QString ThumbnailView::getPreviousPhoto(QString photo) {
    for(int i=0; i<count(); i++) {
        QListWidgetItem *localItem = item(i);
        if(localItem->text()==photo && (i-1)>=0) {
            return item(i-1)->text();
        }
    }
    return NULL;
}
