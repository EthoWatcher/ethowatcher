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
//   qDebug ()<< tutor.getTextoById("j");

   controlWarnig = new ControladoWarningTutor(":/tutor/tutores/ethowatcherInpi.xml");
   QList<QString> seq;

   seq.append("ethoInicio");
   seq.append("ethoCatalogo");

   controlWarnig->setLista(seq);

   controlWarnig->nextList(false);



   tutor.lerXml(":/tutor/tutores/ethowatcherInpi.xml");

    ui->textoTutor->setText(tutor.getTextoById("ethoInicio"));
    tutor.debugID();

    QString html;


    //deixando todos os boteos invisiveisi
    escondeBotoes();
    ui->stackedPassos->setCurrentIndex(0);



    //arrumando os tutores
    ArrumandoTutores();
//    configuraLinhas();





//    ui->stackedPassos->setCurrentIndex(0);
//    ui->imgCfgStaCal->setVisible(false);
//    ui->imgCfgStaCatEto->setVisible(false);
//    ui->rotCfgCal->setVisible(false);
//    ui->rotCfgCatEto->setVisible(false);
//    ui->radCatAutExc->setChecked(true);
//    this->objControleTutorFerramenta = new TControleTutorFerramenta;
//    this->objControleTutorFerramenta->setPageCalibracao(ui->pageCalibracao);
//    this->objControleTutorFerramenta->setPageCatalogoEtografico(ui->pageCatalogoEtografico);
//    this->objControleTutorFerramenta->setPageTipEto(ui->pageTipEto);
//    this->objControleTutorFerramenta->setPageStartAnalysis(ui->pageStartAnalysis);
//    this->objControleTutorFerramenta->setStackedPassos(ui->stackedPassos);
//    this->objControleTutorFerramenta->setGrpStatus(ui->grpStatus);
//    this->objControleTutorFerramenta->setGrpTutor(ui->grpTutor);
//    this->objControleTutorFerramenta->setChkOpcEtoAmb(ui->chkOpcEtoAmb);
//    this->objControleTutorFerramenta->setChkOpcEtoMan(ui->chkOpcEtoMan);
//    this->objControleTutorFerramenta->setChkOpcEtoTrk(ui->chkOpcEtoTrk);
//    this->objControleTutorFerramenta->setRotCfgCatEto(ui->rotCfgCatEto);
//    this->objControleTutorFerramenta->setRotCfgCal(ui->rotCfgCal);
//    this->objControleTutorFerramenta->setImgCfgStaCatEto(ui->imgCfgStaCatEto);
//    this->objControleTutorFerramenta->setImgCfgStaCal(ui->imgCfgStaCal);
//    this->objControleTutorFerramenta->setTextoTutor(ui->textoTutor);
//    this->objControleTutorFerramenta->avancaPasso();
    palette.setColor(QPalette::WindowText, Qt::red);
//    this->objControleTutorFerramenta->sinalizaEtapaCalibracaoEmAberto(palette);
//    this->objControleTutorFerramenta->sinalizaEtapaCatalogoEtograficoEmAberto(palette);

//    new QShortcut( Qt::Key_X, this, SLOT(on_pushButtonAvancar_clicked()));
//    new QShortcut( Qt::Key_Z, this, SLOT(on_pushButtonVoltar_clicked()));

//    ui->pushButtonAvancar->setToolTip("Clik or press 'D' to go forward.");
//    ui->pushButtonVoltar->setToolTip("Click or press 'A' to go back.");
//    ui->btAbrCatEto->setToolTip("Click for create a new catalog.");
//    ui->brNovCatEto->setToolTip("Click for open the catalog.");
//    ui->botCalibracao->setToolTip("Click for calibration.");
//    ui->btIniciarAnalise->setToolTip("Click for start the analysis.");

    controleCalibracao=true;
    controleCatalogo=true;
    controleOpcoesEtografia=false;

    ui->cbEthoAna->setVisible(false);
    ui->cbTutor->setVisible(false);
     ui->stackedPassos->setEnabled(false);
//     ui->grpTutor->setVisible(false);




     this->show();



     estruturaTutorEscolhido = estruturaInicio;
//     estruturaTutorEscolhido.tutor[0]->show();
//     qDebug()<< estruturaTutorEscolhido.passoAtual ;
     estruturaTutorEscolhido.tutor[estruturaTutorEscolhido.passoAtual]->show();
//     proximaInterface(false);


}

EthoWatcherInpi::~EthoWatcherInpi()
{

//    if(telaPessoa->nomeArquivo !=""){

//        telaPessoa->gravandoUserXML();

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

void EthoWatcherInpi::ArrumandoTutores()
{
    tutorInicio = new WarningTutor();

    connect(tutorInicio,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorInicio->setTextDestaque(tutor.getTextoById("ethoInicioTitulo"));
    tutorInicio->setId("ethoInicio");
    tutorInicio->setTextTutor(tutor.getTextoById("ethoInicio"));
    tutorInicio->setTextYes("yes");
    tutorInicio->setTextNo("No");

    tutorCatalogo = new WarningTutor();

    connect(tutorCatalogo,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorCatalogo->setTextDestaque("Do you have a catalog ?");
    tutorCatalogo->setTextTutor(tutor.getTextoById("ethoCatalogo"));
    tutorCatalogo->setTextYes("yes");
    tutorCatalogo->setTextNo("No");


    tutorRegistroVideo = new WarningTutor();
    connect(tutorRegistroVideo,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorRegistroVideo->setTextDestaque("Do you have a register off video ?");
    tutorRegistroVideo->setTextTutor(tutor.getTextoById("ethoregistroVideo"));
    tutorRegistroVideo->setTextYes("yes");
    tutorRegistroVideo->setTextNo("No");

    tutorVideoTraking = new WarningTutor();
    connect(tutorVideoTraking,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorVideoTraking->setTextDestaque("Do you wanna make a etografia or traking ?");
    tutorVideoTraking->setTextTutor(tutor.getTextoById("ethoregistroVideoTraking"));
    tutorVideoTraking->setTextYes("yes");
    tutorVideoTraking->setTextNo("No");



    tutorSegComp = new WarningTutor();
    connect(tutorSegComp,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorSegComp->setTextDestaque("Do you wanna make a segmentacao por comportamento ?");
    tutorSegComp->setTextTutor(tutor.getTextoById("ethoregistroVideoTraking"));
    tutorSegComp->setTextYes("yes");
    tutorSegComp->setTextNo("No");


    tutorSegTempo = new WarningTutor();
    connect(tutorSegTempo,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorSegTempo->setTextDestaque("Do you wanna make a segmentacao por tempo ?");
    tutorSegTempo->setTextTutor(tutor.getTextoById("ethoregistroVideoTraking"));
    tutorSegTempo->setTextYes("yes");
    tutorSegTempo->setTextNo("No");

    tutorAnaSeq = new WarningTutor();
    connect(tutorAnaSeq,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorAnaSeq->setTextDestaque("Do you wanna make a analise sequencial ?");
    tutorAnaSeq->setTextTutor(tutor.getTextoById("ethoregistroVideoTraking"));
    tutorAnaSeq->setTextYes("yes");
    tutorAnaSeq->setTextNo("No");


    tutorAnaConcordancia = new WarningTutor();
    connect(tutorAnaConcordancia,SIGNAL(clicou(bool)),this,SLOT(botaoClicado(bool)));
    tutorAnaConcordancia->setTextDestaque("Do you wanna make uma analise de concordancia ?");
    tutorAnaConcordancia->setTextTutor(tutor.getTextoById("ethoregistroVideoTraking"));
    tutorAnaConcordancia->setTextYes("yes");
    tutorAnaConcordancia->setTextNo("No");



    configuraLinhas();

}

bool EthoWatcherInpi::botaoClicado(bool clicado)
{

    qDebug() <<"chegou o sinal de clicar no botoao";

    if(estruturaTutorEscolhido.tutor[estruturaTutorEscolhido.passoAtual]->getId("ethoInicio")){
        qDebug() <<"oi mundo ";
        if(clicado){

            ui->pbLoadUser->click();
        }else{
            ui->pbCreateUser->click();
        }

    }


    proximaInterface(true);


//    if(tutorEscolhidoE("chaveDigi")){
//        qDebug() <<"chave digital";
//        proximaInterface(true);

//        }

//    if(tutorEscolhidoE("chaveDigi")){
//        qDebug() <<"chave digital";
//        proximaInterface(true);

//        }

//    if(tutorEscolhidoE("chaveTrakin")){
//        qDebug() <<"chave digital";
//        proximaInterface(true);

//        }

//    if(tutorEscolhidoE(("chaveDigiAna"))){
//        proximaInterface(true);
//    }

//    if(tutorEscolhidoE(("chaveAna"))){
//
//    }








}

void EthoWatcherInpi::configuraLinhas()
{

    estruturaInicio.tutor.append(tutorInicio);
    estruturaInicio.passoAtual =0;
    estruturaInicio.nomeCaminhotutor = "chaveInicio";


    //arrumando o tutor da seleçãod digital video based ethografi
    estruturaTutorDigi.tutor.append(tutorCatalogo);
    estruturaTutorDigi.tutor.append(tutorRegistroVideo);
    estruturaTutorDigi.tutor.append(tutorVideoTraking);
    estruturaTutorDigi.passoAtual =0;
    estruturaTutorDigi.nomeCaminhotutor = "chaveDigi";


    estruturaTutorTraking.tutor.append(tutorRegistroVideo);
    estruturaTutorTraking.tutor.append(tutorVideoTraking);
    estruturaTutorTraking.passoAtual =0;
    estruturaTutorTraking.nomeCaminhotutor = "chaveTrakin";


    estruturaTutorAnalys.tutor.append(tutorSegTempo);
    estruturaTutorAnalys.tutor.append(tutorSegComp);
    estruturaTutorAnalys.tutor.append(tutorAnaSeq);
    estruturaTutorAnalys.tutor.append(tutorAnaConcordancia);
    estruturaTutorAnalys.passoAtual =0;
    estruturaTutorAnalys.nomeCaminhotutor = "chaveAna";




    estruturaTutorDigiAnalys.tutor.append(tutorRegistroVideo);
    estruturaTutorDigiAnalys.tutor.append(tutorVideoTraking);
    estruturaTutorDigiAnalys.tutor.append(tutorSegTempo);
    estruturaTutorDigiAnalys.tutor.append(tutorSegComp);
    estruturaTutorDigiAnalys.tutor.append(tutorAnaSeq);
    estruturaTutorDigiAnalys.tutor.append(tutorAnaConcordancia);
    estruturaTutorDigiAnalys.passoAtual =0;
    estruturaTutorDigiAnalys.nomeCaminhotutor = "chaveDigiAna";




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
 */
void EthoWatcherInpi::proximaInterface(bool chNext){
    if(chNext){
        if(estruturaTutorEscolhido.tutor.size() >estruturaTutorEscolhido.passoAtual){
         estruturaTutorEscolhido.tutor[estruturaTutorEscolhido.passoAtual]->show();
            estruturaTutorEscolhido.passoAtual++;
        }
    }else{
        estruturaTutorEscolhido.tutor[estruturaTutorEscolhido.passoAtual]->show();
    }

}



/**
 * @brief EthoWatcherInpi::on_pushButtonAvancar_clicked
 */

void EthoWatcherInpi::on_pushButtonAvancar_clicked()
{



    //selecionado só etografia
    //porem é o emsmo caminho quando seleciona a etografia e o trakin
    if(ui->cbEthoDigi->isChecked()){
        configurandoEtografia();

    // foi selecionado só o trakin
    }else if(ui->cbEthoDigiTraking->isChecked()){
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

    //configurando o tutor escolhido
    estruturaTutorEscolhido = estruturaTutorDigi ;
    botaoClicado(false);
    qDebug() << "o selecionado foi a etografia";

}

void EthoWatcherInpi::configurandoAnalise(){
    //configurando apra aparecer os botões
    ui->pbTimeSegmentation->setVisible(true);
    ui->pbSegCompor->setVisible(true);
    ui->pbAnaliseSeque->setVisible(true);
    ui->pbAnliseConcor->setVisible(true);

    estruturaTutorEscolhido =  estruturaTutorAnalys;
    botaoClicado(false);

}

void EthoWatcherInpi::configurandoTrackin(){
    ui->pbRegisterVideo->setVisible(true);
    ui->pbVideoEtho->setVisible(true);


    estruturaTutorEscolhido = estruturaTutorTraking;
    botaoClicado(false);
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




void EthoWatcherInpi::on_pbConfigAnalyses_clicked()
{
    setNextInterface();
    configurandoAnalise();

}

void EthoWatcherInpi::on_pbCreateUser_clicked()
{
    telaPessoa = new telaCadastroPessoa();
    telaPessoa->show();
    if(telaPessoa->tutor == 1){
        ui->cbTutor->setChecked(true);
    }else{
        ui->cbTutor->setChecked(false);
    }

    ui->lblNomeUsuario->setText(telaPessoa->nome);

    ui->stackedPassos->setEnabled(true);
    ui->pbLoadUser->setEnabled(false);
    ui->pbCreateUser->setEnabled(false);
}

void EthoWatcherInpi::on_pbLoadUser_clicked()
{
    telaPessoa = new telaCadastroPessoa();
    if(telaPessoa->loadUser()){
        qDebug() << telaPessoa->nomeArquivo;

        if(telaPessoa->getTutor()){
            ui->cbTutor->setCheckable(true);
        }else{
            ui->cbTutor->setCheckable(false);
        }

        ui->lblNomeUsuario->setText(telaPessoa->nome);
         ui->stackedPassos->setEnabled(true);
         ui->pbLoadUser->setEnabled(false);
         ui->pbCreateUser->setEnabled(false);

    }else{

        qDebug() << "voce não carregou nenhum usuario";
    }


}

void EthoWatcherInpi::on_cbTutor_clicked(bool checked)
{
    telaPessoa->setTutor(checked);
}
