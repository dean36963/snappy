#ifndef RENAMEEVENTTHUMBACTION_H
#define RENAMEEVENTTHUMBACTION_H

#include <QObject>
#include <QAction>

#include "src/actions/thumbview/abstractthumbaction.h"
#include "src/utils/rolesenums.h"
#include "src/utils/libraryutils.h"

class RenameEventThumbAction : public AbstractThumbAction
{
    Q_OBJECT
public:
    RenameEventThumbAction(QWidget *parent);
public slots:
    void renameEvent();
};

#endif // RENAMEEVENTTHUMBACTION_H
