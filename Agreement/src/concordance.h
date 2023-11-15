#ifndef CONCORDANCE_H
#define CONCORDANCE_H
#include <vector>
#include "ethowatcher.h"


using namespace  std;
#include <QXmlStreamWriter>
#include <QFileDialog>
#include <algorithm>

#include <QtCore>
#include <QThread>
#include <QObject>

class Concordance_Cohen
{
public:
    Concordance_Cohen();

    QString carrega_etografia(Etografia eto1, Etografia eto2);
    void grava_xml_analise(QString caminho_arquivo);

    void gravar_csv(QString path_eto, QString t_saida);
    Etografia eto1;
    Etografia eto2;
    std::vector<std::vector<int> > matrix_concordance_nn ;
    std::vector<float> soma_linha;
    std::vector<float> soma_coluna;

private:
    struct confiabilidade_categoria {
      QString nome;
      std::vector<std::vector<int> > matrix;
      float concordancia_acaso;
      float concordancia_observada;
      float viez;
      float prevalencia;
      float kappa;

      std::vector<std::vector<int> > matrix_max;
      float concordancia_acaso_max;
      float concordancia_observada_max;
      float viez_max;
      float prevalencia_max;
      float kappa_max;
    };

    std::vector< confiabilidade_categoria> list_confiabilidade;

    QString text_csv_concordancia();
    void calculo_concordancia();
    void le_xml_analise(QString caminho_arquivo);


    std::vector<int> lista_eto1;
    std::vector<int> lista_eto2;
    std::vector<int> catalogo_id;
    std::vector<QString> catalogo_categorias_nomes;
    float concordancia_acaso;
    float concordancia_observada;
    float kappa_medio;


};

std::vector<std::vector<int> > gera_matrix_22_pela_categoria(std::vector<int> etrografia_1, std::vector<int> etrografia_2, std::vector<int> catalogo, int id_categ);
std::vector<std::vector<int> > gera_matrix_22(std::vector<std::vector<int> > matrix_nn);


std::vector<int> _constroi_lista_quadros(Etografia eto);
std::vector< std::vector<int> > constroi_matrix_concordancia_cohen(std::vector<int> etografia_1, std::vector<int> etografia_2, std::vector<int> catalogo);
float calcula_concordancia_observada(std::vector< std::vector<int> > matriz_concordancia);
float calcula_concordancia_acaso(std::vector< std::vector<int> > matriz_concordancia);
float calcula_kappa_medio(std::vector<std::vector<int> > matriz_concordancia);

float calculo_vies_categoria(std::vector<std::vector<int> > matiz_concordancia_22);
float calculo_prevalencia_categoria(std::vector<std::vector<int> > matiz_concordancia_22);
std::vector<std::vector<int> > arruma_matrix_kappa_maximo(std::vector<std::vector<int> > matiz_concordancia_22);
float calculo_por_categoria(std::vector<std::vector<int> > matiz_concordancia_22);



float transforma_matris_nn_22();


// calculo do kappa maximo
int  get_soma_linha(std::vector<int> l_grid);

class Marginal{
public:
    int linha;
    int colun;
    Marginal(int linha, int colun){
        this->colun = linha;
        this->linha = colun;
    };
    int get_menor_valor(){
        if (this->colun > this->linha){
            return this->linha;
        }else{
            return this->colun;
        }

    };
    int get_maior_Valor(){
        if (this->colun < this->linha){
            return this->linha;
        }else{
            return this->colun;
        }
    };

    int get_diferenca(){
        bool r_linha_maior = linha > colun;
        if(r_linha_maior){
            return linha - colun;
        }else{
            return colun - linha;
        }

    }


};

std::vector<int>  transpose_linha(std::vector<std::vector<int> >grid, int linha);
std::vector<bool>  transpose_linha_bool(std::vector<std::vector<bool> >grid, int linha);
Marginal get_colu_linha_soma(std::vector<std::vector<int> >grid, int linha);
std::vector<int>  get_all_marginal(std::vector<std::vector<int> >grid);
std::vector<Marginal>  get_tuple_marginal(std::vector<std::vector<int> >grid);
std::vector<std::vector<int> > generate_matriz_maxima(std::vector<std::vector<int> >grid);

std::vector<std::vector<bool> > generate_matriz_maxima_visitada(std::vector<std::vector<int> >grid);



// calculando vies e prevalencia de uma matriz NN
std::vector<float> rota_vetor(double teta, int celula);
float soma_vetor(std::vector<int> ls_celulas);

float realiza_permutacao(std::vector<int> l_centr, int qnt_maxima);
float calcula_prevalencia_NN(std::vector<std::vector<int>> grid, int qnt_maxima = 10000);
float calcula_vies_NN(std::vector<std::vector<int>> grid, int qnt_maxima  = 10000);

//int get_maior_Valor(Marginal tuple_in);
struct valor_visto_pos{
  int valor_visto;
  int pos;
  bool visited;
};

std::tuple<bool, std::vector<std::vector<int> > > solver_nova_max(std::vector<std::vector<int> > & grid_max,
            std::vector<std::vector<bool> > matrix_max_visitada,
            std::vector<valor_visto_pos > ls_matriz,
            std::vector<Marginal> tuple_marginal);

std::tuple<bool, std::vector<std::vector<int> > > solver(std::vector<std::vector<int> > &grid_max,
            std::vector<std::vector<bool> > matrix_max_visitada,
            std::vector<Marginal> tuple_marginal);


std::tuple<bool, std::vector<std::vector<int> > > generate_matriz_maxima_correta(std::vector<std::vector<int> >grid, int qnt_simpl);


// Calculo da concordancia

class Concordance_Fleiss{

public:
    Concordance_Fleiss();

    void add_arquivos_etografia(Etografia eto_grafia);
    QString text_fleiss_concordancia();
    void gravar_csv(QString path_eto, QString t_saida);

private:
    void calculo_concordancia();
    double calcularPI(std::vector<int> entrada, double qnt_de_TCC);
    double calcularPJ(std::vector<int> entrada, double qntd_videos, double qnt_quadros);

    //guarda a lista de etografias para a análise.
    std::vector< dadosVideo *> dadosDosVideos;
    std::vector< analiseEtografica *> etografiaDosVideos;
    std::vector< catalago *> catalagoDosVideos;
    std::vector< Etografia *> list_etografias;
    int quantidadeDeVideo;


    std::vector< analiseEtografica *> etografiaKoho;
    std::vector< dadosVideo *> videosKoho;
    std::vector< catalago *> catalagoKoho;


    std::vector<std::vector< std::vector<int> > > anaEtoDosVideos;
    std::vector<int> frameFleisLinha;

    //SAIDA ?
    std::vector< std::vector<int> > frameFleisTabela;
    std::vector<double> PIcalculados;
    std::vector<double> PJcalculados;
    double Pe;
    double P_medio;
    double Kappa;


//    void grava_xml_analise(QString caminho_arquivo);
//    void grava_csv_analise(QString caminho_arquivo);

};



class Calculo_paper: public QThread
{
    Q_OBJECT
public:
    Calculo_paper(std::vector<int> etrografia_1, std::vector<int> etrografia_2, std::vector<int> catalogo , int qnt_simpl, int qnt_maxima_permutaca, QObject *parent = 0);
    void do_proces();

    struct Concordancia{
        int categoria;
        float observada;
        float acaso;
        float kappa;
        float vies;
        float prevalencia;
        std::vector< std::vector<int> > matriz_concordancia;

    };
    std::vector<int> et1;
    std::vector<int> et2;
    std::vector<Calculo_paper::Concordancia> list_kappa_cat;
    std::vector<Calculo_paper::Concordancia> list_kappa_cat_max;
    Calculo_paper::Concordancia catalogo_var;
    Calculo_paper::Concordancia catalogo_var_max;



private:
    std::vector<int> etrografia_1;
    std::vector<int> etrografia_2;
    std::vector<int> catalogo;
    int qnt_simpl;
    int qnt_maxima_permutaca;
    void run() override {
            qDebug() << "THREAD DA CALCULOOO DOS DESCRITORES " << QThread::currentThreadId();
            this->do_proces();
    }
};



#endif // CONCORDANCE_H
