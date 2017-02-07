//#include "mainwindow.h"
#include <QApplication>
#include "emuladorcadastropessoa.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmuladorCadastroPessoa w;
    w.show();

    return a.exec();
}
