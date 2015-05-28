#ifndef MERGEEVENTSACTION_H
#define MERGEEVENTSACTION_H

#include "src/actions/thumbview/abstractthumbaction.h"
#include "src/utils/rolesenums.h"
#include "src/utils/libraryutils.h"

#include <QObject>
#include <QInputDialog>

class MergeEventsAction : public AbstractThumbAction
{
    Q_OBJECT
public:
    explicit MergeEventsAction(QWidget *parent);
public slots:
    void mergeEvents();
};

#endif // MERGEEVENTSACTION_H
