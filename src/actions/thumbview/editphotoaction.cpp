#include "editphotoaction.h"

EditPhotoAction::EditPhotoAction() : QAction(0) {
    setIcon(QIcon::fromTheme("image-x-generic"));
    setStatusTip("Edit photo in other application");
    setText("Edit photo in other application");
    setData(RolesEnums::SINGLE_PHOTO);
    connect(this,SIGNAL(triggered()),this,SLOT(edit()));
}

void EditPhotoAction::setItems(QList<QListWidgetItem *> items) {
    this->items = items;
}

void EditPhotoAction::edit() {
    QListWidgetItem *item = items.at(0);
    QDesktopServices::openUrl("file://"+item->data(RolesEnums::PHOTO_PATH_PROPERTY).toString());
}
