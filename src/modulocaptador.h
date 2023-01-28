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
#ifndef MODULOCAPTADOR_H
#define MODULOCAPTADOR_H

#include <QObject>
#include <iostream>

#include <QThread>
#include <QTimer>
#include <QImage>
#include <time.h>
#include <QDebug>

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

//necessario para enviar imagens
#include <QImage>



class moduloCaptador : public QObject
{
    Q_OBJECT
public:

    cv::Mat conQim2Mat(QImage imaEntrada);
    bool chInicio= true;
    int frameTotal;
    explicit moduloCaptador(QObject *parent = 0);
    ~moduloCaptador();
    double dWidth;
    double dHeight;
    int codec;
    long int i;
    QImage qimOriginal;
    int fps;
    QString nomeVideo;
    //variaveis para medir tempo
    clock_t tinicial,tfinal;
    clock_t tfinalCaptura;
    float tresposta;
    float trespostaCaptura;
    bool entrou1;
    struct timerMedi{
         std::vector<clock_t> timerInicial;
         std::vector<clock_t> timerFinal;

    };

    timerMedi joao;



    cv::Mat frameBackground;
    cv::Mat frameLido;
    cv::Mat frameDisplay;
    cv::VideoCapture *cap;

    QTimer* tempoLerFrame;



    void setCaptador(int disp);
    void setCaptador(QString fonteVideo);
    void getParamVideo();
    void setCaptadorRange(int inicio, int fim);



    double video_fps;
    double video_frames;
    float video_tempo;
    double video_width, prop_width, widthReduzido;
    double video_heigth, prop_heigth, heigthReduzido;




signals:
    void novaImage();
    void enviaInt(int);

    void fimConfiguracao();
    void fimPrograma();
    void enviaInformacoes(int,QImage,float);
    void enviaImagem(QImage,int); //para video
    void entrouNoTermino();
    void enviaTempoGravacao(int, float);




public slots:
    void setReinicio();


    void setCaptaVideoTodo();
    void mostraThread();
    void configurando();
    void setGravador(int frameTotal1);
    void captando();
    void setCapOn(bool liga);
    void captandoRealTime();

    void confGravador(QString nomeVideo1, int framesPerSecond1, int quntFrames, bool chFormaParada, int codificador1);
    void terminaGravador();

    void setGraOn(bool liga);
    void gravando(int numFra,QImage imAdquirida, float tempo);
    void desligando();
    void iniciandoTimer(double fatorAcele);
    void finalizandoTimer();
    void setFrame(int numeroFrame);

    void setParada(int frame, bool parada);
    void setOnOff(bool gravandoRecebi);

    void captadorVideoRelease();
    void getPlanoFundo();

    cv::Mat pegaPlanoFundo(int numeroFrameFundo);

    QImage pegaPlanoFundoQImage(int numeroFrameFundo);


private:

    int frInicio, frFim;

    QByteArray fonteVideoBit; //qbyteArray original contendo o caminho+nome+extensao
    QByteArray fonteVideoBitExt; //qbyteArray referente a extensão do arquivo
    QByteArray fonteVideoBitExtInv;
    QByteArray fonteVideoBitNomeArquivo; //qbyteArray referente ao nome do arquivo
    QByteArray fonteVideoBitCaminhoArquivo; //qbyteArray referente ao caminho do arquivo
    QByteArray fonteVideoBitOpenCV;
    QString fonteVideoOpenCV;
    std::string fonteVideoOpenCVString;


    bool chaveVideo= false;
    bool chaveDisp= false;
    bool chCaptador=true;
    bool chLigaCaptador=true;
    bool chGravador=true; //se o gravador esta on ou off
    bool chParadaNegada;        //se for verdadeiro ele nao termina nucna
    cv::VideoWriter *gravadorVideo;
     cv::Mat matGravAlex;

    bool chGravadorVideoRelease;

};

#endif // MODULOCAPTADOR_H
