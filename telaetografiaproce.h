#ifndef TELAETOGRAFIAPROCE_H
#define TELAETOGRAFIAPROCE_H

#include <QWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QtMath>

#include "modulocaptador.h"
#include <QThread>
#include <QString>
#include <QByteArray>
#include <QImage>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


//funcionamento da saida em xml
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QListWidget>

#include "moduloprocessamento.h"
#include <QPixmap>
#include <QPainter>
#include <QPen>

#include <QVBoxLayout>
#include <QSignalMapper>
#include <QPushButton>
#include <QList>
#include <QShortcut>
#include <time.h>

//modulorsa
#include "modulorsa.h"
#include "QtMath"
#include "parserxmltocsv.h"


#include "ethowatcheros.h"

namespace Ui {
class telaEtografiaProce;
}

class telaEtografiaProce : public QWidget
{
    Q_OBJECT

public:
    explicit telaEtografiaProce(QWidget *parent = 0);
    void closeEvent(QCloseEvent * event);

    ~telaEtografiaProce();

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


    struct dadosSaidaEto{

        std::vector<int> id;
        std::vector<double> frameComeco;
        std::vector<double> framFim;
        //variaveis de armazenamento para correto funcionamento
        std::vector<double> frameFinalBuffer;
        std::vector<double> pontosPostos;
        std::vector<bool> chPontoValido;

        int quantidadeDepontos=0;

    };

    dadosSaidaEto saida;


    QFile outGravador;
    QString nomeGravarEtografia;
    QString nomeGravarEtografiaCSV;
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
        std::vector<QString> nomeVXML;
        std::vector<QString> nomeOpencv;    //nome do video
        std::vector<int> frameFinal;    //frame final da analise
        std::vector<int> frameInicial; //frame Inicial da analise
        std::vector<int> frameProces;
        std::vector<int> frameBack; //frame Inicial da analise
        std::vector<int> erosao;
        std::vector<int> threshold;
        std::vector<double> escala;
        std::vector<double> fps;
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

    bool chVideoEditado=false;

    std::vector<bool>  objDentro;
    std::vector<std::vector<bool> > matObjDentro;
    double raioTest;
    double contCir=0;
    double conCir2=0;
    double contRet=0;
    double conRet2=0;

    int contadorCirculo;
    int contadorRetangulo;
    int contProce;

cv::Mat conQim2Mat(QImage imaEntrada);


public slots:

//    void resultadoCalibracao();

    void startVideoTodo();
//    void setExperimentador(QString nomeExperimentador, QString laboratorio);
    void recebeContadorMorfo(int contador);

    void recebeImagem(QImage qiCaptador, int numFrame);

private slots:
    void on_pbEtoProce_clicked();

    void on_pbUnicoVideo_clicked();

    void on_pbStart_clicked();

    void on_btPlay_clicked();

    void on_pbEtoVideo_clicked();

    void on_btStop_clicked();

    void on_SliderVelocidade_sliderReleased();

    void on_btAvancar_clicked();

    void on_btVoltar_clicked();

    void on_hsTimer_valueChanged(int value);

    void on_pbLerCatalago_clicked();

    void slotMapeado(int a);

    void on_cbAuto_clicked(bool checked);

    void on_cbNested_clicked(bool checked);

    void on_pbGravarAnalasiteEtografica_clicked();

    void on_pbGravarAnalasiProces_clicked();

    void on_tabButtons_tabBarClicked(int index);

    void on_pbDeleteRegistros_clicked();

    void on_pbSaveImage_clicked();

    void on_pbTraking_clicked();

    void on_chbTamnho_clicked();

    void atualizaProcess(int numFrame);

private:
    Ui::telaEtografiaProce *ui;

    void readCatalago();
    void lerVXML(QString nomeArquivoLer);
    void lerVCXML(QString nomeArquivoLer);
    void enconPontoArea();

    bool chEtografia;
    bool escolheSelecao;
    //etografia da amrcela

//    Etografia* eto;
    //int dados[3];
    moduloCaptador *captadorDeVideo;
    moduloCaptador *captador;



    QThread *captadorThread;
    float somaTempo=0;
    float somaTempoFilming=0;
    moduloProcessamento *dados;
    QThread * thrProce;

    std::vector<moduloProcessamento*> listaProcessamento;
    std::vector<QThread * >listaThreadProcessamento;

    int widthPanProcess;
    int  heightPanProcess;

    int contNumeroGrava=0;
    bool chProceON;

    QPen canetaQuadro;
    QPen canetaAmarela;

    QPen canetaPreta;
    QPen canetaVermelha;

    QList<QPushButton*> buttonList;
    QPushButton *pb;

    QList<QCheckBox *> cheboxList;
    QCheckBox *chebox;


    std::vector<QString> nomeCate;
    std::vector<bool> clicado;
    int numeroDeBotoes;
    double frame_atual;
//    double finalFrame;
    bool habilita=true; //tava false
    int count=0;
    int compAnterior=-1;
    int contAtivoReg=0;
    bool chCorrigir=false;
    //int finalFrame;
    QImage qiFundo;

    void creatShortCurt(QString atalho, QPushButton *pushBut);

    enum tecla{

        a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z

    };

    bool chBotoesCor=true;

    moduloRsa rsaCon;


    clock_t tinicial,tfinal;
    float tresposta;
    float somatTresposta=0;
    bool chPriemira;


    void atualizaRegistro();


//    void lerEtografia();
//    void totalizacoesEtografia();
//    void escreverEtografiaCsv();
    bool chNovoValor=true;


    double frequencia;
    std::vector<double>  vetorFrequencia;
    double latencia;
    std::vector<double>  vetorLatencia;
    double duracao;
    std::vector<double>  vetorDuracao;

    parserXMLtoCSV *parser;
    int contPrcessamento=0;

    void reiniciaProcessamento();
signals:
    void reiniciaProce();




};

#endif // TELAETOGRAFIAPROCE_H
