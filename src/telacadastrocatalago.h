#ifndef TELACADASTROCATALAGO_H
#define TELACADASTROCATALAGO_H

#include <QWidget>
//funcionamento da saida em xml
#include <QtCore>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFileDialog>
#include <QListWidget>
#include <QMessageBox>

#include <QCloseEvent>

#include "warningtutor.h"

namespace Ui {
class telaCadastroCatalago;
}

class telaCadastroCatalago : public QWidget
{
    Q_OBJECT

public:
    explicit telaCadastroCatalago(QWidget *parent = 0);
    ~telaCadastroCatalago();

    void closeEvent(QCloseEvent *event);
private slots:
    void on_pbAddCategoria_clicked();

    void on_pbClearItem_clicked();

    void on_pbCadastroCatalago_clicked();

    void botaoClicado(bool clicado, QString id);

private:
    Ui::telaCadastroCatalago *ui;

    struct dadosEtografia{

        std::vector<int> id;
        std::vector<QString> nomeCategoria;
        std::vector<QString> atalho;
        std::vector<QString> descricao;
        std::vector<bool> dadoRemovido; //variavel de apoio para edicao
                                        //do catalago
        int quantidadeDeDados=0;

    };

    ControladoWarningTutor *controlWarnig;

    QList<QString> seqInicial;

    dadosEtografia dadosEto;
    QString nomeGravarCatalago;
    QFile Output;


};

#endif // TELACADASTROCATALAGO_H
