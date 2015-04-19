#ifndef OPENINFOLDERACTION_H
#define OPENINFOLDERACTION_H

#include <QAction>
#include <QDesktopServices>
#include <QUrl>

#include <iostream>

#include "src/utils/rolesenums.h"
#include "src/model/applicationmodel.h"

using namespace std;

class OpenInFolderAction : public QAction {
    Q_OBJECT
public:
    explicit OpenInFolderAction();
    ~OpenInFolderAction();
public slots:
    void openInFolder();
};

#endif
