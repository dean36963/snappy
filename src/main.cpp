#include "src/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if(!w.hasQuit()) {
        w.show();
        return a.exec();
    }
}
