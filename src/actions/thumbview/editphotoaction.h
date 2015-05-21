#ifndef EDITPHOTOACTION_H
#define EDITPHOTOACTION_H

#include <QAction>
#include <QListWidgetItem>
#include <QList>
#include <QDesktopServices>
#include <QUrl>
#include <QObject>

#include "src/utils/rolesenums.h"
#include "src/actions/thumbview/abstractthumbaction.h"

class EditPhotoAction : public AbstractThumbAction {
    Q_OBJECT
public:
    explicit EditPhotoAction();
public slots:
    void edit();
};

#endif // EDITPHOTOACTION_H
