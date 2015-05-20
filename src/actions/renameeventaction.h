#ifndef RENAMEEVENTACTION_H
#define RENAMEEVENTACTION_H

#include <QAction>
#include <QDesktopServices>
#include <QInputDialog>
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
private:
    bool isValidInput(QFileInfo info, QString userInput, QString *errorMessage);
public slots:
    void renameEvent();
};

#endif // RENAMEEVENTACTION_H
