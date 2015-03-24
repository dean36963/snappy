#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

class Notifier : public QObject
{
    Q_OBJECT
public:
    explicit Notifier(QObject *parent = 0);
    void trigger();

signals:
    void triggered();

public slots:

};

#endif // NOTIFIER_H
