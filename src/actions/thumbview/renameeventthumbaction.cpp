#include "renameeventthumbaction.h"

RenameEventThumbAction::RenameEventThumbAction(QWidget *parent) : AbstractThumbAction(parent)
{
    setStatusTip("Rename event");
    setText("Rename event");
    setData(RolesEnums::SINGLE_EVENT);
    connect(this,SIGNAL(triggered()),this,SLOT(renameEvent()));
}

void RenameEventThumbAction::renameEvent() {
    QString eventPath = items.at(0)->data(RolesEnums::EVENT_PATH_PROPERTY).toString();
    LibraryUtils::renameEventWithPrompt(eventPath,parentWidget());
}

