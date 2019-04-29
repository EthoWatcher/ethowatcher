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
