#ifndef THUMBNAILWIDGET_H
#define THUMBNAILWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QMatrix>
#include <QPixmap>
#include <QFileInfo>
#include <QDir>
#include <QRect>

#include <string>
#include <iostream>

#include "src/utils/imageutils.h"
#include "src/utils/importer.h"

using namespace std;

class ThumbnailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThumbnailWidget(QString photoPath, QWidget *parent = 0, int w = 80, int h = 80);
    ~ThumbnailWidget();
    void changeSize(int w, int h);
    QString getType();

private:
    QString photoPath;
    QGridLayout *layout;
    QLabel *label;
    QString type;

    void setType();
    void setImage();
    QString getThumbPath(QString path);
    bool ifThumbExists();
    bool ifPhotoExists();
    int width,height;
    QPixmap roundCorners(QImage icon, QSize size);

signals:

public slots:
};

#endif // THUMBNAILWIDGET_H
