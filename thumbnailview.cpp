#include "thumbnailview.h"

ThumbnailView::ThumbnailView(QWidget *parent) : QListWidget(parent)
{
    setViewMode(QListWidget::IconMode);
    setDragEnabled(false);
    setResizeMode(QListView::Adjust);
    //setSelectionMode(QAbstractItemView::MultiSelection);

    Notifier* notifier = ApplicationModel::getApplicationModel()->getLibraryModel()->getNotifier();
    notifier->connect(notifier,SIGNAL(triggered()),this,SLOT(refresh()));
}

ThumbnailView::~ThumbnailView()
{

}

void ThumbnailView::refresh() {
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    QList<QString> *photos = libraryModel->getPhotosFromPath(libraryModel->getSelectedEventPath());
    clear();
    if(photos==NULL) {
        delete photos;
        return;
    }
    QListIterator<QString> it(*photos);
    while(it.hasNext()) {
        QString path = it.next();
        ThumbnailWidget *widget = new ThumbnailWidget(path,this);
        QListWidgetItem *item = new QListWidgetItem();
        QSize size(100,100);
        item->setSizeHint(size);
        item->setText(path);
        addItem(item);
        setItemWidget(item,widget);
    }
    delete photos;
}
