//#include "mainwindow.h"
#include <QApplication>
#include "emuladormatiztransicao.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorMatizTransicao w;
    w.show();

    return a.exec();
}
