#ifndef ABSTRACTTHUMBACTION_H
#define ABSTRACTTHUMBACTION_H

#include <QAction>
#include <QListWidgetItem>
#include <QList>

class AbstractThumbAction : public QAction {
    Q_OBJECT
public:
    explicit AbstractThumbAction(QWidget *parent);
    void setItems(QList<QListWidgetItem*> items);
protected:
    QList<QListWidgetItem*> items;
};

#endif // ABSTRACTTHUMBACTION_H
