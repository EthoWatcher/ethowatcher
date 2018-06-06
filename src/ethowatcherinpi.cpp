#include "ethowatcherinpi.h"
#include "ui_ethowatcherinpi.h"
//#include "novocatalogo.h"
#include <QFileDialog>
#include <QShortcut>
#include <QDesktopWidget>
#include <QMessageBox>

EthoWatcherInpi::EthoWatcherInpi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EthoWatcherInpi)
{
   ui->setupUi(this);

   connect(ui->actionControl_Tutor, SIGNAL(triggered(bool)),this,SLOT(clicouTelaLicensa(bool)));
//   qDebug ()<< tutor.getTextoById("j");

//   controlInicio = new  ControladoWarningTutor(":/tutor/tutores/ethowatcherInpi.xml");
//   QList<QString> seq1;
//   seq1.append("ethoApresentacao");
//   seq1.append("ethoInicio");



   //novos
   controlWarnig = new ControladoWarningTutor(":/tutor/tutores/ethowatcherInpi.xml");
   connect(controlWarnig,SIGNAL(clicou(bool,QString)),this,SLOT(botaoClicado(bool,QString)));



   configuraLinhas();


//   controlWarnig->setLista(seqInicial);








    QString html;

    //deixando todos os boteos invisiveisi
    escondeBotoes();
    ui->stackedPassos->setCurrentIndex(0);
//    ArrumandoTutores();

    palette.setColor(QPalette::WindowText, Qt::red);

    controleCalibracao=true;
    controleCatalogo=true;
    controleOpcoesEtografia=false;

    ui->cbEthoAna->setVisible(false);
//    ui->cbTutorEthoPrincipal->setVisible(false);
     ui->stackedPassos->setEnabled(false);
     ui->grpTutor->setVisible(false);




     this->show();

     controlWarnig->setLista(seqInicial);
     controlWarnig->nextList(true);
        telaPessoa = new telaCadastroPessoa();

}

void EthoWatcherInpi::closeEvent (QCloseEvent *event)
{
    qDebug() << "fechou janela ";
    controlWarnig->fechandoJanelas();
}
EthoWatcherInpi::~EthoWatcherInpi()
{

//    if(telaPessoa->nomeArquivo !=""){

//        telaPessoa->gravandoUserXML();

//    }
//    if(telaPessoa != NULL ){
//      delete telaPessoa;
//    }


    delete telaPessoa;


    delete ui;
}

//QPushButton EthoWatcherInpi::getButon()
//{
//    return ui->pushButtonAvancar;
//}


/**
 * @brief EthoWatcherInpi::on_pbBehavioralCatalog_clicked
 */
void EthoWatcherInpi::on_pbBehavioralCatalog_clicked()
{
    telaCatalogo = new telaCadastroCatalago();
    telaCatalogo->show();
}

/**
 * @brief EthoWatcherInpi::on_pbRegisterVideo_clicked
 */
void EthoWatcherInpi::on_pbRegisterVideo_clicked()
{

}
/**
 * @brief EthoWatcherInpi::on_pbVideoEtho_clicked
 */
void EthoWatcherInpi::on_pbVideoEtho_clicked()
{

}
/**
 * @brief EthoWatcherInpi::on_cbEthoDigi_clicked
 */
void EthoWatcherInpi::on_cbEthoDigi_clicked()
{

}

/**
 * @brief EthoWatcherInpi::on_cbEthoAna_clicked
 */
void EthoWatcherInpi::on_cbEthoAna_clicked()
{

}

void EthoWatcherInpi::escondeBotoes()
{
    ui->pbBehavioralCatalog->setVisible(false);
    ui->pbRegisterVideo->setVisible(false);
    ui->pbVideoEtho->setVisible(false);
    ui->pbTimeSegmentation->setVisible(false);
    ui->pbAnaliseSeque->setVisible(false);
    ui->pbAnliseConcor->setVisible(false);
    ui->pbSegCompor->setVisible(false);


}


bool EthoWatcherInpi::botaoClicado(bool clicado, QString id)
{

    qDebug() << " o id chegou " + id;
    if(id == "ethoInicio"){
        controlWarnig->nextList(true);
    }

    if(id == "ethoCadastroPessoa"){
        qDebug() <<"oi mundo ";
        if(clicado){
            ui->pbCreateUser->click();

        }else{

            ui->pbLoadUser->click();

        }

    }

    if(id == "ethoCatalogo"){
        if(clicado){
            ui->pbBehavioralCatalog->click();

        }else{

            controlWarnig->nextList(true);

        }

    }



}

void EthoWatcherInpi::configuraLinhas()
{

    //sequencia inicial
    seqInicial.append("ethoInicio");
    seqInicial.append("ethoCadastroPessoa");
    seqInicial.append("ethoEscolhaEthoTraking");

//    seqInicial.append("default");

    //sequencia por traking
    seqTrakin.append("ethoregistroTraking");
    seqTrakin.append("ethoTrakingVideo");

    //sequencia por catalogo
    seqEtho.append("ethoCatalogo");
    seqEtho.append("ethoRegistroVideo");
    seqEtho.append("ethoEtho");


    //sequencia de analise
    seqAnalise.append("tutorSegTempo");
    seqAnalise.append("tutorSegComp");
    seqAnalise.append("tutorAnaSeq");
    seqAnalise.append("tutorConcordancia");




}
/**
 * @brief EthoWatcherInpi::tutorEscolhidoE
 * @param nomeTutor
 * @return
 */
bool EthoWatcherInpi::tutorEscolhidoE(QString nomeTutor){
    if(estruturaTutorEscolhido.nomeCaminhotutor == nomeTutor){
        return true;
    }else{
        return false;
    }

    return false;
}
/**
 * @brief EthoWatcherInpi::proximaInterface
 * @param chNext
 * retirar
 */
void EthoWatcherInpi::proximaInterface(bool chNext){
//    if(chNext){
//        if(estruturaTutorEscolhido.tutor.size() >estruturaTutorEscolhido.passoAtual){
//         estruturaTutorEscolhido.tutor[estruturaTutorEscolhido.passoAtual]->show();
//            estruturaTutorEscolhido.passoAtual++;
//        }
//    }else{
//        estruturaTutorEscolhido.tutor[estruturaTutorEscolhido.passoAtual]->show();
//    }

}



/**
 * @brief EthoWatcherInpi::on_pushButtonAvancar_clicked
 */

void EthoWatcherInpi::on_pushButtonAvancar_clicked()
{



    //selecionado só etografia
    //porem é o emsmo caminho quando seleciona a etografia e o trakin
    if(ui->cbEthoDigi->isChecked()){
        controlWarnig->setLista(seqEtho);
        controlWarnig->nextList(true);
        configurandoEtografia();

    // foi selecionado só o trakin
    }else if(ui->cbEthoDigiTraking->isChecked()){
        controlWarnig->setLista(seqTrakin);
        controlWarnig->nextList(true);
        configurandoTrackin();

    }


    setNextInterface();


}


void EthoWatcherInpi::setNextInterface(){
    //controlando a janela

      //  this->objControleTutorFerramenta->avancaPasso();

        janelaAtual = ui->stackedPassos->currentIndex();
        qtdJanelas = ui->stackedPassos->count();

        if(janelaAtual==0)
            ui->pushButtonVoltar->setEnabled(true);

        if(janelaAtual < qtdJanelas )
        {
            if(janelaAtual== (qtdJanelas-2))
                ui->pushButtonAvancar->setEnabled(false);

            ui->stackedPassos->setCurrentIndex(janelaAtual+1);
        }

}

void EthoWatcherInpi::configurandoEtografia(){
    //configurando apra aparecer os botões
    ui->pbBehavioralCatalog->setVisible(true);
    ui->pbRegisterVideo->setVisible(true);
    ui->pbVideoEtho->setVisible(true);

//    //configurando o tutor escolhido
//    estruturaTutorEscolhido = estruturaTutorDigi ;
//    botaoClicado(false);
    qDebug() << "o selecionado foi a etografia";

}

void EthoWatcherInpi::configurandoAnalise(){
    //configurando apra aparecer os botões
    ui->pbTimeSegmentation->setVisible(true);
    ui->pbSegCompor->setVisible(true);
    ui->pbAnaliseSeque->setVisible(true);
    ui->pbAnliseConcor->setVisible(true);

    estruturaTutorEscolhido =  estruturaTutorAnalys;
//    botaoClicado(false);

}

void EthoWatcherInpi::configurandoTrackin(){
    ui->pbRegisterVideo->setVisible(true);
    ui->pbVideoEtho->setVisible(true);


    estruturaTutorEscolhido = estruturaTutorTraking;
//    botaoClicado(false);
    qDebug() << "o selecionado foi o trakin";

}


/**
 * @brief EthoWatcherInpi::on_pushButtonVoltar_clicked
 */
void EthoWatcherInpi::on_pushButtonVoltar_clicked()
{
    if(ui->pushButtonVoltar->isEnabled()==true)
    {
//        this->objControleTutorFerramenta->retrocedePasso();

//        escondeBotoes();

        janelaAtual = ui->stackedPassos->currentIndex();
        qtdJanelas = ui->stackedPassos->count();
        if(janelaAtual == 3){
            ui->stackedPassos->setCurrentIndex(0);
        }else{

            if(janelaAtual>0)
            {
                if(janelaAtual==(qtdJanelas-1))
                    ui->pushButtonAvancar->setEnabled(true);

                if(janelaAtual==1)
                    ui->pushButtonVoltar->setEnabled(false);

                ui->stackedPassos->setCurrentIndex(janelaAtual-1);
            }
        }


    }
}




void EthoWatcherInpi::on_pbConfigAnalyses_clicked()
{

    controlWarnig->setLista(seqAnalise);
    controlWarnig->nextList(true);
    setNextInterface();
    configurandoAnalise();

}

void EthoWatcherInpi::on_pbCreateUser_clicked()
{
    telaPessoa = new telaCadastroPessoa();
    telaPessoa->showInterface();
    //        controlWarnig->nextList(true);
    connect(telaPessoa, SIGNAL(fechouJanela()),this, SLOT(telaFechou()));



}





void EthoWatcherInpi::on_pbLoadUser_clicked()
{
    telaPessoa = new telaCadastroPessoa();

    connect(telaPessoa, SIGNAL(fechouJanela()),this, SLOT(telaFechou()));
    if(telaPessoa->loadUser()){
        qDebug() << telaPessoa->nomeArquivo;

        configurandoOsTutores();

    }else{

        qDebug() << "voce não carregou nenhum usuario";
    }


}

void EthoWatcherInpi::configurandoOsTutores(){

//    qDebug() << "o tutor esta " << telaPessoa->getTutor("tutorEthoWatcherPrincipal");
    ui->cbTutorEthoPrincipal->setChecked(true);
    ui->cbTutorCadastroCatalogo->setChecked(true);
     ui->cbTutorCadastroUsuario->setChecked(true);

    ui->cbTutorEthoPrincipal->setChecked(telaPessoa->getTutor("tutorEthoWatcherPrincipal"));
    ui->cbTutorCadastroCatalogo->setChecked(telaPessoa->getTutor("tutorCadastroCatalogo"));
    ui->cbTutorCadastroUsuario->setChecked(telaPessoa->getTutor("tutorCadastroUsuario"));

    ui->lblNomeUsuario->setText(telaPessoa->nome);
     ui->stackedPassos->setEnabled(true);
     ui->pbLoadUser->setEnabled(false);
     ui->pbCreateUser->setEnabled(false);


     configuraHabiTutores();


}

void EthoWatcherInpi::telaFechou(){
    if(telaPessoa->createdUser()){
        configurandoOsTutores();
    }else{
        qDebug()<< "não configurado os tutores";
    }
    controlWarnig->nextList(true);
}

void EthoWatcherInpi::clicouTelaLicensa(bool tela)
{

    qDebug() << " o valor clicado " << tela;
    ui->stackedPassos->setCurrentIndex(3);
    ui->pushButtonVoltar->setEnabled(true);
}


void EthoWatcherInpi::on_cbTutorEthoPrincipal_clicked(bool checked)
{
    telaPessoa->setTutor("tutorEthoWatcherPrincipal",checked);
    configuraHabiTutores();
}

void EthoWatcherInpi::on_cbTutorCadastroCatalogo_clicked(bool checked)
{
    telaPessoa->setTutor("tutorCadastroCatalogo",checked);
    configuraHabiTutores();
}


void EthoWatcherInpi::on_cbTutorCadastroUsuario_clicked(bool checked)
{
    telaPessoa->setTutor("tutorCadastroUsuario",checked);
    configuraHabiTutores();
}

void EthoWatcherInpi::configuraHabiTutores(){


    controlWarnig->setTutor(telaPessoa->getTutor("tutorEthoWatcherPrincipal"));
}
