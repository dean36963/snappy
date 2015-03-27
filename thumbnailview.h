#ifndef THUMBNAILVIEW_H
#define THUMBNAILVIEW_H

#include <QListWidget>
#include <QPalette>
#include <QColor>
#include <QEventLoop>
#include <QFont>
#include <QSize>
#include <QWidget>

#include "applicationmodel.h"
#include "thumbnailwidget.h"

using namespace std;

class ThumbnailView : public QListWidget
{
    Q_OBJECT
public:
    ThumbnailView(QWidget *parent = 0);
    ~ThumbnailView();
    QSize sizeHint() const;
private:
    QEventLoop *event;
    void startProgress();
    void endProgress();

public slots:
    void refresh();
    void thumbSizeChanged(int newValue);
};

#endif // THUMBNAILVIEW_H
