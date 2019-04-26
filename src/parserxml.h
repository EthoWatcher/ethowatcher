#ifndef PARSERXML_H
#define PARSERXML_H

#include <QObject>
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

class parserXML : public QObject
{
    Q_OBJECT
public:
    explicit parserXML(QObject *parent = 0);

    struct dadosVideo{
        bool controle =true;
        QString nome;
        double frameInicial;
        double frameFinal;
        double frameProce;
        int frameBack;
        double fps; //tem que corrigir isso de ler correto o valor
        double escala;

    };
    dadosVideo* videoLido;

    struct dadosMorfo{

        std::vector<double> frame;
        std::vector<double> area;
        std::vector<double>areaM;
        std::vector<double> centroidX;
        std::vector<double> centroidY;
        std::vector<double> anguloObj;
        std::vector<double> tamanhoObj;
        std::vector<float>  altura;
        std::vector<float> alturaM;
        std::vector<float>  largura;
        std::vector<float>larguraM;

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
        std::vector<float> varAltura;
        std::vector<float> varLargura;



    };

    dadosCinema reCinema;

    std::vector< dadosCinema> matrizReCinema;


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

    void readTCCM(QString nomeArquivo );

    QFile OutEtografia;
signals:
private:



public slots:
};

#endif // PARSERXML_H
