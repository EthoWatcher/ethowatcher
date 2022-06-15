#ifndef AGREEMENT_H
#define AGREEMENT_H

#include "Agreement_global.h"
#include "./src/relatorio_paper.h"
#include "./src/ethowatcher.h"
#include <QtCore>
#include <QThread>
#include <QObject>

class AGREEMENT_EXPORT Agreement : public QThread
{
    Q_OBJECT
public:
//    explicit Agreement(QObject *parent =0);
    Agreement(QObject *parent = 0);




    Relatorio_paper *relatorio;
    QString path;
    QString path_executavel;

    QString generate_report(QString path,
                            std::vector<std::vector<std::vector<int>>> ls_videos,
                            int qnt_valores_por_etogrfia,
                            std::vector<int> catalogo,
                            QList<QString> cata_name,
                            int qnt_reamostras,
                            int qnt_simpl, int qnt_simpl_boots,
                            QList<QString> ls_path_eto,
                            int qnt_maxima_permutaca, int seed_bootstap, int qnt_threads);

    Etografia read_eto(QString path);
    std::vector<int> extrai_lista_quadros(Etografia eto);
    std::tuple<QList<QString> , std::vector<int> > get_catalogo(Etografia eto);
    std::vector< std::vector<int> > get_matrix_concordancia_cohen(std::vector<int> etografia_1, std::vector<int> etografia_2 , std::vector<int> catalogo );

    void processa();
public slots:
    void process();
    void chega_valor(int a);

signals:
    void qnt_bootstrap(int a);
    void finished();

private:
    void run() override {
            qDebug() << "THREAD DA INTERFACE " << QThread::currentThreadId();
            QString result;
            /* ... here is the expensive or blocking operation ... */
            relatorio = new Relatorio_paper(ls_videos,
                                            qnt_valores_por_etogrfia,
                                            catalogo,
                                            cata_name,
                                            qnt_reamostras,
                                            qnt_simpl,
                                            qnt_simpl_boots,

                                            qnt_maxima_permutaca,
                                            ls_path_eto,
                                            seed_bootstap,
                                            qnt_threads);


            connect(relatorio, SIGNAL(valueChanged(int)), this, SLOT(chega_valor(int)));
            relatorio->do_proces();
            relatorio->generate_relatorio();
            gera_relatorio_python(path, relatorio->txt_relatorio, this->path_executavel);
            emit finished();

//            emit resultReady(result);
        }


   std::vector<int> etrografia_1;
   std::vector<int> etrografia_2;
   std::vector<int> catalogo;
   QList<QString> cata_name;
   int qnt_reamostras;
   int qnt_simpl;
   int qnt_simpl_boots;
   int qnt_maxima_permutaca;
   int seed_bootstap;
   int qnt_threads;
   QList<QString> ls_path_eto;
   std::vector<std::vector<std::vector<int>>> ls_videos;
   int qnt_valores_por_etogrfia;

};



#endif // AGREEMENT_H
