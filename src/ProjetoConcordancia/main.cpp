#include "mainwindow.h"
#include <QApplication>
#include "emuladortelaconcordancia.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorTelaConcordancia w;
    w.show();

    return a.exec();
}
