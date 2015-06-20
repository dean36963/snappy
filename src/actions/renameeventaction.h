#ifndef RENAMEEVENTACTION_H
#define RENAMEEVENTACTION_H

#include <QAction>
#include <QDesktopServices>
#include <QFileInfo>

#include <iostream>

#include "src/utils/rolesenums.h"
#include "src/model/applicationmodel.h"
#include "src/model/librarymodel.h"

#include "src/utils/libraryutils.h"

class RenameEventAction : public QAction
{
    Q_OBJECT
public:
    RenameEventAction();
    ~RenameEventAction();
public slots:
    void renameEvent();
};

#endif // RENAMEEVENTACTION_H
