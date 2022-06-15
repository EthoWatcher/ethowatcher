#include "Reliability.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Reliability w;
    w.show();
    return a.exec();
}
