#ifndef ETHOWATCHER_H
#define ETHOWATCHER_H

#include <QMainWindow>
#include "telacadastropessoa.h"
#include "telacadastrofilme.h"
//#include "telaaquisicaofilme.h"
#include "telacadastrolistafilme.h"
//#include "telacadastroetograma.h"
#include "telasegementacao.h"
#include "telamatriztransicao.h"
#include "teaconcordancia.h"
#include "telaconversorxmlcsv.h"
#include "telacego.h"
#include "telaetografia.h"
#include "telacadastrocatalago.h"
#include <QString>
#include <QByteArray>
#include <QTreeWidget>
#include <QDebug>
#include "telaetografiaproce.h"
#include "telaunveil.h"
#include "telatemporeal.h"
#include "telafluxocomportamental.h"

namespace Ui {
class ethoWatcher;
}

class ethoWatcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit ethoWatcher(QWidget *parent = 0);
    ~ethoWatcher();

public slots:
    void mudaTela();


private slots:
    void on_pbTela1No_clicked();

    void on_pbTela1Yes_clicked();

    void on_pbTela2ListaVideo_clicked();

    //void on_pbTela2Gravar_clicked();

    void on_pbCadastrarListaVideo_clicked();

    void on_pbAnaliseEtograma_clicked();

    void on_pbDuploCego_clicked();

    void on_pbEstatistica_clicked();

    void on_pbConversorXMLCSV_clicked();

    void on_actionAbout_triggered();

    void on_pbBackAbout_clicked();

   // void on_actionTips_triggered();

    void on_actionLicense_agreement_triggered();

    void on_pbBackLicense_clicked();

    void on_treeWidget_doubleClicked(const QModelIndex &index);

    void on_pbRegisterCatalog_clicked();

    void on_pbTransicao_clicked();

    void on_pbConcordancia_clicked();

    void on_pbUnveil_clicked();

    void on_pbRealTime_clicked();

    void on_pbBehaviorSample_clicked();

private:
    Ui::ethoWatcher *ui;

    //telaAquisicaoFilme *aquisicaoFilme;
    telaCadastroPessoa *cadastroPessoa;
    telaCadastroFilme *cadastroFilme;
    telaCadastroListaFilme *cadastroListaFilme;
    //telaCadastroEtograma *cadastroEtograma;
    telaCego *cego;
    telaEtografia *etografia;
    //telaEstatistica *estatistica;
    telaSegementacao *segment;
    telaMatrizTransicao *transi;
    teaConcordancia *concordancia;
    telaCadastroCatalago *cadastroCatalogo;

    telaConversorXmlCsv* conversorXmlCsv;
    telaEtografiaProce* etografaProce;
    telaUnveil *unveil;


    QString fonteUsuario="";
    QByteArray fonteUsuarioBit;

    telaTempoReal *tempoReal;
    telaFluxoComportamental *fluxoComportamental;

    void resetaCorBotoes();


};

#endif // ETHOWATCHER_H
