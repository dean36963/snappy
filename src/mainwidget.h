#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeWidget>

#include "src/model/applicationmodel.h"
#include "src/photoarea.h"
#include "src/eventtreewidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void addMenuItems(QMenuBar *menu);

private:
    QGridLayout *layout;
    EventTreeWidget *tree;
    PhotoArea *photoArea;

signals:

public slots:

};

#endif // MAINWIDGET_H
