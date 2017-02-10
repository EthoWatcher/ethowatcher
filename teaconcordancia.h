#ifndef TEACONCORDANCIA_H
#define TEACONCORDANCIA_H

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
#include "parserxmltocsv.h"



namespace Ui {
class teaConcordancia;
}

class teaConcordancia : public QWidget
{
    Q_OBJECT

public:
    explicit teaConcordancia(QWidget *parent = 0);
    ~teaConcordancia();

private slots:
    void on_pbKohone1_clicked();

    void on_pbFleissKappa_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pbCohenGravar_clicked();

    void on_pbCarregarFleis_clicked();

    void on_pbAnaFleissKappa_clicked();

    void on_pbGerarKappa_clicked();

private:
    Ui::teaConcordancia *ui;
    //Ui::telaEstatistica *ui;
    QString fonteVideoETOXML;
    QFile OutEtografia;
    void lerETOXML(QString nomeArquivo);


    struct dadosVideo{
        bool controle =true;
        QString nome;
        int frameInicial;
        int frameFinal;
        int fps=30; //tem que corrigir isso de ler correto o valor

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
 int cViSeg=0;


 std::vector<int> totInicio;
 std::vector<int> totFinal;
 std::vector< std::vector<int> > matrizPontosTot;
 std::vector<int> pontosTot;
 std::vector<std::vector<int> > frameTotOriginal;
 std::vector<std::vector<int> > frameTotCortado;
 std::vector<std::vector< std::vector<int>  > > matrixframeTotCortado;
  std::vector<etografiaTotalizacoes> totalizacaoTot;

 //gravar timeBudeget
 QString nomeGravarCatalago;
 QFile Output;
 parserXMLtoCSV *parser;

signals:

 void fimLeituraEtografia();


};

#endif // TEACONCORDANCIA_H
