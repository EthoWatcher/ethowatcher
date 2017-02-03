#ifndef TELACADASTROFILME_H
#define TELACADASTROFILME_H

#include <QWidget>
#include <QFileDialog>
#include <QString>
#include <QByteArray>
#include <QtMath>

//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include "calibracao.h"

#include <QImage>
#include <QPainter>
#include <QPen>

//funcionamento da saida em xml
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include "modulocaptador.h"

#include <QTableWidgetItem>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include "itemareainte.h"
#include "areatraingulo.h"

namespace Ui {
class telaCadastroFilme;
}

class telaCadastroFilme : public QWidget
{
    Q_OBJECT

public:
    explicit telaCadastroFilme(QWidget *parent = 0);
    ~telaCadastroFilme();

    QString fonteVideo; //string original do caminho+nome+extensao

    QByteArray fonteVideoBit; //qbyteArray original contendo o caminho+nome+extensao
    QByteArray fonteVideoBitExt; //qbyteArray referente a extensão do arquivo
    QByteArray fonteVideoBitExtInv;
    QByteArray fonteVideoBitNomeArquivo; //qbyteArray referente ao nome do arquivo
    QByteArray fonteVideoBitCaminhoArquivo; //qbyteArray referente ao caminho do arquivo

    //para abrir a open cv

    QByteArray fonteVideoBitOpenCV;
    QString fonteVideoOpenCV;
    std::string fonteVideoOpenCVString;
    //opencv
    cv::VideoCapture video;
    double video_fps;
    double video_frames;
    float video_tempo;
    double video_width, prop_width, widthReduzido;
    double video_heigth, prop_heigth, heigthReduzido;
    QString tutor;

    QString nomeArquivo;
    double scalTrans;

    //variaveis de saida

    bool primeiraCalibracao=true;

    struct dadosExperimentador{
        QString nome;
        QString lab;

    };

    struct DadosCalibracao{
        QString video;
        cv::Mat background;
        int threshold;
        int erosao;
        QString tipoArea;
        QList <cv::Mat> areas;

        std::vector<cv::Rect> retangulo;
        std::vector<cv::Point> cenCirculo;
        std::vector<double> tamCirculo;

        int matriz[2]; //[rows cols]
        double escala;

        double frameInicial;
        double frameFinal;
        double frameProce;
        double frameFundo;
    };



    struct dadosVideoCadastrado{

        QString ext;
        QString caminho;
        QString nome;
        QString nomeOpencv;

        double videoFps;
        double videoFrames;
        float videoTempo;
        double video_width; //ainda nao implementado
        double video_heigth; //ainda nao implementado

        //dados calibracao
        DadosCalibracao resultado;

        //dados experimento
        int idAnimal;
        QString tituloExperimento;
        QString observacoes;
        //QTime data;//falta a variavel data;

        //dados Aquisição
        float fpsMedio;
        float tempoGastoAquisicao;
        float erroTempoAtrelado;
        int idCamera;

        dadosExperimentador experimentador;
        QDate data;

        int dataDia;
        int dataMes;
        int dataAno;

    };

    dadosVideoCadastrado videoCadastrado;

    QFile output;
    QPainter pintorScala;

    cv::Point scalaP1,scalaP2;
    double disPonto,scala;
    double maxVaria;

    cv::Point janelaP1,janelaMaxP1,janelaMaxP2;
    double janelaHei;
    double janelaWid;


public slots:
    void recebeImagem(QImage qiCaptador, int numFrame);

private slots:

    void on_pbAbreVideo_clicked();

    void on_btPlay_clicked();

    void on_btStop_clicked();

    void on_btAvancar_clicked();

    void on_btVoltar_clicked();

    void on_SliderVelocidade_sliderReleased();

    void on_pbAdquiriFrame_clicked();

    void on_pbConfEscala_clicked();

    void on_tabWPrincipal_currentChanged(int index);

    void on_tabWCalib_currentChanged(int index);

    void on_sbScalP1X_editingFinished();

    void on_sbScalP1Y_editingFinished();

    void on_sbScalP2X_editingFinished();

    void on_sbScalP2Y_editingFinished();

    void on_sbP1XJanela_editingFinished();

    void on_sbP1YJanela_editingFinished();

    void on_sbWidthJanela_valueChanged(double arg1);

    void on_sbHeiJanela_valueChanged(double arg1);

    void on_tabWNoise_currentChanged(int index);

    void on_sbJanelaP1X_editingFinished();

    void on_sbJanelaP2X_editingFinished();

    void on_sbJanelaP1Y_editingFinished();

    void on_sbJanelaP2Y_editingFinished();

    void on_tabWCalib_tabBarClicked(int index);

    void on_pbAddArea_clicked();

    void on_cbCircle_clicked();

    void on_cbRetangle_clicked();

    void on_tabWidListAre_cellPressed(int row, int column);

    void on_sbAreaX_editingFinished();

    void on_sbAreaY_editingFinished();

    void on_sbAreaWid_editingFinished();

    void on_sbAreaHei_editingFinished();

    void on_sbAreaRaio_editingFinished();

    void on_sbAreaWid_valueChanged(double arg1);

    void on_sbAreaHei_valueChanged(double arg1);

    void on_sbAreaRaio_valueChanged(double arg1);

    void on_pushButtonDelArea_clicked();

    void on_pushButtonCapture_clicked();

    void on_pbFrameProce_clicked();

    void on_pbFrameFinal_clicked();

    void on_spinBoxScaleCm_valueChanged(double arg1);

    void on_sbP1XJanela_valueChanged(double arg1);

    void on_pbCadastrar1_clicked();

    void on_hsTimer_sliderPressed();

    void on_hsTimer_valueChanged(int value);


    void on_pbConfigure1_clicked();

    void on_pbConfigureNioseArea_clicked();

    void on_tabWidListAre_cellChanged(int row, int column);

    void on_chbPrevi_clicked(bool checked);

private:
    Ui::telaCadastroFilme *ui;

   // cv::Mat conQim2Mat(QImage imaEntrada);
    QGraphicsPixmapItem  * imageFundopixMap;
    QGraphicsScene * scene;
    itemAreaInte *areaInt;
    bool clik=false;
    bool chVideo=false;


//    void lendoXml(int qualLer);

    moduloCaptador* captador;
    double frame_atual;
    double fatorVeloc;


    struct Resultado{
        QString video;
        cv::Mat background;

        cv::Mat matProce;
        int threshold;
        int erosao;
        QString tipoArea;
        QList <cv::Mat> areas;
        std::vector<cv::Rect> retangulos;

        std::vector<cv::Point> cenCirculo;
        std::vector<double> tamCirculo;

        int matriz[2]; //[rows cols]
        double escala;

        double frameInicial;
        double frameFinal;
        double frameProces;
        double frameFundo;

        QImage qiFrameProce;
        QImage qiFrameBack;
        QImage qiFrameInicial;





    };

    Resultado resultado;



    QImage qiRecebida;
    QImage qiScala;
    QImage qiJanela;
    QImage qiArea;
    QImage qiAreaCir;

    cv::Mat conQim2Mat(QImage imaEntrada);

    bool chaveBack;

    int threshold_value;
    int erosao;
    cv::Mat frame,frameReduzido;
    cv::Mat frameBackground;
    cv::Mat frameProce;
    cv::Mat frameAnimal;
    cv::Mat frameSubtracao, frameSubtracao_gray, frameSegmentacao, frameErosao, frameLimiarizacao, frameVisualizar;
    cv::Mat frameArea, frameCalibArea;
    cv::Mat frameEscala, frameCalibEscala, frameEscalaBranco;


    struct dadosArea{
        QString tipoForma;
        cv::Point origemPont;
        double heightArea;
        double widhtArea;
        double raioArea;
        QColor cor;


    };
    QList <dadosArea> area;
    //std::vector<dadosArea> area;
    int conQtArea=0;

    areaTraingulo *triRedScala, *triBlueScala;
     areaTraingulo *triRedMax, *triBlueMax;


     itemAreaInte * novaArea;
     QList<itemAreaInte*> listaAreaProce;
     QList<bool> listAreaBool;
     QString nomeFigura;
     int countArea=0;
     int itemSelecionado;

    bool chCirculoOn=false;

    void resetaCorConfi();

    bool chAddArea=false;


signals:
    void fimCadastro();
    void deletaTudo();


};

#endif // TELACADASTROFILME_H
