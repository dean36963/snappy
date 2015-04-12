#ifndef LARGEPHOTOVIEW_H
#define LARGEPHOTOVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QList>
#include <QToolBar>
#include <QDesktopServices>

#include <iostream>

#include "largephotowidget.h"
#include "src/model/applicationmodel.h"
#include "src/model/librarymodel.h"

class LargePhotoView : public QWidget
{
    Q_OBJECT
public:
    explicit LargePhotoView(QString path, QWidget *parent=0);
    ~LargePhotoView();

private:
    LargePhotoWidget *photoWidget;
    QGridLayout *layout;
    QToolBar *toolbar;

signals:

public slots:
    void openInFileManager();
    void rotatePhotoAntiClockwise();
};

#endif // LARGEPHOTOVIEW_H
