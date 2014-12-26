#include "librarymodel.h"

LibraryModel::LibraryModel(QString path)
{
    populateModel(path);
}

LibraryModel::~LibraryModel() {

}

void LibraryModel::populateModel(QString path) {
    QDir rootDir = QDir(path);
    rootDir.setFilter(QDir::NoDotAndDotDot|QDir::Dirs);
    if(!rootDir.exists()) {
        cout << "Library path doesn't exist, creating..." << endl;
        if(!rootDir.mkdir(path)) {
            cerr << "Could not create library path." <<endl;
            return;
        }
    }
    QDirIterator dirIter(rootDir,QDirIterator::Subdirectories);
    while(dirIter.hasNext()) {
        dirIter.next();
        QFileInfo info(dirIter.filePath());
        EventFolder ev(path);
        if(ev.isValidEventFolderPath(info.absoluteDir())) {
            cout << info.absoluteFilePath().toStdString() << " IS an event folder" <<endl;
        } else {
            cout << info.absoluteFilePath().toStdString() << " is NOT an event folder" <<endl;
        }
    }
}
