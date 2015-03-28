#ifndef THUMBNAILVIEW_H
#define THUMBNAILVIEW_H

#include <QListWidget>
#include <QPalette>
#include <QColor>
#include <QEventLoop>
#include <QFont>
#include <QSize>
#include <QWidget>
#include <QAction>

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
    QString getNextPhoto(QString photo);
    QString getPreviousPhoto(QString photo);
private:
    QEventLoop *event;
    void startProgress();
    void endProgress();

signals:
    void photoDoubleClicked(QString photoPath);

public slots:
    void refresh();
    void thumbSizeChanged(int newValue);
    void itemDoubleClicked(QListWidgetItem *item);
    void photoChanged(QString newPhoto);
};

#endif // THUMBNAILVIEW_H
