#ifndef TELATEMPOREAL_H
#define TELATEMPOREAL_H

#include <QWidget>
#include "modulocaptador.h"
#include <QThread>
#include <QString>
#include <QByteArray>
#include <QFileDialog>
#include <QImage>
#include <QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "moduloprocessamento.h"
#include <QPixmap>
#include <QPainter>
#include <QPen>


//funcionanmento da tetla
#include <QString>
#include <QByteArray>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QListWidget>
#include <QtMath>


#include <QVBoxLayout>
#include <QSignalMapper>
#include <QPushButton>
#include <QList>
#include <QShortcut>
#include <QCheckBox>

#include <QTimer>
#include <time.h>


#include <parserxmltocsv.h>



namespace Ui {
class telaTempoReal;
}

class telaTempoReal : public QWidget
{
    Q_OBJECT

public:
    explicit telaTempoReal(QWidget *parent = 0);
    ~telaTempoReal();

    struct dadosEtografia{

        std::vector<int> id;
        std::vector<QString> nomeCategoria;
        std::vector<QString> atalho;
        std::vector<QString> descricao;
        std::vector<bool> dadoRemovido; //variavel de apoio para edicao
                                        //do catalago
        int quantidadeDeDados=0;

    };

    clock_t tinicial2,tfinal2;
    clock_t tinicial1,tfinal1;

    clock_t tinicialA,tfinalA;

    struct timerMedi{
         std::vector<clock_t> timerInicial;
         std::vector<clock_t> timerFinal;

    };

    timerMedi joao1, joao2;


    dadosEtografia dadosEto;
    dadosEtografia cAnaEto;

    QString nomeGravarCatalago;
    QFile Output;

    //funcionar a abertura de videos
    QString fonteVideoXML;


    //gravar etografia
    struct dadosSaida{

        std::vector<int> id;
        std::vector<double> frameComeco; //do ponto de etografia
        std::vector<double> framFim;
        //variaveis de armazenamento para correto funcionamento
        //std::vector<double> frameFinalBuffer;
       // std::vector<double> pontosPostos;
        int quantidadeDepontos;
    };

    dadosSaida etografia;


    struct dadosSaidaEto{

        std::vector<int> id;
        std::vector<double> frameComeco;
        std::vector<double> framFim;
        //variaveis de armazenamento para correto funcionamento
        std::vector<double> frameFinalBuffer;
        std::vector<double> pontosPostos;
        std::vector<bool> chPontoValido;

        int quantidadeDepontos=0;

    };

    dadosSaidaEto saida;


    QString nomeGravarEtografia;
    QFile OutEtografia;
    QFile OutEtografia2;
    int contadorDeVideo=0; //qual video da lista vai abrir

    struct dadosArea{


       std::vector<QString> tipo;

        int id;
        std::vector<double> oriX;
        std::vector<double> oriY;
        std::vector<double> width;
        std::vector<double> height;
        std::vector<double> raio;
        std::vector<QString> nomeFig;

//        std::vector<cv::Rect> retangulo;
//        std::vector<cv::Point> cenCirculo;
//        std::vector<double> tamCirculo;

    };

    dadosArea auxArea;
    dadosArea auxArea1;

    //ler videoXML
    struct dadosVXML{
        int quantidadeDeDados=0;
        int contQuantArea=0;
        std::vector<QString> nomeVXML;
        std::vector<QString> nomeOpencv;    //nome do video
        std::vector<int> frameFinal;    //frame final da analise
        std::vector<int> frameInicial; //frame Inicial da analise
        std::vector<int> frameProces;
        std::vector<int> frameBack; //frame Inicial da analise
        std::vector<int> erosao;
        std::vector<int> threshold;
        std::vector<double> escala;
        std::vector<int> fps;
        std::vector<bool> chProImaOn;



        std::vector<dadosArea> area;


        std::vector<bool> chaInteMoveAtivado; //chave que diz se é movel a area ou nao
        std::vector<bool> chaInteMove; //chave que diz se é movel a area ou nao
        std::vector<dadosArea> areaJanInte; //informações sobre area movel ou fixa

        std::vector<bool> chaMaxVar;
        std::vector<double> tamMaxVar;



    };
    dadosVXML videoLista;

    QFile OutVideo;

    //experimentador
    struct dadosExperimentador{
        QString nome;
        QString lab;
    };

    dadosExperimentador experimentador;

    bool chaveArea=false;
    int contArea;
    bool chaJanInte=false;
    bool chaMaxVari=false;

    bool chVideoEditado=false;



    struct dadosMorfo{

        std::vector<double> area;
        std::vector<double> centroidX;
        std::vector<double> centroidY;
        std::vector<double> anguloObj;
        std::vector<double> tamanhoObj;
        std::vector<float>  altura;
        std::vector<float>  largura;

        std::vector<bool> objetoEncontrado; //quando o objeto é encontrado é true

//            std::vector<bool> ruido; //quando for ruido = true

    };

    dadosMorfo reMorfo;
    struct dadosCinema{
        std::vector<double>  varDistancia;
        std::vector<double>  varAngular;
        std::vector<double>  varArea;
        std::vector<double>  varCenX;
        std::vector<double>  varCenY;
        std::vector<double> varTamObjeto;
        std::vector<bool> ruidoMaxVaria;
        std::vector<float> varAltura;
        std::vector<float> varLargura;



    };

    dadosCinema reCinema;
    parserXMLtoCSV *parser;



private slots:
//    void on_pbTeste_clicked();
    void atualizaImagem(int numeroFrame, QImage qimFoto , float Tempo);

    void on_pbStoCap_clicked();

    void on_pbStartCaptador_clicked();

  //  void on_pushButton_clicked();

    void on_pbPlanoFundo_clicked();

    void on_pushButton_4_clicked();


//    void recebeDesenho(QImage des1, bool desenhar, double centX, double centY,
//                       double poLongeX, double poLongey, double agulhX, double agulhy,
//                       double pRetaA1X, double pRetaA1Y, double pRetaA2X, double pRetaA2Y,
//                       double vtxX1, double vtxY1, double vtxX2, double vtxY2, double vtxX3,
//                       double vtxY3, double vtxX4, double vtxY4);


    void recebeDesenho(QImage imaPro, bool desenha, double cmX, double cmY, double pMDCX, double pMDCY, double agulhX, double agulhY, double pob1X, double pob1Y, double pob2X, double pob2Y, double vtxX1, double vtxY1, double vtxX2, double vtxY2, double vtxX3, double vtxY3, double vtxX4, double vtxY4);


   void recebeDadosMorfologicos(QImage imReceb, bool objetoEnco, double areaRecebida,
                                             double centroideX, double centroideY,
                                             float angObjeto, float tamObjet);


   void gravaDadosMorfoCinematico(QImage imaProc, bool objeto, double area1, double mcX, double mcY, float anguloObjeto, float alturaObjeto, float larguraObjeto, double varAngular, double varArea, double VarCenX, double VarCenY, double VarDistancia, double VarOBjeto, float VarAltura, float VarLargura, bool ruidoOn);



   void on_chAImage_clicked(bool checked);

   void on_cbRegistro_clicked(bool checked);

   void on_pbConfig_clicked();

   void on_cbCapturaVideo_clicked(bool checked);

   void on_pbConfigurarVideo_clicked();



   void on_cbParadaFrame_clicked(bool checked);

   void on_leFrameTotal_editingFinished();

   void on_pbStarrFilming_clicked();

   void on_pbStopFilming_clicked();

   void on_pbTerminaGrava_clicked();

   void on_cbProcessInagem_clicked(bool checked);

   void on_telaTempoReal_destroyed();



   void on_pbLerArquivoVxml_clicked();

   void on_cbProcessInagem_clicked();

   void on_pbFimProcessamento_clicked();

   void on_pbSaveTraking_clicked();

   void on_pbGravaRelatorioFPS_clicked();

   void on_pbLerCatalogo_clicked();

   void on_cbAuto_clicked(bool checked);

   void on_cbNested_clicked(bool checked);

   void slotMapeado(int a);

   void on_tabButtons_tabBarClicked(int index);

   void on_pbEtographyStart_clicked();

   void atualizaContadorRegistro();

   void on_pbLerArquivoVxml_clicked(bool checked);

   void on_pbEtographyEnd_clicked();

   void on_pbGravarAnalasiteEtografica_clicked();

   void on_pbGravarAnalasiProces_clicked();

//   void on_pushButton_2_clicked();

//   void on_pbCodec_clicked();

   void on_pbteste_clicked();

private:
    Ui::telaTempoReal *ui;
    moduloCaptador *captadorDeVideo;
    moduloCaptador *captador;
    QThread *captadorThread;
    float somaTempo=0;
    float somaTempoFilming=0;
    moduloProcessamento *dados;
    QThread * thrProce;

    int widthPanProcess;
    int  heightPanProcess;

    int contNumeroGrava=0;
    QFile outGravador;


    //converter o nome do arquivo pegado em um arquivo proprio para a openCV
    QString nomeArquivo="";
    QString nomeArquivoOpenCV;
    QByteArray nomeArquivoBit;
    QByteArray fonteVideoBitOpenCV;
    QString nomeGravarFPS;

    //configurando a camera
    int numeroCamera;

     bool chTermina;
     bool chFilmando=false;
     std::vector<float> vetorTempoAquisicao;
     std::vector<float> vetorTempoFrame;

     std::vector<int> vetorFrameAquisicao;


     void lerVXML(QString nomeArquivoLer);
     void enconPontoArea();
     void escreveFPS();
     QString nomeGravarProcesImagem;
     std::vector<bool>  objDentro;
     std::vector<std::vector<bool> > matObjDentro;
     bool chaTip;
     double raioTest;
     double contCir=0;
     double conCir2=0;
     double contRet=0;
     double conRet2=0;
     int fpsGravado;

     double video_width, video_height;

     double fpsMedio =0;
     double variancia=0;
     double desvioPadrao=0;

     bool chDesenhar;
    void readCatalago();
    int numeroDeBotoes;
    std::vector<QString> nomeCate;
    void creatShortCurt(QString atalho, QPushButton *pushBut);
    QList<QPushButton*> buttonList;
    QPushButton *pb;
    std::vector<bool> clicado;
    bool chEtografia;
    bool escolheSelecao;
    double frame_atual;
    double frameInicioRegistro; //marca o inicio do registro comportamental
    double frameInicioGravacao; //marca o inicio da gravacao;
    double frameInicioPro;

    bool habilita=true; //tava false
    int count=0;

    QTimer *tempoLerFrame;
    clock_t tinicial,tfinal;
    float tresposta;
    bool primeiraB=true;
    int fourCodec;

    int getCodec(int indexCaixa);

    QList<QCheckBox *> cheboxList;
    QCheckBox *chebox;

     bool chNovoValor=true;
     int compAnterior=-1;
     int contAtivoReg=0;
     bool chCorrigir=false;

     void atualizaRegistro();
     int contTempo=0;


signals:
    void desliga();


};

#endif // TELATEMPOREAL_H
