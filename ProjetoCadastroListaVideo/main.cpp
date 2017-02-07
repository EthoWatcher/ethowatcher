//#include "mainwindow.h"
#include <QApplication>
#include "emuladorcadastrolistavideo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorCadastroListaVideo w;
    w.show();

    return a.exec();
}
