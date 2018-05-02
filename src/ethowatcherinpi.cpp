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

}

EthoWatcherInpi::~EthoWatcherInpi()
{
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
    tutorCatalogo->show();
}

/**
 * @brief EthoWatcherInpi::on_pbRegisterVideo_clicked
 */
void EthoWatcherInpi::on_pbRegisterVideo_clicked()
{
    tutorRegistroVideo->show();
}
/**
 * @brief EthoWatcherInpi::on_pbVideoEtho_clicked
 */
void EthoWatcherInpi::on_pbVideoEtho_clicked()
{
    tuto1.show();
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

    configuraLinhas();

}

bool EthoWatcherInpi::botaoClicado(bool clicado)
{

    qDebug() <<"chegou o sinal de clicar no botoao";
    if(tutorEscolhidoE("chaveDigi")){
        qDebug() <<"chave digital";
        proximaInterface(true);

        }

    if(tutorEscolhidoE(("outro"))){
        proximaInterface(true);
    }



}

void EthoWatcherInpi::configuraLinhas()
{

    //arrumando o tutor da seleçãod digital video based ethografi
    estruturaTutorDigi.tutor.append(tutorCatalogo);
    estruturaTutorDigi.tutor.append(tutorRegistroVideo);
    estruturaTutorDigi.tutor.append(tutorVideoTraking);
    estruturaTutorDigi.passoAtual =0;
    estruturaTutorDigi.nomeCaminhotutor = "chaveDigi";

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

    if(ui->cbEthoDigi->isChecked()){
        //configurando apra aparecer os botões
        ui->pbBehavioralCatalog->setVisible(true);
        ui->pbRegisterVideo->setVisible(true);
        ui->pbVideoEtho->setVisible(true);

        //configurando o tutor escolhido
        estruturaTutorEscolhido = estruturaTutorDigi;
        botaoClicado(false);
    }


    if(ui->cbEthoDigiTraking->isChecked()){
        ui->pbRegisterVideo->setVisible(true);
        ui->pbVideoEtho->setVisible(true);


//        estruturaTutorEscolhido = estruturaTutorDigi;
        botaoClicado(false);



    }

    if(ui->cbEthoAna->isChecked()){
        ui->pbTimeSegmentation->setVisible(true);
    }


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
/**
 * @brief EthoWatcherInpi::on_pushButtonVoltar_clicked
 */
void EthoWatcherInpi::on_pushButtonVoltar_clicked()
{
    if(ui->pushButtonVoltar->isEnabled()==true)
    {
//        this->objControleTutorFerramenta->retrocedePasso();

        escondeBotoes();

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

