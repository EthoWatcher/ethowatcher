#ifndef ETOGRAFIA_H
#define ETOGRAFIA_H

#include <QWidget>
#include <QMainWindow>

#include <QLabel>
#include <QTimer>
#include <QKeyEvent>
#include <QPixmap>
#include <QList>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <QVBoxLayout>
#include <QSignalMapper>
#include <QPushButton>
#include <QDebug>
#include <QList>

#include <QImage>
#include <QPainter>


#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QToolTip>
#include <QtMath>
#include <QPainter>
//#include <QDesktopWidget>
#include <QRadioButton>
#include <QSignalMapper>
#include <QtXml/QDomElement>
#include "moduloprocessamento.h"


//const   QString      mensagemErro08_TFNC     =       "Error: Fail to read the file!";

namespace Ui {
class Etografia;
}

class Etografia : public QWidget
{
    Q_OBJECT

public:
    explicit Etografia(QWidget *parent = 0);
    ~Etografia();
//    void setEthoWatcher (QMainWindow *);
//    void setDadosIdentificacao(QString param1, QString param2, QString param3,
//                               QString param4, QString param5, QString param6,
//                               QString param7, QString param8, QString param9);
//    void setTipoAnalise(int param[3]);
//    void setTipoRegistroEventos(QString param);
//    void setArquivoCatalogo(QString param);
//    void setDadosCalibracao(QString param1, cv::Mat param2, int param3, int param4,
//                            QString param5, QList<cv::Mat> param6, int param7[2],
//                            double param8);
    void closeEvent(QCloseEvent *);
//    bool eventFilter(QObject *target, QEvent *event);

    void setCatalago();
    void setInicioVideo(QString nomeOpencvVideo, int frameIncial1, int frameBack, int frameProcessamento, int frameFinal1);
    void setCalibracao(int tres, int eros, double escala);
    void setInfoCatalago(std::vector<QString> nomeCategoria, std::vector<QString> atalho, int quantidadeDeDados);
    void setTratamentoRuido(double origX, double origY, double width, double height, bool chMove, double tamanhoMax);



    void setAutoNested(bool);

    struct dadosSaida{

        std::vector<int> id;
        std::vector<double> frameComeco;
        std::vector<double> framFim;
        //variaveis de armazenamento para correto funcionamento
        std::vector<double> frameFinalBuffer;
        std::vector<double> pontosPostos;
        int quantidadeDepontos;

    };

    dadosSaida saida;
    //std::vector<QPushButton> b1;
    QPushButton *b1[4];
    std::vector<bool> clicado;
    bool habilita=true; //tava false

    bool chaveEtog,chaveProce;

    void setChavesPrograma(bool chaveEtogr, bool chaveProces);

    moduloProcessamento* dados;


    struct dadosMorfo{

        std::vector<double> area;
        std::vector<double> centroidX;
        std::vector<double> centroidY;
        std::vector<double> anguloObj;
        std::vector<double> tamanhoObj;

        std::vector<bool> objetoEncontrado; //quando o objeto é encontrado é true

        std::vector<bool> ruido; //quando for ruido = true

    };

    dadosMorfo reMorfo;
    struct dadosCinema{
        std::vector<double>  varDistancia;
        std::vector<double>  varAngular;
        std::vector<double>  varArea;
        std::vector<double>  varCenX;
        std::vector<double>  varCenY;



    };

    dadosCinema reCinema;

    double centroX,centroY;




private slots:
//    void on_btVideo_clicked();

    void processVideo();

    void atualizaVelocidade();

//    void incrementaFatorDesloc();

//    void decrementaFatorDesloc();

//    void incrementaFatorVeloc();

//    void decrementaFatorVeloc();

    void on_btPlay_clicked();

    void on_btStop_clicked();

    void on_btAvancar_clicked();

    void on_btVoltar_clicked();

    void abreArquivoVideo(QString param);


//    void atualizaAnalise();

//    void on_pushButtonInitialFrame_clicked();

//    void on_pushButtonFinalFrame_clicked();

//    void on_spinBoxFinalFrame_editingFinished();

//    void on_spinBoxInitialFrame_editingFinished();

//    void on_pushButtonProcess_clicked();

//    void on_pushButtonStop_clicked();

    void calculaProporcaoAumentada();

//    void on_checkBoxRoute_stateChanged(int arg1);

//    void on_checkBoxCenterMass_stateChanged(int arg1);

//    void calculaIntersection(cv::Point2f o1, cv::Point2f p1, cv::Point2f o2, cv::Point2f p2);

//    void on_checkBoxBoundingBox_stateChanged(int arg1);

//    void on_checkBoxLengthAnimal_stateChanged(int arg1);

//    void on_checkBoxCoordinates_stateChanged(int arg1);

//    bool leituraCatalogo(QString arqCatalogo);

//    void clicarBotaoCategoria(int index);

//    void clicarCheckBoxSujeito(int index);

    //void carregaCatalogo();

    void slotMapeado(int);

    void processVideoMorf();

    void recebeDesenho(QImage des1, bool desenhar, double centX, double centY,
                       double poLongeX, double poLongey, double agulhX, double agulhy,
                       double pRetaA1X, double pRetaA1Y, double pRetaA2X, double pRetaA2Y,
                       double vtxX1, double vtxY1, double vtxX2, double vtxY2, double vtxX3,
                       double vtxY3, double vtxX4, double vtxY4);


   void recebeDadosMorfologicos(QImage imReceb, bool objetoEnco, double areaRecebida,
                                             double centroideX, double centroideY,
                                             float angObjeto, float tamObjet);

   void geraValoresCinematicos();



 //   void on_labelFramesTotal_linkActivated(const QString &link);

private:
   Ui::Etografia *ui;
//    QMainWindow *etw;
    QCloseEvent *event;


    struct janelaInte{
        double origX;
        double origY;
        double width;
        double height;
        bool chMobile;

    };

    janelaInte jaInte;


//    struct Identificacao{
//        QString experimento;
//        QString data;
//        QString laboratorio;
//        QString idPesquisador;
//        QString idAnimal;
//        QString peso;
//        QString sexo;
//        QString tratamento;
//        QString outrasInfo;
//    };
//    Identificacao identificacao;
//    struct ResultadoCalibracao{
//        QString video;
//        cv::Mat background;
//        int threshold;
//        int erosao;
//        QString tipoArea;
//        QList <cv::Mat> areas;
//        int matriz[2]; //[rows cols]
//        double escala;
//    };
//    ResultadoCalibracao resultadoCalibracao;
//    struct DadosExperimento{
//        Identificacao dadosIdentificacao;
//        int tipoAnalise[3]; //[RealTimeEthography VideoBaseadEthography Tracking]
//        QString tipoRegistroEventos;
//        QString arquivoCatalogo;
//        ResultadoCalibracao dadosCalibracao;
//    };
//    DadosExperimento dadosExperimento;
    QTimer *tmrTimer;
    QString fonteVideo="";
    cv::Mat frame;
    cv::Mat frameReduzido;
    bool controleAtualizaVelocidade;
    cv::VideoCapture* video;
    double frame_atual;
    double tempo_atual;
    double video_fps;
    double video_frames;
    int video_tempo;
    double video_width, prop_width, widthReduzido;
    double video_heigth, prop_heigth, heigthReduzido;
    double video_prop;
    double fatorVeloc;
    int fatorDesloc;
    cv::Mat frameBackground;
    cv::Mat frameAnimal;
    cv::Mat edges;

    int initialFrame;
    int finalFrame;
    bool controleInitialFrame;
    bool controleFinalFrame;
    bool processando;
    int widthPanProcess;
    int heightPanProcess;
    bool redimensionar=true;
    double propAumentada_width, propAumentada_heigth, video_propAumentada;
    cv::Mat frameAumentado;
    QList <cv::Point2f> centroMassa;
    QList <cv::Point2f> centroMassaAumentado;
    cv::Mat tracking;
    cv::Mat trackingBranco;
    bool controleTamanhoAumentado;
    bool desenhaRota;
    bool desenhaCentroMassa;
    bool desenhaComprimentoAnimal;
    bool desenhaCaixaAnimal;
    bool desenhaCoordenadas;
    bool intersection;
    cv::Point2f pointIntersection;
    QList <QList <cv::Point2f> > linhaComprimentoAnimal;
    cv::Mat linhaAnimal;
    cv::Mat linhaAnimalBranco;
    QList <cv::RotatedRect> caixaDelimitadoraAnimal;
    cv::Mat caixaAnimal;
    cv::Mat caixaAnimalBranco;
    cv::Mat coordenadas;
    cv::Mat coordenadasBranco;
    bool controleAvancaVideo;
    QList <QString> listaCategorias;
    QList <QString> listaSujeitos;
    QList <QString> listaCodigosCategorias;
    QList <QString> listaCodigosSujeitos;
    QList <QString> listaDescricoesCategorias;
    QList <QString> listaDescricoesSujeitos;    
    int sujeitoSelecionado;
    int categoriaSelecionada;
    QList <QList <double> > eventos;
    //catalogo *catalogoEmUso;

//   QString splitTooltip(QString text, int width);

    int numeroDeBotoes;
    bool escolheSelecao;
    std::vector<QString> nomeCate;

    QList<QPushButton*> buttonList;
    QPushButton *pb;

    double numeroFrameFinal;
    cv::Mat fundoFrame1;
    bool entrou12=true;

int count=0;


//variaveis para aquisicao dos dados morfologicos
double centroideXAntiga;
double centroideYAntiga;

double moduloVaria;
int contadorMorfo=0;
bool chaveObjeto= false;

void setFrameInicialFinal(int frameInicial2, int frameFinal2);

int numFrameProce;
int numFrameBack;
int numrameProce;
    double maxVaria;


signals:

void enviandoDadosEtograficos();
void processe();

void fimProce();

public slots:

    void termina();





};

#endif // ETOGRAFIA_H
