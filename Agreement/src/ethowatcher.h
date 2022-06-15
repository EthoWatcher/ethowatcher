#ifndef ETHOWATCHER_H
#define ETHOWATCHER_H

#include <QtCore>
#include <QFileDialog>
using namespace std;

struct dadosVideo{
    bool controle; //=true;
    QString nome;
    int frameInicial;
    int frameProce;
    int frameFinal;
    double fps; //=30; //tem que corrigir isso de ler correto o valor

};

struct catalago{
    int quantidadeDeCategorias; //=0;
    QString caminhoArquivo;
    QString tipoAnalise;
    std::vector<int> id;
    std::vector<QString> nome;
    bool controle; // true;

};


struct analiseEtografica{
   QString caminho_etografia;
   int quantidadeDePontos; //=0;
   QString tipoDeAnalise;
   std::vector<int> ponto;
   std::vector<int> id;
   std::vector<double> frameInicial;
   std::vector<double> frameFinal;
   bool controle; // =true;
};



struct Etografia{

    catalago *catalogo;
    analiseEtografica *registro;
    dadosVideo *video;

};




struct etografiaTotalizacoes{
    std::vector<QString>  componente;
    std::vector<double> duracao;
    std::vector<double> freq;
    std::vector<double> latencia;
    std::vector<bool> clicado;
    std::vector<bool> bordaSubida; //para analise de frequencia
    //double

};

void assert_file_exist(QString nome_arquivo);
QString abrindo_etografia();
Etografia lerETOXML(QString nomeArquivo);


std::vector<int> extrai_lista_quadro_quadro(Etografia etografia);
std::vector<int> extrai_catalogo(Etografia etografia);


class ethowatcher
{
public:
    ethowatcher();
};

#endif // ETHOWATCHER_H
