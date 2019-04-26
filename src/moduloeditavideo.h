#ifndef MODULOEDITAVIDEO_H
#define MODULOEDITAVIDEO_H

#include <QObject>
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
#include <QFile>
#include <QProgressBar>
#include <QVBoxLayout>
#include <time.h>



class moduloEditaVideo : public QObject
{
    Q_OBJECT
public:
    explicit moduloEditaVideo(QObject *parent = 0);
    ~moduloEditaVideo();


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
        std::vector<QString> nomeArquivoVXML;
        std::vector<QString> nomeOpencv;    //nome do video
        std::vector<QString> caminho;
        std::vector<int> frameFinal;    //frame final da analise
        std::vector<int> frameInicial; //frame Inicial da analise
        std::vector<int> frameProces;
        std::vector<int> frameBack; //frame Inicial da analise
        std::vector<int> erosao;
        std::vector<int> threshold;
        std::vector<double> escala;
        std::vector<double> fps;
        std::vector<bool> chProImaOn;



        std::vector<dadosArea> area;


        std::vector<bool> chaInteMoveAtivado; //chave que diz se é movel a area ou nao
        std::vector<bool> chaInteMove; //chave que diz se é movel a area ou nao
        std::vector<dadosArea> areaJanInte; //informações sobre area movel ou fixa

        std::vector<bool> chaMaxVar;
        std::vector<double> tamMaxVar;
        //        std::vector<QString> nomePesquisador;

        std::vector<QString> laboratorio;
        std::vector<QString> tituloExperimento;
        std::vector<QString> data;
        std::vector<QString> otherInfo;
        std::vector<QString> animalID;
        std::vector<QString> wight;
        std::vector<QString> animalSex;
        std::vector<QString> nomePesquisador;
        std::vector<QString> threatmen;

        std::vector<double> quantidadeFrames;
        std::vector<double> quantidadeTempo;
        std::vector<double> width;
        std::vector<double> height;





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
    dadosExperimentador key;
//    struct dadosExperimentador{
//        QString nome;
//        QString lab;
//        QString senha;

//    };


    bool chaveArea=false;
    int contArea;
    bool chaJanInte=false;
    bool chaMaxVari=false;
    bool chaveDadoOriginal= false;






    void setOpenVideo(QString noVideo); //abre video
    void setGravaVideo(QString noVideoGravado, int codecX); //abre o gravador de video
    void graVideo(double fInicio, double fFinal); //set os frames para gravar
    void setIniFim(double frInicio, double frFim); //set os frames de incio e de fim
    void graVideo(); //grava video quando é para o duplo cego;
    void setFimVideo();
    void setFimGraVideo();
    void lendoVideoXml(int qualLer);
    double getInicioVideo();
    double getFimVideo();


    //void iniGraVidoCego(QString arquivoVideo, QString nomeCaminhoEditado, QString nomeVideoEditado); //passa o arquivo de video cadastrado
                                                                     //e o nome do video editado
    bool readXmlVideoOrignal(QString nomeArquivoEditado);
    void writXmlVideoCego(QString nomeArquivoEditado);

    void setKey(QString nom, QString la, QString senh);

    int getCodec(int indexCaixa);



signals:
    void frame(int);
    void setProgres(int, int);

public slots:

    void iniGraVidoCego(QString arquivoVideo, QString nomeCaminhoEditado, QString nomeVideoEditado, int codec); //passa o arquivo de video cadastrado
    void iniGraFluxoComportamento(QString nomeVXML, QString nomeEditado, QList<int> frameInicio, QList<int> frameFinal, int codec);



private:

    QString gravarNomeCaminhoVideo,gravarNomeVideo;

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


void lerVXML(QString nomeArquivoLer);
    moduloRsa rsa;

    QFile outputVideoEditado;
    QFile output;


    cv::VideoCapture * video;
    cv::VideoWriter* videoEditado;
    double dWidth;
    double dHeight;
    double videoFps;
    cv::Mat framVideo;

    double framInicio,framFim;


    QThread *thread1;

    clock_t tinicial,tfinal;
    float tresposta;

    int codecVideo;
private slots:





};

#endif // MODULOEDITAVIDEO_H
