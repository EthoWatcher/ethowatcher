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
#include "modulorsa.h"

moduloRsa::moduloRsa(QObject *parent) : QObject(parent)
{
    chave.p=11;//p=5; //7 //primeiro primo

    chave.q=23;//q=7;  //5 //segundo primo

    chave.n= chave.p*chave.q;

    chave.totiente=(chave.p-1)*(chave.q-1);

    chave.e=7; //o lambda tem que ser um fatorial que não seja multiplo do numero
    //por exemplo se p for 5 e o q 7
    //o totiente é 4*6= 24
    //encontra os fatorial
    //24|2
    //12|2
    //6|2
    //3|3
    //1|1
    //por exemplo o e pode ser 7 nesse caso

    chave.d=63;
}


int moduloRsa::criptoRSA(int numeroASerCodificado){

    int numeroCodificado=0;

    numeroCodificado=numeroASerCodificado;
    for(int a=0;a<(chave.e-1);a++){

        numeroCodificado=(numeroCodificado*numeroASerCodificado)%chave.n;//%n;

    }

    return numeroCodificado;


}

int moduloRsa::decriptoRSA(int valorCriptografado){

    int valorDecodificado=0;


    valorDecodificado=valorCriptografado;
    for(int a=0;a<(chave.d-1);a++){

        valorDecodificado=(valorDecodificado*valorCriptografado)%chave.n;//%n;

    }

    return valorDecodificado;

}

void moduloRsa::valoresdeD(){

    bool primeiraEntrada=true;
    int achandood=0;
    for(int j=0;j<5000;j++){
        achandood=(chave.e*j)%chave.totiente;
        if(achandood==1){
            qDebug() << QString::number(j) << QString::number(achandood);
            if(primeiraEntrada){
                primeiraEntrada=false;
                // d=j;
            }

        }
    }


}

QString moduloRsa::criptoRSAQstring(QString valorOriginalString){


    //valores para criptografar
    //QString valorOriginalString;
    QByteArray valorOriginalBit;
    std::vector<int> valoresCriptografados;
    QByteArray numerosGravados;
    int valorDecomposto[3];
    int i,j,k=0;
    QString valorCriptoString;

    valorOriginalBit=valorOriginalString.toLatin1();

    numerosGravados.resize(valorOriginalString.size()*3);
    int valor;
    int somaIJ=0;

    for( i=0; i<valorOriginalBit.length();i++){
        valor= valorOriginalBit[i];
        valoresCriptografados.push_back(criptoRSA(valor));

//        numerosGravados[0]=1;

        valorDecomposto[2] = valoresCriptografados[i]%10;
        valorDecomposto[1] =
                (valoresCriptografados[i]%100-valorDecomposto[2])/10;
        valorDecomposto[0] =
                (valoresCriptografados[i]-valorDecomposto[1]*10
                -valorDecomposto[2])/100;

        QByteArray conversor;

        for(j=0;j<3;j++){
            conversor=QByteArray::number(valorDecomposto[j]);
            somaIJ=(3*i)+j;
            if(numerosGravados.size() < somaIJ){
                numerosGravados.resize(somaIJ);
            }
            numerosGravados[somaIJ]=conversor[0];

        }

    }

    valorCriptoString=QString::fromLatin1(numerosGravados);

    return valorCriptoString;
    //        return valorOriginalString;


}

QString moduloRsa::decriptoRSAQstring(QString valorCriptografadoString){

    QByteArray valorCriptografadobit;
    int valorDecrip[3];
    int valorDecriptografar=0;
    int valorDecriptografadoInt=0;
    QByteArray valorDecriptografadoBit;
    QString valorDecriptografadoString;
    int contador=0;
    int k=0;

    valorDecriptografadoBit.resize(valorCriptografadoString.size()/3);
    valorCriptografadobit=valorCriptografadoString.toLatin1();


    while(k<valorCriptografadobit.length()){

        valorDecrip[0]= valorCriptografadobit[k]-48;//centena
        k++;
        valorDecrip[1]=valorCriptografadobit[k]-48;//dezena

        k++;
        valorDecrip[2]=valorCriptografadobit[k]-48;//unidade
        k++;

        valorDecriptografar= valorDecrip[0]*100+valorDecrip[1]*10+valorDecrip[2];


        valorDecriptografadoInt=decriptoRSA(valorDecriptografar);

        if(valorDecriptografadoInt <0){
            valorDecriptografadoInt = valorDecriptografadoInt * -1;
        }


        valorDecriptografadoBit[contador]= valorDecriptografadoInt;

        contador++;

    }


    valorDecriptografadoString=QString::fromLatin1(valorDecriptografadoBit);



    return valorDecriptografadoString;



}
