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

#include "applicationmodel.h"
#include "thumbnailwidget.h"
#include "thumbnailview.h"
#include "largephotoview.h"

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
    QAction *backAction;
    QAction *nextAction;
    QAction *prevAction;

signals:

public slots:
    void eventChanged();
    void showFullPhoto(QString photoPath);
    void showThumbs();
    void eventActivated(QTreeWidgetItem *, int);
    void nextPhoto();
    void prevPhoto();
};

#endif // PHOTOAREA_H
