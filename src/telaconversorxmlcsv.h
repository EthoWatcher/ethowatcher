#ifndef TELACONVERSORXMLCSV_H
#define TELACONVERSORXMLCSV_H

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
#include<parserxmltocsv.h>


namespace Ui {
class telaConversorXmlCsv;
}

class telaConversorXmlCsv : public QWidget
{
    Q_OBJECT

public:
    explicit telaConversorXmlCsv(QWidget *parent = 0);
    ~telaConversorXmlCsv();

private slots:
    void on_pbCarregarXml_clicked();

private:
    Ui::telaConversorXmlCsv *ui;
    //variveis para abrir o video
    QString fonteCaminhoArquivo;
    QByteArray fonteVideoBit; //qbyteArray original contendo o caminho+nome+extensao
    QByteArray fonteVideoBitExt; //qbyteArray referente a extensão do arquivo
    QByteArray fonteVideoBitExtInv;
    QFile output;
    QFile outGravador;
    void lerETOXML(QString nomeArquivo);
    void lerTRKING(QString nomeArquivo);
    void totalizacoesEtografia();

    QFile OutEtografia;

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
    void lerTimeXml(int qualLer);
    void escreverTimeCsv();

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


    //para o de sequencia
//    void lerSeqXml();
    void escreverSeqCsv();

    //para o de kopo
//    void lerKohoXml();
    void escreverKohoCsv();

    //para o de fleiss
//    void lerFleissXml();
    void escreverFleisCsv();

    QString conPontoVirgula(double num);



    struct dadosVideo{
        bool controle =true;
        QString nome;
        double frameInicial;
        double frameFinal;
        double frameProce;
        int frameBack;
        int fps=30; //tem que corrigir isso de ler correto o valor
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


    struct etografiaTotalizacoes{
        std::vector<QString>  componente;
        std::vector<double> duracao;
        std::vector<double> freq;
        std::vector<double> latencia;
        std::vector<bool> clicado;
        std::vector<bool> bordaSubida; //para analise de frequencia

        double inicioSessao;
        double finalSessao;
        //double


    };

    etografiaTotalizacoes totalizacao1;

    std::vector<etografiaTotalizacoes> totalizacaoTot;

    void escreverEtografiaCsv();
    void escreverTrakinCsv();


    struct areaInte{

        std::vector<QString> figName;
        std::vector<QString> tipoArea;
        std::vector<double> centX;
        std::vector<double> centY;
        std::vector<double> width;
        std::vector<double> heigth;
        std::vector<double> raio;

    };

    areaInte areasDeInteresse;

    struct dadosMorfo{

        std::vector<double> frame;
        std::vector<double> area;
        std::vector<double> centroidX;
        std::vector<double> centroidY;
        std::vector<double> anguloObj;
        std::vector<double> tamanhoObj;

        std::vector<bool> objetoEncontrado; //quando o objeto é encontrado é true

//            std::vector<bool> ruido; //quando for ruido = true

    };

    dadosMorfo reMorfo;

    std::vector< dadosMorfo> matrizReMorfo;


    struct dadosCinema{
        std::vector<double>  varDistancia;
        std::vector<double>  varAngular;
        std::vector<double>  varArea;
        std::vector<double>  varCenX;
        std::vector<double>  varCenY;
        std::vector<double> varTamObjeto;
        std::vector<bool> ruidoMaxVaria;



    };

    dadosCinema reCinema;

    std::vector< dadosCinema> matrizReCinema;

    double frequencia;
    std::vector<double>  vetorFrequencia;
    double latencia;
    std::vector<double>  vetorLatencia;
    double duracao;
    std::vector<double>  vetorDuracao;

     parserXMLtoCSV conversor;


};

#endif // TELACONVERSORXMLCSV_H
