#include "Reliability.h"
#include "ui_Reliability.h"



Reliability::Reliability(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Reliability)
{
    ui->setupUi(this);

    ls_categorias = new QVBoxLayout(ui->wd_catregorias);
    ui->widget_14->setVisible(false);
    ui->widget_13->setVisible(false);

}

Reliability::~Reliability()
{
    delete ui;
}


//void MainWindow::on_pushButton_clicked()
//{
//    QWidget *parent1 = nullptr;
//    const QString &caption = QString("Save File");
//    QString path = QFileDialog::getSaveFileName(
//                parent1,
//                caption,
//                "C://Users//Bio//Desktop//videos//",
//                "Report (*.xlsx)"
//                );

//    QString saida;

//    Agreement ma;

//    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
//    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
//    std::vector<int> catalogo  = {0, 1, 2};

//    QList<QString> cata_name = {"swimming",
//                                 "climbimg",
//                                 "Immobility"};



//    qDebug() << ma.generate_report(path, etrografia_1,
//                                   etrografia_2,
//                                   catalogo,
//                                   cata_name);


//}


void Reliability::on_pb_add_categorie_clicked()
{
//    QString text =
//    bool r_bol = ls_categorias->parent() == ui->wd_catregorias;

    ui->tabWidget->setTabEnabled(0, false);
    QString new_cate_name = ui->le_categorie_text->text();


    QLabel *label = new QLabel(new_cate_name);

    ls_categorias->addWidget(label);

    ui->le_categorie_text->setText("");

    ls_label.append(label);


    bool r_qnt_categorias = ls_label.count() >= 2;
    if(r_qnt_categorias){
        ui->pb_create_matriz->setEnabled(true);

    }


//    QLayout * layout = ui->wd_cate->layout();

//    QVBoxLayout *vLayout = new QVBoxLayout(ui->wd_cate);


//    label->setGeometry(120, 20, 150, 30);

//    a.setText(new_cate_name);



//    layout
}


void Reliability::on_pb_create_matriz_clicked()
{
    QList<QString> ls_categories;

    for(auto item:ls_label ){
        ls_categories.push_back(item->text());
    }

    int qn_pontos = ls_categorias->count();


    QGridLayout *matriz_conf = new QGridLayout(ui->wd_matriz);

    int i=0;
    for(auto item: ls_categories)
    {
        matriz_conf->addWidget(new QLabel(item),0,i+1, Qt::AlignCenter);
        matriz_conf->addWidget(new QLabel(item),i+1,0, Qt::AlignCenter);

        i++;
    }


    for(int j=1; j<= ls_categorias->count(); j++){
        QList<QLineEdit*> coluna;
        for(int k=1; k<= ls_categorias->count(); k++){
            QLineEdit *li = new QLineEdit(QString::number(j));

            matriz_conf->addWidget(li,k,j,  Qt::AlignCenter);

            coluna.push_back(li);

        }
        ls_edi.push_back(coluna);

    }

    ui->pb_create_matriz->setEnabled(false);
    ui->groupBox_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pb_finish_editing->setEnabled(true);


}


void Reliability::on_pushButton_2_clicked()
{
//    std::vector<std::vector<int>> matriz_confusao;
//    for(auto linha: ls_edi){
//        std::vector<int> col_int;
//        for(auto col: linha){
//            col_int.push_back(col->text().toInt());
//        }
//        matriz_confusao.push_back(col_int);
//    }
    std::vector<int> etrografia_1  = {};
    std::vector<int> etrografia_2  = {};

    for(int i=0; i< matriz_confusao.size(); i++){
        for(int j=0; j< matriz_confusao.size(); j++){
            for(int k=0; k< matriz_confusao[j][i]; k++){
               etrografia_2.push_back(j);
               etrografia_1.push_back(i);
               qDebug() << i << j;
            }

        }
    }


    std::vector<int> catalogo;
    for(int i=0; i< matriz_confusao.size(); i++){
        catalogo.push_back(i);
    }
    QList<QString> cata_name;

    for(auto labl: ls_label){
        cata_name.append(labl->text());
    }

    QWidget *parent1 = nullptr;
    const QString &caption = QString("Save File");
    QString path = QFileDialog::getSaveFileName(
                parent1,
                caption,
                "C://Users//Bio//Desktop//videos//",
                "Report (*.xlsx)"
                );



//    Agreement ma;
//    qDebug() << ma.generate_report(path, etrografia_1,
//                                   etrografia_2,
//                                   catalogo,
//                                   cata_name,
//                                   100,
//                                   1,1);


    int qnt_reamostras = ui->sb_reamostra_2->value();
    int qnt_simpl = ui->sb_qnt_simp_medida->value();
    int qnt_simpl_boots = ui->sb_sim_boots_2->value();

    int qnt_maxima_permutaca= ui->sb_numero_maximo_3->value();
    int seed_bootstap = ui->sb_seed_2->value();
    int qnt_threads = ui->sb_paralel_2->value();


    ui->progress_editados->setMaximum(qnt_reamostras);
    Agreement* workerThread = new Agreement();




    std::vector<std::vector<std::vector<int>>> ls_videos;
    std::vector<std::vector<int>> ls_etografias;
    ls_etografias.push_back(etrografia_1);
    ls_etografias.push_back(etrografia_2);
    ls_videos.push_back(ls_etografias);
    int qnt_valores_por_etogrfia = int(ls_etografias[0].size());






    qDebug() << "THREAD DA INTERFACE " << QThread::currentThreadId();
    qDebug() << workerThread->generate_report(path, ls_videos,
                                   qnt_valores_por_etogrfia,
                                   catalogo,
                                   cata_name,
                                   qnt_reamostras,
                                   qnt_simpl,
                                   qnt_simpl_boots,
                                  ls_path_lidos,
                                  qnt_maxima_permutaca,
                                  seed_bootstap,
                                  qnt_threads);

    connect(workerThread, &Agreement::finished, workerThread, &QObject::deleteLater);
    connect(workerThread, &Agreement::qnt_bootstrap, this, &Reliability::chega_valor_boots_editados);
    workerThread->start(QThread::HighestPriority);


    ui->pushButton_2->setEnabled(false);

    qDebug() <<"tese";
}


void Reliability::on_pb_load_eto_clicked()
{
    ui->tabWidget->setTabEnabled(1, false);
    Agreement ma;
    QWidget *parent1 = nullptr;
    const QString &caption = QString("Save File");

    QString path = QFileDialog::getOpenFileName(
                parent1,
                caption,
                "C://Users//Bio//Desktop//videos//",
                "Report (*.etoxml)"
                );

    int i = path.lastIndexOf("/");
    QString y = path.mid(i+1, path.size());

    this->ls_path_lidos.append(path);
    ls_etografias.append(ma.read_eto(path));

    bool r_colocou_todas_eto = ls_etografias.count() ==2;
    if(r_colocou_todas_eto){

        this->print_categories();


        ui->pb_load_eto->setEnabled(false);
        ui->lb_eto_2->setText(y);
    }else{
        ui->lb_eto_1->setText(y);
    }

}

void Reliability::print_categories()
{
    Agreement ma;
    catalogo = ma.get_catalogo(ls_etografias[0]);

    //adicionar para checar as etografias

    ls_categorias = new QVBoxLayout(ui->wd_set_categories);


    for(auto cate: std::get<0>(catalogo)){
        QLabel *label = new QLabel(cate);

        ls_categorias->addWidget(label);

    }

    this->ls_edi = create_matriz_confusao(std::get<0>(catalogo), ui->wd_matriz_2);

    matriz_confusao = ma.get_matrix_concordancia_cohen(
                                    ma.extrai_lista_quadros(ls_etografias[0]),
                                    ma.extrai_lista_quadros(ls_etografias[1]), std::get<1>(catalogo));
    prenche_valores_matriz(matriz_confusao, this->ls_edi);

    // seria legal checar se é o meso catalogo usado.

}


std::tuple<std::vector<int> , std::vector<int> > gera_etografias_pela_matriz(std::vector<std::vector<int> > matriz_confusao)
{
    std::vector<int> etrografia_1  = {};
    std::vector<int> etrografia_2  = {};

    for(int i=0; i< matriz_confusao.size(); i++){
        for(int j=0; j< matriz_confusao.size(); j++){
            for(int k=0; k< matriz_confusao[j][i]; k++){
               etrografia_2.push_back(j);
               etrografia_1.push_back(i);
//               qDebug() << i << j;
            }

        }
    }
    std::tuple<std::vector<int> , std::vector<int> > etografias = std::tuple<std::vector<int> , std::vector<int> >(etrografia_1, etrografia_2);
    return etografias;
}

QList<QList<QLineEdit*>> create_matriz_confusao(QList<QString> ls_categories, QWidget *tela)
{

    int qn_pontos = ls_categories.count();

    QGridLayout *matriz_conf = new QGridLayout(tela);

    int i=0;
    for(auto item: ls_categories)
    {
        matriz_conf->addWidget(new QLabel(item),0,i+1, Qt::AlignCenter);
        matriz_conf->addWidget(new QLabel(item),i+1,0, Qt::AlignCenter);

        i++;
    }

    QList<QList<QLineEdit*>> ls_edi;
    for(int j=1; j<= ls_categories.count(); j++){
        QList<QLineEdit*> coluna;
        for(int k=1; k<= ls_categories.count(); k++){
            QLineEdit *li = new QLineEdit(QString::number(j));
            li->setEnabled(false);
            matriz_conf->addWidget(li,k,j,  Qt::AlignCenter);

            coluna.push_back(li);

        }
        ls_edi.push_back(coluna);
    }

    return ls_edi;
}

void prenche_valores_matriz(std::vector<std::vector<int> > matriz_confusao, QList<QList<QLineEdit*>> local)
{
    for(int i=0; i< matriz_confusao.size(); i++){
        for(int j=0; j< matriz_confusao.size(); j++){
            local[i][j]->setText(QString::number(matriz_confusao[i][j]));
        }
    }

}

void Reliability::on_sb_qnt_simp_2_valueChanged(int arg1)
{
    auto grid = this->matriz_confusao;
    auto arruma_grid = [&grid] (int dive_por){
        std::vector<std::vector<int>> saida;

        for(auto linha: grid){
            std::vector<int> linha_add;
            for(auto celula: linha){
                linha_add.push_back( int(ceil( celula/dive_por)));
            }
            saida.push_back(linha_add);
        }

        return saida;

    }(arg1);



     prenche_valores_matriz(arruma_grid, this->ls_edi);
}

//funcao que roda a análise
void Reliability::on_pb_creat_analisis_clicked()
{
    QWidget *parent1 = nullptr;
    const QString &caption = QString("Save File");
    QString path = QFileDialog::getSaveFileName(
                parent1,
                caption,
                "C://Users//Bio//Desktop//videos//",
                "Report (*.xlsx)"
                );



    ui->pb_creat_analisis->setEnabled(false);
    ui->gb_controlers->setEnabled(false);
    Agreement func;

    Etografia eto_lida2 = func.read_eto(ls_path_lidos[0]);
    Etografia eto_lida3 = func.read_eto(ls_path_lidos[1]);
//    Etografia eto_lida4 = func.read_eto("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/6e5h4h6bis4.etoxml");
//    Etografia eto_lida5 = func.read_eto("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/1/6e5h4h6.etoxml");

//    Etografia eto_lida_v1_2 = func.read_eto("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/2e3hc5.etoxml");
//    Etografia eto_lida_v1_3 = func.read_eto("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/2e3hc5bis4.etoxml");
//    Etografia eto_lida_v1_4 = func.read_eto("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/22e31hc25b.etoxml");
//    Etografia eto_lida_v1_5 = func.read_eto("C:/Users/User/Desktop/artigo_cbeb/dados/Coleta de dados/2/52e03hc52a.etoxml");


//    catalogo = func.get_catalogo(ls_etografias[0]);
//    catalogo = func.get_catalogo(func.read_eto());

//    func.extrai_lista_quadros(func.read_eto());

//    auto etrografia_1 = func.extrai_lista_quadros(ls_etografias[0]);
//    auto etrografia_2 = func.extrai_lista_quadros(ls_etografias[1]);

    catalogo = func.get_catalogo(eto_lida2);

    auto catalogo_int = std::get<1>(this->catalogo);
    auto cata_name = std::get<0>(this->catalogo);

    int qnt_reamostras = ui->sb_reamostra->value();
    int qnt_simpl = ui->sb_qnt_simp_2->value();
    int qnt_simpl_boots = ui->sb_sim_boots->value();

    int qnt_maxima_permutaca= ui->sb_numero_maximo->value();
    int seed_bootstap = ui->sb_seed->value();
    int qnt_threads = ui->sb_paralel->value();

    ui->progress_load_eto->setMaximum(qnt_reamostras);

//    QList<QString> ls_path_eto;
//    for(auto eto: ls_etografias){
//        ls_path_eto.append(eto.video->nome);
//    }

    std::vector<std::vector<std::vector<int>>> ls_videos;


    std::vector<std::vector<int>> ls_etografias;
    ls_etografias.push_back(func.extrai_lista_quadros(eto_lida2));
    ls_etografias.push_back(func.extrai_lista_quadros(eto_lida3));
//    ls_etografias.push_back(func.extrai_lista_quadros(eto_lida4));
//    ls_etografias.push_back(func.extrai_lista_quadros(eto_lida5));



//    std::vector<std::vector<int>> ls_etografias2;
//    ls_etografias2.push_back(func.extrai_lista_quadros(eto_lida_v1_2));
//    ls_etografias2.push_back(func.extrai_lista_quadros(eto_lida_v1_3));
//    ls_etografias2.push_back(func.extrai_lista_quadros(eto_lida_v1_4));
//    ls_etografias2.push_back(func.extrai_lista_quadros(eto_lida_v1_5));




    ls_videos.push_back(ls_etografias);
//    ls_videos.push_back(ls_etografias2);
    int qnt_valores_por_etogrfia = int(ls_etografias[0].size());


    Agreement* workerThread = new Agreement();

    qDebug() << path;
    qDebug() << "THREAD DA INTERFACE " << QThread::currentThreadId();
    qDebug() << workerThread->generate_report(path, ls_videos,
                                   qnt_valores_por_etogrfia,
                                   catalogo_int,
                                   cata_name,
                                   qnt_reamostras,
                                   qnt_simpl,
                                   qnt_simpl_boots,
                                  ls_path_lidos,
                                  qnt_maxima_permutaca,
                                  seed_bootstap,
                                  qnt_threads);

    connect(workerThread, &Agreement::finished, workerThread, &QObject::deleteLater);
    connect(workerThread, &Agreement::qnt_bootstrap, this, &Reliability::chega_valor_boots);
    workerThread->start(QThread::HighestPriority);


    qDebug() << path;

    //    QThread cThread;


    //    QThread* thread = new QThread;
    //    https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
    //    ma.moveToThread(&cThread);
    //    worker->moveToThread(thread);

    //    auto a = QThread::create(workerThread->processa);

    //    connect(workerThread, &Agreement::resultReady, this, &MyObject::handleResults);
    //    connect(thread, SIGNAL(started()), worker,  SLOT(DoWork()));
    //    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    //    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    //    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    //    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

}

void Reliability::chega_valor_boots(int valr)
{
    qDebug() << "Esta chendo os dados na interface" << valr;
    ui->progress_load_eto->setValue(valr);

    int qnt_reamostras = ui->sb_reamostra->value();
    bool r_bool_fim = qnt_reamostras <= valr;

    if(r_bool_fim){
        ui->pb_creat_analisis->setEnabled(false);
    }

}

void Reliability::chega_valor_boots_editados(int valr)
{
    qDebug() << "Esta chendo os dados na interface" << valr;
    ui->progress_editados->setValue(valr);

}


void Reliability::on_pb_finish_editing_clicked()
{
//    this->ls_edi = create_matriz_confusao(std::get<0>(catalogo), ui->wd_matriz_2);

    auto creat_matriz_confusa =  [](QList<QList<QLineEdit*>> ls_edi){
//        ls_edi
        std::vector<std::vector<int>> matriz_confusao;
        for(auto linha: ls_edi){
            std::vector<int> linha_conf;
            for(auto cel: linha){
                linha_conf.push_back(cel->text().toInt());
            }
            matriz_confusao.push_back(linha_conf);
        }
        return matriz_confusao;

    };


    this->matriz_confusao = creat_matriz_confusa(this->ls_edi);

//    matriz_confusao = ma.get_matrix_concordancia_cohen(
//                                    ma.extrai_lista_quadros(ls_etografias[0]),
//                                    ma.extrai_lista_quadros(ls_etografias[1]), std::get<1>(catalogo));
//    prenche_valores_matriz(matriz_confusao, this->ls_edi);
     prenche_valores_matriz(matriz_confusao, this->ls_edi);
     ui->gb_boots_controle_1->setEnabled(true);
     ui->wd_matriz->setEnabled(false);
     ui->gb_boots_controle_1->setEnabled(true);
     ui->pb_finish_editing->setEnabled(false);

}


void Reliability::on_sb_qnt_simp_medida_valueChanged(int arg1)
{
    auto grid = this->matriz_confusao;
    auto arruma_grid = [&grid] (int dive_por){
        std::vector<std::vector<int>> saida;

        for(auto linha: grid){
            std::vector<int> linha_add;
            for(auto celula: linha){
                linha_add.push_back( int(ceil( celula/dive_por)));
            }
            saida.push_back(linha_add);
        }

        return saida;

    }(arg1);



     prenche_valores_matriz(arruma_grid, this->ls_edi);
}

