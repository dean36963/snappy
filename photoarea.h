#ifndef PHOTOAREA_H
#define PHOTOAREA_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include "applicationmodel.h"

class PhotoArea : public QWidget
{
    Q_OBJECT
public:
    explicit PhotoArea(QWidget *parent = 0);
    ~PhotoArea();
private:

    QGridLayout *layout;
    QLabel *label;
signals:

public slots:
    void eventChanged();
};

#endif // PHOTOAREA_H
