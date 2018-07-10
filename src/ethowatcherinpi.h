#ifndef ETHOWATCHERINPI_H
#define ETHOWATCHERINPI_H


#include <QMainWindow>
//#include "tutoretho.h"
#include "warningtutor.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include "telacadastropessoa.h"
#include "telacadastrocatalago.h"
#include "telacadastrofilme.h"

#include "controladorinterfaces.h"


namespace Ui {
class EthoWatcherInpi;
}

class EthoWatcherInpi : public QMainWindow
{
    Q_OBJECT

public:
    explicit EthoWatcherInpi(QWidget *parent = 0);
    ~EthoWatcherInpi();

    void carregaImagens( const char * imagem = 0);
    QPushButton getButon();
    //void setResultadoCalibracao(QString *);

    void configurandoEtografia();
    void configurandoTrackin();
    void configurandoAnalise();
    void configurandoOsTutores();
    void closeEvent(QCloseEvent *event);


public slots:
    void telaFechou();
    void clicouTelaLicensa(bool tela);
private slots:

    void on_pushButtonAvancar_clicked();

    void on_pushButtonVoltar_clicked();

    void on_pbBehavioralCatalog_clicked();

    void on_pbRegisterVideo_clicked();

    void on_pbVideoEtho_clicked();

    void on_cbEthoDigi_clicked();

    void on_cbEthoAna_clicked();
    void escondeBotoes();
    bool botaoClicado(bool clicado, QString id);
    void configuraLinhas();
    bool tutorEscolhidoE(QString nomeTutor);
    void proximaInterface(bool chNext);

    void on_pbConfigAnalyses_clicked();

    void on_pbCreateUser_clicked();

    void on_pbLoadUser_clicked();

//    void on_cbTutor_clicked(bool checked);

    void on_cbTutorEthoPrincipal_clicked(bool checked);

    void on_cbTutorCadastroCatalogo_clicked(bool checked);


    void on_cbTutorCadastroUsuario_clicked(bool checked);

private:
    Ui::EthoWatcherInpi *ui;
    int janelaAtual;
    int qtdJanelas;
    QPalette palette;

    ControladoWarningTutor *controlWarnig;

    QList<QString> seqInicial;
    QList<QString> seqTrakin;
    QList<QString> seqEtho;
    QList<QString> seqAnalise;


    struct EstruturaDeTutor{
        QList<WarningTutor*> tutor;
        int passoAtual;
        QString nomeCaminhotutor;
    };

    EstruturaDeTutor estruturaInicio;
    EstruturaDeTutor estruturaTutorEscolhido;
    EstruturaDeTutor estruturaTutorDigi;
    EstruturaDeTutor estruturaTutorTraking;
    EstruturaDeTutor estruturaTutorAnalys;
    EstruturaDeTutor estruturaTutorDigiAnalys;
    EstruturaDeTutor estruturaTutorTrakingAnalys;


    WarningTutor *tutorInicio;
    WarningTutor *tutorCatalogo;
    WarningTutor *tutorRegistroVideo;
    WarningTutor *tutorVideoTraking;
    WarningTutor *tutorSegComp;
    WarningTutor *tutorSegTempo;
    WarningTutor *tutorAnaSeq;
    WarningTutor *tutorAnaConcordancia;

    void ArrumandoTutores();






    struct Identificacao{
        QString experimento;
        QString data;
        QString laboratorio;
        QString idPesquisador;
        QString idAnimal;
        QString peso;
        QString sexo;
        QString tratamento;
        QString outrasInfo;
    };

    Identificacao identificacao;

    struct ResultadoCalibracao{
        QString video;
        cv::Mat background;
        int threshold;
        int erosao;
        QString tipoArea;
        QList <cv::Mat> areas;
        int matriz[2]; //[rows cols]
        double escala;
    };

    ResultadoCalibracao resultadoCalibracao;

    struct DadosExperimento{
        Identificacao dadosIdentificacao;
        int tipoAnalise[3]; //[RealTimeEthography VideoBaseadEthography Tracking]
        QString tipoRegistroEventos;
        QString arquivoCatalogo;
        ResultadoCalibracao dadosCalibracao;
    };

    DadosExperimento dadosExperimento;

    bool controleCalibracao, controleCatalogo, controleOpcoesEtografia;

    WarningTutor tuto1;
    void setNextInterface();


    telaCadastroPessoa *telaPessoa;
    telaCadastroCatalago *telaCatalogo;
    telaCadastroFilme *etografaRegistro;
    void configuraHabiTutores();



    ControladorInterfaces * controInterface;
};


#endif // ETHOWATCHERINPI_H