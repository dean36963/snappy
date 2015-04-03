#ifndef LARGEPHOTOVIEW_H
#define LARGEPHOTOVIEW_H

#include <QWidget>
#include <QString>
#include <QMatrix>
#include <QLabel>
#include <QSize>
#include <QGridLayout>
#include <QResizeEvent>
#include <QWheelEvent>
#include <QImage>
#include <QRect>
#include <QPoint>

#include "src/model/applicationmodel.h"
#include "src/utils/imageutils.h"

class LargePhotoView : public QWidget
{
    Q_OBJECT
public:
    explicit LargePhotoView(QString photoPath, QWidget *parent);
    ~LargePhotoView();

private:
    QString photoPath;
    QLabel *label;
    QWidget *parent;
    QGridLayout *layout;
    QAction *backAction;
    QImage *image;
    QRect *zoomArea;
    double zoomLevel;

    void setImage(QSize size);
    void checkZoom();
    void resetZoom();
    void drawZoomedState();

    QPoint getMidPoint(QRect input);

protected:
    virtual void resizeEvent(QResizeEvent *);
    void wheelEvent(QWheelEvent *e);

signals:


public slots:
    void pictureChanged(QString newPic);
    void increaseZoom();
    void decreaseZoom();
};

#endif // LARGEPHOTOVIEW_H
