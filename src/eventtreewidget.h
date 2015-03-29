#ifndef EVENTTREEWIDGET_H
#define EVENTTREEWIDGET_H

#include <QObject>
#include <QTreeWidget>

#include "src/model/librarymodel.h"
#include "src/model/applicationmodel.h"

class EventTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit EventTreeWidget(QWidget *parent = 0);
    ~EventTreeWidget();
signals:
public slots:
    void onSelectionChange();
    void onLibraryChange();
};

#endif // EVENTTREEWIDGET_H
