#include "setupwizard.h"

SetupWizard::SetupWizard(QWidget *parent) : QWizard(parent) {
    libraryPage = new LibraryWizardPage(this);

    setModal(true);

    addPage(libraryPage);
    libraryPage->setFinalPage(true);
}

SetupWizard::~SetupWizard() {
    delete libraryPage;
}

QString SetupWizard::getLibraryPath() {
    return libraryPage->getLibraryPath();
}

