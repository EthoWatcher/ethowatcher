#include "botoesinterfaces.h"

BotoesInterfaces::BotoesInterfaces(QWidget *InterfaceEtho)
{
    this->nova = InterfaceEtho;
    this->setText("oi");
    qDebug("oi mundo");
    connect(this,SIGNAL(clicked(bool)),this,SLOT(botaoClicado(bool)));
//    QObject::connect(this,SIGNAL(clicked(bool)),this,SLOT(botaoClicado(bool)));



}

void BotoesInterfaces::botaoClicado(bool clickado)
{
    qDebug("botao clicaldo");
    this-> nova->show();
}
