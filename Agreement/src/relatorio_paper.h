#ifndef RELATORIO_PAPER_H
#define RELATORIO_PAPER_H

#include <vector>
#include "concordance.h"
#include "bootstrap.h"
#include <QtCore>
#include <QTemporaryFile>
#include <QProcess>
#include <QFileDialog>
#include <QFile>

#include <QObject>

#include <QThread>

class Relatorio_paper: public QObject
{
    Q_OBJECT

public:

    explicit Relatorio_paper(std::vector<std::vector<std::vector<int>>> ls_videos,
                                    int qnt_valores_por_etogrfia,
                                     std::vector<int> catalogo,
                                     QList<QString> cata_name,
                                     int qnt_amostras,
                                     int qnt_simpl, int qnt_simpl_boots,
                                     int qnt_maxima_permutaca,
                                     QList<QString> ls_path_eto,
                                     int seed_bootstap = 1,int qnt_threads =5, QObject *parent = nullptr);

    void do_proces();
    void generate_relatorio();
    std::vector< Calculo_paper *>  varios_kappa;
    Calculo_paper *medido;
    QString txt_relatorio;


private:
    QList<QString> cata_name;
    std::vector<int> etrografia_1;
     std::vector<int> etrografia_2;
     std::vector<int> catalogo;

     int qnt_amostras;
     int qnt_simpl;
     int qnt_simpl_boots;
     int qnt_maxima_permutaca;
     int seed_bootstap;
     int qnt_threads;
     QList<QString> ls_path_eto;

     std::vector<std::vector<std::vector<int>>> ls_videos;
     int qnt_valores_por_etogrfia;


signals:
    void valueChanged(int s);


};
void gera_relatorio_python(QString path, QString text, QString exe_path);





QString creat_var(QString name, QString saida_ls);
QString creat_list_string(QList<QString> saida_ls);
QString creat_list(QList<QString> saida_ls);
QString generate_list_number_json(std::vector<int> ls_int);
QString creat_object(QList<QString> saida_ls);


#endif // RELATORIO_PAPER_H
