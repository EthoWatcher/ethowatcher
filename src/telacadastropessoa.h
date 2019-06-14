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

    void showInterface();


    void setTutorPrincipal(ControladoWarningTutor *etoTutor);
signals:

    void fechouJanela();


private slots:
    void on_pushButton_2_clicked();
     void botaoClicado(bool, QString);

public slots:
    void mudaLetra();

private:
    Ui::telaCadastroPessoa *ui;

    ControladoWarningTutor *controlWarnig;

    ControladoWarningTutor *controlWarnigPrincial;

    QList<QString> seqInicial;


protected:
    void closeEvent(QCloseEvent *);

};

#endif // TELACADASTROPESSOA_H
