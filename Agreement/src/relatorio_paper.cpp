#include "relatorio_paper.h"

#include <memory>

Relatorio_paper::Relatorio_paper(std::vector<std::vector<std::vector<int> > > ls_videos, int qnt_valores_por_etogrfia,
                                 std::vector<int> catalogo,
                                 QList<QString> cata_name,
                                 int qnt_amostras,
                                 int qnt_simpl,
                                 int qnt_simpl_boots, int qnt_maxima_permutaca,
                                 QList<QString> ls_path_eto,
                                 int seed_bootstap, int qnt_threads, QObject *parent): QObject(parent)
{


    this->ls_videos = ls_videos;
    this->qnt_valores_por_etogrfia = qnt_valores_por_etogrfia;

//     this->etrografia_1 =  ls_videos;
//     this->etrografia_2 = etrografia_2;
     this->catalogo = catalogo;
     this->cata_name = cata_name;
     this->qnt_amostras = qnt_amostras;
     this->qnt_simpl = qnt_simpl;
     this->qnt_simpl_boots = qnt_simpl_boots;
     this->ls_path_eto = ls_path_eto;
     this->seed_bootstap = seed_bootstap;
     this->qnt_maxima_permutaca = qnt_maxima_permutaca;

    this->qnt_threads = qnt_threads;
}

void Relatorio_paper::do_proces()
{
    auto transfor_to_saida  = [](Calculo_paper c){

    };

    this->cata_name = cata_name;

//    std::vector<int> etrografia_1  = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2};
//    std::vector<int> etrografia_2  = {1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2};
//    std::vector<int> catalogo  = {0, 1, 2};

    qDebug() << "THREAD DA relatorio " << QThread::currentThreadId();

    //remendo todo TEM Q ARRUMAR
     this->etrografia_1 = this->ls_videos[0][0];
    this->etrografia_2 = this->ls_videos[0][1];
     this->medido = new Calculo_paper(etrografia_1, etrografia_2, catalogo, qnt_simpl, qnt_maxima_permutaca);


     this->medido->start(QThread::HighestPriority);
     connect(medido, &Calculo_paper::finished, medido, &QObject::deleteLater);

//     int qnt_valores_por_etogrfia = int(ls_etografias[0].size());

     QList<Bootstrap_2> ls_boot;
     for(auto ls_etografias : ls_videos){
         Bootstrap_2 boo = Bootstrap_2(ls_etografias, qnt_valores_por_etogrfia, seed_bootstap);
         ls_boot.append(boo);
     }
//     std::vector<std::vector<int>> ls_etografias;
//     ls_etografias.push_back(etrografia_1);
//     ls_etografias.push_back(etrografia_2);

//     Bootstrap_2 boo = Bootstrap_2(ls_etografias, qnt_valores_por_etogrfia, seed_bootstap);

//     QList<Bootstrap_2> ls_boot;
//     ls_boot.append(boo);
//     ls_boot.append(boo1);
     Bootstrap_mult_videos mult_bol = Bootstrap_mult_videos(ls_boot, qnt_valores_por_etogrfia, 10);


//    varios_kappa.push_back(c_1);
//    Bootstrap a = Bootstrap(etrografia_1,etrografia_2, seed_bootstap );

    for(int i=0; i<qnt_amostras; i++){

        std::tuple< std::vector<int>, std::vector<int> >  novas_etografias  = mult_bol.generate_new_etografia();
        std::vector<int> e1 = std::get<0>(novas_etografias);
        std::vector<int> e2 = std::get<1>(novas_etografias);


        std::vector<Calculo_paper*> ls_parelo;
//        int qnt_threads =5;
//        int j=0;
//        bool r_regra_parale = i < qnt_amostras && (j < qnt_threads);
        for(int j=0; j< qnt_threads; j++){
            Calculo_paper *c = new Calculo_paper(e1, e2, catalogo, qnt_simpl_boots, qnt_maxima_permutaca);
            connect(c, &Calculo_paper::finished, c, &QObject::deleteLater);

            ls_parelo.push_back(c);
            i++;
            bool r_regra_parale = !(i < qnt_amostras);
            if(r_regra_parale){
                break;
            }
        }

        for(auto thread: ls_parelo){
            thread->start(QThread::HighestPriority);
        }

        for(auto thread: ls_parelo){
            thread->wait();
        }

        for(auto thread: ls_parelo){
            this->varios_kappa.push_back(thread);
//            thread->wait();
        }



        emit valueChanged(i);
        qDebug() << i;

    }



    this->medido->wait();
    emit valueChanged(qnt_amostras);



}

void Relatorio_paper::generate_relatorio()
{

    auto ge_conc = [](Calculo_paper::Concordancia con, QList<QString> texto ){
        auto gene_matriz_conco = [](std::vector< std::vector<int> > matriz_concordancia){
            QList<QString> ls_matriz;
            for(auto linha: matriz_concordancia){
                ls_matriz.push_back(generate_list_number_json(linha));
            }

            return creat_list(ls_matriz);
        };

        QList<QString> ls_kappa;
        ls_kappa.push_back(creat_var("categoria", "'" + texto[con.categoria]+ "'"));
        ls_kappa.push_back(creat_var("observada",  QString::number(con.observada)));
        ls_kappa.push_back(creat_var("acaso",  QString::number(con.acaso)));
        ls_kappa.push_back(creat_var("vies",  QString::number(con.vies)));
        ls_kappa.push_back(creat_var("kappa",  QString::number(con.kappa)));
        ls_kappa.push_back(creat_var("prevalencia",  QString::number(con.prevalencia)));
        ls_kappa.push_back(creat_var("matriz_concordancia", gene_matriz_conco(con.matriz_concordancia)));

        return creat_object(ls_kappa);
    };

    auto ge_ls_categoria = [&ge_conc](std::vector<Calculo_paper::Concordancia> list_concordancia,
                                      QList<QString> texto){
        QList<QString> saida_ls;

        for(auto linha: list_concordancia){
            saida_ls.push_back(ge_conc(linha, texto));
        }
        return creat_list(saida_ls);

    };

    auto generating_calculo_paper_json = [&ge_conc, &ge_ls_categoria ](Calculo_paper *c ,
                                             QList<QString> texto_ls_cat, bool imprime_lista_etografia   ){
        QList<QString> saida_ls;
        QList<QString> texto = {"Catalog"};
        //removendo a escrita da etografia produzida.
        if(imprime_lista_etografia){
            saida_ls.push_back(creat_var("et1",generate_list_number_json(c->et1)));
            saida_ls.push_back(creat_var("et2",generate_list_number_json(c->et2)));
        }

        saida_ls.push_back(creat_var("catalogo_var",ge_conc(c->catalogo_var, texto)));
        saida_ls.push_back(creat_var("catalogo_var_max",ge_conc(c->catalogo_var_max, texto)));
        saida_ls.push_back(creat_var("list_kappa_cat",ge_ls_categoria(c->list_kappa_cat, texto_ls_cat)));
        saida_ls.push_back(creat_var("list_kappa_cat_max",ge_ls_categoria(c->list_kappa_cat_max, texto_ls_cat)));

        return creat_object(saida_ls);
    };




    QList<QString> relatorio;
    relatorio.push_back(creat_var("medido",
                                  generating_calculo_paper_json(this->medido, this->cata_name, true)));

    relatorio.push_back(creat_var("ls_cat_txt",creat_list_string(this->cata_name)));



    QList<QString> varios_kapp;
    for(auto bootstraped: this->varios_kappa){
        varios_kapp.push_back(generating_calculo_paper_json(bootstraped, this->cata_name, false));
    }

    relatorio.push_back(creat_var("varios_kappa",creat_list(varios_kapp)));

    relatorio.push_back(creat_var("qnt_amostras", QString::number(qnt_amostras)));
    relatorio.push_back(creat_var("qnt_simpl", QString::number(qnt_simpl)));
    relatorio.push_back(creat_var("qnt_simpl_boots", QString::number(qnt_simpl_boots)));
    relatorio.push_back(creat_var("qnt_maxima_permutaca", QString::number(qnt_maxima_permutaca)));
    relatorio.push_back(creat_var("seed_bootstap", QString::number(seed_bootstap)));
    relatorio.push_back(creat_var("qnt_threads", QString::number(qnt_threads)));
    relatorio.push_back(creat_var("ls_eto",creat_list_string(ls_path_eto)));



//    relatorio.push_back(creat_var("medido",
//                                  generating_calculo_paper_json(this->medido)));


    txt_relatorio = creat_object(relatorio);

//    qDebug() << txt_relatorio;


}


QString creat_var(QString name, QString saida_ls){
    QString saida;

    saida = "'" + name + "'"+ ":" + saida_ls;
    return saida;

};

QString creat_list_string(QList<QString> saida_ls){
    QString saida;

    saida = saida + "[";
    bool r_nao_tem = saida_ls.size() == 0;
    if(r_nao_tem){
        saida = saida + "]";
    }else{
        for(int i=0 ; i< saida_ls.size(); i++){
            bool r_ultimo = i == saida_ls.size() - 1;
            if(r_ultimo){
                saida = saida + "'"+ saida_ls[i] +"'" + "]";
            }else{
                saida = saida + "'"+ saida_ls[i] +"'" + " , " ;
            }
        }

    }


    return saida;

};

QString creat_list(QList<QString> saida_ls){
    QString saida;

    saida = saida + "[";
    for(int i=0 ; i< saida_ls.size(); i++){
        bool r_ultimo = i == saida_ls.size() - 1;
        if(r_ultimo){
            saida = saida + saida_ls[i] + "]";
        }else{
            saida = saida + saida_ls[i] + " , " ;
        }
    }
    return saida;

};

QString creat_object(QList<QString> saida_ls){
    QString saida;

    saida = saida + "{";
    for(int i=0 ; i< saida_ls.size(); i++){
        bool r_ultimo = i == saida_ls.size() - 1;
        if(r_ultimo){
            saida = saida + saida_ls[i] + "}";
        }else{
            saida = saida + saida_ls[i] + " , " ;
        }
    }
    return saida;

};

QString generate_list_number_json(std::vector<int> ls_int)
{
    QString saida;

//    saida =  creat_var "'" + name + "'"+ ":[";

    saida = "[";

    for(int i=0 ; i< ls_int.size(); i++){
        bool r_ultimo = i == ls_int.size() - 1;
        if(r_ultimo){
            saida = saida + QString::number(ls_int[i]) + "]";
        }else{
            saida = saida + QString::number(ls_int[i]) + " , " ;
        }

    }

    return saida;

}


void gera_relatorio_python(QString path, QString text, QString exe_path)
{
    //    https://forum.qt.io/topic/115682/how-to-get-the-path-of-a-c-file-which-is-added-as-the-resource-file/12

    //C:\Users\User\AppData\Local\Temp o arquivo temporario fica aqui
    //gerando relatorio
    QString filename = path + ".txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
//        QTextStream stream(&file);
//        stream << text;
        file.write(text.toUtf8());
    }

    //fazendo outras coisas

//    QWidget *parent1 = nullptr;
//    const QString &caption = QString("Save File");
//    QString path_22 = QFileDialog::getSaveFileName(
//                parent1,
//                caption,
//                "C://Users//Bio//Desktop//videos//",
//                "Report (*.exe)"
//                );

//    std::string path_inside_qrc =  "C:/gera_relatorio/gera_relatorio.exe";

////    std::string path_inside_qrc =  path_22.toStdString();
////    std::string path_inside_qrc = ":/script/relatorio/dist/gera_relatorio.exe";
//    std::unique_ptr<QTemporaryFile> temporary_file;

//    temporary_file.reset(
//        QTemporaryFile::createNativeFile(QString::fromStdString(path_inside_qrc))
//     );
//    std::string file_name = temporary_file->fileName().toUtf8().constData();

////    QObject *parent;
//    QString program = temporary_file->fileName();

//    QString newname = program + ".exe";


//    QFile::copy(program, newname);

    QStringList arguments;
    arguments << path; //<< text;




//     QString Cmd = "cmd";
//    QProcess::startDetached(program, arguments );
    QObject *parent = nullptr;
    QString newname = exe_path; //"C:/gera_relatorio/gera_relatorio.exe";
    QProcess *myProcess = new QProcess(parent);
    myProcess->start( newname, arguments);
//    myProcess->waitForFinished(-1);


    if(myProcess->waitForStarted(5000))
    {
        QByteArray out_data = myProcess->readAllStandardOutput();
        QString out_string(out_data);
        qDebug() << out_string.toStdString().c_str();
    }
    else
    {
        qDebug() << "myProcess did not start in time";
    }
     myProcess->waitForFinished();


//    temporary_file.reset();


    if (QFile::exists(newname))
    {
        QFile::remove(newname);

    }

}
