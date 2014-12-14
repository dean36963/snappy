#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QTreeWidget>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    QGridLayout *layout;
    QPushButton *button;
    QTreeWidget *tree;

signals:

public slots:

};

#endif // MAINWIDGET_H
