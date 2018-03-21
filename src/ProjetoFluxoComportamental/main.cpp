//#include "mainwindow.h"
#include <QApplication>
#include "emuladortelafluxocomportamental.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorTelaFluxoComportamental w;
    w.show();

    return a.exec();
}
