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
    delete event;
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
    delete photos;
}
