#ifndef LARGEPHOTOVIEW_H
#define LARGEPHOTOVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QToolBar>
#include <QDesktopServices>
#include <QAction>
#include <QKeySequence>

#include <iostream>

#include "largephotowidget.h"
#include "src/model/applicationmodel.h"
#include "src/model/librarymodel.h"
#include "src/utils/importer.h"
#include "src/thumbnailview.h"

class LargePhotoView : public QWidget
{
    Q_OBJECT
public:
    explicit LargePhotoView(QString path, QWidget *parent, ThumbnailView *listArea);
    ~LargePhotoView();

private:
    LargePhotoWidget *photoWidget;
    QGridLayout *layout;
    QToolBar *toolbar;
    ThumbnailView *listArea;

    void rotatePhoto(int rotation);
    QString getShortcutLabel(QString tooltip,QString shortcut);

    bool fullscreen;

signals:
    void disposed();
    void restore();

public slots:
    void openInFileManager();
    void rotatePhotoAntiClockwise();
    void rotatePhotoClockwise();
    void editPhoto();
    void backAction();
    void prevPhoto();
    void nextPhoto();
    void toggleFullscreen();
};

#endif // LARGEPHOTOVIEW_H
