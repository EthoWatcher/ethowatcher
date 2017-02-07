//#include "mainwindow.h"
#include <QApplication>
#include "emuladortelaetografia.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorTelaEtografia w;
    w.show();

    return a.exec();
}
