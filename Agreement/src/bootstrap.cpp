#include "bootstrap.h"
//#include <random>
#include <time.h>

Bootstrap::Bootstrap(std::vector<int> etrografia_1, std::vector<int> etrografia_2, int s_rand)
{
    this->original_1 = etrografia_1;
    this->original_2 = etrografia_2;

    for(int i=0; i< etrografia_1.size(); i++){
        this->list_concordance.push_back( std::tuple<int, int>(etrografia_1[i], etrografia_2[i]) );
    }

    gen1 =  new RandCustom(s_rand);


    //tem que ver qual é a melhor solução, uma o srand
//    std::srand(s_rand);
//    srand (time(NULL));


}


std::tuple< std::vector<int>, std::vector<int> > Bootstrap::generate_new_etografia(){
//     std::simple_rand.seed(42);
     int r_list[original_1.size()];
     std::vector<int>  nova_eto_1; //[original_1.size()];
     std::vector<int>  nova_eto_2;


     for (int i=0; i< int(original_1.size()) ; i++){
         int x =  gen1->generate(); //std::rand()
         r_list[i]= 0 + (x % this->original_1.size() );
     }

     for(int i=0; i< int(original_1.size()); i++){
        int x_rand = r_list[i];
        nova_eto_1.push_back( std::get<0>(this->list_concordance[x_rand]));
        nova_eto_2.push_back( std::get<1>(this->list_concordance[x_rand]));
     }

     std::tuple< std::vector<int>, std::vector<int> >  novas_etografias = std::tuple< std::vector<int>, std::vector<int> > (nova_eto_1, nova_eto_2);
     return  novas_etografias;




}

Bootstrap_2::Bootstrap_2(std::vector<std::vector<int> > ls_etografias, int qnt_valores_por_etogrfia, int s_rand)
{

    gen1 = new RandCustom(s_rand);
    this->qnt_valores_por_etogrfia = qnt_valores_por_etogrfia;

    std::vector<int> l_centr = [](std::vector<std::vector<int> > ls_etografias){
        std::vector<int> saida;
        for(int i=0; i< int(ls_etografias.size()); i++){
            saida.push_back(i);
        }

        return  saida;
    }(ls_etografias); //mesmo tamanho que a entrada.


    this->ls_combinacoes_etografia_2 = this->gera_list_combi(l_centr);


    auto add_new_eto = [this](std::vector<int> etrografia_1, std::vector<int> etrografia_2){
        for(int i=0; i< etrografia_1.size(); i++){
            this->list_concordance.push_back( std::tuple<int, int>(etrografia_1[i], etrografia_2[i]) );
        }

    };


    for(auto prox_eto_com : ls_combinacoes_etografia_2){
        add_new_eto(ls_etografias[prox_eto_com[0]], ls_etografias[prox_eto_com[1]]);
    }


//    qDebug() <<ls_combinacoes_etografia_2;

}

std::tuple<std::vector<int>, std::vector<int> > Bootstrap_2::generate_new_etografia()
{
    int r_list[qnt_valores_por_etogrfia];
    std::vector<int>  nova_eto_1; //[original_1.size()];
    std::vector<int>  nova_eto_2;


//    int qnt_quadros_amostra =this->list_concordance.size() -1;
    for (int i=0; i< int(qnt_valores_por_etogrfia) ; i++){
        int x =  gen1->generate(); //std::rand()
        r_list[i]= 0 + (x % this->list_concordance.size() );
    }

    for(int i=0; i< int(qnt_valores_por_etogrfia); i++){
       int x_rand = r_list[i];
       nova_eto_1.push_back( std::get<0>(this->list_concordance[x_rand]));
       nova_eto_2.push_back( std::get<1>(this->list_concordance[x_rand]));
    }

    std::tuple< std::vector<int>, std::vector<int> >  novas_etografias = std::tuple< std::vector<int>, std::vector<int> > (nova_eto_1, nova_eto_2);
    return  novas_etografias;


}

std::vector<std::vector<int> > Bootstrap_2::gera_list_combi(std::vector<int> l_centr)
{
    std::vector<std::vector<int>> ls_comb_2;

    auto add_new_valor = [&ls_comb_2]( std::vector<int> l_cent){
        auto r_checa_nova = [&ls_comb_2](int ini, int prox){

            for(auto linha: ls_comb_2){
                 bool r_li_0 = linha[0] == ini;
                 bool r_li_1 = linha[1] == prox;
                 if (r_li_0 && r_li_1){
                     return  false;
                 }
            }


            return  true;
        };


        for(int i=0; i< int(l_cent.size()-1); i++){
            int ini= l_cent[i];
            int prox = l_cent[i+1];
            bool r_tem_nova = r_checa_nova(ini, prox);
            if(r_tem_nova){
                ls_comb_2.push_back({ini, prox});
            }

        }


    };

    do {

//        qDebug() << l_centr;

        add_new_valor(l_centr);


    } while (std::next_permutation(l_centr.begin(), l_centr.end()));


    return ls_comb_2;
}

Bootstrap_mult_videos::Bootstrap_mult_videos(QList<Bootstrap_2> ls_ml_videos, int qnt_valores_por_etogrfia, int s_rand)
{
    this->gen1 =  new RandCustom(s_rand);
    this->qnt_valores_por_etogrfia = qnt_valores_por_etogrfia;
    auto add_new_eto = [this](std::vector<int> etrografia_1, std::vector<int> etrografia_2){
        for(int i=0; i< etrografia_1.size(); i++){
            this->list_concordance.push_back( std::tuple<int, int>(etrografia_1[i], etrografia_2[i]) );
        }

    };


    this->ls_ml_videos = ls_ml_videos;

    for(auto boo: this->ls_ml_videos){
//        auto ls_c_vi = boo.list_concordance;
        std::vector<int> etografia_1;
        std::vector<int> etografia_2;
        for(int i=0; i< boo.list_concordance.size(); i++){

            int eto_quadro_1 = std::get<0>(boo.list_concordance[i]);
            int eto_quadro_2 = std::get<1>(boo.list_concordance[i]);

            etografia_1.push_back(eto_quadro_1);
            etografia_2.push_back(eto_quadro_2);
        }


         add_new_eto(etografia_1, etografia_2);

    }

}

std::tuple<std::vector<int>, std::vector<int> > Bootstrap_mult_videos::generate_new_etografia()
{
    int r_list[qnt_valores_por_etogrfia];
    std::vector<int>  nova_eto_1; //[original_1.size()];
    std::vector<int>  nova_eto_2;


//    int qnt_quadros_amostra =this->list_concordance.size() -1;
    for (int i=0; i< int(qnt_valores_por_etogrfia) ; i++){
        int x =  gen1->generate(); //std::rand()
        r_list[i]= 0 + (x % this->list_concordance.size() );
    }

    for(int i=0; i< int(qnt_valores_por_etogrfia); i++){
       int x_rand = r_list[i];
       nova_eto_1.push_back( std::get<0>(this->list_concordance[x_rand]));
       nova_eto_2.push_back( std::get<1>(this->list_concordance[x_rand]));
    }

    std::tuple< std::vector<int>, std::vector<int> >  novas_etografias = std::tuple< std::vector<int>, std::vector<int> > (nova_eto_1, nova_eto_2);
    return  novas_etografias;

}
