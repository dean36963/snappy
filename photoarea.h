#ifndef PHOTOAREA_H
#define PHOTOAREA_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>

#include <QPushButton>

#include "applicationmodel.h"
#include "thumbnailwidget.h"

class PhotoArea : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoArea(QWidget *parent = 0);
    ~PhotoArea();
private:
    QListWidget *listArea;
    QGridLayout *layout;
    QLabel *label;

    ThumbnailWidget *photoWidget;
    QPushButton *button;
signals:

public slots:
    void eventChanged();
};

#endif // PHOTOAREA_H
