#include "renameeventaction.h"

RenameEventAction::RenameEventAction() : QAction(0) {
    setIcon(QIcon::fromTheme("image-x-generic"));
    setStatusTip("Rename event");
    setText("Rename event");
    setData(RolesEnums::EVENTS_ONLY);
    connect(this,SIGNAL(triggered()),this,SLOT(renameEvent()));
}

RenameEventAction::~RenameEventAction() {

}

void RenameEventAction::renameEvent() {
    LibraryModel *libraryModel = ApplicationModel::getApplicationModel()->getLibraryModel();
    QString eventPath = libraryModel->getSelectedEventPath();
    LibraryUtils::renameEventWithPrompt(eventPath,parentWidget());
}
