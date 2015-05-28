#include "abstractthumbaction.h"

AbstractThumbAction::AbstractThumbAction(QWidget *parent) : QAction(parent) {
}

void AbstractThumbAction::setItems(QList<QListWidgetItem*> items) {
    this->items = items;
}

