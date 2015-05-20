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
    QFileInfo info(eventPath);
    QString userInput = info.fileName();
    if(libraryModel->isNamedEvent(eventPath)) {
        userInput = libraryModel->getFriendlyEventName(eventPath);
    }
    QString errorMessage("Select a new name for the event.");
    bool ok = false;
    bool valid = false;
    do {

        userInput = QInputDialog::getText(parentWidget(),"Rename Event",errorMessage,
                                                  QLineEdit::Normal,userInput,&ok);
        //TODO proper path handling, do for windows port :S
        info.setFile(info.dir().absolutePath().append("/").append(userInput));
        valid = isValidInput(info,userInput,&errorMessage);
    } while (ok && !valid);
    if(ok) {
        LibraryUtils::renameEvent(eventPath,info.fileName());
    }
}

bool RenameEventAction::isValidInput(QFileInfo info, QString userInput, QString *errorMessage) {
    errorMessage->clear();
    if(!LibraryUtils::validName(userInput)) {
        errorMessage->append("Not a valid name. Use alpha-numeric characters, spaces, underscores and dashes only.");
        return false;
    }
    if(info.exists()) {
        errorMessage->append("Event already exists. Use a unique event name.");
        return false;
    }
    return true;
}
