#include "ethoinpi.h"
#include "ui_ethoinpi.h"


EthoInpi::EthoInpi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EthoInpi)
{
    ui->setupUi(this);
}

EthoInpi::~EthoInpi()
{
    delete ui;
}

void EthoInpi::on_pbLoadUser_clicked()
{
    ui->swPrincipal->setCurrentIndex(1);

}

void EthoInpi::on_pbTranscrition_clicked()
{

// cria uma nova janela de transcrição
    InterfaceDecisao *novaTelaTrascription = new InterfaceDecisao();


 // addiciona uma nova tela cadastro
    telaCadastroCatalago * cads = new telaCadastroCatalago();
//    telaCadastroFilme* filme = new telaCadastroFilme();
//    telaCadastroFilme * filme = new telaCadastroFilme();


    novaTelaTrascription->addBotoesInterface(adicionaInterfaceNoBotao(cads));
 //   novaTelaTrascription->addBotoesInterface(adicionaInterfaceNoBotao(filme));

    novaTelaTrascription->mostraInterface();


}

BotoesInterfaces *EthoInpi::adicionaInterfaceNoBotao(QWidget *novaInterface){
    BotoesInterfaces *botao = new BotoesInterfaces(novaInterface);
    return botao;
}
