//#include "mainwindow.h"
#include <QApplication>
#include "emuladorverdadeirorealtime.h";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorVerdadeiroRealTime w;
    w.show();

    return a.exec();
}
