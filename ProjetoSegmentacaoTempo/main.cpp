#include "mainwindow.h"
#include <QApplication>
#include "emuladorsegmentacaotempo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorSegmentacaoTempo w;
    w.show();

    return a.exec();
}
