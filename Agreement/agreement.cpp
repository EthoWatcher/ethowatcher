#include "agreement.h"

Agreement::Agreement(QObject *parent): QThread(parent)
{

}

QString Agreement::generate_report(QString path,
                                   std::vector<std::vector<std::vector<int> > > ls_videos,
                                   int qnt_valores_por_etogrfia,
                                   std::vector<int> catalogo,
                                   QList<QString> cata_name,
                                   int qnt_reamostras,
                                   int qnt_simpl, int qnt_simpl_boots,
                                   QList<QString> ls_path_eto,
                                   int qnt_maxima_permutaca,
                                   int seed_bootstap,
                                   int qnt_threads
                                   )
{
//    qDebug() << "report";

//    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
//    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
//    std::vector<int> catalogo  = {0, 1, 2};
//    QList<QString> cata_name = {"swimming",
//                                 "climbimg",
//                                 "Immobility"};
////    0 - swimming
////    1 - climbimg
////    2 - Immobility
///

    QWidget *parent1 = nullptr;
   const QString &caption = QString("Save File");
//   QFileDialog::getOpenFileName()
   QString path_22 = QFileDialog::getOpenFileName(
               parent1,
               caption,
               "C://Users//Bio//Desktop//videos//",
               "Report (*.exe)"
               );

    this->path_executavel = path_22;
    this->path = path;
    this->ls_videos = ls_videos;
    this->qnt_valores_por_etogrfia = qnt_valores_por_etogrfia;
    this->catalogo  = catalogo;
    this->cata_name = cata_name;
    this->qnt_reamostras = qnt_reamostras;
    this->qnt_simpl =  qnt_simpl;
    this->qnt_simpl_boots = qnt_simpl_boots;
    this->ls_path_eto = ls_path_eto;

    this->qnt_maxima_permutaca =  qnt_maxima_permutaca;
    this->seed_bootstap = seed_bootstap;
    this-> qnt_threads = qnt_threads;



//    connect(relatorio, SIGNAL(valueChanged(int)), this, SLOT(chega_valor(int)));

//            &Relatorio_paper::valueChanged, this, &Agreement::chega_valor);

//    relatorio.generate_relatorio();
//    gera_relatorio_python(path, relatorio.txt_relatorio);

    return "relatorio.txt_relatorio";

}

Etografia Agreement::read_eto(QString path)
{
    return lerETOXML(path);
}

std::vector<int> Agreement::extrai_lista_quadros(Etografia eto)
{
    std::tuple<QList<QString> , std::vector<int>> catalogo = this->get_catalogo(eto);


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


    return arruma_lista(_constroi_lista_quadros(eto), std::get<0>(catalogo));

}

std::tuple<QList<QString>, std::vector<int> > Agreement::get_catalogo(Etografia eto)
{
    std::vector<QString> catalogo_categorias_nomes;
    catalogo_categorias_nomes = eto.catalogo->nome;
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

    std::tuple<QList<QString> , std::vector<int>> saida =
            std::tuple< QList<QString> , std::vector<int> > (cata_name, catalogo);

    return saida;

}

std::vector<std::vector<int> > Agreement::get_matrix_concordancia_cohen(std::vector<int> etografia_1, std::vector<int> etografia_2, std::vector<int> catalogo)
{
    return constroi_matrix_concordancia_cohen(etografia_1, etografia_2 , catalogo );
}

void Agreement::processa()
{
    relatorio->generate_relatorio();
    gera_relatorio_python(path, relatorio->txt_relatorio, this->path_executavel);
    emit finished();
}

void Agreement::process()
{
    relatorio->generate_relatorio();
    gera_relatorio_python(path, relatorio->txt_relatorio, this->path_executavel);
    emit finished();
}




void Agreement::chega_valor(int a)
{
    qDebug() << a << "FROM CLASSE";
    emit qnt_bootstrap(a);

}
