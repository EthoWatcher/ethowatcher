#ifndef TELABLIND_H
#define TELABLIND_H

#include <QWidget>
#include <QFileDialog>
#include <QXmlStreamReader>

//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDate>


//funcionar o aleatorio
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QString>
#include <QThread>
#include <QDebug>

//gravando
#include <QXmlStreamWriter>
#include "modulorsa.h"
#include "moduloeditavideo.h"



namespace Ui {
class telablind;
}

class telablind : public QWidget
{
    Q_OBJECT

public:
    explicit telablind(QWidget *parent = 0);
    ~telablind();

//    struct dadosExperimentador{
//        QString nome;
//        QString lab;

//    };

//    struct DadosCalibracao{
//        QString video;
//        cv::Mat background;
//        int threshold;
//        int erosao;
//        QString tipoArea;
//        QList <cv::Mat> areas;
//        int matriz[2]; //[rows cols]
//        double escala;

//        double frameInicial;
//        double frameFinal;
//        double frameFundo;
//    };



//    struct dadosVideoCadastrado{

//        QString ext;
//        QString caminho;
//        QString nome;
//        QString nomeOpencv;

//        double videoFps;
//        double videoFrames;
//        float videoTempo;
//        double video_width; //ainda nao implementado
//        double video_heigth; //ainda nao implementado

//        //dados calibracao
//        DadosCalibracao resultado;

//        //dados experimento
//        int idAnimal;
//        QString tituloExperimento;
//        QString observacoes;
//        //QTime data;//falta a variavel data;

//        //dados Aquisição
//        float fpsMedio;
//        float tempoGastoAquisicao;
//        float erroTempoAtrelado;
//        int idCamera;

//        dadosExperimentador experimentador;
//        QDate data;

//        int dataDia;
//        int dataMes;
//        int dataAno;

//    };

//    dadosVideoCadastrado videoCadastrado;

    struct dadosEtografia{

        std::vector<int> id;
        std::vector<QString> nomeCategoria;
        std::vector<QString> atalho;
        std::vector<QString> descricao;
        std::vector<bool> dadoRemovido; //variavel de apoio para edicao
                                        //do catalago
        int quantidadeDeDados=0;

    };

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
        QString senha;
    };

    dadosExperimentador experimentador;
    dadosExperimentador expKey;

    bool chaveArea=false;
    int contArea;
    bool chaJanInte=false;
    bool chaMaxVari=false;






signals:

    void enviIncio(QString, QString, QString,int);


private slots:
    void on_pbAddListaVideo_clicked();

    void on_pbAbrirPasta_clicked();

    void on_pbNumeroAleatorio_clicked();

//    void on_pbTeste_clicked();

//    void on_pushButton_clicked();

    void on_pbBliding_clicked();

    void on_pbSetUserKey_clicked();

private:
    Ui::telablind *ui;
    QString caminhoArquivo;
    QString listaVideo;
    std::vector<QString> nomeDosVideos;
    std::vector<QString> nomeDosVideosMenor;
    QFile output;
    QFile outputKey;
    QString nomeParaOpenCV(QString nomeArq);
   // void gravandoVideo(QString nomeVideo,double);
    void gravandovideo(int i);


    void lendoVideoXml(int);

    int count=0;

    QString abrirVideo;

    cv::VideoCapture video;
    cv::VideoWriter* videoEditado;
    cv::Mat frameLido;

    //variaveis necessárias para fazer o aleatorio

   std::vector<bool> numeroEscrito; //se o numero ja foi encontrado
   std::vector<int> j; //pega o valor aleatorio atribuido

   void inicializaNumeroAleatorio();
   int getNumeroAleatorio();
   void aleatorizaAOrdem();
   std::vector<QString> nomeDosVideosAleatorizado;
   std::vector<double> frameInicialVideosAleatorizado;
   std::vector<double> frameFinalVideosAleatorizado;

   //gravando o video editado;

   void gravandoXMLVideoEditado(QString);
   QFile outputVideoEditado;

   struct structVideoEditado{
       QString nomeOpencv;


   };

   structVideoEditado vEditado;

   moduloRsa rsa;

   moduloEditaVideo* editaVideo;

   QThread* novaThread;

   QProgressBar* progre;


   QList <QThread*> listaDeThread;
   QList < moduloEditaVideo*> listaEditaVideo;
   QList <QProgressBar*> listaPB;
    void lerVXML(QString nomeArquivoLer);



};



#endif // TELABLIND_H