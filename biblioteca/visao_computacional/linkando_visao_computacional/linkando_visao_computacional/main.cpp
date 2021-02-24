#include <QCoreApplication>
#include "visao_computacional.h"
#include <QDebug>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Visao_computacional vis;
    vis.Test();
    std::cout << "123123";
    qDebug()<< vis.Soma(10,20);
    return a.exec();
}
