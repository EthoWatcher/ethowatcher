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
#include "parserxmltocsv.h"

parserXMLtoCSV::parserXMLtoCSV()
{
    catalagoLido= new catalago();
    videoLido= new dadosVideo();
    etografiaLida= new analiseEtografica();
}



parserXMLtoCSV::~parserXMLtoCSV()
{
    delete this;
}

void parserXMLtoCSV::converteArquivo(QString nomePath)
{

//    fonteCaminhoArquivo = QFileDialog::getOpenFileName(
//                this,
//                tr("Open File"),
//               "C://ethowatcher",
//               "Arquivos do Ethowatcher (*.aseq *.fkf *.kkf *.tbf *.etoxml *.tkin )"
//                );

    fonteCaminhoArquivo = nomePath;

    qDebug() << "entrou " << fonteCaminhoArquivo;


 if(!fonteCaminhoArquivo.isEmpty()){

     output.setFileName( fonteCaminhoArquivo);

     fonteVideoBit = fonteCaminhoArquivo.toLatin1();

     int i= fonteVideoBit.length();
     int inicio=0;
     //aquirir a extensão do arquivo
     while(fonteVideoBit[i] != 46){
         i--;
         fonteVideoBitExtInv[inicio]= fonteVideoBit[i];
         inicio++;
     }


     //desinverter a extensão do arquivo

     int j=0;
     while(fonteVideoBitExtInv[j] != 0){
         fonteVideoBitExt[j]=fonteVideoBitExtInv[fonteVideoBitExtInv.length()-1-j];
         j++;

     }



     if(fonteVideoBitExt==".tbf"){
         lerTimeXml(0); //le o experimentador
         lerTimeXml(1); //le o catalago
         lerTimeXml(2); //le os dados do video
         lerTimeXml(3); //le os dados do video
         lerTimeXml(4); //le o time budget do video
         lerTimeXml(8); //le os comportmaneto
//         escreverTimeCsv();
         //ler xml timebudget;
         //manda para a função de ler esse video
     }
     if(fonteVideoBitExt==".aseq"){
         lerTimeXml(0); //le o experimentador
         lerTimeXml(1); //le o catalago
         lerTimeXml(2); //le os dados do video
         lerTimeXml(3); //le os dados do video
         lerTimeXml(5); //le o time budget do video

          qDebug() <<"leu o xml";
//         escreverSeqCsv();
         //ler xml timebudget;
         //manda para a função de ler esse video
     }
     if(fonteVideoBitExt==".kkf"){
         lerTimeXml(0); //le o experimentador
         lerTimeXml(1); //le o catalago
         lerTimeXml(2); //le os dados do video
         lerTimeXml(3); //le os dados do video
         lerTimeXml(6); //le o kohone kappa
//         lerKohoXml();
//         escreverKohoCsv();
         //ler xml timebudget;
         //manda para a função de ler esse video
     }

     if(fonteVideoBitExt==".fkf"){
         lerTimeXml(0); //le o experimentador
         lerTimeXml(1); //le o catalago
         lerTimeXml(2); //le os dados do video
         lerTimeXml(3); //le os dados do video
         lerTimeXml(7); //le o fleiss kappa
//         escreverFleisCsv();
         //manda para a função de ler esse video
     }

     if(fonteVideoBitExt==".etoxml"){




         lerETOXML(fonteCaminhoArquivo);

          totalizacoesEtografia();


     }

     if(fonteVideoBitExt==".tkin"){


         lerTRKING(fonteCaminhoArquivo);


     }

  //  QMessageBox::information(this,"Fim","The arquivo was successfully opened.");
//    QMessageBox::information(this,"Fim","Informe o nome do csv");
     //</>encontrando a extensão do arquivo aberto


//    nomeArquivoGravarCsv = QFileDialog::getSaveFileName(
//                 this,
//                 tr("Save File"),
//                 "C://",
//                "csv Files (*.csv)"
//                );
     // pega o nome do arquivo e usa para escrever o csv


int lugar = fonteVideoBit.lastIndexOf("/");

//encontra o nome do arquivo do user
QByteArray nomeArquivoUser= fonteVideoBit.right(fonteVideoBit.size()-lugar);
nomeArquivoUser.replace(QByteArray("."),QByteArray("_"));

//encontra o cmainho
QByteArray caminho = fonteVideoBit;
caminho.truncate(lugar);



//QByteArray nomeArquivo =

qDebug() << fonteVideoBit ;
qDebug() << fonteVideoBit.lastIndexOf("/");
qDebug() << caminho;
qDebug() << nomeArquivoUser;

QByteArray finalCSV = caminho+nomeArquivoUser+"_"+".csv";
qDebug() << finalCSV;


//qDebug() << novoArquivo;


    nomeArquivoGravarCsv= QString::fromLatin1(finalCSV); //"C:/ethowatcher/lalal.csv";


    //gravando os files
    if(fonteVideoBitExt==".tbf"){

      escreverTimeCsv();


    }
     if(fonteVideoBitExt==".aseq"){
         escreverSeqCsv();
     }

     if(fonteVideoBitExt==".kkf"){
          escreverKohoCsv();
     }

     if(fonteVideoBitExt==".fkf"){
          escreverFleisCsv();
     }


     if(fonteVideoBitExt==".etoxml"){

         //encontrando a f d l



        escreverEtografiaCsv();


     }


     if(fonteVideoBitExt==".tkin"){

         qDebug() <<" trakin sendo gravado";
        escreverTrakinCsv();
     }



   // ui->stackedWidget->setCurrentIndex(1);

 }


}

void parserXMLtoCSV::lerETOXML(QString nomeArquivo)
{
    OutEtografia.setFileName(nomeArquivo);
    OutEtografia.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutEtografia); //passa o endereço

    QString conversor;


    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        if(streamReader.name() == "analise"){

          if(etografiaLida->controle){

              etografiaLida->ponto.push_back(streamReader.attributes().value("ponto").toInt());
              etografiaLida->id.push_back(streamReader.attributes().value("id").toInt());
              etografiaLida->frameInicial.push_back(streamReader.attributes().value("frameInicial").toDouble());
              etografiaLida->frameFinal.push_back(streamReader.attributes().value("frameFinal").toDouble());
              //   contadorTamanho++;
              etografiaLida->quantidadeDePontos++;

            }
            etografiaLida->controle=!etografiaLida->controle;
           //qDebug() << leitorXML.attributes().value("id").toInt();

        }


        if(streamReader.name() == "categoria"){

          if(catalagoLido->controle){
              QString nome;
             // etografiaLida.ponto.push_back(streamReader.attributes().value("ponto").toInt());
              catalagoLido->id.push_back(streamReader.attributes().value("id").toInt());
                nome= streamReader.attributes().value("nome").toString();
              catalagoLido->nome.push_back(nome);
              //etografiaLida.frameFinal.push_back(streamReader.attributes().value("frameFinal").toDouble());
              //   contadorTamanho++;
              catalagoLido->quantidadeDeCategorias++;

            }

          catalagoLido->controle=!catalagoLido->controle;
           //qDebug() << leitorXML.attributes().value("id").toInt();

        }

        if(streamReader.name() == "nomeCaminhoExt"){

            catalagoLido->caminhoArquivo= streamReader.readElementText();


        }

        if(streamReader.name() == "tipoAnalise"){

            catalagoLido->tipoAnalise= streamReader.readElementText();


        }

//        if((streamReader.name() == "dadosVideoAnalisado")||(videoLido->controle)){


          if(streamReader.name() == "nomeVxml"){

              videoLido->nome= streamReader.readElementText();

          }

          if(streamReader.name() == "frameInicial"){


              videoLido->frameInicial= streamReader.readElementText().toDouble();

          }

          if(streamReader.name() == "frameProces"){


              videoLido->frameProce= streamReader.readElementText().toDouble();

          }

          if(streamReader.name() == "frameFinal"){
           videoLido->frameFinal= streamReader.readElementText().toDouble();

            //videoLido->controle=false;
        }

          if(streamReader.name() == "fps"){
           videoLido->fps= streamReader.readElementText().toDouble();

            videoLido->controle=false;
        }

//        }

    }



    OutEtografia.close();
}

void parserXMLtoCSV::lerTRKING(QString nomeArquivo)
{

    OutEtografia.setFileName(nomeArquivo);
    OutEtografia.open(QIODevice::ReadOnly);

    if(OutEtografia.isOpen()){
        qDebug() << "esta aberto o arquivo de trankin na leitura";
    }

    QXmlStreamReader streamReader(&OutEtografia); //passa o endereço

    QString conversor;
    bool entrou=false;
    bool entrou1=false;
    bool entrou2=false;
    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

//        qDebug()<< streamReader.name();

//        if(streamReader.name()== "dadosVideosAnalisado"){
//            entrou1=~entrou1;
//        }


//        if(entrou1==true){

            if(streamReader.name()== "nomeVxml"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){
            videoLido->nome= conversor;
            }}
            if(streamReader.name()== "frameInicial"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameInicial= conversor.toDouble();
            }}

            if(streamReader.name()== "frameProces"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameProce= conversor.toDouble();
            }}


            if(streamReader.name()== "frameFinal"){
            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameFinal= conversor.toDouble();
            }}

            if(streamReader.name()== "fps"){

            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->fps= conversor.toDouble();

            }}

            if(streamReader.name()== "escala"){

            QString conversor= streamReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->escala= conversor.toDouble();

            }
            }

//        }




        if(streamReader.name()== "anaProceImagem"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){

            if(streamReader.name()== "area"){

            QString conversor= streamReader.attributes().value("id").toString();
            qDebug()<< " o conversor da area tem o valor " << conversor;
            if( !conversor.isEmpty() ){//ele acaba entrando daus vez pra cada tag

                qDebug() << " hahahahahah ";
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

            if(streamReader.name()== "proce"){

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
                    reMorfo.centroidX.push_back(streamReader.attributes().value("ceX").toDouble());
                    reMorfo.centroidY.push_back(streamReader.attributes().value("ceY").toDouble());

                    reMorfo.altura.push_back(streamReader.attributes().value("altP").toFloat());
                    reMorfo.largura.push_back(streamReader.attributes().value("larP").toFloat());

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



        if(streamReader.name()== "areasDeInteresse"){
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
        if(streamReader.name()== "figName"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.figName.push_back(conversor);

        }}

        if(streamReader.name()== "tipoArea"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.tipoArea.push_back(conversor);

        }}

        if(streamReader.name()== "centX"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.centX.push_back(conversor.toDouble());

        }}

        if(streamReader.name()== "centY"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.centY.push_back(conversor.toDouble());

        }}

        if(streamReader.name()== "heigth"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.heigth.push_back(conversor.toDouble());

        }}

        if(streamReader.name()== "width"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.width.push_back(conversor.toDouble());

        }}

        if(streamReader.name()== "raio"){

        QString conversor= streamReader.readElementText();
        if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
        //videoLido->fps= conversor.toInt();
        areasDeInteresse.heigth.push_back(conversor.toDouble());
        areasDeInteresse.width.push_back(conversor.toDouble());

        }}




        }







    }
    OutEtografia.close();




}

void parserXMLtoCSV::totalizacoesEtografia()
{
//encontra frequencia
    for(int ka=0; ka<catalagoLido->id.size(); ka++){
        //cada categoria
        frequencia=0;

        for(int ja=0; ja<etografiaLida->id.size(); ja++){

            if(etografiaLida->id[ja]==ka){

               frequencia=frequencia+1;
            }
        }
        vetorFrequencia.push_back(frequencia);
    }

    //encontra latencia
    int primeiraOcorrencia=0;
    bool chLate;


    for(int ka=0; ka<catalagoLido->id.size(); ka++){
        //cada categoria
        //latencia
        latencia=videoLido->frameFinal;
        chLate=true;

        //encontra a primeria vez que aconteceu
        for(int ja=0; ja<etografiaLida->id.size(); ja++){

            if( (etografiaLida->id[ja]==ka) &&(chLate)){

               primeiraOcorrencia= ja;
               chLate=false;

            }

        }

        latencia= etografiaLida->frameInicial[primeiraOcorrencia] - videoLido->frameProce;
        vetorLatencia.push_back(latencia/videoLido->fps);
    }


    //encontra duracao;

    for(int ka=0; ka<catalagoLido->id.size(); ka++){
        //cada categoria
        duracao=0;

        for(int ja=0; ja<etografiaLida->id.size(); ja++){

            if(etografiaLida->id[ja]==ka){

               duracao= etografiaLida->frameFinal[ja]- etografiaLida->frameInicial[ja] + duracao;

            }
        }
        vetorDuracao.push_back(duracao/videoLido->fps);
    }



    chLate=false;










}

void parserXMLtoCSV::lerTimeXml(int qualLer)
{
    QXmlStreamReader xmlReader(&output);
    //output.open(QIODevice::ReadOnly | QIODevice::Text);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    if(qualLer==0){ //dadosPesquisador
    while(!xmlReader.atEnd() && !xmlReader.hasError()){


        xmlReader.readNext();


        if(xmlReader.name()== "nomeAnalisador"){
        experimentador.nome= xmlReader.readElementText();
           //qDebug() << xmlReader.readElementText();

        }


           if(xmlReader.name()== "laboratorio"){
         experimentador.lab= xmlReader.readElementText();
              // qDebug() << xmlReader.readElementText();
           }

        }
    }



    if(qualLer==1){ //dadosCatalago
    bool entrou=false;

        while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "dadosCatalagoUsado"){
            entrou=~entrou;
        }


        if(entrou==true){

            if(xmlReader.name()== "caminhoCatalago"){

                catalagoLido->caminhoArquivo= xmlReader.readElementText();

            }

            if(xmlReader.name()== "categoria"){
              QString conversor =  xmlReader.attributes().value("nome").toString();
                if(!conversor.isEmpty()){ //ele acaba entrando daus vez pra cada tag
                    catalagoLido->nome.push_back(conversor);

                }

            }



        }

    }


    }

    if(qualLer==2){ //dadosVideos
    bool entrou=false;

        while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "dadosVideosUsados"){
            entrou=~entrou;
        }


        if(entrou==true){

            if(xmlReader.name()== "caminhoVideo"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){
            videoLido->nome= conversor;
            }}
            if(xmlReader.name()== "frameInicial"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameInicial= conversor.toDouble();
            }}
            if(xmlReader.name()== "frameProces"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameProce= conversor.toDouble();
            }}
            if(xmlReader.name()== "frameFinal"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameFinal= conversor.toDouble();
            }}
            if(xmlReader.name()== "fps"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->fps= conversor.toDouble();
            }}
        }

    }


    }


    if(qualLer==3){ //dadosAnalises
    bool entrou=false;


    while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "analises"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){


            if(xmlReader.name()== "categoria"){
            QString conversor= xmlReader.attributes().value("tipo").toString();
            if(!conversor.isEmpty()){
            etografiaLida->tipoDeAnalise= conversor;
            }else{

              etografiasLidas.push_back(etografiaLida);

            }

            }
            if(xmlReader.name()== "caminhoAnaliseEto"){

            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            etografiaLida->caminho= conversor;
            }

            }

        }

    }


    }

    if(qualLer==4){ //dadosSessões
    bool entrou=false;


    while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "sessoes"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){


            if(xmlReader.name()== "sessao"){
            QString conversor= xmlReader.attributes().value("id").toString();
            QString conversor1= xmlReader.attributes().value("inicio").toString();
            QString conversor2= xmlReader.attributes().value("fim").toString();
            if(!conversor.isEmpty()){
                totalizacao1.inicioSessao= conversor1.toDouble();
                totalizacao1.finalSessao= conversor2.toDouble();

            }else{

              totalizacaoTot.push_back(totalizacao1);
                totalizacao1.duracao.clear();//zera as durações
                totalizacao1.latencia.clear();
                totalizacao1.freq.clear();
                    }
            }

//            if(xmlReader.name()== "categoria"){

//            QString conversor= xmlReader.readElementText();
//            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
//           // etografiaLida->caminho= conversor;
//            }else{

//                //zerando os valores

//            }

//            }

            if(xmlReader.name()== "duracao"){

            QString conversorlal= xmlReader.readElementText();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                totalizacao1.duracao.push_back( conversorlal.toDouble());
            }

            }

            if(xmlReader.name()== "frequencia"){

            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag

                totalizacao1.freq.push_back(conversor.toDouble());
            }

            }

            if(xmlReader.name()== "latencia"){

            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag

                totalizacao1.latencia.push_back(conversor.toDouble());

            }

            }



        }

    }


    }

    if(qualLer==5){ //dados analise sequencial
    bool entrou=false;
    bool entrouPorce=false;


    while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "sessoes"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){


//            if(xmlReader.name()== "sessao"){
//            QString conversor= xmlReader.attributes().value("id").toString();
//            if(!conversor.isEmpty()){
//                analiseSequencial.dados.push_back(123);
//                totalizacao1.inicioSessao= conversor1.toDouble();
//                totalizacao1.finalSessao= conversor2.toDouble();

//            }else{

//              totalizacaoTot.push_back(totalizacao1);
//                totalizacao1.duracao.clear();//zera as durações
//                totalizacao1.latencia.clear();
//                totalizacao1.freq.clear();
//                    }
//            }

            if(xmlReader.name()== "categoria"){

            QString conversor= xmlReader.attributes().value("name").toString();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
           analiseSequencial.classeCatalago.push_back(conversor);
                // etografiaLida->caminho= conversor;
            }else{

                analiseSequencial.listaDados.push_back(analiseSequencial.dados);
                analiseSequencial.dados.clear();
                //zerando os valores

            }

            }

            if(xmlReader.name()== "caAnaSeg"){

            QString conversorlal= xmlReader.attributes().value("quant").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                analiseSequencial.dados.push_back( conversorlal.toInt());
            }

            }


        }

        if(xmlReader.name()== "sessaoPorce"){
            if(entrouPorce==true){
                entrouPorce=false;
            }else{
                entrouPorce=true;
            }
        }



        if(entrouPorce==true){


            if(xmlReader.name()== "caAnaSegPorce"){

            QString conversorlal= xmlReader.attributes().value("quant").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                analiseSequencial.dadosPorce.push_back( conversorlal.toDouble());
            }

            }



            if(xmlReader.name()== "categoriaPorce"){

            QString conversor= xmlReader.attributes().value("name").toString();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
           analiseSequencial.classeCatalagoPorcentagem.push_back(conversor);
                // etografiaLida->caminho= conversor;
            }else{

                analiseSequencial.listaDadosPorcentagem.push_back(analiseSequencial.dadosPorce);
                analiseSequencial.dadosPorce.clear();
                //zerando os valores

            }

            }



        }






    }

    }


    if(qualLer==6){ //dados analise koho kappa
    bool entrou=false;
    bool entrou1=false;

    while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "tabelaConcordancia"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){


//            if(xmlReader.name()== "sessao"){
//            QString conversor= xmlReader.attributes().value("id").toString();
//            if(!conversor.isEmpty()){
//                analiseSequencial.dados.push_back(123);
//                totalizacao1.inicioSessao= conversor1.toDouble();
//                totalizacao1.finalSessao= conversor2.toDouble();

//            }else{

//              totalizacaoTot.push_back(totalizacao1);
//                totalizacao1.duracao.clear();//zera as durações
//                totalizacao1.latencia.clear();
//                totalizacao1.freq.clear();
//                    }
//            }

            if(xmlReader.name()== "categoriaKK"){

            QString conversor= xmlReader.attributes().value("nome").toString();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
           KohoKappa.nomeCate.push_back(conversor);
                //analiseSequencial.classeCatalago.push_back(conversor);
                // etografiaLida->caminho= conversor;
            }else{
              KohoKappa.cohoKappaMatrix.push_back(KohoKappa.cohoKappa);
//                analiseSequencial.listaDados.push_back(analiseSequencial.dados);
              KohoKappa.cohoKappa.clear();
                //zerando os valores
            }

            }

            if(xmlReader.name()== "caAnaSeg"){

            QString conversorlal= xmlReader.attributes().value("quant").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                KohoKappa.cohoKappa.push_back( conversorlal.toInt());
            }

            }





        }

        if(xmlReader.name()== "tabelaPorcentagem"){
            if(entrou1==true){
                entrou1=false;
            }else{
                entrou1=true;
            }
        }


        if(entrou1==true){



            if(xmlReader.name()== "categoriaKK"){

            QString conversor= xmlReader.attributes().value("nome").toString();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
//           KohoKappa.nomeCate.push_back(conversor);
                //analiseSequencial.classeCatalago.push_back(conversor);
                // etografiaLida->caminho= conversor;
            }else{
              KohoKappa.cohoKappaPorMatrix.push_back(KohoKappa.cohoKappaPor);
//                analiseSequencial.listaDados.push_back(analiseSequencial.dados);
              KohoKappa.cohoKappaPor.clear();
                //zerando os valores
            }

            }

            if(xmlReader.name()== "caAnaSeg"){

            QString conversorlal= xmlReader.attributes().value("porcent").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                KohoKappa.cohoKappaPor.push_back( conversorlal.toFloat());
            }

            }


        }



        if(xmlReader.name()== "k1"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            KohoKappa.k1= conversor.toFloat();
        }
        }
        if(xmlReader.name()== "k2"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            KohoKappa.k2= conversor.toFloat();
        }
        }
        if(xmlReader.name()== "indiceKohoneKappa"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            KohoKappa.kappa= conversor.toFloat();
        }
        }

    }//do while


    }


    if(qualLer==7){ //dados analise fleiss kappa
    bool entrou=false;
    bool entrou1=false;
    bool entrou2=false;


    while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name()== "analise"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }

        if(xmlReader.name()== "tabelaSomatorio"){
            if(entrou1==true){
                entrou1=false;
            }else{
                entrou1=true;
            }
        }

        if(xmlReader.name()== "pi"){
            if(entrou2==true){
                entrou2=false;
            }else{
                entrou2=true;
            }
        }




        if(entrou==true){


            if(xmlReader.name()== "aFr"){

            QString conversor= xmlReader.attributes().value("num").toString();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
//           analiseSequencial.classeCatalago.push_back(conversor);
                // etografiaLida->caminho= conversor;
            }else{

                flKaDa.matrizConcordancia.push_back(flKaDa.linhaConcordancia);
                flKaDa.linhaConcordancia.clear();
                //zerando os valores

            }

            }

            if(xmlReader.name()== "con"){

            QString conversorlal= xmlReader.attributes().value("q").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                flKaDa.linhaConcordancia.push_back( conversorlal.toInt());
            }
            }



//            if(xmlReader.name()== "tabelaSomatorio"){

//            QString conversorlal= xmlReader.attributes().value("q").toString();
//            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
//                flKaDa.linhaConcordancia.push_back( conversorlal.toInt());
//            }
//            }


//            if(xmlReader.name()== "pi"){

//            QString conversorlal= xmlReader.attributes().value("q").toString();
//            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
//                flKaDa.linhaConcordancia.push_back( conversorlal.toInt());
//            }
//            }







        }
        //final do primeiro entroeu
        if(entrou1==true){

            if(xmlReader.name()== "con"){

            QString conversorlal= xmlReader.attributes().value("q").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                flKaDa.somatorio.push_back( conversorlal.toInt());
            }
            }

        }

        if(entrou2==true){

            if(xmlReader.name()== "con"){

            QString conversorlal= xmlReader.attributes().value("q").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                flKaDa.pi.push_back( conversorlal.toInt());
            }
            }

        }



        if(xmlReader.name()== "Pe"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            flKaDa.pe= conversor.toFloat();
        }
        }
        if(xmlReader.name()== "P"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            flKaDa.p= conversor.toFloat();
        }
        }
        if(xmlReader.name()== "indiceFleissKappa"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            flKaDa.indiceFleissKappa= conversor.toFloat();
        }
        }




    }
    }

    if(qualLer=8){

        while(!xmlReader.atEnd() && !xmlReader.hasError()){

            xmlReader.readNext();

        if(xmlReader.name() == "analise"){

          if(etografiaLida->controle){

              etografiaLida->ponto.push_back(xmlReader.attributes().value("ponto").toInt());
              etografiaLida->id.push_back(xmlReader.attributes().value("id").toInt());
              etografiaLida->frameInicial.push_back(xmlReader.attributes().value("frameInicial").toDouble());
              etografiaLida->frameFinal.push_back(xmlReader.attributes().value("frameFinal").toDouble());
              //   contadorTamanho++;
              etografiaLida->quantidadeDePontos++;

            }
            etografiaLida->controle=!etografiaLida->controle;
           //qDebug() << leitorXML.attributes().value("id").toInt();

        }

        }


    }





    output.close();
    xmlReader.clear();



}

//segmentacao de tempo
void parserXMLtoCSV::escreverTimeCsv()
{

    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador <<"EthoWatcher Open Source \n";
    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"Experiment" << "\n";
    csvGravador <<"Animal" << "\n";
    csvGravador <<"Weight" << "\n";
    csvGravador <<"sex" << "\n";
    csvGravador <<"Treatment/condition" << "\n";
    csvGravador <<"Other Info" << "\n";
    //csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"WARNING: in this version, decimals are separated by COMMA \n";
//    csvGravador <<"video file \n";

    csvGravador << "ETHOGRAPHY REPORT" << "\n";
////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
    csvGravador << "video file is " << videoLido->nome<< "\n";

    csvGravador << "Analysis initiated at " << conPontoVirgula( videoLido->frameProce /videoLido->fps)  << " (seconds) of the video file \n ";
    csvGravador << "Analysis terminated at " << conPontoVirgula(videoLido->frameFinal / videoLido->fps) << " (seconds) of the video file \n";
    csvGravador <<"\n";
//    csvGravador <<"informacoes do catalogo analisado: \n";
    csvGravador <<"O catalogo utilizado foi o " <<";" << catalagoLido->caminhoArquivo << "\n";
//    csvGravador <<"categorias\n";
//    for(int i=0; i< catalagoLido->nome.size(); i++ ){
//       csvGravador << catalagoLido->nome[i]<< "\n";

//    }
//    csvGravador <<"\n";
//    csvGravador <<"A analise etografica utilizada \n";
//    csvGravador <<"id, caminho, tipo \n";
//    for(int i=0; i< etografiasLidas.size();i++){

//      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
//    }
//    csvGravador <<"\n";
//    csvGravador <<"\n";

    //apartir daqui é diferente das outras analises
//    csvGravador <<"As totalizacoes da analise sequencial\n";
//    csvGravador << "" <<";";
//    for(int grt=0; grt< catalagoLido->nome.size(); grt++){
//       csvGravador << catalagoLido->nome[grt] <<";";
//    }
    csvGravador << "\n";
    csvGravador << "\n";
    csvGravador << "\n";

    double duracao=0;
    csvGravador << "time" << ";" << "Categories"<< ";" << "Duration(s)" << "\n";

    for(int ka1=0; ka1< etografiaLida->frameInicial.size(); ka1++){

        csvGravador << conPontoVirgula(etografiaLida->frameInicial[ka1] / videoLido->fps);
        //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

        csvGravador << ";";
        csvGravador << catalagoLido->nome[etografiaLida->id[ka1]];
        csvGravador << ";";

        duracao= etografiaLida->frameFinal[ka1]- etografiaLida->frameInicial[ka1];
        csvGravador <<conPontoVirgula( duracao / videoLido->fps);
        csvGravador << "\n";

    }



//    csvGravador <<"\n";
//    csvGravador <<"\n";
//    csvGravador <<"As totalizacoes do time budge";
    for(int tot=0; tot< totalizacaoTot.size(); tot++){

        //csvGravador <<  "RESULTS FOR THE ENTIRE PERIOD of ANALYSIS \n\n";




      csvGravador <<"\n RESULTS FOR \n Segmentation initiated at ;"<<  conPontoVirgula( totalizacaoTot[tot].inicioSessao/videoLido->fps) ;
      csvGravador << ";  Segmentation terminated at ;" << conPontoVirgula( totalizacaoTot[tot].finalSessao/videoLido->fps) <<"\n\n";
     // csvGravador << "categoria;duracao;frequencia;latencia \n";


      if(tot==0){

          csvGravador << "Category"<< ";" << "Duration(s)" << ";" <<"Freq."  << ";" << "Latency(s)" << "\n";
      }else{

          csvGravador << "Category"<< ";" << "Duration(s)" << ";" <<"Freq." << "\n";
      }

      for(int fr=0; fr< totalizacaoTot[tot].freq.size(); fr++){

          csvGravador<< catalagoLido->nome[fr]<<";" <<
                       conPontoVirgula( totalizacaoTot[tot].duracao[fr]/videoLido->fps) <<";"<<
                        conPontoVirgula(totalizacaoTot[tot].freq[fr]) <<";" ;
          if(tot==0){
              csvGravador <<conPontoVirgula(totalizacaoTot[tot].latencia[fr]/videoLido->fps) <<";\n";
          }else{

              csvGravador <<";\n";

          }

      }


    }




//    outGravador.write("O pesquisador foi o:, ");
//    outGravador.write(experimentador.nome.toLatin1()+"\n");
//    outGravador.write("a,b,c \n");
    outGravador.close();





}


//segmentao cade tempo
void parserXMLtoCSV::escreverSeqCsv()
{

    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador << "Informacoes do usuario\n";
    csvGravador <<"pesquisador ; laboratorio" << "\n";
    csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"\n";
    csvGravador <<"informacoes do video analisado: \n";
    csvGravador << "nome; fps; frame analisado inicial; frame analisado final \n";
    csvGravador << videoLido->nome<< "," << videoLido->fps << ";"
         << videoLido->frameInicial << "," << videoLido->frameFinal<< "\n";
    csvGravador <<"\n";
    csvGravador <<"informacoes do catalogo analisado: \n";
    csvGravador <<"O catalogo utilizado foi o " <<"," << catalagoLido->caminhoArquivo << "\n";
    csvGravador <<"categorias\n";
    for(int i=0; i< catalagoLido->nome.size(); i++ ){
       csvGravador << catalagoLido->nome[i]<< "\n";

    }
    csvGravador <<"\n";
    csvGravador <<"As analises etograficas utilizadas \n";
    csvGravador <<"id; caminho, tipo \n";
    for(int i=0; i< etografiasLidas.size();i++){

      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
    }
    csvGravador <<"\n";
    csvGravador <<"\n";

    //apartir daqui é diferente das outras analises
    csvGravador <<"A matriz de transição\n";
    csvGravador << "" <<";";
    for(int grt=0; grt< analiseSequencial.listaDados.size(); grt++){
       csvGravador << catalagoLido->nome[grt] <<";";
    }
    csvGravador << "\n";

    for(int tot=0; tot< analiseSequencial.listaDados.size(); tot++){
//      csvGravador <<"\n do frame inicial ; "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
//      csvGravador << "ate o frame final ; " << totalizacaoTot[tot].finalSessao <<"\n";

        csvGravador << catalagoLido->nome[tot] <<";";
      for(int fr=0; fr< analiseSequencial.listaDados.size(); fr++){


          csvGravador<< conPontoVirgula( analiseSequencial.listaDados[tot][fr]) <<";";
      }

        csvGravador << "\n";

    }



    //apartir daqui é diferente das outras analises
    csvGravador <<"As porcentagem da matrix de transição\n";
    csvGravador << "" <<";";
    for(int grt=0; grt< analiseSequencial.listaDadosPorcentagem.size(); grt++){
       csvGravador << catalagoLido->nome[grt] <<";";
    }
    csvGravador << "\n";

    for(int tot=0; tot< analiseSequencial.listaDadosPorcentagem.size(); tot++){
//      csvGravador <<"\n do frame inicial ; "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
//      csvGravador << "ate o frame final ; " << totalizacaoTot[tot].finalSessao <<"\n";

        csvGravador << catalagoLido->nome[tot] <<";";
      for(int fr=0; fr< analiseSequencial.listaDadosPorcentagem.size(); fr++){


          csvGravador<< conPontoVirgula( analiseSequencial.listaDadosPorcentagem[tot][fr]) <<";";
      }

        csvGravador << "\n";

    }




//    outGravador.write("O pesquisador foi o:, ");
//    outGravador.write(experimentador.nome.toLatin1()+"\n");
//    outGravador.write("a,b,c \n");
    outGravador.close();

}

//void parserXMLtoCSV::lerKohoXml()
//{

//}

void parserXMLtoCSV::escreverKohoCsv()
{
    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador << "Informacion about the user\n";
    csvGravador <<"Researcher ; Laboratory" << "\n";
    csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"\n";
    csvGravador <<"The information of analysed videos: \n";
    csvGravador << "Name; Frames per second (fps); Frame started the analysis; Frame finished the analysis \n";
    csvGravador << videoLido->nome<< ";" << videoLido->fps << ";"
         << videoLido->frameInicial << ";" << videoLido->frameFinal<< "\n";
    csvGravador <<"\n";
    csvGravador <<"The information of catalogue: \n";
    csvGravador <<"The catalogue used in etography are: " <<";" << catalagoLido->caminhoArquivo << "\n";
    csvGravador <<"Categories\n";
    for(int i=0; i< catalagoLido->nome.size(); i++ ){
       csvGravador << catalagoLido->nome[i]<< "\n";

    }
    csvGravador <<"\n";
    csvGravador <<"The etographys used in the Cohen's Kappa analyses are \n";
    csvGravador <<"Id; Path; Type \n";
    for(int i=0; i< etografiasLidas.size();i++){

      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
    }
    csvGravador <<"\n";
    csvGravador <<"\n";

    //apartir daqui é diferente das outras analises
    csvGravador <<"The agreement matriz of Cohen's Kappa are\n";
    csvGravador << "" <<";";


    for(int grt=0; grt< KohoKappa.cohoKappaMatrix.size(); grt++){
       csvGravador << catalagoLido->nome[grt] <<";";
    }
    csvGravador << "\n";

    for(int tot=0; tot< KohoKappa.cohoKappaMatrix.size(); tot++){
//      csvGravador <<"\n do frame inicial , "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
//      csvGravador << "ate o frame final , " << totalizacaoTot[tot].finalSessao <<"\n";

        csvGravador << catalagoLido->nome[tot] <<";";
      for(int fr=0; fr< KohoKappa.cohoKappaMatrix.size(); fr++){


          csvGravador<< conPontoVirgula(KohoKappa.cohoKappaMatrix[tot][fr]) <<";";
      }

        csvGravador << "\n";

    }

    csvGravador <<"The agreement porcentage matriz of Cohen's Kappa are: \n";
    csvGravador << "" <<";";


    for(int grt=0; grt< KohoKappa.cohoKappaPorMatrix.size(); grt++){
       csvGravador << catalagoLido->nome[grt] <<";";
    }
    csvGravador << "\n";

    for(int tot=0; tot< KohoKappa.cohoKappaPorMatrix.size(); tot++){
//      csvGravador <<"\n do frame inicial ; "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
//      csvGravador << "ate o frame final ; " << totalizacaoTot[tot].finalSessao <<"\n";

        csvGravador << catalagoLido->nome[tot] <<";";
      for(int fr=0; fr< KohoKappa.cohoKappaPorMatrix.size(); fr++){


          csvGravador<< conPontoVirgula(KohoKappa.cohoKappaPorMatrix[tot][fr]) <<";";
      }

        csvGravador << "\n";

    }
     csvGravador << "\n";
      csvGravador << "\n";
       csvGravador << "The final result are\n";

    csvGravador <<"The agreement porcentage (k1) are ; " << conPontoVirgula(  KohoKappa.k1 *100) <<" (%)\n" ; // A porcentagem de concordancia
    csvGravador <<"The agreement porcentage by chance (k2) are ; " << conPontoVirgula(KohoKappa.k2 *100) <<"(%)\n" ;//A porcentagem de concordancai por acaso
    csvGravador <<"The Cohen's Kappa; " <<conPontoVirgula(KohoKappa.kappa *100) <<"\n" ;

//    outGravador.write("O pesquisador foi o:, ");
//    outGravador.write(experimentador.nome.toLatin1()+"\n");
//    outGravador.write("a,b,c \n");
    outGravador.close();
}

//void parserXMLtoCSV::lerFleissXml()
//{

//}

void parserXMLtoCSV::escreverFleisCsv()
{

    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador << "The user information\n";
    csvGravador <<"Researcher ; Laboratory" << "\n";
    csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"\n";
    csvGravador <<"Information about the analysed video: \n";
    csvGravador << "Name; Frames per second (fps); Frame started the analysis; Frame finished the analysis \n";
    csvGravador << videoLido->nome<< ";" << videoLido->fps << ";"
         << videoLido->frameInicial << ";" << videoLido->frameFinal<< "\n";
    csvGravador <<"\n";
    csvGravador <<"Information of the catalog: \n";
    csvGravador <<"Path of the used catalog are in: " <<";" << catalagoLido->caminhoArquivo << "\n";
    csvGravador <<"Categories\n";
    for(int i=0; i< catalagoLido->nome.size(); i++ ){
       csvGravador << catalagoLido->nome[i]<< "\n";

    }
    csvGravador <<"\n";
    csvGravador <<"The ethographys analised\n";
    csvGravador <<"Id; Path; Type \n";
    for(int i=0; i< etografiasLidas.size();i++){

      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
    }
    csvGravador <<"\n";
    csvGravador <<"\n";

    //apartir daqui é diferente das outras analises
    csvGravador <<"The total of the Fleiss Kappa analysis\n";
    csvGravador << "" <<";";
    for(int grt=0; grt< catalagoLido->nome.size(); grt++){
       csvGravador << catalagoLido->nome[grt] <<";";
    }
    csvGravador << "Undefined (frames that are not marked)"<<";";
    csvGravador << "\n";

    for(int tot=0; tot< flKaDa.matrizConcordancia.size(); tot++){
//      csvGravador <<"\n do frame inicial , "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
//      csvGravador << "ate o frame final , " << totalizacaoTot[tot].finalSessao <<"\n";

        csvGravador << tot <<";";
      for(int fr=0; fr< flKaDa.matrizConcordancia[tot].size(); fr++){


          csvGravador<< conPontoVirgula( flKaDa.matrizConcordancia[tot][fr]) <<";";
      }

        csvGravador << "\n";

    }

//    csvGravador << "somatorio" <<",";
//  for(int fr=0; fr< flKaDa.somatorio.size(); fr++){


//      csvGravador<< flKaDa.somatorio[fr] <<",";
//  }
//  csvGravador << "\n";

//  csvGravador << "pi" <<",";
//for(int fr=0; fr< flKaDa.pi.size(); fr++){


//    csvGravador<< flKaDa.pi[fr] <<",";
//}
//csvGravador << "\n";


     csvGravador << "\n";
      csvGravador << "\n";
       csvGravador << "The final result are\n";

    csvGravador <<"The agreement porcentage by change (p) are: ; " <<flKaDa.p <<"\n" ; //A porcentagem de concordancia por acaso (p)
    csvGravador <<"The mean agreement pocentage (pe) aer: ; " <<flKaDa.pe <<"\n" ; //A porcentagem de concordância média
    csvGravador <<"The Fleiss Kappa :; " <<flKaDa.indiceFleissKappa <<"\n" ;




//    outGravador.write("O pesquisador foi o:, ");
//    outGravador.write(experimentador.nome.toLatin1()+"\n");
//    outGravador.write("a,b,c \n");
    outGravador.close();





}

QString parserXMLtoCSV::conPontoVirgula(double num)
{
    QByteArray numeroArray,numeroArraySaida;
    numeroArray = QByteArray::number(num);
    numeroArraySaida =numeroArray;


    numeroArraySaida.replace(QByteArray("."),QByteArray(","));
    return  QString::fromLatin1( numeroArraySaida);


}

void parserXMLtoCSV::escreverEtografiaCsv()
{
    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador <<"EthoWatcher Open Source \n";
    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"Experiment" << "\n";
    csvGravador <<"Animal" << "\n";
    csvGravador <<"Weight" << "\n";
    csvGravador <<"sex" << "\n";
    csvGravador <<"Treatment/condition" << "\n";
    csvGravador <<"Other Info" << "\n";
    //csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"WARNING: in this version, decimals are separated by COMMA \n";
//    csvGravador <<"video file \n";

    csvGravador << "ETHOGRAPHY REPORT" << "\n";
////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
    csvGravador << "Registred video file are locate in " << videoLido->nome<< "\n";

    csvGravador << "Analysis initiated at " << conPontoVirgula( videoLido->frameProce /videoLido->fps)  << " (seconds) of the video file \n ";
    csvGravador << "Analysis terminated at " << conPontoVirgula(videoLido->frameFinal / videoLido->fps) << " (seconds) of the video file \n";
    csvGravador <<"\n";
//    csvGravador <<"informacoes do catalogo analisado: \n";
    csvGravador <<"The selected catalog are : " <<";" << catalagoLido->caminhoArquivo << "\n";
//    csvGravador <<"categorias\n";
//    for(int i=0; i< catalagoLido->nome.size(); i++ ){
//       csvGravador << catalagoLido->nome[i]<< "\n";

//    }
//    csvGravador <<"\n";
//    csvGravador <<"A analise etografica utilizada \n";
//    csvGravador <<"id, caminho, tipo \n";
//    for(int i=0; i< etografiasLidas.size();i++){

//      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
//    }
//    csvGravador <<"\n";
//    csvGravador <<"\n";

    //apartir daqui é diferente das outras analises
//    csvGravador <<"As totalizacoes da analise sequencial\n";
//    csvGravador << "" <<";";
//    for(int grt=0; grt< catalagoLido->nome.size(); grt++){
//       csvGravador << catalagoLido->nome[grt] <<";";
//    }
    csvGravador << "\n";
    csvGravador << "\n";
    csvGravador << "\n";

    double duracao=0;
    csvGravador << "Time (s)" << ";" << "Categories"<< ";" << "Duration(s)" << "\n";

    for(int ka1=0; ka1< etografiaLida->frameInicial.size(); ka1++){

        csvGravador << conPontoVirgula(etografiaLida->frameInicial[ka1] / videoLido->fps);
        //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

        csvGravador << ";";
        csvGravador << catalagoLido->nome[etografiaLida->id[ka1]];
        csvGravador << ";";

        duracao= etografiaLida->frameFinal[ka1]- etografiaLida->frameInicial[ka1];
        csvGravador <<conPontoVirgula( duracao / videoLido->fps);
        csvGravador << "\n";

    }

    csvGravador <<  "RESULTS FOR THE ENTIRE PERIOD of ANALYSIS \n\n";

    csvGravador << "Category"<< ";" << "Duration(s)" << ";" <<"Freq."  << ";" << "Latency(s)" << "\n";

    for(int ka2=0; ka2< catalagoLido->nome.size(); ka2++){
        csvGravador << catalagoLido->nome[ka2] << ";"
                     << conPontoVirgula(vetorDuracao[ka2])<< ";"
                     << conPontoVirgula(vetorFrequencia[ka2])<< ";"
                     << conPontoVirgula(vetorLatencia[ka2]) << ";" ;
        csvGravador << "\n";
    }

    outGravador.close();



}

void parserXMLtoCSV::escreverTrakinCsv()
{


 for(int ki=0; ki< matrizReMorfo.size() ; ki++){

     QByteArray nomeArquivoByte;
     nomeArquivoByte= nomeArquivoGravarCsv.toLatin1();
     int numero = nomeArquivoByte.lastIndexOf(".");
     nomeArquivoByte.insert(numero,QString::number(ki)+ areasDeInteresse.figName[ki]);

     //prepend(ki);
     outGravador.setFileName(QString::fromLatin1(nomeArquivoByte));

    //outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    if(outGravador.isOpen()){
        qDebug() << "foi aberto o gravado csv para o traking";
    }

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador <<"EthoWatcher Open Source \n";
    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"Experiment" << "\n";
    csvGravador <<"Animal" << "\n";
    csvGravador <<"Weight" << "\n";
    csvGravador <<"sex" << "\n";
    csvGravador <<"Treatment/condition" << "\n";
    csvGravador <<"Other Info" << "\n";
    //csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"WARNING: in this version, decimals are separated by COMMA \n";
//    csvGravador <<"video file \n";

    csvGravador << "TRACKING - ACTIVITY REPORT" << "\n";
////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
    csvGravador << "Registred video file are locate in " << videoLido->nome<< "\n";
    csvGravador << "Start in ;" << conPontoVirgula( videoLido->frameProce / videoLido->fps) << ";" << "seconds ;" << videoLido->frameProce << "; frames "  "\n";
    csvGravador << "End in ;" << conPontoVirgula( videoLido->frameFinal / videoLido->fps )<< ";" << "seconds ;" << videoLido->frameFinal << "; frames "  "\n";
//    csvGravador << "Analysis initiated at " << conPontoVirgula( videoLido->frameProce /videoLido->fps)  << " (seconds) of the video file \n ";
//    csvGravador << "Analysis terminated at " << conPontoVirgula(videoLido->frameFinal / videoLido->fps) << " (seconds) of the video file \n";
    csvGravador << "1 cm = ;" << conPontoVirgula( videoLido->escala) << ";" << " pixeis\n";
    csvGravador << "1 pixel= " << conPontoVirgula(1/(videoLido->escala * videoLido->escala)) << "cm2";
    csvGravador <<"\n";
    csvGravador << "Figure Name ;" << areasDeInteresse.figName[ki]<< "\n";
    csvGravador << "Figure Tipe ;" << areasDeInteresse.tipoArea[ki] << "\n";
    csvGravador << "Figure Beginning at Vertical pixel ;" << areasDeInteresse.centX[ki] << "\n";
    csvGravador << "Figure Beginning at Horizontal pixel ;" << areasDeInteresse.centY[ki] << "\n";

    if(areasDeInteresse.tipoArea[ki]=="Circle"){

        csvGravador << "Figure Raio; " << areasDeInteresse.width[ki]<< "\n";


    }else{
         csvGravador << "Figure Height; " << areasDeInteresse.heigth[ki]<< "\n";
         csvGravador << "Figure Width; " << areasDeInteresse.width[ki]<< "\n";

    }


//    csvGravador << "Figure Tipe ;" << areasDeInteresse.tipoArea[ki] << "\n";
//    csvGravador << "Figure Tipe ;" << areasDeInteresse.tipoArea[ki] << "\n";
    //csvGravador << "Figure Name ;" << areasDeInteresse.tipoArea[ki];


//    csvGravador <<"informacoes do catalogo analisado: \n";
   // csvGravador <<"O catalogo utilizado foi o " <<";" << catalagoLido->caminhoArquivo << "\n";
//    csvGravador <<"categorias\n";
//    for(int i=0; i< catalagoLido->nome.size(); i++ ){
//       csvGravador << catalagoLido->nome[i]<< "\n";

//    }
//    csvGravador <<"\n";
//    csvGravador <<"A analise etografica utilizada \n";
//    csvGravador <<"id, caminho, tipo \n";
//    for(int i=0; i< etografiasLidas.size();i++){

//      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
//    }
//    csvGravador <<"\n";
//    csvGravador <<"\n";

    //apartir daqui é diferente das outras analises
//    csvGravador <<"As totalizacoes da analise sequencial\n";
//    csvGravador << "" <<";";
//    for(int grt=0; grt< catalagoLido->nome.size(); grt++){
//       csvGravador << catalagoLido->nome[grt] <<";";
//    }
    csvGravador << "\n";
    csvGravador << "\n";
    csvGravador << "\n";

    double duracao=0;
    //csvGravador << "Time (s)" << ";" << "Categories"<< ";" << "Duration(s)" << "\n";

   //asdasd  for(int ki=0; ki< matrizReMorfo.size() ; ki++){
        csvGravador << "\n";
        csvGravador << "\n";
        csvGravador << "\n";



        csvGravador <<  ";"      <<    ";"    << "Number of pixels;"     << "Area (in cm2);";
        csvGravador <<  "Horizontal coordinate of the centroid;"      <<    "Vertical coordinate of the centroid;";
        csvGravador <<  "AA(in degrees);" <<"Height of the animal;" <<"Width of the animal;" <<"Object Detected;" ;
        csvGravador << "Distance travelled by the centroid;" << "Distance travelled by the centroid;";
        csvGravador << "Variation of Area (from the former frame);";
        csvGravador << "Variation of Height of animal (from the former frame);";
        csvGravador << "Variation of width of animal (from the former frame);";
        csvGravador << "Variation of Angule of animal;";
        csvGravador << "Intrinsic noise (minimum variation distance traveled by the centroid)" << "\n";


        //a area de intesse 0 é sempre a altura e largura da imagem original;

        csvGravador << "frames;" << "second;" << "of the animal's body;" << "of the animal's body;";
        csvGravador << "(in pixels, from" << "0 to "<< areasDeInteresse.width[0] <<  " );" << "(in pixels, from " <<  "0 to " << areasDeInteresse.heigth[0] << " );";
        csvGravador <<  "Angle between animal and Horizontal coordinate ;" << "in cm;" << "in cm;" <<"true or false;" ;
        csvGravador << "(in pixels);" << "(in cm);";
        csvGravador << "in cm2;";
        csvGravador << "in cm;";
        csvGravador << "in cm;";
        csvGravador << "in degrees;" ;
        csvGravador << "true or false" << "\n";


        for(int kj=0; kj<   matrizReMorfo[ki].area.size(); kj++){
           // csvGravador << "aaaaa \n";
            csvGravador <<  matrizReMorfo[ki].frame[kj] << ";"<< conPontoVirgula((matrizReMorfo[ki].frame[kj] ) / videoLido->fps) << ";" ;
            csvGravador << conPontoVirgula(matrizReMorfo[ki].area[kj]) << ";" << conPontoVirgula(matrizReMorfo[ki].area[kj]/(videoLido->escala*videoLido->escala))<< ";";
            csvGravador << conPontoVirgula(matrizReMorfo[ki].centroidX[kj]) << ";" << conPontoVirgula(matrizReMorfo[ki].centroidY[kj])<<";";
            csvGravador << conPontoVirgula(matrizReMorfo[ki].anguloObj[kj]) << ";" ;
            csvGravador << conPontoVirgula(matrizReMorfo[ki].altura[kj]/(videoLido->escala)) << ";" ;
            csvGravador << conPontoVirgula(matrizReMorfo[ki].largura[kj]/(videoLido->escala)) << ";" ;
//            reMorfo.tamanhoObj

           if( matrizReMorfo[ki].objetoEncontrado[kj]){
               csvGravador << "true;";
           }else{
               csvGravador << "false;";
           }
           csvGravador << conPontoVirgula(matrizReCinema[ki].varDistancia[kj]) << ";" << conPontoVirgula(matrizReCinema[ki].varDistancia[kj]/(videoLido->escala))<< ";";
           csvGravador << conPontoVirgula(matrizReCinema[ki].varArea[kj]/(videoLido->escala*videoLido->escala) ) << ";" ;
           csvGravador << conPontoVirgula(matrizReCinema[ki].varAltura[kj]/(videoLido->escala) ) << ";" ;
           csvGravador << conPontoVirgula(matrizReCinema[ki].varLargura[kj]/(videoLido->escala) ) << ";" ;
           csvGravador << conPontoVirgula(matrizReCinema[ki].varAngular[kj] ) << ";" ;


           if( matrizReCinema[ki].ruidoMaxVaria[kj] ){
                  csvGravador << "true;";
        }else{

               csvGravador << "false;";

           }

           //reCinema.ruidoMaxVaria
//reCinema.varTamObjeto
//reCinema.varArea
           //

//           reCinema.varAngular.push_back(streamReader.attributes().value("Van").toDouble());
//           reCinema.varArea.push_back(streamReader.attributes().value("Var").toDouble());
//           reCinema.varDistancia.push_back(streamReader.attributes().value("Vd").toDouble());
//           reCinema.varTamObjeto.push_back(streamReader.attributes().value("VtoP").toDouble());



            csvGravador << "\n";

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

//            csvGravador << conPontoVirgula(etografiaLida->frameInicial[ka1] / videoLido->fps);
//            //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

//            csvGravador << ";";
//            csvGravador << catalagoLido->nome[etografiaLida->id[ka1]];
//            csvGravador << ";";

//            duracao= etografiaLida->frameFinal[ka1]- etografiaLida->frameInicial[ka1];
//            csvGravador <<conPontoVirgula( duracao / videoLido->fps);
//



        }



        outGravador.close();

    }










}
