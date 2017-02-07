//#include "mainwindow.h"
#include <QApplication>
#include "emuladortelacego.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorTelaCego w;
    w.show();

    return a.exec();
}
