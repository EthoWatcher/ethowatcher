/*
EthoWatcher OS is a software to assist study of animal behavior.
Copyright (C) 2018  Universidade Federal de Santa Catarina.

EthoWatcher OS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef MODULOPROCESSAMENTO_H
#define MODULOPROCESSAMENTO_H

#include <QObject>
#include <iostream>
#include <QThread>
#include <QtCore> //necessário para funcionar o Qtimer
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtMath>
#include <time.h>


#include <QDebug>
#include <QtMath>

class moduloProcessamento : public QObject
{
    Q_OBJECT
public:
    explicit moduloProcessamento(QObject *parent = 0);
    ~moduloProcessamento();
    //necessario para medicao de tempo
    int a;
    bool entrou1, entrou2;
    int frameTotal=300;
    clock_t tinicial,tfinal;
    clock_t tinicial1,tfinal1;
    float tresposta;
    cv::Mat frameBackground;

    cv::Mat fraRecebido;

    struct timerMedi{
         std::vector<clock_t> timerInicial;
         std::vector<clock_t> timerFinal;

    };

    timerMedi joao;


        bool entrada;//para a tela começar a ir atras do centro de imagem


        struct dadosFigura{
            //QImage imaPro,
            std::vector<bool> desenha;
            std::vector<double> cmX;
            std::vector<double> cmY;
            std::vector<double> pMDCX;
            std::vector<double> pMDCY;
            std::vector<double> agulhX;
            std::vector<double> agulhY;
            std::vector<double> pob1X;
            std::vector<double> pob1Y;
            std::vector<double> pob2X;
            std::vector<double> pob2Y;
            std::vector<double> vtxX1;
            std::vector<double> vtxY1;
            std::vector<double> vtxX2;
            std::vector<double> vtxY2;
            std::vector<double> vtxX3;
            std::vector<double> vtxY3;
            std::vector<double> vtxX4;
            std::vector<double> vtxY4;


        };

        dadosFigura desenhoSaida;




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

        void setParametrosVideo(double videoWidth, double videoHeig);
        void setFrameFundo(QImage imaEntrada);
        void confiCameraVir(double origX, double origY, double width, double height, bool chMove, bool chelaMove);
        void setMaxVariacao(double max);
        void setAreaInteresse(double x, double y, double tamanho);
        void setAreaInteresse(double x, double y, double height, double width);
        void setNomeFigura(QString nome);
        QString figuraNome;
        cv::Mat frameAreaInteresse;
        cv::Mat frameAreaInteresseB;
        cv::Mat conQim2Mat(QImage imaEntrada);

        void desenhaObjetoInterresse(cv::Mat frameErodido);




signals:
    void enviaQimage(QImage);
    void enviaInt(int);
    void enviaMorfInt(int);
    void fimProce();

    void valoresProcessamento(float ,float  ,
                              float ,float ,
                              float ,float ,
                              float,
                              float,float,float,float,
                              bool, QImage,int);

    void dadosMorfologicos(QImage imaProc,bool objeto,double area1, //area
                           double mcX, double mcY,
                           float anguloObjeto,
                           float altura, float largura); //centroide

    void desenhaFigura(QImage imaPro, bool desenha, double cmX, double cmY,
                        double pMDCX,double pMDCY,
                       double agulhX, double agulhY,
                       double pob1X, double pob1Y,
                       double pob2X, double pob2Y,   //pob2x é o tamanho do objeto
                       double vtxX1,double vtxY1,double vtxX2,double vtxY2,
                       double vtxX3,double vtxY3,double vtxX4,double vtxY4);

    void dadosMorfoCinematico(QImage imaProc, bool objeto,double area1, //area
                              double mcX, double mcY,
                              float anguloObjeto,
                              float alturaObj,
                              float larguraObj,
                              double varAngular, double varArea,
                              double VarCenX, double VarCenY, double VarDistancia, double VarOBjeto, float varAlt, float varLar, bool ruido); //centroide

    void roiImage(QImage imageDeinteresse);

public slots:

    void processamentoDeVideoRealTime(int i, QImage imgRecegida, float temp);
    void processamentoDeVideoTodo(QImage imgRecegida, int i);
    void processamentoDeVideo();
    void setBackground(cv::Mat planoFundo);
    void setCalibracao(int threshold, int erosaoCa);

    void mostraThread();
    void processamentoMorfologico();
    void gravaDesenhoFigura(QImage imaPro, bool desenha, double cmX, double cmY,
                                     double pMDCX,double pMDCY,
                                    double agulhX, double agulhY,
                                    double pob1X, double pob1Y,
                                    double pob2X, double pob2Y,
                                    double vtxX1,double vtxY1,double vtxX2,double vtxY2,
                                    double vtxX3,double vtxY3,double vtxX4,double vtxY4);

    void gravaDadosMorfoCinematico(QImage imaProc, bool objeto, double area1, //area
               double mcX, double mcY,
               float anguloObjeto,
               float alturaObjeto,
               float larguraObjeto,
               double varAngular, double varArea,
               double VarCenX, double VarCenY, double VarDistancia, double VarOBjeto, float VarAltura, float VarLargura, bool ruidoOn); //centroide


    void calculaIntersection(cv::Point2f o1, cv::Point2f p1, cv::Point2f o2, cv::Point2f p2);

    void desligando();

    cv::Mat setCameraVirtual(cv::Point centroObjetoInicial, cv::Point origenRoi , int widthRoi, int heightRoi);
    cv::Mat moveVirtCamera(cv::Mat imagemInteresse, cv::Point centroMassa);

    void recebeDadosMorfologicos(QImage imReceb, bool objetoEnco, double areaRecebida, double centroideX, double centroideY, float angObjeto, float altura, float largura);


private:

int contMorfo=0;
int contGlobal;
    struct janelaInte{
        double origX;
        double origY;
        double width;
        double height;
        bool chMobile;

    };

    janelaInte jaInte;


    int xRoiWidth, yRoiHeight; //tamanho da janela
    cv::Point origiemRoi, origiemObjeto;
    cv::Point novaOrigem;

    cv::Mat matProcessado;
    cv::Mat matOriginal;
    cv::Mat frameDisplay;
    cv::Mat frameDisplay1;
    bool emitiu=false;
    int frameDoVideo=0; //qual o frameDoVideo
    int offset=30; //ofset do video
    //variaveis necessarias

    double video_width;
    double video_heigth;
    int threshold_value;
    int erosao;
    cv::Mat frameAnimal;
    cv::Mat frameSubtracao, frameSubtracao_gray, frameSegmentacao, frameErosao, frameLimiarizacao, frameVisualizar;

    //QList <cv::Point2f> centroMassa;
   // QList <cv::Point2f> centroMassaAumentado;

    bool intersection;
    cv::Point2f pointIntersection;
    //QList <QList <cv::Point2f> > linhaComprimentoAnimal;
    //QList <cv::RotatedRect> caixaDelimitadoraAnimal;
   // cv::Mat frameAumentado;

    cv::Point2f p11, p21;
    int d;
   int dmax=0;
   //int parada=200;



  // struct resultadoComprimento{
  //     float xP1,xP2;
  //     float yP1,yP2;

  // };
   //cv::Point2f vtx[4];
   //resultadoComprimento resultado1;





   cv::Mat frameAumentado2;


   cv::Mat tracking;
   cv::Mat trackingBranco;

   cv::Mat linhaAnimal;
   cv::Mat linhaAnimalBranco;
   cv::Mat caixaAnimal;
   cv::Mat caixaAnimalBranco;
   cv::Mat coordenadas;
   cv::Mat coordenadasBranco;



   //novo processamento
   //processamento da area
   std::vector<cv::Point> contornosRoi;
   double area;
   bool objetoEncontrado;

   //processamento do centro de massa
   cv::Moments mu; //momento
   cv::Point2f mcRoi; //mass center do roi
   cv::Point2f mc;    // mass center do roi
   cv::Point2f antigoMc;

   //variavel da janela de interesse movel
   //cv::Point origiemRoi; //ponto de origem do roi;

   //varaiveis do tamanhod o objeto
   cv::RotatedRect caixaCirculo;
   cv::Point2f vtxRoi[4];
   cv::Point2f vtx[4];



    //variaveis do angulo e do tamanho
   cv::Point vetorMLC,vetorRC,pontoR;
   float anguloVetor;
    cv::Point pontoLongeCentro;
   float tamanho;
   float maiorTamanho1=0;
   int ponto1=0;
   float maiorTamanho2=0;
   int ponto2=0;
   float subX;
   float subY;

   float incliCaixa;
     float tamanhoRetaCaixa[4];

     float inclinacaoRetaAnimal;
     float diferAngulo;
     float mrAnimal;
     int tolerancia =25;



   float inclinacaoReta(float p1x, float p1y, float p2x, float p2y);
   float diferencaDeAngulo(float mr, float ms);

   cv::Point pobjeto1, pobjeto2;


   cv::Mat imaInte,imaInteDisplay;
   cv::Mat frameErosaoInterese;

   bool chaJanelaMovel=true;

   int contadorMorfo=0;
   bool chaveObjeto= false;
   double moduloVaria;
   double maxVaria;
   double centroideXAntiga;
   double centroideYAntiga;

    bool chPrimeiroVideoTodo;


    bool primeiroFrame=true;
    double novoArea, novoCentroideX, novoCentroideY ;
    double novoAngObj;
    double novoTamanhoObj;
    bool novoRuido;



    double antigoArea, antigoCentroideX,antigoCentroideY ;
    float antigoAnguloObj;
    float antigoTamanhoObj;

    float antigoAltura, antigoLargura;
    float novoAltura,novoLargura;


    bool antigoRuido;

    double novaVarAngular, novaVarArea, novaVarCenY,novaVarCenX, novaVarDistancia, novaVarTamanhoObj;
    float novaVarAltura,novaVarLargura;
    double antigaVarAngular, antigaVarArea, antigaVarCenY,antigaVarCenX, antigaVarDistancia, antigaVarTamanhoObj;


    double antigaArea1;
    cv::Point2f antigaMc1, antigaVtx[4];
    float antigaAnguloVetor1, antigaMaiorTamanho1;

    float antigaAltur, antigaLargur;


    cv::Point antigaPontoLongeCentro, antigaPontoR, antigaPobjeto1,antigaPobjeto2;


};

#endif // MODULOPROCESSAMENTO_H
