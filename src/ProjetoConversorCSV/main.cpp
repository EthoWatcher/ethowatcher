//#include "mainwindow.h"
#include <QApplication>
#include "emuladorconversor.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorConversor w;
    w.show();

    return a.exec();
}
