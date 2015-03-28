#include "librarywizardpage.h"

LibraryWizardPage::LibraryWizardPage(QWidget *parent) : QWizardPage(parent) {
    setTitle("Library Settings");
    setSubTitle("Specify where Snappy's library will reside.");

    pathLabel = new QLabel("Library Path: ");
    pathLineEdit = new QLineEdit;
    pathLineEdit->setText(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    pathButton = new QPushButton("Browse");
    pathLabel->setBuddy(pathLineEdit);

    QString detailMessage("Please provide a directory that Snappy will use as a library. ");
    detailMessage.append("This can be an existing directory, or a new one. ");
    detailMessage.append("If it is an existing directory containing photos, ");
    detailMessage.append("bear in mind that Snappy imports new photos at locations like: ");
    detailMessage.append("\'SNAPPY_LIBRARY/2014/12/25/img.jpg\', ");
    detailMessage.append("so if your photos are organised differently you might want to ");
    detailMessage.append("choose a new directory and reimport your photos.");

    details = new QLabel(detailMessage);
    details->setWordWrap(true);

    layout = new QGridLayout(this);
    layout->addWidget(pathLabel,0,0);
    layout->addWidget(pathLineEdit,0,1);
    layout->addWidget(pathButton,0,2);
    layout->addWidget(details,1,0,1,3);
    setLayout(layout);

    connect(pathButton,SIGNAL(clicked()),this,SLOT(openFileDialog()));

    registerField("Library Path",pathLineEdit);
}

LibraryWizardPage::~LibraryWizardPage()
{
    delete pathLabel;
    delete pathLineEdit;
    delete pathButton;
    delete layout;
    delete details;
}

bool LibraryWizardPage::isComplete() const {
    QFileInfo info(pathLineEdit->text());
    if(info.exists() && info.isDir()) {
        return true;
    }
    return false;
}

void LibraryWizardPage::openFileDialog() {
    QFileDialog dialog(this);
    QString chosenDir = dialog.getExistingDirectory(this,"Select a photo library folder",QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    if(chosenDir!="") {
        pathLineEdit->setText(chosenDir);
        emit completeChanged();
    }
}

QString LibraryWizardPage::getLibraryPath() {
    return pathLineEdit->text();
}
