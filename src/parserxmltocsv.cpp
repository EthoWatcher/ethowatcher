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

void parserXMLtoCSV::converteArquivo(QString nomePath, QList<QList<Cell> > ls_gravar)
{

    //    fonteCaminhoArquivo = QFileDialog::getOpenFileName(
    //                this,
    //                tr("Open File"),
    //               "C://ethowatcher",
    //               "Arquivos do Ethowatcher (*.aseq *.fkf *.kkf *.tbf *.etoxml *.tkin )"
    //                );

    fonteCaminhoArquivo = nomePath;
//    //    cabecalho_str = cabecalho;

      qDebug() << "entrou " << fonteCaminhoArquivo;
//    QList<Cell> saida;

    if(!fonteCaminhoArquivo.isEmpty()){

        output.setFileName( fonteCaminhoArquivo);

        fonteVideoBit = fonteCaminhoArquivo.toLatin1();

        QStringList myStringList = fonteCaminhoArquivo.split('.');
        auto fonteVideoBitExt =myStringList.last();
        qDebug() << fonteVideoBitExt;
        fonteVideoBit = QByteArray::fromStdString(fonteVideoBitExt.toStdString());

//        int i= fonteVideoBit.length();
//        int inicio=0;
//        //aquirir a extensão do arquivo
//        while(fonteVideoBit[i] != 46){
//            i--;
//            fonteVideoBitExtInv[inicio]= fonteVideoBit[i];
//            inicio++;
//        }


//        //desinverter a extensão do arquivo

//        int j=0;
//        while(fonteVideoBitExtInv[j] != 0){
//            fonteVideoBitExt[j]=fonteVideoBitExtInv[fonteVideoBitExtInv.length()-1-j];
//            j++;

//        }



        if(fonteVideoBitExt=="tbf"){
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
        if(fonteVideoBitExt=="aseq"){
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
        if(fonteVideoBitExt=="kkf"){
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

        if(fonteVideoBitExt=="fkf"){
            lerTimeXml(0); //le o experimentador
            lerTimeXml(1); //le o catalago
            lerTimeXml(2); //le os dados do video
            lerTimeXml(3); //le os dados do video
            lerTimeXml(7); //le o fleiss kappa
            //         escreverFleisCsv();
            //manda para a função de ler esse video
        }

        if(fonteVideoBitExt=="etoxml"){




            lerETOXML(fonteCaminhoArquivo);

            totalizacoesEtografia();


        }

        if(fonteVideoBitExt=="tkin"){


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


//        int lugar = fonteVideoBit.lastIndexOf("/");

//        //encontra o nome do arquivo do user
        QByteArray nomeArquivoUser = QByteArray::fromStdString(fonteCaminhoArquivo.toStdString());
        nomeArquivoUser.replace(QByteArray("."),QByteArray("_"));

        //        //encontra o cmainho
        //        QByteArray caminho = fonteVideoBit;
        //        caminho.truncate(lugar);

        //        //QByteArray nomeArquivo =

        //        qDebug() << fonteVideoBit ;
        //        qDebug() << fonteVideoBit.lastIndexOf("/");
        //        qDebug() << caminho;
        //        qDebug() << nomeArquivoUser;

        //        QByteArray finalCSV = caminho+nomeArquivoUser+"_";
        //        qDebug() << finalCSV;


        //qDebug() << novoArquivo;

//        QByteArray finalCSV = caminho + nomeArquivoUser + "_";
//        nomeArquivoGravarCsv= QString::fromLatin1(finalCSV); //"C:/ethowatcher/lalal.csv";
        nomeArquivoGravarCsv =  QString::fromStdString(nomeArquivoUser.toStdString()); //nomeArquivoGravarCsv + "_xlsx.xlsx";
        qDebug() << nomeArquivoGravarCsv;

        //gravando os files
        if(fonteVideoBitExt=="tbf"){

            escreverTimeCsv(ls_gravar);


        }
        if(fonteVideoBitExt=="aseq"){
            escreverSeqCsv(ls_gravar);
        }

        if(fonteVideoBitExt=="kkf"){
            escreverKohoCsv();
        }

        if(fonteVideoBitExt=="fkf"){
            escreverFleisCsv();
        }


        if(fonteVideoBitExt=="etoxml"){

            //encontrando a f d l

            escreverEtografiaCsv(ls_gravar);
        }

        if(fonteVideoBitExt=="tkin"){

            qDebug() <<" trakin sendo gravado";



            escreverTrakinCsv(ls_gravar);
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

        if(streamReader.name().toString() == "analise"){

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


        if(streamReader.name().toString() == "categoria"){

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

        if(streamReader.name().toString() == "nomeCaminhoExt"){

            catalagoLido->caminhoArquivo= streamReader.readElementText();


        }

        if(streamReader.name().toString() == "tipoAnalise"){

            catalagoLido->tipoAnalise= streamReader.readElementText();


        }

//        if((streamReader.name() == "dadosVideoAnalisado")||(videoLido->controle)){


          if(streamReader.name().toString() == "nomeVxml"){

              videoLido->nome= streamReader.readElementText();

          }

          if(streamReader.name().toString() == "frameInicial"){


              videoLido->frameInicial= streamReader.readElementText().toDouble();

          }

          if(streamReader.name().toString() == "frameProces"){


              videoLido->frameProce= streamReader.readElementText().toDouble();

          }

          if(streamReader.name().toString() == "frameFinal"){
           videoLido->frameFinal= streamReader.readElementText().toDouble();

            //videoLido->controle=false;
        }

          if(streamReader.name().toString() == "fps"){
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

//        }




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


        if(xmlReader.name().toString()== "nomeAnalisador"){
        experimentador.nome= xmlReader.readElementText();
           //qDebug() << xmlReader.readElementText();

        }


           if(xmlReader.name().toString()== "laboratorio"){
         experimentador.lab= xmlReader.readElementText();
              // qDebug() << xmlReader.readElementText();
           }

        }
    }



    if(qualLer==1){ //dadosCatalago
    bool entrou=false;

        while(!xmlReader.atEnd() && !xmlReader.hasError()){

        xmlReader.readNext();


        if(xmlReader.name().toString()== "dadosCatalagoUsado"){
            entrou=~entrou;
        }


        if(entrou==true){

            if(xmlReader.name().toString()== "caminhoCatalago"){

                catalagoLido->caminhoArquivo= xmlReader.readElementText();

            }

            if(xmlReader.name().toString()== "categoria"){
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


        if(xmlReader.name().toString()== "dadosVideosUsados"){
            entrou=~entrou;
        }


        if(entrou==true){

            if(xmlReader.name().toString()== "caminhoVideo"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){
            videoLido->nome= conversor;
            }}
            if(xmlReader.name().toString()== "frameInicial"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameInicial= conversor.toDouble();
            }}
            if(xmlReader.name().toString()== "frameProces"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameProce= conversor.toDouble();
            }}
            if(xmlReader.name().toString()== "frameFinal"){
            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
            videoLido->frameFinal= conversor.toDouble();
            }}
            if(xmlReader.name().toString()== "fps"){
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


        if(xmlReader.name().toString()== "analises"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){


            if(xmlReader.name().toString()== "categoria"){
            QString conversor= xmlReader.attributes().value("tipo").toString();
            if(!conversor.isEmpty()){
            etografiaLida->tipoDeAnalise= conversor;
            }else{

              etografiasLidas.push_back(etografiaLida);

            }

            }
            if(xmlReader.name().toString()== "caminhoAnaliseEto"){

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


        if(xmlReader.name().toString()== "sessoes"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }


        if(entrou==true){


            if(xmlReader.name().toString()== "sessao"){
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

            if(xmlReader.name().toString()== "duracao"){

            QString conversorlal= xmlReader.readElementText();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                totalizacao1.duracao.push_back( conversorlal.toDouble());
            }

            }

            if(xmlReader.name().toString()== "frequencia"){

            QString conversor= xmlReader.readElementText();
            if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag

                totalizacao1.freq.push_back(conversor.toDouble());
            }

            }

            if(xmlReader.name().toString()== "latencia"){

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


        if(xmlReader.name().toString()== "sessoes"){
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

            if(xmlReader.name().toString()== "categoria"){

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

            if(xmlReader.name().toString()== "caAnaSeg"){

            QString conversorlal= xmlReader.attributes().value("quant").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                analiseSequencial.dados.push_back( conversorlal.toInt());
            }

            }


        }

        if(xmlReader.name().toString()== "sessaoPorce"){
            if(entrouPorce==true){
                entrouPorce=false;
            }else{
                entrouPorce=true;
            }
        }



        if(entrouPorce==true){


            if(xmlReader.name().toString()== "caAnaSegPorce"){

            QString conversorlal= xmlReader.attributes().value("quant").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                analiseSequencial.dadosPorce.push_back( conversorlal.toDouble());
            }

            }



            if(xmlReader.name().toString()== "categoriaPorce"){

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


        if(xmlReader.name().toString()== "tabelaConcordancia"){
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

            if(xmlReader.name().toString()== "categoriaKK"){

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

            if(xmlReader.name().toString()== "caAnaSeg"){

            QString conversorlal= xmlReader.attributes().value("quant").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                KohoKappa.cohoKappa.push_back( conversorlal.toInt());
            }

            }





        }

        if(xmlReader.name().toString()== "tabelaPorcentagem"){
            if(entrou1==true){
                entrou1=false;
            }else{
                entrou1=true;
            }
        }


        if(entrou1==true){



            if(xmlReader.name().toString()== "categoriaKK"){

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

            if(xmlReader.name().toString()== "caAnaSeg"){

            QString conversorlal= xmlReader.attributes().value("porcent").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                KohoKappa.cohoKappaPor.push_back( conversorlal.toFloat());
            }

            }


        }



        if(xmlReader.name().toString()== "k1"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            KohoKappa.k1= conversor.toFloat();
        }
        }
        if(xmlReader.name().toString()== "k2"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            KohoKappa.k2= conversor.toFloat();
        }
        }
        if(xmlReader.name().toString()== "indiceKohoneKappa"){
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


        if(xmlReader.name().toString()== "analise"){
            if(entrou==true){
                entrou=false;
            }else{
                entrou=true;
            }
        }

        if(xmlReader.name().toString()== "tabelaSomatorio"){
            if(entrou1==true){
                entrou1=false;
            }else{
                entrou1=true;
            }
        }

        if(xmlReader.name().toString()== "pi"){
            if(entrou2==true){
                entrou2=false;
            }else{
                entrou2=true;
            }
        }




        if(entrou==true){


            if(xmlReader.name().toString()== "aFr"){

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

            if(xmlReader.name().toString()== "con"){

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

            if(xmlReader.name().toString()== "con"){

            QString conversorlal= xmlReader.attributes().value("q").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                flKaDa.somatorio.push_back( conversorlal.toInt());
            }
            }

        }

        if(entrou2==true){

            if(xmlReader.name().toString()== "con"){

            QString conversorlal= xmlReader.attributes().value("q").toString();
            if(!conversorlal.isEmpty()){//ele acaba entrando daus vez pra cada tag
                flKaDa.pi.push_back( conversorlal.toInt());
            }
            }

        }



        if(xmlReader.name().toString()== "Pe"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            flKaDa.pe= conversor.toFloat();
        }
        }
        if(xmlReader.name().toString()== "P"){
        QString conversor= xmlReader.readElementText();
        if(!conversor.isEmpty()){
            flKaDa.p= conversor.toFloat();
        }
        }
        if(xmlReader.name().toString()== "indiceFleissKappa"){
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

        if(xmlReader.name().toString() == "analise"){

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
void parserXMLtoCSV::escreverTimeCsv(QList<QList<Cell> > ls_gravar)
{

////    outGravador.setFileName(nomeArquivoGravarCsv);
////    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

////    QTextStream csvGravador(&outGravador);

//    csvGravador <<"sep=; \n";
//    csvGravador <<"EthoWatcher Open Source \n";
//    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
//    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";
//    csvGravador <<"Experiment" << "\n";
//    csvGravador <<"Animal" << "\n";
//    csvGravador <<"Weight" << "\n";
//    csvGravador <<"sex" << "\n";
//    csvGravador <<"Treatment/condition" << "\n";
//    csvGravador <<"Other Info" << "\n";
//    //csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
//    csvGravador <<"WARNING: in this version, decimals are separated by DOT(.) \n";
////    csvGravador <<"video file \n";

//    csvGravador << "ETHOGRAPHY REPORT" << "\n";
//////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
//    csvGravador << "video file is " << videoLido->nome<< "\n";

//    csvGravador << "Analysis initiated at " << videoLido->frameProce /videoLido->fps << " (seconds) of the video file \n ";
//    csvGravador << "Analysis terminated at " << videoLido->frameFinal / videoLido->fps << " (seconds) of the video file \n";
//    csvGravador <<"\n";
////    csvGravador <<"informacoes do catalogo analisado: \n";
//    csvGravador <<"O catalogo utilizado foi o " <<";" << catalagoLido->caminhoArquivo << "\n";
////    csvGravador <<"categorias\n";
////    for(int i=0; i< catalagoLido->nome.size(); i++ ){
////       csvGravador << catalagoLido->nome[i]<< "\n";

////    }
////    csvGravador <<"\n";
////    csvGravador <<"A analise etografica utilizada \n";
////    csvGravador <<"id, caminho, tipo \n";
////    for(int i=0; i< etografiasLidas.size();i++){

////      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
////    }
////    csvGravador <<"\n";
////    csvGravador <<"\n";

//    //apartir daqui é diferente das outras analises
////    csvGravador <<"As totalizacoes da analise sequencial\n";
////    csvGravador << "" <<";";
////    for(int grt=0; grt< catalagoLido->nome.size(); grt++){
////       csvGravador << catalagoLido->nome[grt] <<";";
////    }
//    csvGravador << "\n";
//    csvGravador << "\n";
//    csvGravador << "\n";

//    double duracao=0;
//    csvGravador << "time" << ";" << "Categories"<< ";" << "Duration(s)" << "\n";

//    for(int ka1=0; ka1< etografiaLida->frameInicial.size(); ka1++){

//        csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;
//        //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

//        csvGravador << ";";
//        csvGravador << catalagoLido->nome[etografiaLida->id[ka1]];
//        csvGravador << ";";

//        duracao= etografiaLida->frameFinal[ka1]- etografiaLida->frameInicial[ka1];
//        csvGravador << duracao / videoLido->fps;
//        csvGravador << "\n";

//    }



////    csvGravador <<"\n";
////    csvGravador <<"\n";
////    csvGravador <<"As totalizacoes do time budge";
//    for(int tot=0; tot< totalizacaoTot.size(); tot++){

//        //csvGravador <<  "RESULTS FOR THE ENTIRE PERIOD of ANALYSIS \n\n";




//      csvGravador <<"\n RESULTS FOR \n Segmentation initiated at ;"<<  totalizacaoTot[tot].inicioSessao/videoLido->fps ;
//      csvGravador << ";  Segmentation terminated at ;" << totalizacaoTot[tot].finalSessao/videoLido->fps <<"\n\n";
//     // csvGravador << "categoria;duracao;frequencia;latencia \n";


//      if(tot==0){

//          csvGravador << "Category"<< ";" << "Duration(s)" << ";" <<"Freq."  << ";" << "Latency(s)" << "\n";
//      }else{

//          csvGravador << "Category"<< ";" << "Duration(s)" << ";" <<"Freq." << "\n";
//      }

//      for(int fr=0; fr< totalizacaoTot[tot].freq.size(); fr++){

//          csvGravador<< catalagoLido->nome[fr]<<";" <<
//                        totalizacaoTot[tot].duracao[fr]/videoLido->fps <<";"<<
//                        totalizacaoTot[tot].freq[fr] <<";" ;
//          if(tot==0){
//              csvGravador <<totalizacaoTot[tot].latencia[fr]/videoLido->fps <<";\n";
//          }else{

//              csvGravador <<";\n";

//          }

//      }


//    }

//    QList<QList<Cell> > ls_gravar;
//    QList<Cell> saida;

//    int linha = 1;
//    add_cell(&saida, "A1", "EthoWatcher Open Source");

//    add_cell(&saida, "A2", "Observer");
//    add_cell(&saida, "B2", experimentador.nome.toLatin1());

//    add_cell(&saida, "A3", "Lab");
//    add_cell(&saida, "B3", experimentador.lab.toLatin1());

//    add_cell(&saida, "A4", "Experiment info");

//    add_cell(&saida, "A5", "Experiment");
//    add_cell(&saida, "B5", "Date");
//    add_cell(&saida, "C5", "Other Info");

//    // falta adicionar o cabeçalho.
//    //    add_cell(&saida, "A6", dado_experimento.tituloExperimento);
//    //    add_cell(&saida, "B6", dado_experimento.data);
//    //    add_cell(&saida, "C6", dado_experimento.otherInfo);

//    add_cell(&saida, "A7", "Animal Info");
//    add_cell(&saida, "A8", "Animal ID");
//    add_cell(&saida, "B8", "Weight");
//    add_cell(&saida, "C8", "Sex");

//    //    add_cell(&saida, "A9", dado_experimento.animalID);
//    //    add_cell(&saida, "B9", dado_experimento.wight);
//    //    add_cell(&saida, "C9", dado_experimento.animalSex);

//    //    add_cell(&saida, "A10", "Registred video file are locate in PRECISA
//    //    RESOLVER"); //+ nome_caminho_video);

//    add_cell(&saida, "A11",
//             "Analysis initiated at " +
//                 QString::number(videoLido->frameInicial / videoLido->fps) +
//                 " (seconds) of the video file");
//    add_cell(&saida, "A12",
//             "Analysis terminated at " +
//                 QString::number(videoLido->frameFinal / videoLido->fps) +
//                 " (seconds) of the video file");

//    add_cell(&saida, "A13",
//             "The selected catalog are : " + catalagoLido->caminhoArquivo);

//    //    ls_gravar.append(entrada);
//    ls_gravar.append(saida);

    QByteArray nomeArquivoByte;
    nomeArquivoByte= nomeArquivoGravarCsv.toLatin1();
//    int numero = nomeArquivoByte.lastIndexOf(".");
////    nomeArquivoByte.insert(numero+1, "_xlsx.xlsx");

    nomeArquivoByte = nomeArquivoByte + "_xlsx.xlsx";
    gravar_csv_ls_cell(nomeArquivoByte, ls_gravar);



//    outGravador.write("O pesquisador foi o:, ");
//    outGravador.write(experimentador.nome.toLatin1()+"\n");
//    outGravador.write("a,b,c \n");
//    outGravador.close();





}


//segmentao cade tempo
void parserXMLtoCSV::escreverSeqCsv(QList<QList<Cell> > ls_gravar)
{

//    QList<QList<Cell> > ls_gravar;
    QList<Cell> saida;

    int linha = 1;
    add_cell(&saida, "A1","EthoWatcher Open Source");

    add_cell(&saida, "A2","Observer");
    add_cell(&saida, "B2",experimentador.nome.toLatin1());

    add_cell(&saida, "A3","Lab");
    add_cell(&saida, "B3",experimentador.lab.toLatin1());

    add_cell(&saida, "A4","Experiment info");

    add_cell(&saida, "A5","Experiment");
    add_cell(&saida, "B5","Date");
    add_cell(&saida, "C5","Other Info");

    //falta adicionar o cabeçalho.
//    add_cell(&saida, "A6", dado_experimento.tituloExperimento);
//    add_cell(&saida, "B6", dado_experimento.data);
//    add_cell(&saida, "C6", dado_experimento.otherInfo);


    add_cell(&saida, "A7","Animal Info");
    add_cell(&saida, "A8","Animal ID");
    add_cell(&saida, "B8","Weight");
    add_cell(&saida, "C8","Sex");

//    add_cell(&saida, "A9", dado_experimento.animalID);
//    add_cell(&saida, "B9", dado_experimento.wight);
//    add_cell(&saida, "C9", dado_experimento.animalSex);

    //    add_cell(&saida, "A10", "Registred video file are locate in PRECISA
    //    RESOLVER"); //+ nome_caminho_video);

    add_cell(&saida, "A11", "Analysis initiated at " + QString::number( videoLido->frameInicial / videoLido->fps) + " (seconds) of the video file");
    add_cell(&saida, "A12", "Analysis terminated at " + QString::number( videoLido->frameFinal / videoLido->fps) + " (seconds) of the video file");

    add_cell(&saida, "A13", "The selected catalog are : " + catalagoLido->caminhoArquivo);

//    ls_gravar.append(entrada);
    ls_gravar.append(saida);


    QByteArray nomeArquivoByte;
    nomeArquivoByte= nomeArquivoGravarCsv.toLatin1();
//    int numero = nomeArquivoByte.lastIndexOf(".");
////    nomeArquivoByte.insert(numero+1, "_xlsx.xlsx");

    nomeArquivoByte = nomeArquivoByte + "_xlsx.xlsx";

    gravar_csv_ls_cell(nomeArquivoByte, ls_gravar);

//    outGravador.setFileName(nomeArquivoGravarCsv);
//    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

//    QTextStream csvGravador(&outGravador);

//    csvGravador <<"sep=; \n";
//    csvGravador << "Informacoes do usuario\n";
//    csvGravador <<"pesquisador ; laboratorio" << "\n";
//    csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
//    csvGravador <<"\n";
//    csvGravador <<"informacoes do video analisado: \n";
//    csvGravador << "nome; fps; frame analisado inicial; frame analisado final \n";
//    csvGravador << videoLido->nome<< "," << videoLido->fps << ";"
//         << videoLido->frameInicial << "," << videoLido->frameFinal<< "\n";
//    csvGravador <<"\n";
//    csvGravador <<"informacoes do catalogo analisado: \n";
//    csvGravador <<"O catalogo utilizado foi o " <<"," << catalagoLido->caminhoArquivo << "\n";
//    csvGravador <<"categorias\n";
//    for(int i=0; i< catalagoLido->nome.size(); i++ ){
//       csvGravador << catalagoLido->nome[i]<< "\n";

//    }
//    csvGravador <<"\n";
//    csvGravador <<"As analises etograficas utilizadas \n";
//    csvGravador <<"id; caminho, tipo \n";
//    for(int i=0; i< etografiasLidas.size();i++){

//      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
//    }
//    csvGravador <<"\n";
//    csvGravador <<"\n";

//    //apartir daqui é diferente das outras analises
//    csvGravador <<"A matriz de transição\n";
//    csvGravador << "" <<";";
//    for(int grt=0; grt< analiseSequencial.listaDados.size(); grt++){
//       csvGravador << catalagoLido->nome[grt] <<";";
//    }
//    csvGravador << "\n";

////    for(int tot=0; tot< analiseSequencial.listaDados.size(); tot++){
//////      csvGravador <<"\n do frame inicial ; "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
//////      csvGravador << "ate o frame final ; " << totalizacaoTot[tot].finalSessao <<"\n";

////        csvGravador << catalagoLido->nome[tot] <<";";
////      for(int fr=0; fr< analiseSequencial.listaDados.size(); fr++){


////          csvGravador<< analiseSequencial.listaDados[tot][fr] <<";";
////      }

////        csvGravador << "\n";

////    }



//    //apartir daqui é diferente das outras analises
//    csvGravador <<"As porcentagem da matrix de transição\n";
//    csvGravador << "" <<";";
//    for(int grt=0; grt< analiseSequencial.listaDadosPorcentagem.size(); grt++){
//       csvGravador << catalagoLido->nome[grt] <<";";
//    }
//    csvGravador << "\n";

//    for(int tot=0; tot< analiseSequencial.listaDadosPorcentagem.size(); tot++){
////      csvGravador <<"\n do frame inicial ; "<< totalizacaoTot[tot].inicioSessao <<"\n" ;
////      csvGravador << "ate o frame final ; " << totalizacaoTot[tot].finalSessao <<"\n";

//        csvGravador << catalagoLido->nome[tot] <<";";
//      for(int fr=0; fr< analiseSequencial.listaDadosPorcentagem.size(); fr++){


//          csvGravador<<  analiseSequencial.listaDadosPorcentagem[tot][fr] <<";";
//      }

//        csvGravador << "\n";

//    }




//    outGravador.write("O pesquisador foi o:, ");
//    outGravador.write(experimentador.nome.toLatin1()+"\n");
//    outGravador.write("a,b,c \n");
//    outGravador.close();
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


          csvGravador<< KohoKappa.cohoKappaMatrix[tot][fr] <<";";
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


          csvGravador<< KohoKappa.cohoKappaPorMatrix[tot][fr] <<";";
      }

        csvGravador << "\n";

    }
     csvGravador << "\n";
      csvGravador << "\n";
       csvGravador << "The final result are\n";

    csvGravador <<"The agreement porcentage (k1) are ; " <<  KohoKappa.k1 *100 <<" (%)\n" ; // A porcentagem de concordancia
    csvGravador <<"The agreement porcentage by chance (k2) are ; " << KohoKappa.k2 *100 <<"(%)\n" ;//A porcentagem de concordancai por acaso
    csvGravador <<"The Cohen's Kappa; " <<KohoKappa.kappa *100 <<"\n" ;

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


          csvGravador<<  flKaDa.matrizConcordancia[tot][fr] <<";";
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

void parserXMLtoCSV::escreverEtografiaCsv(QList<QList<Cell>> ls_gravar)
{
    QByteArray nomeArquivoByte;
    nomeArquivoByte = nomeArquivoGravarCsv.toLatin1();
//     int numero = nomeArquivoByte.lastIndexOf(".");
//        nomeArquivoByte = nomeArquivoByte + QString::number(ki).toLatin1() +
//                          areasDeInteresse.figName[ki].toLatin1();
//        //     nomeArquivoByte.insert(numero,QString::number(ki)+
    //     areasDeInteresse.figName[ki]);
    nomeArquivoByte = nomeArquivoByte + "_xlsx.xlsx";

//    QList<QList<Cell>> ls_gravar;
//    ls_gravar.append(entrada);

    gravar_csv_ls_cell(nomeArquivoByte, ls_gravar);


//    outGravador.setFileName(nomeArquivoGravarCsv);
//    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

//    QTextStream csvGravador(&outGravador);

//    csvGravador <<"sep=; \n";
//    csvGravador <<"EthoWatcher Open Source \n";
//    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
//    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";
//    csvGravador <<"Experiment" << "\n";
//    csvGravador <<"Animal" << "\n";
//    csvGravador <<"Weight" << "\n";
//    csvGravador <<"sex" << "\n";
//    csvGravador <<"Treatment/condition" << "\n";
//    csvGravador <<"Other Info" << "\n";
//    //csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
//    csvGravador <<"WARNING: in this version, decimals are separated by COMMA \n";
////    csvGravador <<"video file \n";

//    csvGravador << "ETHOGRAPHY REPORT" << "\n";
//////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
//    csvGravador << "Registred video file are locate in " << videoLido->nome<< "\n";

//    csvGravador << "Analysis initiated at " <<  videoLido->frameProce /videoLido->fps  << " (seconds) of the video file \n ";
//    csvGravador << "Analysis terminated at " << videoLido->frameFinal / videoLido->fps << " (seconds) of the video file \n";
//    csvGravador <<"\n";
////    csvGravador <<"informacoes do catalogo analisado: \n";
//    csvGravador <<"The selected catalog are : " <<";" << catalagoLido->caminhoArquivo << "\n";
////    csvGravador <<"categorias\n";
////    for(int i=0; i< catalagoLido->nome.size(); i++ ){
////       csvGravador << catalagoLido->nome[i]<< "\n";

////    }
////    csvGravador <<"\n";
////    csvGravador <<"A analise etografica utilizada \n";
////    csvGravador <<"id, caminho, tipo \n";
////    for(int i=0; i< etografiasLidas.size();i++){

////      csvGravador << i << ";" << etografiasLidas[i]->caminho << ";" << etografiasLidas[i]->tipoDeAnalise;
////    }
////    csvGravador <<"\n";
////    csvGravador <<"\n";

//    //apartir daqui é diferente das outras analises
////    csvGravador <<"As totalizacoes da analise sequencial\n";
////    csvGravador << "" <<";";
////    for(int grt=0; grt< catalagoLido->nome.size(); grt++){
////       csvGravador << catalagoLido->nome[grt] <<";";
////    }
//    csvGravador << "\n";
//    csvGravador << "\n";
//    csvGravador << "\n";

//    double duracao=0;
//    csvGravador << "Time (s)" << ";" << "Categories"<< ";" << "Duration(s)" << "\n";

//    for(int ka1=0; ka1< etografiaLida->frameInicial.size(); ka1++){

//        csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;
//        //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

//        csvGravador << ";";
//        csvGravador << catalagoLido->nome[etografiaLida->id[ka1]];
//        csvGravador << ";";

//        duracao= etografiaLida->frameFinal[ka1]- etografiaLida->frameInicial[ka1];
//        csvGravador << duracao / videoLido->fps;
//        csvGravador << "\n";

//    }

//    csvGravador <<  "RESULTS FOR THE ENTIRE PERIOD of ANALYSIS \n\n";

//    csvGravador << "Category"<< ";" << "Duration(s)" << ";" <<"Freq."  << ";" << "Latency(s)" << "\n";

//    for(int ka2=0; ka2< catalagoLido->nome.size(); ka2++){
//        csvGravador << catalagoLido->nome[ka2] << ";"
//                     << vetorDuracao[ka2]<< ";"
//                     << vetorFrequencia[ka2] << ";"
//                     << vetorLatencia[ka2] << ";" ;
//        csvGravador << "\n";
//    }

//    outGravador.close();



}

void parserXMLtoCSV::escreverTrakinCsv(QList<QList<Cell> > entrada)
{



 for(int ki=0; ki< matrizReMorfo.size() ; ki++){
     QList<QList<Cell> > ls_gravar;
     ls_gravar.append(entrada[0]);
     QList<Cell> saida;

     QByteArray nomeArquivoByte;
     nomeArquivoByte = nomeArquivoGravarCsv.toLatin1();
//     int numero = nomeArquivoByte.lastIndexOf(".");
     nomeArquivoByte = nomeArquivoByte + QString::number(ki).toLatin1() + areasDeInteresse.figName[ki].toLatin1();
//     nomeArquivoByte.insert(numero,QString::number(ki)+ areasDeInteresse.figName[ki]);
     nomeArquivoByte = nomeArquivoByte + "_xlsx.xlsx";
     //prepend(ki);
//     outGravador.setFileName(QString::fromLatin1(nomeArquivoByte));

//    //outGravador.setFileName(nomeArquivoGravarCsv);
//    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

//    if(outGravador.isOpen()){
//        qDebug() << "foi aberto o gravado csv para o traking";
//    }

//    QTextStream csvGravador(&outGravador);


      int linha = 16;





//      TRACKING - ACTIVITY REPORT
//      add_cell(&saida, "A1","EthoWatcher Open Source");
//    csvGravador <<cabecalho_str + "\n";

//    csvGravador <<"video file \n";

//    csvGravador << "TRACKING - ACTIVITY REPORT" << "\n";
////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
//    csvGravador << "Registred video file are location path " << videoLido->nome<< "\n";
//    csvGravador << "Transcription start : ;" <<  videoLido->frameProce / videoLido->fps << ";" << "seconds ;" << videoLido->frameProce << "; frames of the video file"  "\n";
//    csvGravador << "Transcription temintated in ;" <<  videoLido->frameFinal / videoLido->fps<< ";" << "seconds ;" << videoLido->frameFinal << "; frames "  "\n";
//    csvGravador << "Analysis initiated at " << conPontoVirgula( videoLido->frameProce /videoLido->fps)  << " (seconds) of the video file \n ";
//    csvGravador << "Analysis terminated at " << conPontoVirgula(videoLido->frameFinal / videoLido->fps) << " (seconds) of the video file \n";


    add_cell(&saida, "A"+QString::number(linha),
                        "1 mm =" +QString::number(videoLido->escala)+ " pixeis" );
    linha += 1;
    add_cell(&saida, "A"+QString::number(linha),
                        "1 pixel=" +QString::number(1/(videoLido->escala * videoLido->escala))+ " mm2" );
    linha += 1;
    add_cell(&saida, "A"+QString::number(linha),
                        "Area " +areasDeInteresse.figName[ki]);


//    csvGravador << "1 mm = ;" <<  videoLido->escala << ";" << " pixeis\n";
//    csvGravador << "1 pixel= ;" << 1/(videoLido->escala * videoLido->escala) << ";mm2";
//    csvGravador <<"\n";
//    csvGravador << "Area Name ;" << areasDeInteresse.figName[ki]<< "\n";
//    csvGravador << "Figure Tipe ;" << areasDeInteresse.tipoArea[ki] << "\n";
//    csvGravador << "Figure Beginning at Vertical pixel ;" << areasDeInteresse.centX[ki] << "\n";
//    csvGravador << "Figure Beginning at Horizontal pixel ;" << areasDeInteresse.centY[ki] << "\n";


     add_cell(&saida, "A"+QString::number(linha),"TRACKING - ACTIVITY REPORT");
    if(areasDeInteresse.tipoArea[ki]=="Circle"){
        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),
                            "Figure radius: " +QString::number(1/(videoLido->escala * videoLido->escala)) );

//        csvGravador << "Figure Raio; " << areasDeInteresse.width[ki]<< "\n";


    }else{
        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),
                            "Figure Height: " +QString::number(1/(videoLido->escala * videoLido->escala)) );
        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),
                            "Figure Width: " +QString::number(areasDeInteresse.width[ki]) );

//         csvGravador << "Figure Height; " << areasDeInteresse.heigth[ki]<< "\n";
//         csvGravador << "Figure Width; " << areasDeInteresse.width[ki]<< "\n";

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
//    csvGravador << "\n";
//    csvGravador << "\n";
//    csvGravador << "\n";

    double duracao=0;
    //csvGravador << "Time (s)" << ";" << "Categories"<< ";" << "Duration(s)" << "\n";

   //asdasd  for(int ki=0; ki< matrizReMorfo.size() ; ki++){
//        csvGravador << "\n";
//        csvGravador << "\n";
//        csvGravador << "\n";

        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),"frames");
        add_cell(&saida, "B"+QString::number(linha),"second");
        add_cell(&saida, "C"+QString::number(linha),"Number of pixels of the animal's body");
        add_cell(&saida, "D"+QString::number(linha),"Area of the animal's body (in mm2)");

        QString s = "Horizontal coordinate of the centroid of the animal's body (in pixels, from 0 to " + QString::number(areasDeInteresse.width[0])+ ")";
        add_cell(&saida, "E"+ QString::number(linha), s);

        add_cell(&saida, "F"+ QString::number(linha),"Vertical coordinate of the centroid of the animal's body (in pixels, from 0 to " + QString::number(areasDeInteresse.heigth[0])+ ")");

        add_cell(&saida, "G"+QString::number(linha),"Angle between animal and Horizontal coordinate(in degrees)");

        add_cell(&saida, "H"+QString::number(linha),"Height of the animal (in mm)");
        add_cell(&saida, "I"+QString::number(linha),"Width of the animal (in mm)");
        add_cell(&saida, "J"+QString::number(linha),"Object Detected (true or false)");
        add_cell(&saida, "K"+QString::number(linha),"Distance travelled by the centroid (in pixels)");
        add_cell(&saida, "L"+QString::number(linha),"Distance travelled by the centroid (in mm)");
        add_cell(&saida, "M"+QString::number(linha),"Variation of Area (from the former frame) (in mm^2)");

        add_cell(&saida, "N"+QString::number(linha),"Variation of Height of animal (from the former frame)(in mm)");
        add_cell(&saida, "O"+QString::number(linha),"Variation of Width of animal (from the former frame) (in mm)");
        add_cell(&saida, "P"+QString::number(linha),"Variation of Angule of animal (in degrees)");
        add_cell(&saida, "Q"+QString::number(linha),"Intrinsic noise (minimum variation distance traveled by the centroid) (true or false)");



//        csvGravador <<  ";"      <<    ";"    << "Number of pixels;"     << "Area (in mm2);";
//        csvGravador <<  "Horizontal coordinate of the centroid;"      <<    "Vertical coordinate of the centroid;";
//        csvGravador <<  "AA(in degrees);" <<"Height of the animal;" <<"Width of the animal;" <<"Object Detected;" ;
//        csvGravador << "Distance travelled by the centroid;" << "Distance travelled by the centroid;";
//        csvGravador << "Variation of Area (from the former frame);";
//        csvGravador << "Variation of Height of animal (from the former frame);";
//        csvGravador << "Variation of Width of animal (from the former frame);";
//        csvGravador << "Variation of Angule of animal;";
//        csvGravador << "Intrinsic noise (minimum variation distance traveled by the centroid)" << "\n";


        //a area de intesse 0 é sempre a altura e largura da imagem original;

//        csvGravador << "frames;" << "second;" << "of the animal's body;" << "of the animal's body;";
//        csvGravador << "(in pixels, from" << "0 to "<< areasDeInteresse.width[0] <<  " );" << "(in pixels, from " <<  "0 to " << areasDeInteresse.heigth[0] << " );";
//        csvGravador <<  "Angle between animal and Horizontal coordinate ;" << "in mm;" << "in mm;" <<"true or false;" ;
//        csvGravador << "(in pixels);" << "(in mm);";
//        csvGravador << "in mm2;";
//        csvGravador << "in mm;";
//        csvGravador << "in mm;";
//        csvGravador << "in degrees;" ;
//        csvGravador << "true or false" << "\n";


        for(int kj=0; kj<   matrizReMorfo[ki].area.size(); kj++){

            linha += 1;
            add_cell(&saida, "A"+QString::number(linha),QString::number(matrizReMorfo[ki].frame[kj]) ,true);
            add_cell(&saida, "B"+QString::number(linha),QString::number(matrizReMorfo[ki].frame[kj]  / videoLido->fps) ,true);
            add_cell(&saida, "C"+QString::number(linha),QString::number(matrizReMorfo[ki].area[kj]) ,true);
            add_cell(&saida, "D"+QString::number(linha),QString::number(matrizReMorfo[ki].area[kj]/(videoLido->escala*videoLido->escala)) ,true);


            add_cell(&saida, "E"+QString::number(linha), QString::number(matrizReMorfo[ki].centroidX[kj]) ,true);
            add_cell(&saida, "F"+QString::number(linha), QString::number(matrizReMorfo[ki].centroidY[kj]) ,true);
            add_cell(&saida, "G"+QString::number(linha),QString::number(matrizReMorfo[ki].anguloObj[kj]) ,true);
            add_cell(&saida, "H"+QString::number(linha),QString::number(matrizReMorfo[ki].altura[kj]/(videoLido->escala)) ,true);
            add_cell(&saida, "I"+QString::number(linha),QString::number(matrizReMorfo[ki].largura[kj]/(videoLido->escala)) ,true);

            if( matrizReMorfo[ki].objetoEncontrado[kj]){
                add_cell(&saida, "J"+QString::number(linha),"true" , false);
//                csvGravador << "true;";
            }else{
                add_cell(&saida, "J"+QString::number(linha),"false" , false);
//                csvGravador << "false;";
            }



            add_cell(&saida, "K"+QString::number(linha),QString::number(matrizReCinema[ki].varDistancia[kj]) ,true);
            add_cell(&saida, "L"+QString::number(linha),QString::number(matrizReCinema[ki].varDistancia[kj]/(videoLido->escala)) ,true);
            add_cell(&saida, "M"+QString::number(linha),QString::number(matrizReCinema[ki].varArea[kj]/(videoLido->escala*videoLido->escala)) ,true);
            add_cell(&saida, "N"+QString::number(linha),QString::number(matrizReCinema[ki].varAltura[kj]/(videoLido->escala)) ,true);
            add_cell(&saida, "O"+QString::number(linha),QString::number(matrizReCinema[ki].varLargura[kj]/(videoLido->escala)) ,true);
            add_cell(&saida, "P"+QString::number(linha),QString::number(matrizReCinema[ki].varAngular[kj]) ,true);

            if( matrizReCinema[ki].ruidoMaxVaria[kj] ){
                add_cell(&saida, "Q"+QString::number(linha),"true" ,false);
//                   csvGravador << "true;";
            }else{
                add_cell(&saida, "Q"+QString::number(linha), "false" ,false);

//                csvGravador << "false;";

            }




//           // csvGravador << "aaaaa \n";
//            csvGravador <<  matrizReMorfo[ki].frame[kj] << ";"<< matrizReMorfo[ki].frame[kj]  / videoLido->fps << ";" ;
//            csvGravador << matrizReMorfo[ki].area[kj] << ";" << matrizReMorfo[ki].area[kj]/(videoLido->escala*videoLido->escala)<< ";";

//            csvGravador << matrizReMorfo[ki].centroidX[kj] << ";" << matrizReMorfo[ki].centroidY[kj]<<";";
//            csvGravador << matrizReMorfo[ki].anguloObj[kj] << ";" ;
//            csvGravador << matrizReMorfo[ki].altura[kj]/(videoLido->escala) << ";" ;
//            csvGravador << matrizReMorfo[ki].largura[kj]/(videoLido->escala) << ";" ;
////            reMorfo.tamanhoObj

//           if( matrizReMorfo[ki].objetoEncontrado[kj]){
//               csvGravador << "true;";
//           }else{
//               csvGravador << "false;";
//           }
//           csvGravador << matrizReCinema[ki].varDistancia[kj] << ";" << matrizReCinema[ki].varDistancia[kj]/(videoLido->escala)<< ";";
//           csvGravador << matrizReCinema[ki].varArea[kj]/(videoLido->escala*videoLido->escala)  << ";" ;
//           csvGravador << matrizReCinema[ki].varAltura[kj]/(videoLido->escala) << ";" ;
//           csvGravador << matrizReCinema[ki].varLargura[kj]/(videoLido->escala) << ";" ;
//           csvGravador << matrizReCinema[ki].varAngular[kj] << ";" ;


//           if( matrizReCinema[ki].ruidoMaxVaria[kj] ){
//                  csvGravador << "true;";
//        }else{

//               csvGravador << "false;";

//           }

           //reCinema.ruidoMaxVaria
//reCinema.varTamObjeto
//reCinema.varArea
           //

//           reCinema.varAngular.push_back(streamReader.attributes().value("Van").toDouble());
//           reCinema.varArea.push_back(streamReader.attributes().value("Var").toDouble());
//           reCinema.varDistancia.push_back(streamReader.attributes().value("Vd").toDouble());
//           reCinema.varTamObjeto.push_back(streamReader.attributes().value("VtoP").toDouble());


//            linha +=1;
//            csvGravador << "\n";

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

        ls_gravar.append(saida);




        gravar_csv_ls_cell(nomeArquivoByte, ls_gravar);
//        gravaaaaaaaaaa o csv


//        outGravador.close();

    }


}
