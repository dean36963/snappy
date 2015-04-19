#ifndef EVENTTREEWIDGET_H
#define EVENTTREEWIDGET_H

#include <QObject>
#include <QTreeWidget>
#include <QAction>
#include <QList>

#include "src/model/librarymodel.h"
#include "src/model/applicationmodel.h"

class EventTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit EventTreeWidget(QWidget *parent = 0);
    ~EventTreeWidget();
signals:
private:
    QList<QAction*> actions;
    const static int ACTION_CONTEXT_ROLE;

    void initActions();
    void changeActionContext();
public slots:
    void onSelectionChange();
    void onLibraryChange();
    void onItemClicked(QTreeWidgetItem*item, int);
    void onEventChanged();
};

#endif // EVENTTREEWIDGET_H
