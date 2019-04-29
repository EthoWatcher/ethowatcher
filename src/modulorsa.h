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
#ifndef MODULORSA_H
#define MODULORSA_H

#include <QObject>
#include <QDebug>

class moduloRsa : public QObject
{
    Q_OBJECT
public:
    explicit moduloRsa(QObject *parent = 0);

    struct chaveRSA{
    int p; //primeiro primo
    int q; //segundo primo
    int n;
    int d; //chave de decodificacao
    int e; //ou lambda
    int totiente;
    };
    chaveRSA chave;

    QString criptoRSAQstring(QString valorOriginalString);
    QString decriptoRSAQstring(QString valorCriptografadoString);

    int criptoRSA(int numeroASerCodificado);
    int decriptoRSA(int valorCriptografado);

    void valoresdeD();


    ///valores
    QString valorOriginalString;
    QByteArray valorOriginalBit;
  //  int valorDecrip[3];
   // int valorDecriptografar=0;





public slots:


signals:



private:







};

#endif // MODULORSA_H
