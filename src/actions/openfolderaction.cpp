#include "src/actions/openfolderaction.h"

OpenInFolderAction::OpenInFolderAction() : QAction(0) {
    setIcon(QIcon::fromTheme("folder"));
    setStatusTip("Open in File Browser");
    setText("Open in File Browser");
    setData(RolesEnums::ALL);
    connect(this,SIGNAL(triggered()),this,SLOT(openInFolder()));
}

OpenInFolderAction::~OpenInFolderAction() {

}

void OpenInFolderAction::openInFolder() {
    QString eventPath = ApplicationModel::getApplicationModel()->getLibraryModel()->getSelectedEventPath();
    //TODO X platform?
    QDesktopServices::openUrl(QUrl("file://"+eventPath));
}
