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
#include "telaunveil.h"
#include "ui_telaunveil.h"

telaUnveil::telaUnveil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaUnveil)
{
    ui->setupUi(this);

    //ui->tabCego->setColumnCount(2);
}

telaUnveil::~telaUnveil()
{
    delete ui;
}

void telaUnveil::on_pbUserKey_clicked()
{
    QString fonteVideo;
    fonteVideo = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
               "C:/ethowatcher/usuariosCadastrados",
               "User Files (*.uxml)"
                );



    outputKey.setFileName(fonteVideo); //seta o nome do arquivo

    QXmlStreamReader xmlReader(&outputKey);
    //output.open(QIODevice::ReadOnly | QIODevice::Text);
    outputKey.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!xmlReader.atEnd() && !xmlReader.hasError()){


        xmlReader.readNext();

        //pega os nome dos arquivos que devem ser abertos
        if(xmlReader.name().toString()== "nome"){
        expKey.nome = xmlReader.readElementText() ;

        }

        if(xmlReader.name().toString() == "laboratorio"){

         expKey.lab = xmlReader.readElementText() ;

        }

        if(xmlReader.name().toString() == "password"){
          expKey.senha = xmlReader.readElementText() ;
        }


    }
    outputKey.close();
}

void telaUnveil::on_pbAddVideo_clicked()
{
    QString fonteVideoXML;
    fonteVideoXML = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users//Bio//Desktop//videos//",
                "Video Files (*.vcxml)"
                );


    if(!fonteVideoXML.isEmpty()){
        //ui->lblVideoName->setText(fonteVideoXML);

        videoLista.nomeVXML.push_back(fonteVideoXML);
        videoLista.nomeVXML.push_back(fonteVideoXML);
        //se final vxml

        lerVXML(fonteVideoXML);

    }

    if(unveilKey[0].nome == expKey.nome){
        if(unveilKey[0].lab == expKey.lab){
            if(unveilKey[0].senha == expKey.senha){

                qDebug()<<"deu certo";

                ui->tabCego->insertRow(ui->tabCego->rowCount());
                ui->tabCego->setItem(ui->tabCego->rowCount()-1,0,new QTableWidgetItem(fonteVideoXML));
                ui->tabCego->setItem(ui->tabCego->rowCount()-1,1,new QTableWidgetItem("ok"));

                chLiberado.push_back(true);
                chLiberado.push_back(true);


//                //configurando TableWidget
//                ui->tabCego->resizeColumnsToContents();
//                ui->tabCego->clearSelection();
//                ui->tabCego->clearFocus();





            }else{
                qDebug()<<"c erro";
                ui->tabCego->insertRow(ui->tabCego->rowCount());
                ui->tabCego->setItem(ui->tabCego->rowCount()-1,0,new QTableWidgetItem(fonteVideoXML));
                ui->tabCego->setItem(ui->tabCego->rowCount()-1,1,new QTableWidgetItem("false"));
                chLiberado.push_back(false);
                chLiberado.push_back(false);
            }


        }else{
            qDebug()<<"b erro";
            ui->tabCego->insertRow(ui->tabCego->rowCount());
            ui->tabCego->setItem(ui->tabCego->rowCount()-1,0,new QTableWidgetItem(fonteVideoXML));
            ui->tabCego->setItem(ui->tabCego->rowCount()-1,1,new QTableWidgetItem("false"));
            chLiberado.push_back(false);
            chLiberado.push_back(false);

        }


    }else{
        qDebug()<<"a erro";
        ui->tabCego->insertRow(ui->tabCego->rowCount());
        ui->tabCego->setItem(ui->tabCego->rowCount()-1,0,new QTableWidgetItem(fonteVideoXML));
        ui->tabCego->setItem(ui->tabCego->rowCount()-1,1,new QTableWidgetItem("false"));
        chLiberado.push_back(false);
        chLiberado.push_back(false);

    }


    //configurando TableWidget
    ui->tabCego->resizeColumnsToContents();
    ui->tabCego->clearSelection();
    ui->tabCego->clearFocus();

    contVideo1++;
    contVideo= contVideo+2;



}

void telaUnveil::on_pbUnveil_clicked()
{


    QString nomeArquivoGravarCsv;
    nomeArquivoGravarCsv = QFileDialog::getSaveFileName(
                 this,
                 tr("Save File"),
                 "C://",
                "csv Files (*.csv)"
                );

    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador <<"EthoWatcher Open Source \n";
    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";

    csvGravador <<" Arquivo do cadastro do video cegado ;" <<"Arquivo de video cegado;" << "Arquivo de cadastro do video original;" << "Arquivo de video original"<< "\n";
    int ak=0;
    int max=0;
    int cont=0;

    std::vector<QString> vxml;

    for(int k1=0;k1 < videoLista.nomeArquivoVXML.size(); k1++){

        QString recebe=  videoLista.nomeArquivoVXML[k1];
        QByteArray teste =recebe.toLatin1();
        if(teste.contains(".vxml")){
            vxml.push_back(recebe);
            vxml.push_back(recebe);

        }


       // qDebug() << videoLista.nomeOpencv[k1];
        qDebug() << videoLista.nomeArquivoVXML[k1];
    }






    while(ak<contVideo){


        if(chLiberado[ak]){


        csvGravador << videoLista.nomeVXML[ak] << ";" <<videoLista.nomeOpencv[ak] <<";"
                    << vxml[(ak)]<< ";" <<  videoLista.nomeOpencv[ak+1] <<"\n";
        csvGravador << "\n"<< "\n";


        }

        ak=ak+2;
        cont++;

    }


    for(int k1=0;k1 < videoLista.nomeArquivoVXML.size(); k1++){

       // qDebug() << videoLista.nomeOpencv[k1];
        qDebug() << videoLista.nomeArquivoVXML[k1];
    }

     //csvGravador <<"fim";
    //csvGravador << videoLista.nomeOpencv[2] <<";" << videoLista.nomeOpencv[3] << "\n";



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
//    csvGravador << "video file is " << videoLido->nome<< "\n";

//    csvGravador << "Analysis initiated at " << conPontoVirgula( videoLido->frameProce /videoLido->fps)  << " (seconds) of the video file \n ";
//    csvGravador << "Analysis terminated at " << conPontoVirgula(videoLido->frameFinal / videoLido->fps) << " (seconds) of the video file \n";
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

//        csvGravador << conPontoVirgula(etografiaLida->frameInicial[ka1] / videoLido->fps);
//        //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

//        csvGravador << ";";
//        csvGravador << catalagoLido->nome[etografiaLida->id[ka1]];
//        csvGravador << ";";

//        duracao= etografiaLida->frameFinal[ka1]- etografiaLida->frameInicial[ka1];
//        csvGravador <<conPontoVirgula( duracao / videoLido->fps);
//        csvGravador << "\n";

//    }

//    csvGravador <<  "RESULTS FOR THE ENTIRE PERIOD of ANALYSIS \n\n";

//    csvGravador << "category"<< ";" << "Duration(s)" << ";" <<"Freq."  << ";" << "Latency(s)" << "\n";

//    for(int ka2=0; ka2< catalagoLido->nome.size(); ka2++){
//        csvGravador << catalagoLido->nome[ka2] << ";"
//                     << conPontoVirgula(vetorDuracao[ka2])<< ";"
//                     << conPontoVirgula(vetorFrequencia[ka2])<< ";"
//                     << conPontoVirgula(vetorLatencia[ka2]) << ";" ;
//        csvGravador << "\n";
//    }

    outGravador.close();




}

QString telaUnveil::conPontoVirgula(double num)
{
    QByteArray numeroArray,numeroArraySaida;
    numeroArray = QByteArray::number(num);
    numeroArraySaida =numeroArray;


    numeroArraySaida.replace(QByteArray("."),QByteArray(","));
    return  QString::fromLatin1( numeroArraySaida);
}

void telaUnveil::lerVXML(QString nomeArquivoLer)
{

    OutVideo.setFileName(nomeArquivoLer);
    OutVideo.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutVideo); //passa o endereço

    QString conversor;

    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        //pega os nome dos arquivos que devem ser abertos
        if(streamReader.name().toString()== "c"){
        experimentador.nome = rsaDecri.decriptoRSAQstring(streamReader.readElementText()) ;

        }

        if(streamReader.name().toString() == "b"){

         experimentador.lab = rsaDecri.decriptoRSAQstring(streamReader.readElementText()) ;

        }

        if(streamReader.name().toString() == "a"){
          experimentador.senha = rsaDecri.decriptoRSAQstring(streamReader.readElementText()) ;
        }



        if(streamReader.name().toString()== "nomeArquivoVXML"){
        videoLista.nomeArquivoVXML.push_back( rsaDecri.decriptoRSAQstring(streamReader.readElementText()));
        videoLista.nomeArquivoVXML.push_back( rsaDecri.decriptoRSAQstring(streamReader.readElementText()));
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name().toString()== "nomeOpencv"){
        videoLista.nomeOpencv.push_back( rsaDecri.decriptoRSAQstring(streamReader.readElementText()));
           //qDebug() << leitorXML.readElementText();

        }


           if(streamReader.name().toString()== "frameInicial"){

         conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
        videoLista.frameInicial.push_back(conversor.toInt());
              // qDebug() << leitorXML.readElementText();
           }

           if(streamReader.name().toString()== "frameFinal"){
               conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
        videoLista.frameFinal.push_back(conversor.toInt());
              // qDebug() << leitorXML.readElementText();
           }



           if(streamReader.name().toString() == "frameProces"){
               conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
        videoLista.frameProces.push_back(conversor.toInt());


           }
            if(streamReader.name().toString() == "frameBack"){

                conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
         videoLista.frameBack.push_back(conversor.toInt());

            }



            if(streamReader.name().toString() == "treshold"){

                       conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());

                       videoLista.threshold.push_back(conversor.toInt());

              }

           if(streamReader.name().toString() == "erosao"){

               conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
        videoLista.erosao.push_back(conversor.toInt());

           }


           if(streamReader.name().toString() == "escala"){

               conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
        videoLista.escala.push_back(conversor.toDouble());

           }

           if(streamReader.name().toString() == "fps"){

               conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
        videoLista.fps.push_back(conversor.toInt());

           }

           if(streamReader.name().toString()== "proImageOn"){ //se foi cadastrado para o processamento de imagem

               conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
               if(conversor=="true"){
                   videoLista.chProImaOn.push_back(true); //tem o processamento de imagem

               }else{

                   videoLista.chProImaOn.push_back(false);

               }


           }

           if(streamReader.name().toString()== "janelaInteresse"){

               if(chaJanInte==true){
                   chaJanInte=false;

               }else{
                   chaJanInte=true;

                   videoLista.areaJanInte.push_back(auxArea1);

               }
           }

           if(chaJanInte==true){
               if(streamReader.name().toString() == "ativado"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());

                   if(conversor=="false"){
                     videoLista.chaInteMoveAtivado.push_back(false);
                   }else{
                     videoLista.chaInteMoveAtivado.push_back(true);
                   }


               }


               if(streamReader.name().toString() == "movel"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());

                   if(conversor=="false"){
                     videoLista.chaInteMove.push_back(false);
                   }else{
                     videoLista.chaInteMove.push_back(true);
                   }


               }

               if(streamReader.name().toString() == "origX"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());

                     videoLista.areaJanInte[contadorDeVideo].oriX.push_back(conversor.toDouble());

               }
               if(streamReader.name().toString() == "origY"){

                conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                videoLista.areaJanInte[contadorDeVideo].oriY.push_back(conversor.toDouble());

               }

               if(streamReader.name().toString() == "width"){

                conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                videoLista.areaJanInte[contadorDeVideo].width.push_back(conversor.toDouble());

               }
               if(streamReader.name().toString() == "heigth"){

                conversor = rsaDecri.decriptoRSAQstring( streamReader.readElementText());
                videoLista.areaJanInte[contadorDeVideo].height.push_back(conversor.toDouble());

               }

           }


           if(streamReader.name().toString() == "maximaVariacaoCentro"){

               if(chaMaxVari==true){
                   chaMaxVari=false;

               }else{
                   chaMaxVari=true;
                   //videoLista.areaJanInte.push_back(auxArea);

               }
           }

           if(chaMaxVari){

               if(streamReader.name().toString() == "tamanho"){

                conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                videoLista.tamMaxVar.push_back(conversor.toDouble());

               }


           }







           if(streamReader.name().toString() == "areasDeInteresse"){

               if(chaveArea==true){
                   chaveArea=false;

               }else{
                   chaveArea=true;
                   videoLista.area.push_back(auxArea);

               }
           }

           if(chaveArea==true){


               if(streamReader.name().toString() == "area"){

               QString conversora= rsaDecri.decriptoRSAQstring(streamReader.attributes().value("tipo").toString());
               if(!conversora.isEmpty()){//ele acaba entrando daus vez pra cada tag
//                   videoLista.contQuantArea++;
                   //auxArea.tipo = conversora;
                   //videoLista.area.push_back(auxArea);
                   videoLista.area[contadorDeVideo].tipo.push_back(conversora);
                   //   analiseSequencial.classeCatalago.push_back(conversor);
                   // etografiaLida->caminho= conversor;
               }else{




                 //  analiseSequencial.listaDados.push_back(analiseSequencial.dados);
                 //  analiseSequencial.dados.clear();
                   //zerando os valores

               }

               }

               if(streamReader.name().toString() == "nomeFig"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                   videoLista.area[contadorDeVideo].nomeFig.push_back(conversor);
                   //auxArea.oriX =  conversor.toDouble();

               }


               if(streamReader.name().toString() == "oriX"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                   videoLista.area[contadorDeVideo].oriX.push_back(conversor.toDouble());
                   //auxArea.oriX =  conversor.toDouble();

               }

               if(streamReader.name().toString() == "oriY"){

                   conversor = rsaDecri.decriptoRSAQstring( streamReader.readElementText());
                   videoLista.area[contadorDeVideo].oriY.push_back(conversor.toDouble());
                   //auxArea.oriY =  conversor.toDouble();

               }

               if(streamReader.name().toString() == "height"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                   videoLista.area[contadorDeVideo].height.push_back(conversor.toDouble());
                   //auxArea.height =  conversor.toDouble();

               }

               if(streamReader.name().toString() == "width"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                   videoLista.area[contadorDeVideo].width.push_back(conversor.toDouble());
                  // auxArea.width =  conversor.toDouble();

               }

               if(streamReader.name().toString() == "rad"){

                   conversor = rsaDecri.decriptoRSAQstring(streamReader.readElementText());
                   videoLista.area[contadorDeVideo].raio.push_back(conversor.toDouble());
                   //auxArea.raio =  conversor.toDouble();

               }//fim if rad




           }//fim chave das areas






        }//fim while



    //videoLista.quantidadeDeDados++; //= contadorTamanho; //conta quantidade de dados;


    unveilKey.push_back( experimentador);

   OutVideo.close();




}
