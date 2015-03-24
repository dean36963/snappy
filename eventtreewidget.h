#ifndef EVENTTREEWIDGET_H
#define EVENTTREEWIDGET_H

#include <QObject>
#include <QTreeWidget>

#include "librarymodel.h"
#include "applicationmodel.h"

class EventTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit EventTreeWidget(QWidget *parent = 0);
    ~EventTreeWidget();
signals:
public slots:
    void onSelectionChange();
};

#endif // EVENTTREEWIDGET_H
