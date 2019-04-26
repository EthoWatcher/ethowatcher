#ifndef TELAUNVEIL_H
#define TELAUNVEIL_H

#include <QWidget>
#include <QFileDialog>
#include <QXmlStreamReader>
#include "modulorsa.h"
#include <QFile>
#include <QtMath>


namespace Ui {
class telaUnveil;
}

class telaUnveil : public QWidget
{
    Q_OBJECT

public:
    explicit telaUnveil(QWidget *parent = 0);
    ~telaUnveil();

    struct dadosExperimentador{
        QString nome;
        QString lab;
        QString senha;
    };

    dadosExperimentador experimentador;
    dadosExperimentador expKey;
   std::vector< dadosExperimentador > unveilKey;


   int contadorDeVideo=0; //qual video da lista vai abrir
   int contVideo=0;
   int contVideo1=0;

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
       std::vector<QString> nomeVXML; //na verdade aqui é arquivo vcxml
       std::vector<QString> nomeArquivoVXML;
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

   std::vector<bool> chLiberado;



private slots:
    void on_pbUserKey_clicked();

    void on_pbAddVideo_clicked();

    void on_pbUnveil_clicked();

private:
    Ui::telaUnveil *ui;
    QFile output;
    QFile outputKey;

    QString conPontoVirgula(double num);

    QFile outGravador;
    void lerVXML(QString nomeArquivoLer);
    bool chaveArea=false;
    int contArea;
    bool chaJanInte=false;
    bool chaMaxVari=false;
    moduloRsa rsaDecri;

};

#endif // TELAUNVEIL_H
