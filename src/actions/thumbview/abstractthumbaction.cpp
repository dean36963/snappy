#include "abstractthumbaction.h"

AbstractThumbAction::AbstractThumbAction() : QAction(0) {
}

void AbstractThumbAction::setItems(QList<QListWidgetItem*> items) {
    this->items = items;
}

