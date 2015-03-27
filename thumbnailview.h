#ifndef THUMBNAILVIEW_H
#define THUMBNAILVIEW_H

#include <QListWidget>
#include <QPalette>
#include <QColor>
#include <QEventLoop>
#include <QFont>

#include "applicationmodel.h"
#include "thumbnailwidget.h"

using namespace std;

class ThumbnailView : public QListWidget
{
    Q_OBJECT
public:
    ThumbnailView(QWidget *parent = 0);
    ~ThumbnailView();
private:
    QEventLoop *event;
    void startProgress();
    void endProgress();

public slots:
    void refresh();
};

#endif // THUMBNAILVIEW_H
