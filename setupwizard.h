#ifndef SETUPWIZARD_H
#define SETUPWIZARD_H

#include <QObject>
#include <QWidget>
#include <QWizard>
#include <QWizardPage>

#include "librarywizardpage.h"

class SetupWizard : public QWizard
{
    Q_OBJECT
public:
    SetupWizard(QWidget *parent = 0 );
    ~SetupWizard();
    QString getLibraryPath();
private:
    LibraryWizardPage *libraryPage;
};

#endif // SETUPWIZARD_H
