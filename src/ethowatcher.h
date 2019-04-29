/*
EthoWatcher OS is a software to assist study of animal behavior.
Copyright (C) 2018  Universidade Federal de Santa Catarina.

EthoWatcher OS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
#include "telablind.h"

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
    bool chLoadUser;

    //telaAquisicaoFilme *aquisicaoFilme;
    telaCadastroPessoa *cadastroPessoa;
    telaCadastroFilme *cadastroFilme;
    telaCadastroListaFilme *cadastroListaFilme;
    //telaCadastroEtograma *cadastroEtograma;
    telablind *cego;
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
