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
#include "telablind.h"
#include "ui_telablind.h"

telablind::telablind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telablind)
{
    ui->setupUi(this);
    //ui->stackedWidget->setCurrentIndex(0);
    ui->staWidPrin->setCurrentIndex(0);
}

telablind::~telablind()
{
    qDebug() << "tela cego desligando 0";
    for(int kaa=0; kaa< listaEditaVideo.size(); kaa++){

        delete listaEditaVideo[kaa];
    }
    qDebug() << "tela cego desligando 1";
    delete ui;
}

void telablind::on_pbAddListaVideo_clicked()
{


    //ageitar para que abra so .lvxml
    listaVideo = QFileDialog::getOpenFileName();

    //ler o arquivo xml
    //nomeDosVideos
      output.setFileName(listaVideo); //seta o nome do arquivo

      QXmlStreamReader xmlReader(&output);
      //output.open(QIODevice::ReadOnly | QIODevice::Text);
      output.open(QIODevice::ReadOnly | QIODevice::Text);

      while(!xmlReader.atEnd() && !xmlReader.hasError()){


          xmlReader.readNext();

          //pega os nome dos arquivos que devem ser abertos
          if(xmlReader.name()== "completo"){
          nomeDosVideos.push_back(xmlReader.readElementText()) ;

          count++;
          //adiciona o valor aleatorio
          //numeroAlatorio.push_back(numeroRandon)
          //qDebug() << xmlReader.readElementText();

          }

          if(xmlReader.name() == "nome"){

               nomeDosVideosMenor.push_back(xmlReader.readElementText());
          }


      }
      output.close();


      QStringList titulos;
      titulos << "Video Names ";
      ui->tabWidVideoList->setColumnCount(1);

      ui->tabWidVideoList->setHorizontalHeaderLabels(titulos);


      for(int f2=0;f2<( nomeDosVideosMenor.size());f2++){
              ui->tabWidVideoList->insertRow(ui->tabWidVideoList->rowCount());
              //cria uma nova linha
              //categoria


                 //no valor zero coloca

              ui->tabWidVideoList->setItem(ui->tabWidVideoList->rowCount()-1
                                         ,0,new QTableWidgetItem(
                                             nomeDosVideosMenor[f2]));





      }




//      ui->tbListVideo
    //correto
    //ui->stackedWidget->setCurrentIndex(1);

    //debug
    //ui->stackedWidget->setCurrentIndex(2);

}

void telablind::on_pbAbrirPasta_clicked()
{
    //forma que abre um caminho
    caminhoArquivo = QFileDialog::getExistingDirectory();
   // ui->textEdit_2->setText(caminhoArquivo);

    //bloco que aleatoriza o nome
    //inicializa os numero aleatorios
    inicializaNumeroAleatorio();

    //pega um numero aleatorio pra cada video
    for(int l=0;l<count;l++){
    j.push_back(getNumeroAleatorio());
    numeroEscrito.push_back(false); //cria uma variavel que diz que ainda nao foi utilizada
    }


    //mostra o numero aleatorio
    for(int l=0;l<count;l++){
        qDebug() << QString::number(j[l]);
    }

    aleatorizaAOrdem();




//    for(int i=0; i<count; i++){
//    output.setFileName(nomeDosVideosAleatorizado[i]);
//        gravandovideo(i);


//    }




}



QString telablind::nomeParaOpenCV(QString nomeArq){

    QByteArray fonteVideoBit,fonteVideoBitOpenCV;
    QString fonteVideoOpenCV;


    if(!nomeArq.isNull())
    {
        fonteVideoBit = nomeArq.toLatin1();

        //ageitando a extensão apara a opencv

        int k=0;
        int ka=0;

        while(fonteVideoBit[k] != 0) //enquanto não tem string nula ou seja não é o fim do arquivo
        {
            fonteVideoBitOpenCV[ka] = fonteVideoBit[k];

            if(fonteVideoBit[k] == 47){ //47 esta relacionado com a barra

                ka++;
                 fonteVideoBitOpenCV[ka] = 47;

            }

            ka++;
            k++;


        }


    fonteVideoOpenCV = QString::fromLatin1(fonteVideoBitOpenCV);

    return fonteVideoOpenCV;

    }


}


void telablind::lendoVideoXml(int qualLer){
//    QXmlStreamReader xmlReader(&output);
//    //output.open(QIODevice::ReadOnly | QIODevice::Text);
//    output.open(QIODevice::ReadOnly | QIODevice::Text);

//    if(qualLer==0){ //dadosPesquisador
//    while(!xmlReader.atEnd() && !xmlReader.hasError()){


//        xmlReader.readNext();


//        if(xmlReader.name()== "nomePesquisador"){
//        videoCadastrado.experimentador.nome= xmlReader.readElementText();
//           //qDebug() << xmlReader.readElementText();

//        }


//           if(xmlReader.name()== "laboratorio"){
//        videoCadastrado.experimentador.lab= xmlReader.readElementText();
//              // qDebug() << xmlReader.readElementText();
//           }

//        }
//    }


//    if(qualLer==1){ //dadosExperimento
//    while(!xmlReader.atEnd() && !xmlReader.hasError()){


//        xmlReader.readNext();


//        if(xmlReader.name()== "tituloExperimento"){
//    videoCadastrado.tituloExperimento = xmlReader.readElementText();
//          // qDebug() << xmlReader.readElementText();

//        }

//        //encontra o primeiro nome escrito nomePesquisador
//           if(xmlReader.name()== "animal"){
//               videoCadastrado.idAnimal = xmlReader.readElementText().toInt();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "diaRealizado"){

//           videoCadastrado.dataDia =  xmlReader.readElementText().toInt();

//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "mesRealizado"){

//           videoCadastrado.dataMes =  xmlReader.readElementText().toInt();

//              // qDebug() << xmlReader.readElementText();
//           }

//           if(xmlReader.name()== "anoRealizado"){

//           videoCadastrado.dataAno =  xmlReader.readElementText().toInt();


//           }

//           if(xmlReader.name()== "observacao"){
//               videoCadastrado.observacoes = xmlReader.readElementText();
//              // qDebug() << xmlReader.readElementText();
//           }

//        }
//    }


//    if(qualLer==2){ //dadosOriginal
//    while(!xmlReader.atEnd() && !xmlReader.hasError()){


//        xmlReader.readNext();


//        if(xmlReader.name()== "nomeOpencv"){
//        videoCadastrado.nomeOpencv = xmlReader.readElementText();
//           //qDebug() << xmlReader.readElementText();

//        }

//        //encontra o primeiro nome escrito nomePesquisador
//           if(xmlReader.name()== "caminho"){
//               videoCadastrado.caminho = xmlReader.readElementText();
//          //     qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "nomeOriginal"){
//           videoCadastrado.nome = xmlReader.readElementText();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "extensao"){
//           videoCadastrado.ext = xmlReader.readElementText();
//             //  qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "fps"){
//               videoCadastrado.videoFps = xmlReader.readElementText().toDouble();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "quantidadeFrames"){
//              videoCadastrado.videoFrames = xmlReader.readElementText().toDouble();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "quantidadeTempo"){
//               videoCadastrado.videoTempo = xmlReader.readElementText().toDouble();
//              // qDebug() << xmlReader.readElementText();
//           }

//        }
//    }

//    if(qualLer==3){ //dadosCalibracao
//    while(!xmlReader.atEnd() && !xmlReader.hasError()){


//        xmlReader.readNext();

//        //encontra o primeiro nome escrito nomePesquisador
//        if(xmlReader.name()== "frameInicial"){
//        videoCadastrado.resultado.frameInicial=xmlReader.readElementText().toDouble();
//          // qDebug() << xmlReader.readElementText();

//        }

//        //encontra o primeiro nome escrito nomePesquisador
//           if(xmlReader.name()== "frameBack"){
//               videoCadastrado.resultado.frameFundo=xmlReader.readElementText().toDouble();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "frameFinal"){
//               videoCadastrado.resultado.frameFinal=xmlReader.readElementText().toDouble();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "erosao"){
//               videoCadastrado.resultado.erosao=xmlReader.readElementText().toInt();
//               //qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "escala"){
//               videoCadastrado.resultado.escala=xmlReader.readElementText().toDouble();
//             //  qDebug() << xmlReader.readElementText();
//           }

//        }
//    }


//    if(qualLer==4){ //dadosAquisicao
//    while(!xmlReader.atEnd() && !xmlReader.hasError()){


//        xmlReader.readNext();



//        //encontra o primeiro nome escrito nomePesquisador
//           if(xmlReader.name()== "camera"){
//               videoCadastrado.idCamera= xmlReader.readElementText().toInt();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "fpsMedio"){
//               videoCadastrado.fpsMedio= xmlReader.readElementText().toFloat();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "tempoProcessamento"){
//               videoCadastrado.tempoGastoAquisicao= xmlReader.readElementText().toFloat();
//              // qDebug() << xmlReader.readElementText();
//           }
//           if(xmlReader.name()== "erroDeTempo"){
//               videoCadastrado.erroTempoAtrelado= xmlReader.readElementText().toFloat();
//              // qDebug() << xmlReader.readElementText();
//           }

//        }
//    }




//        //finalizando o arquivo para poder fazer multiplas vezes
//        output.close();
//        xmlReader.clear();
}


void telablind::gravandovideo(int i){





//    lendoVideoXml(0);
//    lendoVideoXml(1);
//    lendoVideoXml(2);
//    lendoVideoXml(3);


 //   ui->textEdit_2->setText(videoCadastrado.nomeOpencv);



    //abrirVideo = nomeParaOpenCV("C:/filmes/funcionaMarcela.avi");
    //ui->textEdit_2->setText(abrirVideo);

    video.open(videoLista.nomeOpencv[0].toStdString());
    QString numero=QString::number(i);

    QString nomeEditado="editadoOpen"+numero+".avi";
    QString caminhoArquivoNome;

    caminhoArquivoNome= nomeParaOpenCV(caminhoArquivo)+"//"+ nomeEditado;

    vEditado.nomeOpencv=caminhoArquivoNome;

    double dWidth = video.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = video.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
    cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

    int codec = CV_FOURCC('x', '2', '6', '4');

    //cv codec XVID 1684633208
    //cv codec H264 875967096

//    videoEditado.open()
    videoEditado = new cv::VideoWriter();
    videoEditado->open(caminhoArquivoNome.toStdString(),1684633208,  videoLista.fps[0] ,frameSize,true);
    if(video.isOpened()){

//        ui->textEdit_2->setText("oi mundo");
        if(videoEditado->isOpened()){
//            ui->textEdit_2->setText("oi mundo1");


     for(int i=0; i<=videoLista.frameFinal.size();i++){
            if((i>videoLista.frameInicial[i])&&(i<videoLista.frameFinal[i]))
            {
             video.read(frameLido);
            videoEditado->write(frameLido);
            }

        }
        // videoEditado

//         ui->textEdit_2->setText(QString::number(videoCadastrado.videoFps));
        }






    }

    videoEditado->release();
    video.release();


    gravandoXMLVideoEditado(caminhoArquivo+"/"+"editadoOpen"+QString::number(i)+".vcxml");

}

//parte aleatorio


void telablind::inicializaNumeroAleatorio()
{
    //cria a semente unica
    unsigned int thread;
    unsigned int tempo;
    unsigned int semente;
    thread = (unsigned int) QThread::currentThreadId();
    tempo= (unsigned int) time(NULL);
    semente = thread+ tempo;

    srand(semente); //valor unico cada vez que faz o processo

   // srand((unsigned int) QThread::currentThreadId());
    //srand (time(NULL));

}

int telablind::getNumeroAleatorio(){

    int numeroSaida;
    numeroSaida=rand() % 1000 + 1;
    return numeroSaida;

}




void telablind::on_pbNumeroAleatorio_clicked()
{
    inicializaNumeroAleatorio();

    for(int l=0;l<3;l++){
    j.push_back(getNumeroAleatorio());
    numeroEscrito.push_back(false); //cria uma variavel que diz que ainda nao foi utilizada
    }

    for(int l=0;l<3;l++){
        qDebug() << QString::number(j[l]);
    }

    aleatorizaAOrdem();

   // ui->textEdit_3->setText(QString::number(j[0])+" "+
    //        QString::number(j[1])+ " "+
    //        QString::number(j[2])+ " ");


}

void telablind::aleatorizaAOrdem(){


    int posicao=0;
    //int posicaoDeEscrita=0;
    //encontra qual é o numero aleatorio maior e qual é sua posicao
    //alem disso esclui os arquivos que ja entraram
    // count == quantidade de vídeos.
    for(int k=0; k<count; k++){
    int maiorValor=0;
    for(int i=0; i<count;i++){

        if ((j[i] > maiorValor)&&(!numeroEscrito[i]))
        {
            maiorValor= j[i];
            //j[i].nomeAleatorio="Maior";
            //j[i].nomeAleatorio=lala.number(quantidade);
            //numeroEscrito[i]=true;
            posicao=i;
        }



    }
    //OU SEJA O 0 NESSE ARRAY VAI SER O VÍDEO BLIND 0
    nomeDosVideosAleatorizado.push_back(nomeDosVideos[posicao]);
    //frameInicialVideosAleatorizado.push_back();



    numeroEscrito[posicao]=true;

    qDebug() << nomeDosVideosAleatorizado[k] << "lala";

    }




}


void telablind::gravandoXMLVideoEditado(QString nomeArquivoEditado){

//    outputVideoEditado.setFileName(nomeArquivoEditado);
//    outputVideoEditado.open(QIODevice::WriteOnly);
////! [write output]
////! [start stream]
////!



//    QXmlStreamWriter streamWriter(&outputVideoEditado); //passa o endereço
//    streamWriter.setAutoFormatting(true);
//    streamWriter.writeStartDocument();//começa o documento

//    streamWriter.writeStartElement("cadastroVideo"); //abre o cadastroVideo

//    streamWriter.writeStartElement("dadoPesquisador"); //abre o elemento de informacoes

//        streamWriter.writeTextElement("nomePesquisador", experimentador.nome);
//        streamWriter.writeTextElement("laboratorio", experimentador.lab);

//    streamWriter.writeEndElement(); //fecha o elemento de informacoes

//    streamWriter.writeStartElement("dadoOriginal"); //abre o elemento de dado original
//        streamWriter.writeTextElement("nomeOpencv", rsa.criptoRSAQstring(videoLista.nomeOpencv[0]));
//    streamWriter.writeEndElement();//

//    streamWriter.writeStartElement("dadoShufle"); //abre o elemento de dado original
//         streamWriter.writeTextElement("nomeOpencv", rsa.criptoRSAQstring(vEditado.nomeOpencv));
//         //streamWriter.writeTextElement("caminho", videoCadastrado.caminho);
//         //streamWriter.writeTextElement("nomeOriginal", videoCadastrado.nome);
//        // streamWriter.writeTextElement("extensao", videoCadastrado.ext);
//         streamWriter.writeTextElement("fps", QString::number(videoCadastrado.videoFps));
//         streamWriter.writeTextElement("quantidadeFrames",QString::number(videoLista.videoFrames));
//         streamWriter.writeTextElement("quantidadeTempo", QString::number(videoCadastrado.videoTempo));

//        streamWriter.writeTextElement("frameInicial", QString::number (videoCadastrado.resultado.frameInicial));
//        streamWriter.writeTextElement("frameBack", QString::number(videoCadastrado.resultado.frameFundo));
//        streamWriter.writeTextElement("frameFinal",QString::number (videoCadastrado.resultado.frameFinal));
//        streamWriter.writeTextElement("erosao", QString::number(videoCadastrado.resultado.erosao));
//        streamWriter.writeTextElement("escala", QString::number(videoCadastrado.resultado.escala));

//    streamWriter.writeEndElement(); //fecha o elemento de informacoes
//    streamWriter.writeEndElement();


//    streamWriter.writeEndDocument();//começa o documento

//outputVideoEditado.close();

}

void telablind::lerVXML(QString nomeArquivoLer)
{
    OutVideo.setFileName(nomeArquivoLer);
    OutVideo.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutVideo); //passa o endereço

    QString conversor;

    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        if(streamReader.name()== "nomeOpencv"){
        videoLista.nomeOpencv.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }


           if(streamReader.name()== "frameInicial"){

         conversor = streamReader.readElementText();
        videoLista.frameInicial.push_back(conversor.toInt());
              // qDebug() << leitorXML.readElementText();
           }

           if(streamReader.name()== "frameFinal"){
               conversor = streamReader.readElementText();
        videoLista.frameFinal.push_back(conversor.toInt());
              // qDebug() << leitorXML.readElementText();
           }



           if(streamReader.name() == "frameProces"){
               conversor = streamReader.readElementText();
        videoLista.frameProces.push_back(conversor.toInt());


           }
            if(streamReader.name() == "frameBack"){

                conversor = streamReader.readElementText();
         videoLista.frameBack.push_back(conversor.toInt());

            }



            if(streamReader.name() == "treshold"){

                       conversor = streamReader.readElementText();

                       videoLista.threshold.push_back(conversor.toInt());

              }

           if(streamReader.name() == "erosao"){

               conversor = streamReader.readElementText();
        videoLista.erosao.push_back(conversor.toInt());

           }


           if(streamReader.name() == "escala"){

               conversor = streamReader.readElementText();
        videoLista.escala.push_back(conversor.toDouble());

           }

           if(streamReader.name() == "fps"){

               conversor = streamReader.readElementText();
        videoLista.fps.push_back(conversor.toInt());

           }

           if(streamReader.name()== "proImageOn"){ //se foi cadastrado para o processamento de imagem

               conversor = streamReader.readElementText();
               if(conversor=="true"){
                   videoLista.chProImaOn.push_back(true); //tem o processamento de imagem

               }else{

                   videoLista.chProImaOn.push_back(false);

               }


           }

           if(streamReader.name()== "janelaInteresse"){

               if(chaJanInte==true){
                   chaJanInte=false;

               }else{
                   chaJanInte=true;

                   videoLista.areaJanInte.push_back(auxArea1);

               }
           }

           if(chaJanInte==true){
               if(streamReader.name() == "ativado"){

                   conversor = streamReader.readElementText();

                   if(conversor=="false"){
                     videoLista.chaInteMoveAtivado.push_back(false);
                   }else{
                     videoLista.chaInteMoveAtivado.push_back(true);
                   }


               }


               if(streamReader.name() == "movel"){

                   conversor = streamReader.readElementText();

                   if(conversor=="false"){
                     videoLista.chaInteMove.push_back(false);
                   }else{
                     videoLista.chaInteMove.push_back(true);
                   }


               }

               if(streamReader.name() == "origX"){

                   conversor = streamReader.readElementText();

                     videoLista.areaJanInte[contadorDeVideo].oriX.push_back(conversor.toDouble());

               }
               if(streamReader.name() == "origY"){

                conversor = streamReader.readElementText();
                videoLista.areaJanInte[contadorDeVideo].oriY.push_back(conversor.toDouble());

               }

               if(streamReader.name() == "width"){

                conversor = streamReader.readElementText();
                videoLista.areaJanInte[contadorDeVideo].width.push_back(conversor.toDouble());

               }
               if(streamReader.name() == "heigth"){

                conversor = streamReader.readElementText();
                videoLista.areaJanInte[contadorDeVideo].height.push_back(conversor.toDouble());

               }

           }


           if(streamReader.name()== "maximaVariacaoCentro"){

               if(chaMaxVari==true){
                   chaMaxVari=false;

               }else{
                   chaMaxVari=true;
                   //videoLista.areaJanInte.push_back(auxArea);

               }
           }

           if(chaMaxVari){

               if(streamReader.name() == "tamanho"){

                conversor = streamReader.readElementText();
                videoLista.tamMaxVar.push_back(conversor.toDouble());

               }


           }







           if(streamReader.name()== "areasDeInteresse"){

               if(chaveArea==true){
                   chaveArea=false;

               }else{
                   chaveArea=true;
                   videoLista.area.push_back(auxArea);

               }
           }

           if(chaveArea==true){


               if(streamReader.name()== "area"){

               QString conversora= streamReader.attributes().value("tipo").toString();
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

               if(streamReader.name() == "nomeFig"){

                   conversor = streamReader.readElementText();
                   videoLista.area[contadorDeVideo].nomeFig.push_back(conversor);
                   //auxArea.oriX =  conversor.toDouble();

               }


               if(streamReader.name() == "oriX"){

                   conversor = streamReader.readElementText();
                   videoLista.area[contadorDeVideo].oriX.push_back(conversor.toDouble());
                   //auxArea.oriX =  conversor.toDouble();

               }

               if(streamReader.name() == "oriY"){

                   conversor = streamReader.readElementText();
                   videoLista.area[contadorDeVideo].oriY.push_back(conversor.toDouble());
                   //auxArea.oriY =  conversor.toDouble();

               }

               if(streamReader.name() == "height"){

                   conversor = streamReader.readElementText();
                   videoLista.area[contadorDeVideo].height.push_back(conversor.toDouble());
                   //auxArea.height =  conversor.toDouble();

               }

               if(streamReader.name() == "width"){

                   conversor = streamReader.readElementText();
                   videoLista.area[contadorDeVideo].width.push_back(conversor.toDouble());
                  // auxArea.width =  conversor.toDouble();

               }

               if(streamReader.name() == "rad"){

                   conversor = streamReader.readElementText();
                   videoLista.area[contadorDeVideo].raio.push_back(conversor.toDouble());
                   //auxArea.raio =  conversor.toDouble();

               }//fim if rad




           }//fim chave das areas






        }//fim while



    //videoLista.quantidadeDeDados++; //= contadorTamanho; //conta quantidade de dados;


   OutVideo.close();
}





//void telablind::on_pbTeste_clicked()
//{
//    qDebug () <<"inicio" << QThread::currentThreadId();
//    listaVideo = QFileDialog::getOpenFileName();
//    caminhoArquivo = QFileDialog::getExistingDirectory();

//    editaVideo = new moduloEditaVideo();
//    novaThread = new QThread();

//    connect(this,SIGNAL(enviIncio(QString,QString,QString)),editaVideo,SLOT(iniGraVidoCego(QString,QString,QString)));
//    connect(editaVideo,SIGNAL(setProgres(int,int)),ui->progressBar,SLOT(setRange(int,int)));
//    connect(editaVideo,SIGNAL(frame(int)),ui->progressBar,SLOT(setValue(int)));


//    editaVideo->moveToThread(novaThread);

//    novaThread->start();

//    emit enviIncio(listaVideo,caminhoArquivo,"patiRFID1Pati11l121");

//    //editaVideo->iniGraVidoCego(listaVideo,caminhoArquivo,"patiRFID1Pati11l1");

//    qDebug () <<"fim do TESTE" << QThread::currentThreadId();

//}

//void telablind::on_pushButton_clicked()
//{

//}

void telablind::on_pbBliding_clicked()
{
    qDebug () <<"inicio" << QThread::currentThreadId();
    ui->staWidPrin->setCurrentIndex(1);

    QVBoxLayout *vlay = new QVBoxLayout(ui->saProgress);


    //listaVideo = QFileDialog::getOpenFileName();
    //caminhoArquivo = QFileDialog::getExistingDirectory();
    for(int jk=0; jk<nomeDosVideosAleatorizado.size() ;jk++){

        editaVideo = new moduloEditaVideo();
        novaThread = new QThread();
        progre = new QProgressBar();

        listaDeThread.push_back(novaThread);
        listaEditaVideo.push_back(editaVideo);
        listaPB.push_back(progre);


    }



    for(int jl=0; jl<nomeDosVideosAleatorizado.size() ;jl++){



        vlay->addWidget(listaPB[jl]);

    //colocando os botões no layute faz aparecer na tela
    ui->saProgress->setLayout(vlay);


    //comeca o blinding
    listaEditaVideo[jl]->setKey(expKey.nome, expKey.lab, expKey.senha);
     connect(this,SIGNAL(enviIncio(QString,QString,QString,int)),listaEditaVideo[jl],SLOT(iniGraVidoCego(QString,QString,QString,int)));
     connect(listaEditaVideo[jl],SIGNAL(setProgres(int,int)),listaPB[jl],SLOT(setRange(int,int)));
     connect(listaEditaVideo[jl],SIGNAL(frame(int)),listaPB[jl],SLOT(setValue(int)));
     listaEditaVideo[jl]->moveToThread(listaDeThread[jl]);

     listaDeThread[jl]->start();

     QString textoEditado;
     textoEditado =ui->leNomePadr->text()+QString::number(jl);

     qDebug() << "arquivo vxml é o"<< nomeDosVideosAleatorizado[jl];
     emit enviIncio(nomeDosVideosAleatorizado[jl],caminhoArquivo, textoEditado,ui->comboBoX->currentIndex());

     disconnect(this,SIGNAL(enviIncio(QString,QString,QString,int)),listaEditaVideo[jl],SLOT(iniGraVidoCego(QString,QString,QString,int)));


    }




//    editaVideo->moveToThread(novaThread);

//    novaThread->start();

//    emit enviIncio(nomeDosVideosAleatorizado[0],caminhoArquivo,ui->leNomePadr->text());

    //editaVideo->iniGraVidoCego(listaVideo,caminhoArquivo,"patiRFID1Pati11l1");

    qDebug () <<"fim do TESTE" << QThread::currentThreadId();


    this->grava_lista_chaves();

    //nomeDosVideosAleatorizado[i]
}


void telablind::grava_lista_chaves(){

    QString nomeArquivoGravarCsv;
    nomeArquivoGravarCsv = QFileDialog::getSaveFileName(
                 this,
                 tr("Save File"),
                 "C://",
                "csv Files (*.csv)"
                );

    QFile outGravador;
    outGravador.setFileName(nomeArquivoGravarCsv);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador <<"EthoWatcher Open Source \n";
    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";

    csvGravador <<" Blinded video register ;" <<"Original video register" << "\n"; //"Arquivo de cadastro do video original;" << "Arquivo de video original"<<
    int ak=0;
    int max=0;
    int cont=0;

    std::vector<QString> vxml;

    for(int jl=0; jl<nomeDosVideosAleatorizado.size() ;jl++){

      QString textoEditado;
      textoEditado =ui->leNomePadr->text()+QString::number(jl);
      csvGravador << caminhoArquivo +"/"+ textoEditado << ";" << nomeDosVideosAleatorizado[jl] <<"\n";

    }


    ////        vlay->addWidget(listaPB[jl]);

    //    //colocando os botões no layute faz aparecer na tela
    //    ui->saProgress->setLayout(vlay);


    //    //comeca o blinding
    //    listaEditaVideo[jl]->setKey(expKey.nome, expKey.lab, expKey.senha);
    //     connect(this,SIGNAL(enviIncio(QString,QString,QString,int)),listaEditaVideo[jl],SLOT(iniGraVidoCego(QString,QString,QString,int)));
    //     connect(listaEditaVideo[jl],SIGNAL(setProgres(int,int)),listaPB[jl],SLOT(setRange(int,int)));
    //     connect(listaEditaVideo[jl],SIGNAL(frame(int)),listaPB[jl],SLOT(setValue(int)));
    //     listaEditaVideo[jl]->moveToThread(listaDeThread[jl]);

    //     listaDeThread[jl]->start();

    //     QString textoEditado;
    //     textoEditado =ui->leNomePadr->text()+QString::number(jl);

    //     qDebug() << "arquivo vxml é o"<< nomeDosVideosAleatorizado[jl];

    outGravador.close();
}



void telablind::on_pbSetUserKey_clicked()
{
//    QString fonteVideo;
//    fonteVideo = QFileDialog::getOpenFileName(
//                this,
//                tr("Open File"),
//               "C:/ethowatcher/usuariosCadastrados",
//               "User Files (*.uxml)"
//                );



//    outputKey.setFileName(fonteVideo); //seta o nome do arquivo

//    QXmlStreamReader xmlReader(&outputKey);
//    //output.open(QIODevice::ReadOnly | QIODevice::Text);
//    outputKey.open(QIODevice::ReadOnly | QIODevice::Text);

//    while(!xmlReader.atEnd() && !xmlReader.hasError()){


//        xmlReader.readNext();

//        //pega os nome dos arquivos que devem ser abertos
//        if(xmlReader.name()== "nome"){
//        expKey.nome = xmlReader.readElementText() ;

//        }

//        if(xmlReader.name() == "laboratorio"){

//            expKey.lab = xmlReader.readElementText() ;

//        }

//        if(xmlReader.name() == "password"){
//            expKey.senha = xmlReader.readElementText() ;
//        }


//    }
//    output.close();


}
