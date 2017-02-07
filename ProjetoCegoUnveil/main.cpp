//#include "mainwindow.h"
#include <QApplication>
#include "emuladorunveil.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorUnveil w;
    w.show();

    return a.exec();
}
