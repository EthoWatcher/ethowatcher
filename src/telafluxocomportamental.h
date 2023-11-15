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
#ifndef TELAFLUXOCOMPORTAMENTAL_H
#define TELAFLUXOCOMPORTAMENTAL_H

#include <QWidget>
#include <QFileDialog>
#include <QByteArray>

//funcionamento da saida em xml
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

//gravando csv
#include <QTextStream>
#include <QTableWidget>
#include <QTableWidgetItem>


#include <QCheckBox>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <moduloeditavideo.h>
#include <QThread>
#include <parserxml.h>





namespace Ui {
class telaFluxoComportamental;
}

class telaFluxoComportamental : public QWidget
{
    Q_OBJECT

public:
    explicit telaFluxoComportamental(QWidget *parent = 0);
    ~telaFluxoComportamental();
    struct dadosExperimentador{
        QString nome;
        QString lab;

    };

    dadosExperimentador experimentador;

    struct catalago{
        int quantidadeDeCategorias=0;
        QString caminhoArquivo;
        QString tipoAnalise;
        std::vector<int> id;
        std::vector<QString> nome;
        bool controle =true;

    };
    catalago* catalagoLido;

    QString nomeArquivoGravarCsv;
    //para o time buget
//    void lerTimeXml(int qualLer);
//    void escreverTimeCsv();

    struct analiseSequencialComportamento{

          std::vector<int> dados;
          std::vector< std::vector<int> > listaDados;
          std::vector<QString> classeCatalago;




    };

    analiseSequencialComportamento analiseSequencial;

    struct analiseKohoKapa{
        std::vector<int> cohoKappa;
        std::vector<std::vector<int> > cohoKappaMatrix;
        std::vector<QString> nomeCate;
        std::vector<float> cohoKappaPor;
        std::vector<std::vector<float> > cohoKappaPorMatrix;
        float k1,k2, kappa;


    };

    analiseKohoKapa KohoKappa;


    struct analiseFleissKappa{

        std::vector<int> linhaConcordancia;
        std::vector< std::vector<int> > matrizConcordancia;
        float pe,p,indiceFleissKappa;
        std::vector<int> somatorio;
        std::vector<int> pi;


    };

    analiseFleissKappa flKaDa;

    struct dadosVideo{
        bool controle =true;
        QString nome;
        double frameInicial;
        double frameFinal;
        double frameProce;
        int frameBack;
        double fps=30; //tem que corrigir isso de ler correto o valor
        double escala;

    };
    dadosVideo* videoLido;



    struct analiseEtografica{

       int quantidadeDePontos=0;
       QString tipoDeAnalise;
       QString caminho;
       std::vector<int> ponto;
       std::vector<int> id;
       std::vector<double> frameInicial;
       std::vector<double> frameFinal;

       bool controle =true;



    };

    analiseEtografica* etografiaLida;

    std::vector< analiseEtografica*> etografiasLidas;




private slots:
    void on_pbAnaliseFile_clicked();

    void on_pbSaveFile_clicked();

    void on_pbOpenTCCM_clicked();

private:
    Ui::telaFluxoComportamental *ui;

    QString fonteCaminhoArquivo;
    QByteArray fonteVideoBit; //qbyteArray original contendo o caminho+nome+extensao
    QByteArray fonteVideoBitExt; //qbyteArray referente a extensão do arquivo
    QByteArray fonteVideoBitExtInv;
    QFile output;
    QFile outGravador;
    void lerTimeXml(int qualLer);

     QFile OutEtografia;
     void lerETOXML(QString nomeArquivo);

     QTableWidget *tableWid;
     QTableWidgetItem *tableItem;

     void geraTabela(int numero);
     QWidget *wid1;

     QList<QLabel*> listlblCategorias;
     QList<QSlider*> listSlider;
     QList<QLabel*> listlblPorcento;

     QList<QWidget*> vetorListaWid0;
     QList<QWidget*> vetorListaWid1;
     QList<QWidget*> listaWidColuna1Cate;
     QList<QWidget*> listaWidColuna2Slider;
     QList<QWidget*> listaWidColuna3Porcento;


     QCheckBox *chek;
     QList<QCheckBox*> listChek;
     QLabel *label1;
     QLabel *label2;
     QSlider *slider;

    QWidget* tela;
    QVBoxLayout *layout1;
    QWidget* tela1;
    QVBoxLayout *layout2;

    QWidget* tela2;
    QVBoxLayout *layout3;
     QHBoxLayout *layoutHorizontal;
     bool chEtr;
     QVBoxLayout *vLay;


     moduloEditaVideo *editaVideo;
     QThread* novaThread;
     void encontraPontosGravar();
     void encontrarFrames(int area_selecioada_id);
     QList<int> editFrameInicio;
     QList<int> editFrameFim;
     QList<int> categoria;
     QString nomeFluxoComportamental;
     int codecVideo;

     parserXML parserTCCM;
     QString fonteCaminhoTCCM;
     bool chTCCon;

     std::vector<parserXML::dadosMorfo *> segMorfo;
     std::vector<parserXML::dadosCinema *> segCinema;

     void gravaXML(QString nomeArquivo);

     QFile Output;

signals:

     void enviaInicioFluxo(QString nome , QString nomeEditado, QList<int> inicio, QList<int>fim,int codec );

};

#endif // TELAFLUXOCOMPORTAMENTAL_H
