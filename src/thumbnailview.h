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
#include <QKeyEvent>

#include "src/model/applicationmodel.h"
#include "src/model/librarymodel.h"
#include "src/thumbnailwidget.h"
#include "src/utils/rolesenums.h"

#include "src/actions/thumbview/editphotoaction.h"
#include "src/actions/thumbview/abstractthumbaction.h"
#include "src/actions/thumbview/mergeeventsaction.h"

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

    void refocus();
protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QEventLoop *event;
    void startProgress();
    void endProgress();
    int mouseModifiers;
    void refreshWithEvents(QList<QString> events);
    void refreshWithPhotos(QList<QString> photos);
    QList<AbstractThumbAction*> actions;
    void initActions();
    bool isActionVisible(AbstractThumbAction *action);

signals:
    void photoDoubleClicked(QString photoPath);

public slots:
    void refresh();
    void thumbSizeChanged(int newValue);
    void itemDoubleClicked(QListWidgetItem *item);
    void photoChanged(QString newPhoto);
    void updateActionContext();
};

#endif // THUMBNAILVIEW_H
