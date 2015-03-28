#ifndef LARGEPHOTOVIEW_H
#define LARGEPHOTOVIEW_H

#include <QWidget>
#include <QString>
#include <QMatrix>
#include <QLabel>
#include <QSize>
#include <QGridLayout>
#include <QResizeEvent>

#include "applicationmodel.h"
#include "imageutils.h"

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

    void setImage(QSize size);

protected:
    virtual void resizeEvent(QResizeEvent *);

signals:


public slots:
    void pictureChanged(QString newPic);
};

#endif // LARGEPHOTOVIEW_H
