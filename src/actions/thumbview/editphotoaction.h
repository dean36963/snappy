#ifndef EDITPHOTOACTION_H
#define EDITPHOTOACTION_H

#include <QAction>
#include <QListWidgetItem>
#include <QList>
#include <QDesktopServices>
#include <QUrl>

#include "src/utils/rolesenums.h"

class EditPhotoAction : public QAction {
    Q_OBJECT
public:
    EditPhotoAction();
    void setItems(QList<QListWidgetItem*> items);
public slots:
    void edit();
private:
    QList<QListWidgetItem*> items;
};

#endif // EDITPHOTOACTION_H
