#include "botoesinterfaces.h"

BotoesInterfaces::BotoesInterfaces(QWidget *InterfaceEtho)
{
    this->nova = InterfaceEtho;

    this->setText("oi");

    connect(this,SIGNAL(pressed()),this,SLOT(botaoClicado()));
//    QObject::connect(this,SIGNAL(clicked(bool)),this,SLOT(botaoClicado(bool)));



}

void BotoesInterfaces::botaoClicado()
{


    this-> nova->show();
    //caso a interface tenha sido destruida


}
