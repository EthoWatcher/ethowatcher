#ifndef TELAETOGRAFIA_H
#define TELAETOGRAFIA_H

#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QtMath>


//funcionamento da saida em xml
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QListWidget>

//etografia da marcela
#include "etografia.h"

//rsa
//modulorsa
#include "modulorsa.h"


namespace Ui {
class telaEtografia;
}

class telaEtografia : public QWidget
{
    Q_OBJECT

public:
    explicit telaEtografia(QWidget *parent = 0);
    ~telaEtografia();

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
        std::vector<QString> nomeOpencv;    //nome do video
        std::vector<int> frameFinal;    //frame final da analise
        std::vector<int> frameInicial; //frame Inicial da analise
        std::vector<int> frameProces;
        std::vector<int> frameBack; //frame Inicial da analise
        std::vector<int> erosao;
        std::vector<int> threshold;
        std::vector<double> escala;


        std::vector<dadosArea> area;


        std::vector<bool> chaInteMove; //chave que diz se é movel a area ou nao
        std::vector<dadosArea> areaJanInte; //informações sobre area movel ou fixa

        std::vector<bool> chaMaxVar;
        std::vector<double> tamMaxVar;



    };
    dadosVXML videoLista;

    QFile OutVideo;

    //experimentador
    struct dadosExperimentador{
        QString nome;
        QString lab;
    };

    dadosExperimentador experimentador;

    void setExperimentador(QString nome1, QString lab1);


    //leitura da lsita de videos
    QString  nomeLVxml;
    QFile OutListavideo;

    //cego
    moduloRsa rsa;

    //para a escolha da modalidade de etogafia

    bool chaveEto, chaveProces;
    bool chaTip;


    //para a gravar o relatorio

    QString nomeGravarProcesImagem;

    bool chaveArea=false;
    int contArea;
    bool chaJanInte=false;
    bool chaMaxVari=false;

    std::vector<bool>  objDentro;
    std::vector<std::vector<bool> > matObjDentro;
    double raioTest;
    double contCir=0;
    double conCir2=0;
    double contRet=0;
    double conRet2=0;



private slots:
    void on_pbUnicoVideo_clicked();

    void on_pbMulti_clicked();

    void on_pbCadastroCatalago_clicked();

    void on_pbEtografia_clicked();

    void on_pbCriarCatalago_clicked();

    void on_pbClearItem_clicked();

    void on_pbAddCategoria_clicked();

    void on_pbLerCatalago_clicked();

    void on_pbComecarAnalise_clicked();

    void on_cbAuto_clicked();

    void on_cbNested_clicked();

//    void on_pushButton_clicked();

    void on_pbGravarAnalasiteEtografica_clicked();



    void on_pbRefazer_clicked();

    void on_pbEtoVideo_clicked();

    void on_pbEtoProce_clicked();

    void on_pbEtoSem_clicked();

    void on_pbGravarAnalasiProces_clicked();

    void on_pbNextAnali_clicked();

private:
    Ui::telaEtografia *ui;

    void readCatalago();
    void lerVXML(QString);
    void enconPontoArea();

    //etografia da amrcela

    Etografia* eto;
    int dados[3];

public slots:

    void receverAnaliseEtografia();

};

#endif // TELAETOGRAFIA_H
