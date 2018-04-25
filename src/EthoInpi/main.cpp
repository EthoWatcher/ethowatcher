#include "ethoinpi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EthoInpi w;
    w.show();

    return a.exec();
}
