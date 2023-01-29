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
#include "parserxml.h"

parserXML::parserXML(QObject *parent) : QObject(parent)
{
    videoLido= new dadosVideo();
//    etografiaLida= new analiseEtografica();
}

void parserXML::readTCCM(QString nomeArquivo)
{

    OutEtografia.setFileName(nomeArquivo);
    OutEtografia.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutEtografia); //passa o endereço

    QString conversor;
    bool entrou=false;
    bool entrou1=false;
    bool entrou2=false;
    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();


        if(streamReader.name().toString()== "dadosVideosAnalisado"){
            entrou1=~entrou1;
        }


        if(entrou1==true){

            if(streamReader.name().toString()== "nomeVxml"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){
            videoLido->nome= conversor;
            }}
            if(streamReader.name().toString()== "frameInicial"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameInicial= conversor.toDouble();
            }}

            if(streamReader.name().toString()== "frameProces"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameProce= conversor.toDouble();
            }}


            if(streamReader.name().toString()== "frameFinal"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameFinal= conversor.toDouble();
            }}

            if(streamReader.name().toString()== "fps"){

            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->fps= conversor.toDouble();

            }}

            if(streamReader.name().toString()== "escala"){

            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->escala= conversor.toDouble();

            }
            }

        }




        if(streamReader.name().toString()== "anaProceImagem"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){

            if(streamReader.name().toString()== "area"){

            QString conversor= streamReader.attributes().value("id").toString();
            if(conversor != ""){//ele acaba entrando daus vez pra cada tag
           //KohoKappa.nomeCate.push_back(conversor);
                //analiseSequencial.classeCatalago.push_back(conversor);
                // etografiaLida->caminho= conversor;
            }else{

                matrizReMorfo.push_back(reMorfo);
                matrizReCinema.push_back(reCinema);

                reMorfo.frame.clear();
                reMorfo.anguloObj.clear();
                reMorfo.area.clear();
                reMorfo.centroidX.clear();
                reMorfo.centroidY.clear();
                reMorfo.objetoEncontrado.clear();
                reMorfo.altura.clear();
                reMorfo.largura.clear();

                //reMorfo.tamanhoObj.clear();

                reCinema.ruidoMaxVaria.clear();
                reCinema.varAngular.clear();
                reCinema.varArea.clear();
                reCinema.varCenX.clear();
                reCinema.varCenY.clear();
                reCinema.varDistancia.clear();
                reCinema.varAltura.clear();
                reCinema.varLargura.clear();
                //reCinema.varTamObjeto.clear();
//              KohoKappa.cohoKappaMatrix.push_back(KohoKappa.cohoKappa);
////                analiseSequencial.listaDados.push_back(analiseSequencial.dados);
//              KohoKappa.cohoKappa.clear();
                //zerando os valores
            }

            }

            //if(xmlReader.name()== "caAnaSeg"){

            if(streamReader.name().toString()== "proce"){

                QString conObjeto= streamReader.attributes().value("OE").toString();


                if(!conObjeto.isEmpty()){//ele acaba entrando daus vez pra cada tag
               //KohoKappa.nomeCate.push_back(conversor);
                    //analiseSequencial.classeCatalago.push_back(conversor);
                    // etografiaLida->caminho= conversor;

                    if(conObjeto=="true"){

                       reMorfo.objetoEncontrado.push_back(true);
                    }else{
                       reMorfo.objetoEncontrado.push_back(false);
                    }

                    reMorfo.frame.push_back(streamReader.attributes().value("f").toDouble());
                    reMorfo.anguloObj.push_back(streamReader.attributes().value("an").toDouble());
                    reMorfo.area.push_back(streamReader.attributes().value("arP").toDouble());
                    reMorfo.areaM.push_back(streamReader.attributes().value("arM").toDouble());
                    reMorfo.centroidX.push_back(streamReader.attributes().value("ceX").toDouble());
                    reMorfo.centroidY.push_back(streamReader.attributes().value("ceY").toDouble());

                    reMorfo.altura.push_back(streamReader.attributes().value("altP").toFloat());
                    reMorfo.alturaM.push_back(streamReader.attributes().value("altM").toFloat());
                    reMorfo.largura.push_back(streamReader.attributes().value("larP").toFloat());
                    reMorfo.larguraM.push_back(streamReader.attributes().value("larM").toFloat());

                    //altP, altM, larP, larM, an, Var , Vd, Valt, Vlar, Van, rMinV


                    //reMorfo.tamanhoObj.push_back(streamReader.attributes().value("taP").toDouble());


                    QString conMax= streamReader.attributes().value("rMinV").toString();

                    if(conMax=="true"){
                        reCinema.ruidoMaxVaria.push_back(true);

                    }else{

                        reCinema.ruidoMaxVaria.push_back(false);
                    }


                    reCinema.varAngular.push_back(streamReader.attributes().value("Van").toDouble());
                    reCinema.varArea.push_back(streamReader.attributes().value("Var").toDouble());
                    reCinema.varDistancia.push_back(streamReader.attributes().value("Vd").toDouble());
                    reCinema.varAltura.push_back(streamReader.attributes().value("Valt").toFloat());
                    reCinema.varLargura.push_back(streamReader.attributes().value("Vlar").toFloat());

                    //reCinema.varTamObjeto.push_back(streamReader.attributes().value("VtoP").toDouble());



                }else{


                    //se ele sai

                }
//            QString conversorlal= xmlReader.attributes().value("quant").toString();
//            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
//                KohoKappa.cohoKappa.push_back( conversorlal.toInt());
//            }


            }


//            if(streamReader.name()== "areasDeInteresse"){
//                if(entrou==true){
//                    entrou=false;
//                }else{
//                    entrou=true;
//                }
//            }



        }



        if(streamReader.name().toString()== "areasDeInteresse"){
            if(entrou2==true){
                entrou2=false;
            }else{
                entrou2=true;
            }
        }





        if(entrou2){

        QString conversor= streamReader.attributes().value("id").toString();
        if(!conversor.isEmpty()){

            //ele acaba entrando daus vez pra cada tag
       //KohoKappa.nomeCate.push_back(conversor);
            //analiseSequencial.classeCatalago.push_back(conversor);
            // etografiaLida->caminho= conversor;
        }else{

//            matrizReMorfo.push_back(reMorfo);
//            matrizReCinema.push_back(reCinema);

//            reMorfo.anguloObj.clear();
//            reMorfo.area.clear();
//            reMorfo.centroidX.clear();
//            reMorfo.centroidY.clear();
//            reMorfo.objetoEncontrado.clear();
//            reMorfo.tamanhoObj.clear();

//            reCinema.ruidoMaxVaria.clear();
//            reCinema.varAngular.clear();
//            reCinema.varArea.clear();
//            reCinema.varCenX.clear();
//            reCinema.varCenY.clear();
//            reCinema.varDistancia.clear();
//            reCinema.varTamObjeto.clear();
////              KohoKappa.cohoKappaMatrix.push_back(KohoKappa.cohoKappa);
//////                analiseSequencial.listaDados.push_back(analiseSequencial.dados);
////              KohoKappa.cohoKappa.clear();
//            //zerando os valores
        }
        //<figName>
        if(streamReader.name().toString()== "figName"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.figName.push_back(conversor);

        }}

        if(streamReader.name().toString()== "tipoArea"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.tipoArea.push_back(conversor);

        }}

        if(streamReader.name().toString()== "centX"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.centX.push_back(conversor.toDouble());

        }}

        if(streamReader.name().toString()== "centY"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.centY.push_back(conversor.toDouble());

        }}

        if(streamReader.name().toString()== "heigth"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.heigth.push_back(conversor.toDouble());

        }}

        if(streamReader.name().toString()== "width"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.width.push_back(conversor.toDouble());

        }}

        if(streamReader.name().toString()== "raio"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.heigth.push_back(conversor.toDouble());
        areasDeInteresse.width.push_back(conversor.toDouble());

        }}




        }







    }
    qDebug() << "leu certo o xml do traking";
    OutEtografia.close();
}
