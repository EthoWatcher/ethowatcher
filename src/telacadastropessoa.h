#ifndef TELACADASTROPESSOA_H
#define TELACADASTROPESSOA_H

#include <QWidget>
#include <QString>
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>



namespace Ui {
class telaCadastroPessoa;
}

class telaCadastroPessoa : public QWidget
{
    Q_OBJECT

public:
    explicit telaCadastroPessoa(QWidget *parent = 0);
    ~telaCadastroPessoa();

    //comum para todos;
    QString nomePessoa, nomeLaboratorio;

    //vem do arquivo janelaCadastroMelhor
    void gravandoXML();
    void lendoXML();

    QString nome,nomeArquivo,extensao,nomeExtensao,lab,idObservador,sexo,arquivo;
    int vezes,tutor;

    void loadUser();
    void setLocalArquivo();
    void gravandoUserXML();


    void setTutor(bool chTutor);
signals:

    void fechouJanela();


private slots:
    void on_pushButton_2_clicked();

public slots:
    void mudaLetra();

private:
    Ui::telaCadastroPessoa *ui;

};

#endif // TELACADASTROPESSOA_H
