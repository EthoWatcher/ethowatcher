#ifndef TELACADASTROLISTAFILME_H
#define TELACADASTROLISTAFILME_H

#include <QWidget>

//funcionamento da saida em xml
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QListWidget>


#include <QString>
#include <vector>

namespace Ui {
class telaCadastroListaFilme;
}

class telaCadastroListaFilme : public QWidget
{
    Q_OBJECT

public:
    explicit telaCadastroListaFilme(QWidget *parent = 0);
    ~telaCadastroListaFilme();


    struct videoLocal{
        QString caminho;
        QString nome;
        QString extensao;
    };

    videoLocal *video;



private slots:
    void on_pbOpenXml_clicked();

    void on_pbAddVideo_clicked();

    void on_pbDeletar_clicked();

    void on_pbGravarXML_clicked();

private:
    Ui::telaCadastroListaFilme *ui;
    QString nomeArquivo;
    QFile output;

    QString separandoCaminho(QString);
    QString separandoNome(QString);
    QString separandoExt(QString);
    //teste

    int *pointer= NULL;
    QString *ponteiro = NULL;


    int contador=0;

    int count = 0;

    int* numbers = NULL;
    int* more_numbers = NULL;



    QString* palavras=NULL;
    QString* maisPalavra=NULL;

    std::vector<std::string> joao;
    std::vector<QString> nome;

    QListWidget *item;

    QString nomeGravarListaVideo;


};

#endif // TELACADASTROLISTAFILME_H
