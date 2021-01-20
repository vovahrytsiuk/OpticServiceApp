#include "mainwindow.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.addLibraryPath(a.applicationDirPath()+"/plugins");


    return a.exec();
}
