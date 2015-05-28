#include "mergeeventsaction.h"

MergeEventsAction::MergeEventsAction(QWidget *parent) : AbstractThumbAction(parent)
{
    setIcon(QIcon::fromTheme("image-x-generic"));
    setStatusTip("Merge events");
    setText("Merge events");
    setData(RolesEnums::MULTIPLE_EVENTS);
    connect(this,SIGNAL(triggered()),this,SLOT(mergeEvents()));
}

void MergeEventsAction::mergeEvents() {
    QList<QString> eventPaths = QList<QString>();
    eventPaths.append(items.at(0)->data(RolesEnums::EVENT_PATH_PROPERTY).toString());
    eventPaths.append(items.at(1)->data(RolesEnums::EVENT_PATH_PROPERTY).toString());

    bool eventNameOk = false;
    QString label("Choose the name of your new event.");
    while(!eventNameOk) {
        QString chosenEventName("");
        chosenEventName = QInputDialog::getText((QWidget*)parent(),QString("Merged Event Name"),
                        label,
                        QLineEdit::Normal,chosenEventName);
        if(chosenEventName=="") {
            return;
        }
        if(LibraryUtils::validName(chosenEventName)) {
            eventNameOk = LibraryUtils::mergeEvents(chosenEventName,eventPaths);
        } else if(!label.contains("\n")) {
            label.append("\nNot a valid name. Use alpha-numeric characters, spaces, underscores and dashes only.");
        }
    }
}

