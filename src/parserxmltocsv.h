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
#ifndef PARSERXMLTOCSV_H
#define PARSERXMLTOCSV_H

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

//#include "xlsxdocument.h"

struct Cell {
  bool r_number;
  QString number;
  QString content;
} ;

static void add_cell (QList<Cell> *array_add, QString cell_number, QString content, bool r_number = false){
    Cell c;
    c.r_number = r_number;
    c.content = content;
    c.number = cell_number;
    array_add->append(c);

};

static QString next_letter (QString letter) {
    // melhorar essa função
          QString alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
          int start = alfabeto.indexOf(letter, 0, Qt::CaseInsensitive);
          QString saida = alfabeto.at(start+1);
          return saida;

//          QStringList alga_list = alfabeto.split(";");
//          int tamanho = alga_list.length();
//          bool r_reseta = tamanho <= start + 1;

//          if (r_reseta){
//             return alga_list[0];
//          }else{
//             return alga_list[start+1];
//          }

    };

static void gravar_csv_ls_cell(QString csv_path, QList< QList<Cell> > t_saida){
//    QFile outGravador_csv;
    QXlsx::Document xlsx;

    for (auto list_celulas : t_saida){
        for (auto celula: list_celulas){
            if(celula.r_number){
                xlsx.write(celula.number, celula.content.toDouble());
            }else{
                xlsx.write(celula.number, celula.content);
            }

        }
    }
    xlsx.saveAs(csv_path);

};


class parserXMLtoCSV
{
public:

    QString cabecalho_str;
    void converteArquivo(QString nomePath, QList<Cell> entrada);

    parserXMLtoCSV();
    ~parserXMLtoCSV();
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
    void escreverTimeCsv(QList<Cell> entrada);

    struct analiseSequencialComportamento{

          std::vector<int> dados;
          std::vector<double> dadosPorce;
          std::vector< std::vector<int> > listaDados;
          std::vector< std::vector<double> > listaDadosPorcentagem;

          std::vector<QString> classeCatalago;
           std::vector<QString> classeCatalagoPorcentagem;




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
    void escreverSeqCsv(QList<Cell> entrada);

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
        double fps; //tem que corrigir isso de ler correto o valor
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
    void escreverTrakinCsv( QList<Cell> entrada);


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
        std::vector<double> areaM;
        std::vector<double> centroidX;
        std::vector<double> centroidY;
        std::vector<double> anguloObj;
        std::vector<double> tamanhoObj;
        std::vector<float>  altura;
        std::vector<float>  largura;

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

    double frequencia;
    std::vector<double>  vetorFrequencia;
    double latencia;
    std::vector<double>  vetorLatencia;
    double duracao;
    std::vector<double>  vetorDuracao;




};

#endif // PARSERXMLTOCSV_H
