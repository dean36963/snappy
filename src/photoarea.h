#ifndef PHOTOAREA_H
#define PHOTOAREA_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QSlider>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>

#include "src/model/applicationmodel.h"
#include "src/thumbnailwidget.h"
#include "src/thumbnailview.h"
#include "src/largephotoview.h"

class PhotoArea : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoArea(QWidget *parent = 0);
    ~PhotoArea();
    void addMenuItems(QMenuBar *menu);
private:
    ThumbnailView *listArea;
    QGridLayout *layout;
    QLabel *label;
    QPushButton *button;
    QSlider *thumbSizeSlider;
    LargePhotoView *largePhotoView;

signals:

public slots:
    void eventChanged();
    void showFullPhoto(QString photoPath);
    void showThumbs();
    void eventActivated(QTreeWidgetItem *, int);
    void largePhotoViewDisposed();
    void largePhotoViewRestored();
};

#endif // PHOTOAREA_H
