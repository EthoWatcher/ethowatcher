#include "interfacedecisao.h"

InterfaceDecisao::InterfaceDecisao(QWidget *parent) : QWidget(parent)
{


}

void InterfaceDecisao::addBotoesInterface(BotoesInterfaces *novoBotoao)
{
    todosBotoes.push_back(novoBotoao);
}
/**
 * @brief InterfaceDecisao::mostraInterface
 * adiciona todos os botões em um layoute vertical
 */
void InterfaceDecisao::mostraInterface()
{
    QLayout *lay = new QVBoxLayout();

    for(int i =0; i<todosBotoes.size();i++){
        lay->addWidget(todosBotoes[i]);
    }

    this->setLayout(lay);

    this->show();
}


