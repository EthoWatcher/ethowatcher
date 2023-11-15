#include <QString>
#include <QtTest>
#include <QFile>
#include <QTextStream>

#include "ethowatcher.h"
#include "concordance.h"
#include "bootstrap.h"
#include "relatorio_paper.h"

#include <QApplication>
#include <QDir>
#include <numeric>

// add necessary includes here
QString PATH_DATA = "C:/Doutorado_softwares/Reliability/data/"; //variavel global.
QString PATH_TESTE = "C:/Doutorado_softwares/saida_teste/";


class test_concordancia : public QObject
{
    Q_OBJECT

public:
    test_concordancia();
    ~test_concordancia();

private slots:

    void test_bootstra_seed();
    void test_artigo_dados();
    void test_gera_matrix_22_pela_categoria();

    void test_carrega_etografia();
    void test_novo_amostrador();
    void test_relatorio_paper();


//    void test_bootstra_seed();


    void test_case1();
//    void testCase1();
//    void testCase12();
    void criando_matriz();
//    void teste_parser();
    void teste_calculo_vies();
    void teste_calculo_prevalencia();
    void teste_calculo_kappa_maximo();
    void teste_calculo_por_categoria();
//    void construindo_lista_dados();
    void test_gera_matrix_22();


//    void test_gera_lista_quador();
//    void test_fless_kappa();
//    void test_integracao_cohen();



    // testando bootstrap
    void test_bootstrap();
//    void test_get_all_var();

    //testando matriz maxima
    void test_soma_linha();
    void test_solver();
    void test2_solver();
    void test_generate_matriz_maxima_correta();


    void test_rotacional();
    void test_calcula_prevalencia_NN();

    void test_convert_json_list_int();








};

test_concordancia::test_concordancia()
{

}

test_concordancia::~test_concordancia()
{

}

void test_concordancia::test_novo_amostrador()
{
//    std::vector<int> l_centr = {0, 1, 2,3}; //mesmo tamanho que a entrada.
    //lendo etografias do video 1
    Etografia eto_lida2 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/6e5h4h6.etoxml");
    Etografia eto_lida3 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/6e5h4h6bis4.etoxml");
//    Etografia eto_lida4 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/7e5h4h6a.etoxml");
//    Etografia eto_lida5 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/9e5h4h6b.etoxml");


    //lendo etografias do video 2
    Etografia eto_lida_vid_2_1 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/2e3hc5.etoxml");
    Etografia eto_lida_vid_2_2 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/2e3hc5bis4.etoxml");


    std::vector<QString> catalogo_categorias_nomes;
    catalogo_categorias_nomes = eto_lida2.catalogo->nome;
    catalogo_categorias_nomes.push_back("Undefined (frames that are not marked)");

    std::vector<int> catalogo  = [](std::vector<QString> catalogo_categorias_nomes){
        std::vector<int> saida;

        int i=0;
        for(auto cate: catalogo_categorias_nomes){
            saida.push_back(i);
            i++;
        }

        return saida;

    }(catalogo_categorias_nomes);

    QList<QString> cata_name = [](std::vector<QString> catalogo_categorias_nomes){
        QList<QString> saida ;

        for(auto cate: catalogo_categorias_nomes){
            saida.push_back(cate);
        }

        return saida;
    }(catalogo_categorias_nomes);


    auto arruma_lista = [](std::vector<int> ls_quadros, QList<QString> cata_nam){
        int cat_indef = cata_nam.count() -1 ;
        std::vector<int> saida;

        for(auto quadro: ls_quadros){
            bool r_quadro_indefinido = quadro == -1;
            if(r_quadro_indefinido){
                saida.push_back(cat_indef);
            }else{
                saida.push_back(quadro);
            }

        }

        return saida;

    };

//    std::vector<int> ls_quadros_1 = arruma_lista(_constroi_lista_quadros(eto_lida2), cata_name);
//    std::vector<int> ls_quadros_2 = arruma_lista(_constroi_lista_quadros(eto_lida3), cata_name);

    std::vector<std::vector<int>> ls_etografias;
    ls_etografias.push_back(arruma_lista(_constroi_lista_quadros(eto_lida2), cata_name));
    ls_etografias.push_back(arruma_lista(_constroi_lista_quadros(eto_lida3), cata_name));
//    ls_etografias.push_back(arruma_lista(_constroi_lista_quadros(eto_lida4), cata_name));
//    ls_etografias.push_back(arruma_lista(_constroi_lista_quadros(eto_lida5), cata_name));


    std::vector<std::vector<int>> ls_etografias_video_2;
    ls_etografias_video_2.push_back(arruma_lista(_constroi_lista_quadros(eto_lida_vid_2_1), cata_name));
    ls_etografias_video_2.push_back(arruma_lista(_constroi_lista_quadros(eto_lida_vid_2_2), cata_name));



    int qnt_valores_por_etogrfia = int(ls_etografias[0].size());
    Bootstrap_2 boo = Bootstrap_2(ls_etografias, qnt_valores_por_etogrfia, 10);
    Bootstrap_2 boo1 = Bootstrap_2(ls_etografias_video_2,qnt_valores_por_etogrfia, 10);

    QList<Bootstrap_2> ls_boot;
    ls_boot.append(boo);
    ls_boot.append(boo1);
    Bootstrap_mult_videos mult_bol = Bootstrap_mult_videos(ls_boot,qnt_valores_por_etogrfia, 10);

    auto sai = mult_bol.generate_new_etografia();

    sai = boo.generate_new_etografia();
    sai = boo.generate_new_etografia();
    qDebug() << std::get<0>(sai);



}

void test_concordancia::test_case1()
{
//    QVERIFY2(false, "Failure for some reason");
}


//void test_concordancia::testCase12()
//{
//    //     adicionar para que encontre o arquivo.
//        Etografia eto_lida2 = lerETOXML("../data/1e3z1h4.etoxml");

//        // essa opção vai crashar
//        // fazer um teste somente com essa opção
//        // Etografia eto_lida1 = lerETOXML("");


//        //    QString nome_arquivo = abrindo_etografia();
//        //    Etografia eto_lida = lerETOXML(nome_arquivo);

//        QVERIFY2(true, "Failure");
//}

//void test_concordancia::construindo_lista_dados(){

//    Etografia eto_lida2 = lerETOXML("../data/1e3z1h4.etoxml");
//    Etografia eto_lida3 = lerETOXML("../data/1e3z1h4.etoxml");

//    std::vector<int> catalogo  =  eto_lida2.catalogo->id;

//    // funcao para gerar uma tripa de dados para colocar na matrix de concordancia.
//    // pegar os elementos
//    //frameFinal - anota o ponto final
//    //frameInicial - anota o ponto inicial
//    //id  - lista que tem o id marcado
//    // {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3 ....
//    //{0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 3, 4, 4, 4, 2, 4, 0, 3, 0, 2, 0, 0, 0, 1, 1, 1, 0, 0}


////    auto matriz_concordancia = constroi_matrix_concordancia_cohen(eto_lida2, eto_lida3,catalogo);
//    qDebug() << "saida";
//}

// uma função para construir a estrutura de dados.

void test_concordancia::test_gera_matrix_22(){
    // colocar os dados gerados
    std::vector<int> etrografia_1  = {0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 3, 4, 4, 4, 2, 4, 0, 3, 0, 2, 0, 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> etrografia_2  = {0, 0, 0, 2, 2, 2, 0, 0, 3, 0, 2, 2, 3, 5, 4, 4, 2, 4, 0, 3, 0, 2 ,0 , 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> catalogo  = {0, 1, 2, 3, 4, 5};

    std::vector<std::vector<int> > matrix_concordance_nn = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);
    std::vector<std::vector<int> > matrix_22 = gera_matrix_22(matrix_concordance_nn);


    qDebug() << matrix_22;

}


void test_concordancia::test_gera_matrix_22_pela_categoria(){
    std::vector<int> etrografia_1  = {0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 3, 4, 4, 4, 2, 4, 0, 3, 0, 2, 0, 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> etrografia_2  = {0, 0, 0, 2, 2, 2, 0, 0, 3, 0, 2, 2, 3, 5, 4, 4, 2, 4, 0, 3, 0, 2 ,0 , 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> catalogo  = {0, 1, 2, 3, 4, 5};

    std::vector<std::vector<int> > matrix_22_cat2 = gera_matrix_22_pela_categoria(etrografia_1, etrografia_2, catalogo, 2);


    qDebug() << matrix_22_cat2;

}

//void test_concordancia::test_gera_lista_quador()
//{
//    Etografia eto_lida2 = lerETOXML(PATH_DATA + "1e3z1h4.etoxml");
//    std::vector<int> si = _constroi_lista_quadros(eto_lida2);

//}


//void test_concordancia::teste_parser()
//{
//    Etografia etografia1 = lerETOXML("caminho da etografia");
//    std::vector<int> etrografia_1  = extrai_lista_quadro_quadro(etografia1);
//    Etografia etografia2 = lerETOXML("caminho da etografia");
//    std::vector<int> etrografia_2  = extrai_lista_quadro_quadro(etografia2);

//    // checar se as etografias possuem o mesmo catalogo.

//    std::vector<int> catalogo = extrai_catalogo(etografia1);
//    auto matriz_concordancia = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);


//    qDebug() << calcula_concordancia_acaso(matriz_concordancia);
//}

void test_concordancia::criando_matriz()
{
    std::vector<int> etrografia_1  = {0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 3, 4, 4, 4, 2, 4, 0, 3, 0, 2, 0, 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> etrografia_2  = {0, 0, 0, 2, 2, 2, 0, 0, 3, 0, 2, 2, 3, 5, 4, 4, 2, 4, 0, 3, 0, 2 ,0 , 0, 0, 1, 1, 1, 0, 0};
    std::vector<int> catalogo  = {0, 1, 2, 3, 4, 5};

    auto matriz_concordancia = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);


    float concordancia_acaso = calcula_concordancia_acaso(matriz_concordancia);
    float concordancia_observada = calcula_concordancia_observada(matriz_concordancia);

//    float kappa_medio = calcula_kappa_medio(matriz_concordancia);


    qDebug() << calcula_concordancia_acaso(matriz_concordancia);


}
void test_concordancia::teste_calculo_por_categoria(){
    std::vector<std::vector<int>> vetor_entrada= {{29,21},{23,27}};
    float concordancia_categoria_1 = calculo_por_categoria(vetor_entrada);
    //qDebug() <<viez_categoria;


}

void test_concordancia::teste_calculo_vies(){
    std::vector<std::vector<int>> vetor_entrada= {{29,21},{23,27}};
    float viez_categoria = calculo_vies_categoria(vetor_entrada);
    qDebug() <<viez_categoria;


}

void test_concordancia::teste_calculo_prevalencia(){
    std::vector<std::vector<int>> vetor_entrada= {{29,21},{23,27}};
    float prevalencia_categoria = calculo_prevalencia_categoria(vetor_entrada);
    qDebug() <<prevalencia_categoria;


}

void test_concordancia::teste_calculo_kappa_maximo(){
    std::vector<std::vector<int>> vetor_entrada= {{2,1},{7,50}};
    std::vector<std::vector<int>> kappa_maximo_matrix = arruma_matrix_kappa_maximo(vetor_entrada);
//    qDebug() <<10;

}

//void test_concordancia::test_fless_kappa(){
//    Etografia eto_lida2 = lerETOXML(PATH_DATA + "1e3z1h4.etoxml");
//    Etografia eto_lida3 = lerETOXML(PATH_DATA + "1e3z1h4.etoxml");

//    Concordance_Fleiss calculado_fless;

//    calculado_fless.add_arquivos_etografia(eto_lida2);
//    calculado_fless.add_arquivos_etografia(eto_lida2);
//    calculado_fless.add_arquivos_etografia(eto_lida3);

//    QString texto = calculado_fless.text_fleiss_concordancia();
//    calculado_fless.gravar_csv(PATH_TESTE+"teste_fleiss.csv", texto);


//}

//void test_concordancia::test_integracao_cohen()
//{
//  Concordance_Cohen cohen;
//  Etografia eto_lida1 = lerETOXML(PATH_DATA + "1e3z1h4.etoxml");
//  Etografia eto_lida2 = lerETOXML(PATH_DATA + "1e3z1h4.etoxml");

//  QString saida = cohen.carrega_etografia(eto_lida1, eto_lida2 );

//  cohen.gravar_csv(PATH_TESTE+"teste_cohen.csv", saida);
//}

//struct concordanci{

//};


void test_concordancia::test_artigo_dados()
{
    //0 - swimming
    //1 - climbimg
    //2 - Immobility
    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
    std::vector<int> catalogo  = {0, 1, 2};

    auto matriz_concordancia = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);


    float concordancia_acaso = calcula_concordancia_acaso(matriz_concordancia);
    float concordancia_observada = calcula_concordancia_observada(matriz_concordancia);
    float kappa_catalogo = calcula_kappa_medio(matriz_concordancia);
    qDebug() << "Concordancia Cohone catalogo "<< matriz_concordancia << "concordancia acaso: " << concordancia_acaso << "concordancia observada: " << concordancia_observada << "Kappa: " << kappa_catalogo;


    std::vector<std::vector<int> > matrix_22_swimming = gera_matrix_22_pela_categoria(etrografia_1, etrografia_2, catalogo, 0);
    float viez_swimming = calculo_vies_categoria(matrix_22_swimming);
    float prevalencia_swimming = calculo_prevalencia_categoria(matrix_22_swimming);
    float kappa_swimming = calcula_kappa_medio(matrix_22_swimming);
    qDebug() << "Swimming \n" << matrix_22_swimming << "Vies: " << viez_swimming << "Prevalencia: " << prevalencia_swimming << "Kappa: " << kappa_swimming;

    std::vector<std::vector<int>> kappa_maximo_matrix = arruma_matrix_kappa_maximo(matrix_22_swimming);
    float viez_max_swimming = calculo_vies_categoria(kappa_maximo_matrix);
    float prevalencia_max_swimming = calculo_prevalencia_categoria(kappa_maximo_matrix);
    float kappa_max_swimming = calcula_kappa_medio(kappa_maximo_matrix);
    qDebug() << "Swimming max \n" << kappa_maximo_matrix << "Vies: " << viez_max_swimming << "Prevalencia: " << prevalencia_max_swimming << "Kappa: " << kappa_max_swimming;



//    std::vector<std::vector<int> > matrix_22_climbimg = gera_matrix_22_pela_categoria(etrografia_1, etrografia_2, catalogo, 1);


//    std::vector<std::vector<int> > matrix_22_Immobility = gera_matrix_22_pela_categoria(etrografia_1, etrografia_2, catalogo, 2);


//    float kappa_medio = calcula_kappa_medio(matriz_concordancia);


//    qDebug() << calcula_concordancia_acaso(matriz_concordancia


}

void test_concordancia::test_bootstrap(){
    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
    std::vector<int> catalogo  = {0, 1, 2};

    Bootstrap a = Bootstrap(etrografia_1,etrografia_2 );
    std::tuple< std::vector<int>, std::vector<int> >  novas_etografias  = a.generate_new_etografia();
    std::vector<int> na1 = std::get<0>(novas_etografias);
    std::vector<int> na2 = std::get<1>(novas_etografias);

    std::tuple< std::vector<int>, std::vector<int> >  novas_etografias_2  = a.generate_new_etografia();
    std::vector<int> nb1 = std::get<0>(novas_etografias_2);
    std::vector<int> nb2 = std::get<1>(novas_etografias_2);
    std::tuple< std::vector<int>, std::vector<int> >  novas_etografias_3  = a.generate_new_etografia();
}

//void test_concordancia::test_get_all_var()
//{
//    //arrumar isso para ser uma função
//    //0 - swimming
//    //1 - climbimg
//    //2 - Immobility
//    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
//    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
//    std::vector<int> catalogo  = {0, 1, 2};

//    std::vector< Calculo_paper *>  varios_kappa;

//    Calculo_paper c_1 = Calculo_paper(etrografia_1, etrografia_2, catalogo, 1, 10000);
////    varios_kappa.push_back(c_1);
//    Bootstrap a = Bootstrap(etrografia_1,etrografia_2 );
//    for(int i=0; i<1000; i++){

//        std::tuple< std::vector<int>, std::vector<int> >  novas_etografias  = a.generate_new_etografia();
//        std::vector<int> e1 = std::get<0>(novas_etografias);
//        std::vector<int> e2 = std::get<1>(novas_etografias);
//        Calculo_paper *c = new Calculo_paper(e1, e2, catalogo, 1, 10000);
//        varios_kappa.push_back(c);

//    }


//    // calculando media e std

//    auto calc_media = [](std::vector<float> kappa_medidos )
//        {


//            //calculando a media
//            float media=0;
//            for(float x: kappa_medidos){
//                media = media + x;

//            }
//            media = media/kappa_medidos.size();
//            return media;
//        };

//    auto calc_std = [](std::vector<float> kappa_medidos )
//        {
//            //calculando a media
//            float media=0;
//            for(float x: kappa_medidos){
//                media = media + x;

//            }
//            media = media/kappa_medidos.size();

//            double accum = 0.0;
//            std::for_each (std::begin(kappa_medidos), std::end(kappa_medidos), [&](const double d) {
//                accum += (d - media) * (d - media);
//            });

//            double stdev = sqrt(accum / (kappa_medidos.size()-1));

//            return stdev;
//        };


//    // pegando as variaveis
//    auto get_catalogo_kappa = [](std::vector< Calculo_paper *>  varios_kappa){
//        std::vector<float> kappa_medidos;
//        for(auto x: varios_kappa){
//            kappa_medidos.push_back(x->catalogo_var.kappa);
//        }
//        return kappa_medidos;
//    };

//    auto get_kappa_cat_n = [](std::vector< Calculo_paper *>  varios_kappa, int n){
//        std::vector<float> kappa_medidos;
//        for(auto x: varios_kappa){
//            kappa_medidos.push_back(x->list_kappa_cat[n].kappa);
//        }
//        return kappa_medidos;
//    };

//    auto get_max_kappa_cat_n = [](std::vector< Calculo_paper*>  varios_kappa, int n){
//        std::vector<float> kappa_medidos;
//        for(auto x: varios_kappa){
//            kappa_medidos.push_back(x->list_kappa_cat_max[n].kappa);
//        }
//        return kappa_medidos;
//    };


//    auto kappa_catalogo = get_catalogo_kappa(varios_kappa);
//    auto kappa_med_cate_0 = get_kappa_cat_n(varios_kappa, 0);
//    auto kappa_max_cate_0 = get_max_kappa_cat_n(varios_kappa, 0);


//   float m_medida  = calc_media(kappa_med_cate_0);
//   float m_max     = calc_media(kappa_max_cate_0);
//   float std_mdida = calc_std(kappa_med_cate_0);
//   float std_max   = calc_std(kappa_max_cate_0);
//   float d_cohen   = (m_max - m_medida)/ sqrt(((std_max * std_max) + (std_mdida * std_mdida))/2);

//    qDebug() << m_medida << m_max << std_mdida << std_max << d_cohen;



//}

void test_concordancia::test_soma_linha()
{
    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
    std::vector<int> catalogo  = {0, 1, 2};

    auto matriz_concordancia = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);

    std::vector< std::vector<int> > grid = {
        {2, 2, 2},
        {4, 0, 2},
        {2, 2, 3}
    };
    Marginal m = get_colu_linha_soma(grid, 0);

    qDebug() << m.colun << m.linha;

}

void test_concordancia::test_solver()
{
//    std::vector< std::vector<int> > grid = {
//        {2, 2, 2},
//        {4, 0, 2},
//        {2, 2, 3}
//    };
    std::vector< std::vector<int> > grid = {
        {4, 2, 0},
        {3, 0, 0},
        {0, 2, 2}
    };

    std::vector<std::vector<int> > grid_max = generate_matriz_maxima(grid);

//    std::vector< std::vector<int> > grid_max = {
//        {4, 0, 0},
//        {0, 0, 0},
//        {0, 0, 2}
//    };



    std::vector<std::vector<bool> > matrix_max_visitada = generate_matriz_maxima_visitada(grid);
    std::vector<Marginal> tuple_marginal = get_tuple_marginal(grid);

//    auto resolucao = solver(grid_max, matrix_max_visitada, tuple_marginal);

//    std::vector<std::vector<int> > m_saida = std::get<1>(resolucao);
//    bool r_saida = std::get<0>(resolucao);
//    qDebug() << "saiida";


//    auto resolucao_solver = solver(grid_max, matrix_max_visitada, tuple_marginal);

//    std::vector<std::vector<int> > m_saida_2 = std::get<1>(resolucao_solver);
//    bool r_saida_max = std::get<0>(resolucao_solver);
//    qDebug() << "saiida";

}

void test_concordancia::test2_solver()
{
    std::vector< std::vector<int> > grid = {
        {5, 1, 0},
        {7, 0, 0},
        {0, 0, 0}
    };

    std::vector< std::vector<int> > grid_max = {
        {5, 1, 0},
        {7, 0, 0},
        {0, 0, 0}
    };

    std::vector<std::vector<bool> > matrix_max_visitada = generate_matriz_maxima_visitada(grid);
    std::vector<Marginal> tuple_marginal = get_tuple_marginal(grid);

    auto resolucao_solver = solver(grid_max, matrix_max_visitada, tuple_marginal);
    std::vector<std::vector<int> > m_saida_2 = std::get<1>(resolucao_solver);
    bool r_saida_max = std::get<0>(resolucao_solver);
    qDebug() << "saiida";


}

void test_concordancia::test_generate_matriz_maxima_correta()
{
//    std::vector< std::vector<int> > grid = {
//        {4, 2, 0},
//        {3, 0, 0},
//        {0, 2, 2}
//    };

//    std::vector< std::vector<int> > grid = {
//        {3, 0, 0},
//        {2, 0, 0},
//        {0, 3, 5}
//    };

    std::vector< std::vector<int> > grid = {
        {5, 1, 0},
        {7, 0, 0},
        {0, 0, 0}
    };
    auto resolucao_solver = generate_matriz_maxima_correta(grid, 1);
}


void test_concordancia::test_rotacional()
{
    auto saida = rota_vetor(180, 1); // {-1, 0}
    auto saida2 = rota_vetor(180, 0); // {0, 0}
    auto saida3 = rota_vetor(0, 1);   // {1, 0}

    qDebug() << saida;

}

void test_concordancia::test_calcula_prevalencia_NN()
{
//        std::vector< std::vector<int> > grid = {
//            {4, 2, 0},
//            {3, 0, 0},
//            {0, 2, 2}
//        };

//    std::vector< std::vector<int> > grid = {
//        {2, 4, 2},
//        {2, 0, 2},
//        {2, 2, 3}
//    };
//    std::vector< std::vector<int> > grid = {
//        {2, 4, 2},
//        {2, 3, 2},
//        {2, 2, 3}
//    };

    //preciso checar as permutações.

        std::vector< std::vector<int> > grid = {
            {2, 2},
            {4, 3}
        };


    auto prevalencia_NN = calcula_prevalencia_NN(grid);
    auto vies_NN = calcula_vies_NN(grid);

//    float calculo_vies_categoria(std::vector<std::vector<int> > matiz_concordancia_22);
//    float calculo_prevalencia_categoria(std::vector<std::vector<int> > matiz_concordancia_22);
    auto prevalencia = calculo_prevalencia_categoria(grid);
    auto vies = calculo_vies_categoria(grid);

    qDebug() << prevalencia_NN << prevalencia <<vies_NN << vies;
}

void test_concordancia::test_convert_json_list_int()
{
    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
    auto saida = creat_var("aaa",generate_list_number_json(etrografia_1));
    QList<QString> saida_ls;
    saida_ls.push_back(saida);

    auto s_l = creat_object(saida_ls);

    qDebug() << saida;
}

void test_concordancia::test_bootstra_seed()
{
    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
    std::vector<int> catalogo  = {0, 1, 2};
    QList<QString> cata_name = {"swimming",
                                     "climbimg",
                                     "Immobility"};
    QList<QString> ls_path_eto;
//    0 - swimming
//    1 - climbimg
//    2 - Immobility


    std::vector<std::vector<std::vector<int>>> ls_videos;


    std::vector<std::vector<int>> ls_etografias;
    ls_etografias.push_back(etrografia_1);
    ls_etografias.push_back(etrografia_2);
    ls_videos.push_back(ls_etografias);
    int qnt_valores_por_etogrfia = int(ls_etografias[0].size());


    Relatorio_paper relatorio = Relatorio_paper(ls_videos,
                                                qnt_valores_por_etogrfia,
                                                catalogo,
                                                cata_name,
                                                10, 1,

                                                1, 5, ls_path_eto);
    relatorio.do_proces();
    relatorio.generate_relatorio();

    QWidget *parent1 = nullptr;
    const QString &caption = QString("Save File");
    QString path = QFileDialog::getSaveFileName(
                parent1,
                caption,
                "C://Users//Bio//Desktop//videos//",
                "Report (*.xlsx)"
                );


    gera_relatorio_python(path, relatorio.txt_relatorio);

    qDebug() << "vies";





    Relatorio_paper relatorio_2 = Relatorio_paper(ls_videos,
                                                qnt_valores_por_etogrfia,
                                                catalogo,
                                                cata_name,
                                                10, 1,
                                                  1, 5, ls_path_eto);
    relatorio_2.do_proces();
    relatorio_2.generate_relatorio();



    QString path_2 = QFileDialog::getSaveFileName(
                parent1,
                caption,
                "C://Users//Bio//Desktop//videos//",
                "Report (*.xlsx)"
                );


    gera_relatorio_python(path_2, relatorio_2.txt_relatorio);

    qDebug() << "vies";
}




void test_concordancia::test_relatorio_paper()
{
    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
    std::vector<int> catalogo  = {0, 1, 2};
    QList<QString> cata_name = {"swimming",
                                     "climbimg",
                                     "Immobility"};
//    0 - swimming
//    1 - climbimg
//    2 - Immobility
    int qnt_amostras = 10;
    int qnt_simpl = 1;
    int qnt_simpl_boots = 2;
    int qnt_maxima_permutaca = 10000;
    int seed_bootstap = 2;


    std::vector<std::vector<std::vector<int>>> ls_videos;


    std::vector<std::vector<int>> ls_etografias;
    ls_etografias.push_back(etrografia_1);
    ls_etografias.push_back(etrografia_2);
    ls_videos.push_back(ls_etografias);
    int qnt_valores_por_etogrfia = int(ls_etografias[0].size());

    QList<QString> ls_path_eto;
    Relatorio_paper relatorio = Relatorio_paper(ls_videos,
                                                qnt_valores_por_etogrfia,
                                                catalogo,
                                                cata_name,
                                                qnt_amostras, qnt_simpl,
                                                qnt_simpl_boots,
                                                qnt_maxima_permutaca,
                                                ls_path_eto,
                                                seed_bootstap);
    relatorio.do_proces();
    relatorio.generate_relatorio();

    QWidget *parent1 = nullptr;
    const QString &caption = QString("Save File");
    QString path = QFileDialog::getSaveFileName(
                parent1,
                caption,
                "C://Users//Bio//Desktop//videos//",
                "Report (*.xlsx)"
                );


//    QString filename = path + ".txt";
//    QFile file(filename);
//    if (file.open(QIODevice::ReadWrite)) {
//        QTextStream stream(&file);
//        stream << relatorio.txt_relatorio;
//    }




    gera_relatorio_python(path, relatorio.txt_relatorio);

    qDebug() << "vies";
}

void test_concordancia::test_carrega_etografia()
{
        qDebug() << "INICIO DO test_carrega_etografia";
        Etografia eto_lida2 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/7e5h4h6a.etoxml");
        Etografia eto_lida3 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/9e5h4h6b.etoxml");
        Etografia eto_lida4 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/6e5h4h6bis4.etoxml");
        Etografia eto_lida5 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/6e5h4h6.etoxml");



        Etografia eto_lida_v1_2 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/2e3hc5.etoxml");
        Etografia eto_lida_v1_3 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/2e3hc5bis4.etoxml");
        Etografia eto_lida_v1_4 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/22e31hc25b.etoxml");
        Etografia eto_lida_v1_5 = lerETOXML("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/52e03hc52a.etoxml");

        std::vector<QString> catalogo_categorias_nomes;
        catalogo_categorias_nomes = eto_lida2.catalogo->nome;
        catalogo_categorias_nomes.push_back("Undefined (frames that are not marked)");

        std::vector<int> catalogo  = [](std::vector<QString> catalogo_categorias_nomes){
            std::vector<int> saida;

            int i=0;
            for(auto cate: catalogo_categorias_nomes){
                saida.push_back(i);
                i++;
            }

            return saida;

        }(catalogo_categorias_nomes);

        QList<QString> cata_name = [](std::vector<QString> catalogo_categorias_nomes){
            QList<QString> saida ;

            for(auto cate: catalogo_categorias_nomes){
                saida.push_back(cate);
            }

            return saida;
        }(catalogo_categorias_nomes);


        auto arruma_lista = [](std::vector<int> ls_quadros, QList<QString> cata_nam){
            int cat_indef = cata_nam.count() -1 ;
            std::vector<int> saida;

            for(auto quadro: ls_quadros){
                bool r_quadro_indefinido = quadro == -1;
                if(r_quadro_indefinido){
                    saida.push_back(cat_indef);
                }else{
                    saida.push_back(quadro);
                }

            }

            return saida;

        };

        std::vector<int> ls_quadros_1 = arruma_lista(_constroi_lista_quadros(eto_lida2), cata_name);
        std::vector<int> ls_quadros_2 = arruma_lista(_constroi_lista_quadros(eto_lida3), cata_name);



        std::vector<std::vector<std::vector<int>>> ls_videos;


        std::vector<std::vector<int>> ls_etografias;
        ls_etografias.push_back(ls_quadros_1);
        ls_etografias.push_back(ls_quadros_2);
        ls_etografias.push_back(arruma_lista(_constroi_lista_quadros(eto_lida4), cata_name));
        ls_etografias.push_back(arruma_lista(_constroi_lista_quadros(eto_lida5), cata_name));



        std::vector<std::vector<int>> ls_etografias2;
        ls_etografias2.push_back(arruma_lista(_constroi_lista_quadros(eto_lida_v1_2), cata_name));
        ls_etografias2.push_back(arruma_lista(_constroi_lista_quadros(eto_lida_v1_3), cata_name));
        ls_etografias2.push_back(arruma_lista(_constroi_lista_quadros(eto_lida_v1_4), cata_name));
        ls_etografias2.push_back(arruma_lista(_constroi_lista_quadros(eto_lida_v1_5), cata_name));




        ls_videos.push_back(ls_etografias);
        ls_videos.push_back(ls_etografias2);
        int qnt_valores_por_etogrfia = int(ls_etografias[0].size());


        int qnt_amostras = 10;
        int qnt_simpl = 2;
        int qnt_simpl_boots = 2;
        int qnt_maxima_permutaca = 10000;
        int seed = 2;

        QList<QString> ls_path_eto;
        Relatorio_paper relatorio = Relatorio_paper(ls_videos,
                                                    qnt_valores_por_etogrfia,
                                                    catalogo,
                                                    cata_name,
                                                    qnt_amostras,
                                                    qnt_simpl, qnt_simpl_boots,
                                                    qnt_maxima_permutaca,ls_path_eto, seed);

        relatorio.do_proces();
        relatorio.generate_relatorio();

        QWidget *parent1 = nullptr;
        const QString &caption = QString("Save File");
        QString path = QFileDialog::getSaveFileName(
                    parent1,
                    caption,
                    "C://Users//Bio//Desktop//videos//",
                    "Report (*.xlsx)"
                    );



        gera_relatorio_python(path, relatorio.txt_relatorio);



        qDebug() << "tudo certo";

//        connect(&relatorio, SIGNAL(chan) )

}



QTEST_MAIN(test_concordancia)

#include "tst_test_concordancia.moc"
