#include "notifier.h"

Notifier::Notifier(QObject *parent) :
    QObject(parent)
{
}

void Notifier::trigger() {
    emit triggered();
}
