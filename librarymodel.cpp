#include "librarymodel.h"

LibraryModel::LibraryModel()
{
    populateModel();
}


void LibraryModel::populateModel() {
    QString rootDirPath = QString::fromUtf8(ApplicationModel::getApplicationModel()->getLibraryDirectory().c_str());
    QDir rootDir = QDir(rootDirPath);
    rootDir.setFilter(QDir::NoDotAndDotDot|QDir::Dirs);
    if(!rootDir.exists()) {
        cout << "Library path doesn't exist, creating..." << endl;
        if(!rootDir.mkdir(rootDirPath)) {
            cerr << "Could not create library path." <<endl;
            return;
        }
    }
    QDirIterator dirIter(rootDir,QDirIterator::Subdirectories);
    while(dirIter.hasNext()) {
        dirIter.next();
        QFileInfo info(dirIter.filePath());
        if(EventFolder::isValidEventFolderPath(info.absoluteDir())) {
            cout << info.absoluteFilePath().toStdString() << " IS an event folder" <<endl;
        } else {
            cout << info.absoluteFilePath().toStdString() << " is NOT an event folder" <<endl;
        }
    }
}
