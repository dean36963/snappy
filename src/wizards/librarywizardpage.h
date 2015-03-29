#ifndef LIBRARYWIZARDPAGE_H
#define LIBRARYWIZARDPAGE_H

#include <QObject>
#include <QWidget>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>

#include "src/model/applicationmodel.h"

class LibraryWizardPage : public QWizardPage
{
    Q_OBJECT
public:
    LibraryWizardPage(QWidget *parent = 0);
    ~LibraryWizardPage();
    virtual bool isComplete() const;
    QString getLibraryPath();

    QLabel *pathLabel;
    QLineEdit *pathLineEdit;
    QPushButton *pathButton;
    QGridLayout *layout;
    QLabel *details;
public slots:
    void openFileDialog();
};

#endif // LIBRARYWIZARDPAGE_H
