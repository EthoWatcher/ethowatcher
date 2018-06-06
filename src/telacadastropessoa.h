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

#include "warningtutor.h"

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

    struct TutoresInterfaces{
       int tutorEthoWatcherPrincipal;
       int tutorCadastroUsuario;
       int tutorCadastroCatalogo;

    };

    TutoresInterfaces tutores;

    int vezes,tutor;

    bool loadUser();
    void setLocalArquivo();
    void gravandoUserXML();


    void setTutor(bool chTutor);
    bool getTutor(QString nomeTutor);

    void showInterface();
    bool createdUser();


signals:

    void fechouJanela();


private slots:
    void on_pushButton_2_clicked();

public slots:
    void mudaLetra();
    void botaoClicado(bool,QString);

private:
    bool chCarregado;
    Ui::telaCadastroPessoa *ui;

    ControladoWarningTutor *controlWarnig;
    QList<QString> seqInicial;
};

#endif // TELACADASTROPESSOA_H
