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

namespace Ui {
class telaCadastroCatalago;
}

class telaCadastroCatalago : public QWidget
{
    Q_OBJECT

public:
    explicit telaCadastroCatalago(QWidget *parent = 0);
    ~telaCadastroCatalago();

private slots:
    void on_pbAddCategoria_clicked();

    void on_pbClearItem_clicked();

    void on_pbCadastroCatalago_clicked();

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

    dadosEtografia dadosEto;
    QString nomeGravarCatalago;
    QFile Output;


};

#endif // TELACADASTROCATALAGO_H
