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
#ifndef TELASEGEMENTACAO_H
#define TELASEGEMENTACAO_H

#include <QWidget>
#include <QFileDialog>
#include <vector>
#include <QFile>
#include <QtMath>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QWidget>


#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
//#include <QtGui>
#include <QMessageBox>
#include "parserxmltocsv.h"
#include "parserxml.h"

namespace Ui {
class telaSegementacao;
}

class telaSegementacao : public QWidget
{
    Q_OBJECT

public:
    explicit telaSegementacao(QWidget *parent = 0);
    ~telaSegementacao();
    void setExperimentador(QString nome1, QString lab1);
    void liga_sementacao_etografia();

    QList<Cell> gera_segmentacao_texto(double tamanho_janela_s, int q_proce, int q_final, double fps,
                                        std::vector<double> frameInicial,
                                        std::vector<double> frameFinal,
                                        std::vector<int> id,

                                        std::vector<QString> nome,
                                        int qnt_categorias, int linha);
    QString saida_texto_formada_csv;

private slots:
    void on_pbCaTotalSe_clicked();

    void on_pbTotaAdd_clicked();

    void on_pbTotalRes_clicked();

    void on_pbTotGravar_clicked();

    void on_chbHomo_clicked(bool checked);

    void on_chbHetero_clicked(bool checked);

    void on_pbTCCMfile_clicked();

    void on_pbGravarTCCM_clicked();

private:
    Ui::telaSegementacao *ui;

    void _calcula();
    //Ui::telaEstatistica *ui;
    QString fonteVideoETOXML;
    QFile OutEtografia;
    void lerETOXML(QString nomeArquivo);
    //experimentador
    struct dadosExperimentador{
        QString nome;
        QString lab;
    };

    dadosExperimentador experimentador;

    QList<Cell> _gera_lis_segmetacao(int linha_gap);
    QList<Cell> saida_segm;
    struct dadosVideo{
        bool controle =true;
        QString nome;
        double frameInicial;
        double frameFinal;
        int frameProce;
        double fps=30; //tem que corrigir isso de ler correto o valor

    };
    dadosVideo* videoLido;


    struct catalago{
        int quantidadeDeCategorias=0;
        QString caminhoArquivo;
        QString tipoAnalise;
        std::vector<int> id;
        std::vector<QString> nome;
        bool controle =true;

    };
    catalago* catalagoLido;

    struct analiseEtografica{

       int quantidadeDePontos=0;
       QString tipoDeAnalise;
       std::vector<int> ponto;
       std::vector<int> id;
       std::vector<double> frameInicial;
       std::vector<double> frameFinal;

       bool controle =true;

    };

    analiseEtografica* etografiaLida;


    struct etografiaTotalizacoes{
        std::vector<QString>  componente;
        std::vector<double> duracao;
        std::vector<double> freq;
        std::vector<double> latencia;
        std::vector<bool> clicado;
        std::vector<bool> bordaSubida; //para analise de frequencia
        //double


    };

    etografiaTotalizacoes totalizacao1;



    struct analiseSequencialComportamento{

            std::vector<int> dados;
        //int quantidadeCatalago;
       // typedef std::vector<std::vector<int> > IntMatrix;
       // IntMatrix m;
    //int RR=10;

          std::vector<QString> classeCatalago;


        //std::vector<std::vector<int> >   sequencial;
        //std::vector<int> v2(3,0);
        //std::vector<int> v2( 3 ,10);
       // std::vector<std::vector<int> > matrix(rr, std::vector<int>(CC));


    };

    analiseSequencialComportamento analiseSequencial;


    //contador;
    int quantidadeDeVideo=0;
    std::vector< dadosVideo > dadosDosVideos;
    std::vector< analiseEtografica> etografiaDosVideos;
    std::vector< catalago > catalagoDosVideos;

    analiseEtografica *etografiaKoho;
    dadosVideo *videosKoho;
    std::vector< etografiaTotalizacoes> etoDosVideos;



   std::vector<std::vector<int> > frameVideo; //é um vetor de um vetor inteiro
//   std::vector<int> frameInfo;  //é uma linha dinahmica
    std::vector<std::vector< std::vector<int> > > anaEtoDosVideos;

    catalago *catalagoKoho;

    std::vector<int> cohoKappa;
    std::vector<QString> caminhoAnalise;


    //somatiros
    std::vector<int> somatorioColuna;
    std::vector<int> somatorioLinha;
    int somatorioTotal=0;



    QStringList titulos;
    std::vector<int> frameInfo;  //é uma linha dinahmica
    std::vector<double> fInicial;
    std::vector<double> fFinal;
    bool entrou= false;


    std::vector< std::vector<float> > porcentageTabela;
    std::vector<float> porcentagemLinha;


    //cohonem kapp

    float cohoK1=0;
    float cohoK2=0;
    float cohoKappaResultado=0;


    std::vector< std::vector<int> > frameFleisTabela;
    std::vector<int> frameFleisLinha;

    std::vector<int> somatorioFleisColuna;
    std::vector<double> somatorioProporcao;
    double proporcaoConcordancia=0;

    std::vector<double> pNumero;

 double somatorioP=0;
 double fleKappa=0;


 //QList<QSlider*> listaSlider;
 //pq eu to passando um ponteiro de QLineEdit
 QList<QLineEdit*> listaLineInicio;
 QList<QLineEdit*> listaLineFim;
 QList<QLineEdit*> listaLineLabel;
 QList<QTableWidget*> listaTabelaTotal;
// QList <QWidget*> listaWidget;
// QList <QVBoxLayout*> listaQVBox;
 QList<QLabel*> listaLabel;

 //QSignalMapper *mapperCategorias;
 QVBoxLayout *layoutLeInicio;
 QVBoxLayout *layoutLeFim;
 QVBoxLayout *layoutLblSeg;
 QVBoxLayout *layoutTabWid;
// QVBoxLayout *layoutMut;
 double cViSeg=0;
 int cViSegInteiro; //inteiro
 double dezenaCviSeg=0;
 bool chNumeroQuebrado;


 std::vector<double> totInicio;
 std::vector<double> totFinal;
 std::vector< std::vector<int> > matrizPontosTot;
 std::vector<int> pontosTot;
 std::vector<std::vector<int> > frameTotOriginal;
 std::vector<std::vector<int> > frameTotCortado;
 std::vector<std::vector< std::vector<int>  > > matrixframeTotCortado;
  std::vector<etografiaTotalizacoes> totalizacaoTot;

 std::vector<std::vector<double> > arvoreDeFrames;
 //gravar timeBudeget
 QString nomeGravarCatalago;
 QFile Output;

 parserXMLtoCSV *parser;
 parserXML *parserTCCM;
 bool chTCCon;
 QFile outGravador;

 QString conPontoVirgula(double num);


 std::vector<int> vetorPontos;
 std::vector<double> quadrosPontos;

 std::vector<int> vetorPontosSegmentados;
 std::vector<std::vector<int> > vetorPontosSegmentadosMatriz;


 std::vector<double> inicioPeriodo;
 std::vector<double> fimPeriodo;
 std::vector<double> latenciaTotal;
 std::vector<double> duracaoTotal;
 std::vector<double> frequenciaTotal;
 std::vector<std::vector<double> > duracaoTotalMatriz;
 std::vector<std::vector<double> > frequenciaTotalMatriz;
 std::vector<double> latencia(std::vector<int> entrada);
 std::vector<double> duracaoCategoria(std::vector<int> entrada);
 std::vector<double> frequenciaCategorias(std::vector<int> entrada);



signals:

 void fimLeituraEtografia();



};

#endif // TELASEGEMENTACAO_H
