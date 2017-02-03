#include "moduloeditavideo.h"

moduloEditaVideo::moduloEditaVideo(QObject *parent) : QObject(parent)
{
    //video = new cv::VideoCapture();



}

moduloEditaVideo::~moduloEditaVideo()
{
    qDebug()<< "finalizando edicao de video 0";
  //  setFimVideo();
   // setFimGraVideo();
    qDebug()<< "finalizando edicao de video 1";

}

void moduloEditaVideo::setOpenVideo(QString noVideo)
{
    video = new cv::VideoCapture();
    video->open(noVideo.toStdString());

    if(video->isOpened()){

        dWidth = video->get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
       dHeight = video->get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
        videoFps = video->get(CV_CAP_PROP_FPS);
    }


   // video.

}

void moduloEditaVideo::setGravaVideo(QString noVideoGravado, int codecX)
{
    qDebug() << "setando o gravador";
    videoEditado = new cv::VideoWriter();

    //videoEditado->open()


   // int codec = CV_FOURCC('x', '2', '6', '4');
   // codecX=

    cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
    //cv codec XVID 1684633208
    //cv codec H264 875967096

   videoEditado->open(noVideoGravado.toStdString(), codecX, videoLista.fps[0] ,frameSize,true);

   if(videoEditado->isOpened()){


   }else{

       qDebug() << "nao abriu para gravar";
   }


}

void moduloEditaVideo::graVideo(double fInicio, double fFinal)
{

    if(videoEditado->isOpened()){

        for(double i=  fInicio ; i<=  fFinal ;i++){
            video->set(CV_CAP_PROP_FRAME_COUNT,i);
            video->read(framVideo);
            videoEditado->write(framVideo);

        }
    }


}

void moduloEditaVideo::setIniFim(double frInicio, double frFim)
{
    framInicio = frInicio;
    framFim = frFim;
}




void moduloEditaVideo::graVideo() //funcao que vem para gravar o video
{
    if(videoEditado->isOpened()){

        for(double i= videoLista.frameInicial[0]  ; i<=  videoLista.frameFinal[0] ;i++){
            video->set(CV_CAP_PROP_FRAME_COUNT,i);
            video->read(framVideo);
            videoEditado->write(framVideo);

        }
    }


}





void moduloEditaVideo::setFimVideo()
{
    if(video->isOpened()){


    }
    video->release();

    qDebug()<<"release filme";
}

void moduloEditaVideo::setFimGraVideo()
{
    videoEditado->release();
    qDebug()<<"release gravacao";
}

void moduloEditaVideo::lendoVideoXml(int qualLer)
{
    //out off date
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

double moduloEditaVideo::getInicioVideo()
{
    return videoLista.frameInicial[0];
}

double moduloEditaVideo::getFimVideo()
{
 return videoLista.frameFinal[0];
}

void moduloEditaVideo::iniGraVidoCego(QString arquivoVideo,QString nomeCaminhoEditado, QString nomeVideoEditado, int codec)
{

     gravarNomeCaminhoVideo = nomeCaminhoEditado+"/"+nomeVideoEditado+".avi";
     gravarNomeVideo = nomeVideoEditado+".avi";
    if(readXmlVideoOrignal(arquivoVideo)){

        setOpenVideo(videoLista.nomeOpencv[0]); //nome opencv do arquivo

        codecVideo=getCodec(codec);
        setGravaVideo(nomeCaminhoEditado+"/"+nomeVideoEditado+".avi", getCodec(codec));
        //writXmlVideoCego(videoEditado);
        //int i;
         double ia;
          emit setProgres((int) videoLista.frameInicial[0], (int) videoLista.frameFinal[0] );

          qDebug() << videoLista.frameInicial[0] << videoLista.frameFinal[0];
        if(videoEditado->isOpened()){

            double testFinal =(videoLista.frameFinal[0]- videoLista.frameInicial[0]);
            tinicial = clock();




            for(ia= 0  ; ia<= testFinal  ;ia++){
                video->set(CV_CAP_PROP_POS_FRAMES,videoLista.frameInicial[0]+ ia);

                video->read(framVideo);
//                cv::imshow(arquivoVideo.toStdString(),framVideo);
//                cv::waitKey(20);

                if(!framVideo.empty()){

                  videoEditado->write(framVideo);
                }else{
                    qDebug()<<"erro em ler o foto para gravar";
                }

                //qDebug() << i << QThread::currentThreadId();

                if(((int) ia%100)==0){

                    emit frame( (int) (ia + videoLista.frameInicial[0]));
                }

            }

            tfinal = clock();

            tresposta=(float) (tfinal-tinicial)/CLOCKS_PER_SEC;

                emit frame( (int) videoLista.frameFinal[0] );


            setFimVideo();
            setFimGraVideo();

            qDebug () <<"acabouu";

        }else{

            qDebug() << "final";
        }


        writXmlVideoCego(nomeCaminhoEditado+"/"+ nomeVideoEditado+".vcxml");




    }else{




    }


}

void moduloEditaVideo::iniGraFluxoComportamento(QString nomeVXML, QString nomeEditado, QList<int> frameInicio, QList<int> frameFinal,int codec)
{

    if(readXmlVideoOrignal(nomeVXML)){

        setOpenVideo(videoLista.nomeOpencv[0]); //nome opencv do arquivo
        setGravaVideo(nomeEditado,getCodec(codec)); //transforma o inicide em um codec da opencv

        double kb=0;

        emit setProgres((int) 0, (int) frameInicio.size() );

        tinicial = clock();

        for(int ka=0; ka<frameInicio.size(); ka++){


            for( kb= frameInicio[ka]  ; kb< frameFinal[ka]  ;kb++){
                video->set(CV_CAP_PROP_POS_FRAMES,kb);

                video->read(framVideo);
    //                cv::imshow(arquivoVideo.toStdString(),framVideo);
    //                cv::waitKey(20);

                videoEditado->write(framVideo);


            }


            emit frame( (int) ka+1 );

        }

         tfinal = clock();
         tresposta=(float) (tfinal-tinicial)/CLOCKS_PER_SEC;

        setFimVideo();
        setFimGraVideo();

        qDebug()<<"finalizou " <<tresposta << " s";




    }



}

void moduloEditaVideo::lerVXML(QString nomeArquivoLer)
{
    OutVideo.setFileName(nomeArquivoLer);
    OutVideo.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutVideo); //passa o endereço

    QString conversor;

    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        if(streamReader.name()== "nomePesquisador"){
        videoLista.nomePesquisador.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name()== "laboratorio"){
        videoLista.laboratorio.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }


        if(streamReader.name()== "tituloExperimento"){
        videoLista.tituloExperimento.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name()== "data"){
        videoLista.data.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name()== "otherInfo"){
        videoLista.otherInfo.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name()== "animalID"){
        videoLista.animalID.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }
        if(streamReader.name()== "wight"){
        videoLista.wight.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name()== "animalSex"){
        videoLista.animalSex.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }
        if(streamReader.name()== "nomePesquisador"){
        videoLista.nomePesquisador.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

        if(streamReader.name()== "threatmen"){
        videoLista.threatmen.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }

//        bool chaveDadoOriginal= false;

        if(streamReader.name()== "dadoOriginal"){

            if(chaveDadoOriginal==true){
                chaveDadoOriginal=false;

            }else{
                chaveDadoOriginal=true;
                //videoLista.area.push_back(auxArea);

            }
        }

        if(chaveDadoOriginal==true){

//            std::vector<double> quantidadeFrames;
//            std::vector<double> quantidadeTempo;
//            std::vector<double> width;
//            std::vector<double> height;

            if(streamReader.name()== "quantidadeFrames"){
            videoLista.quantidadeFrames.push_back(streamReader.readElementText().toDouble());
               //qDebug() << leitorXML.readElementText();

            }


            if(streamReader.name()== "quantidadeTempo"){
            videoLista.quantidadeTempo.push_back(streamReader.readElementText().toDouble());
               //qDebug() << leitorXML.readElementText();

            }
            if(streamReader.name()== "width"){
            videoLista.width.push_back(streamReader.readElementText().toDouble());
               //qDebug() << leitorXML.readElementText();

            }
            if(streamReader.name()== "height"){
            videoLista.height.push_back(streamReader.readElementText().toDouble());
               //qDebug() << leitorXML.readElementText();

            }


        }





        if(streamReader.name()== "nomeArquivoVXML"){
        videoLista.nomeArquivoVXML.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();

        }




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

               if(streamReader.name()== "ativado"){

                   conversor = streamReader.readElementText();


                   if(conversor=="true"){
                           videoLista.chaMaxVar.push_back(true);

                   }else{

                          videoLista.chaMaxVar.push_back(false);


                   }

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





bool moduloEditaVideo::readXmlVideoOrignal(QString nomeArquivoEditado)
{
//    output.setFileName(nomeArquivoEditado);
//    output.open(QIODevice::ReadOnly | QIODevice::Text);

    lerVXML(nomeArquivoEditado);

    if(!videoLista.nomeOpencv[0].isEmpty()){

        qDebug() << videoLista.nomeOpencv[0] << "foi";
       return true;

    }else{

      qDebug() << videoLista.nomeOpencv[0] + "nao encontrou o video";
      return false;

    }
//    if(output.isOpen())
//    {
////        lendoVideoXml(0);
////        lendoVideoXml(1);
////        lendoVideoXml(2);
////        lendoVideoXml(3);


//         output.close();
//


//    }else{


//        qDebug() << "nao encontrou o video";
//        return false;


//    }




}

void moduloEditaVideo::writXmlVideoCego(QString nomeArquivoEditado)
{



    QFile outputVideoEditado(nomeArquivoEditado);

    outputVideoEditado.open(QIODevice::WriteOnly);


    QXmlStreamWriter stream(&outputVideoEditado); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento



    stream.writeStartElement("videoCego"); //abre o cadastroVideo
    stream.writeStartElement("key"); //abre o elemento de informacoes
    stream.writeTextElement("a", rsa.criptoRSAQstring(key.senha));
    stream.writeTextElement("b", rsa.criptoRSAQstring(key.lab));
    stream.writeTextElement("c", rsa.criptoRSAQstring(key.nome));
    stream.writeTextElement("tempoGasto", QString::number(tresposta));
    stream.writeTextElement("codecUtilizado",QString::number(codecVideo));
    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("videoCegoEditado");
    stream.writeStartElement("dadoPesquisador"); //abre o elemento de informacoes

    stream.writeTextElement("nomePesquisador",rsa.criptoRSAQstring( experimentador.nome));
    stream.writeTextElement("laboratorio", rsa.criptoRSAQstring(experimentador.lab));

    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("dadoExperimento"); //abre o elemento de informacoes

    //    std::vector<QString> laboratorio;
    //    std::vector<QString> tituloExperimento;
    //    std::vector<QString> data;
    //    std::vector<QString> otherInfo;
    //    std::vector<QString> animalID;
    //    std::vector<QString> wight;
    //    std::vector<QString> animalSex;
    //    std::vector<QString> nomePesquisador;
    //    std::vector<QString> threatmen;

    //    std::vector<double> quantidadeFrames;
    //    std::vector<double> quantidadeTempo;
    //    std::vector<double> width;
    //    std::vector<double> height;
    stream.writeTextElement("tituloExperimento", rsa.criptoRSAQstring( videoLista.tituloExperimento[0]));
    stream.writeTextElement("data",  rsa.criptoRSAQstring(videoLista.data[0]) );
    stream.writeTextElement("otherInfo",rsa.criptoRSAQstring( videoLista.otherInfo[0]));
    stream.writeTextElement("animalID", rsa.criptoRSAQstring(videoLista.animalID[0]));
    stream.writeTextElement("wight",rsa.criptoRSAQstring(videoLista.wight[0]));
    stream.writeTextElement("animalSex", rsa.criptoRSAQstring(videoLista.animalSex[0]));
    stream.writeTextElement("threatmen", rsa.criptoRSAQstring(videoLista.threatmen[0]));

    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("dadoOriginal"); //abre o elemento de dado original

    //qDebug()<<"1";
   // qDebug()<<videoLista.nomeArquivoVXML[0];
    stream.writeTextElement("nomeArquivoVXML",rsa.criptoRSAQstring(nomeArquivoEditado));

   // qDebug()<<gravarNomeCaminhoVideo;
    stream.writeTextElement("nomeOpencv",rsa.criptoRSAQstring(gravarNomeCaminhoVideo)); //rsa.criptoRSAQstring(videoLista.nomeOpencv[0]));
    //         stream.writeTextElement("caminho", videoLista.caminho);
   //  stream.writeTextElement("nomeOriginal", videoLista.nome[0]);
      //   stream.writeTextElement("extensao", videoLista.ext)*///;
    stream.writeTextElement("fps",rsa.criptoRSAQstring( QString::number(videoLista.fps[0])));
   // qDebug()<<videoLista.fps[0];
    stream.writeTextElement("quantidadeFrames", rsa.criptoRSAQstring(QString::number(videoLista.frameFinal[0]-videoLista.frameInicial[0])));
   //qDebug()<<videoLista.frameFinal[0];
  // qDebug()<<videoLista.frameInicial[0];
    stream.writeTextElement("quantidadeTempo", rsa.criptoRSAQstring(QString::number((videoLista.frameFinal[0]-videoLista.frameInicial[0])/videoLista.fps[0])));


   // qDebug()<<videoLista.width[0];
    stream.writeTextElement("width",rsa.criptoRSAQstring( QString::number(videoLista.width[0])));
   // qDebug()<<videoLista.height[0];
    stream.writeTextElement("height",rsa.criptoRSAQstring(QString::number(videoLista.height[0])));

    //qDebug()<<"2";

    stream.writeEndElement(); //fecha o elemento de dado original

    stream.writeStartElement("dadoCalibracaoEdicao");

    stream.writeTextElement("frameInicial", rsa.criptoRSAQstring(QString::number (0)));
    stream.writeTextElement("frameBack", rsa.criptoRSAQstring(QString::number(videoLista.frameBack[0]-videoLista.frameInicial[0])));
    stream.writeTextElement("frameFinal",rsa.criptoRSAQstring(QString::number(videoLista.frameFinal[0]-videoLista.frameInicial[0])));
    stream.writeTextElement("frameProces",rsa.criptoRSAQstring(QString::number(videoLista.frameProces[0]-videoLista.frameInicial[0])));
    stream.writeTextElement("treshold",rsa.criptoRSAQstring(QString::number(videoLista.threshold[0])));
    stream.writeTextElement("erosao", rsa.criptoRSAQstring(QString::number(videoLista.erosao[0])));
    stream.writeTextElement("escala", rsa.criptoRSAQstring(QString::number(videoLista.escala[0])));


   // qDebug()<<"3";

    if(videoLista.chProImaOn[0]){

        stream.writeTextElement("proImageOn", rsa.criptoRSAQstring("true"));

    }else{

        stream.writeTextElement("proImageOn", rsa.criptoRSAQstring("false"));
    }


   // qDebug()<<"4";
    stream.writeStartElement("tratamentoRuido");

    stream.writeStartElement("janelaInteresse");
    if(videoLista.chaInteMoveAtivado[0]){// janela de interesse

        stream.writeTextElement("ativado", rsa.criptoRSAQstring("true"));
        if(videoLista.chaInteMove[0]){//
            stream.writeTextElement("movel",rsa.criptoRSAQstring("true"));
        }else{
            stream.writeTextElement("movel",rsa.criptoRSAQstring("false"));
        }

        std::vector<QString> tipo;

        int id;


        stream.writeTextElement("origX",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].oriX[0] ))); //px
        stream.writeTextElement("origY",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].oriY[0]))); //px
        stream.writeTextElement("width",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].width[0]))); //px
        stream.writeTextElement("heigth",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].height[0]))); //px


    }else{
        stream.writeTextElement("ativado",rsa.criptoRSAQstring("false"));

        stream.writeTextElement("movel",rsa.criptoRSAQstring("false"));
        stream.writeTextElement("origX",rsa.criptoRSAQstring(QString::number(0)));
        stream.writeTextElement("origY",rsa.criptoRSAQstring(QString::number(0)));
        stream.writeTextElement("width",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].width[0]))); //px
        stream.writeTextElement("heigth",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].height[0]))); //px



    }


    //qDebug()<<"5";
    stream.writeEndElement();

    stream.writeStartElement("maximaVariacaoCentro");

    if(videoLista.chaMaxVar[0]){// habilita maxima variação

        stream.writeTextElement("ativado",rsa.criptoRSAQstring("true"));
        stream.writeTextElement("tamanho",rsa.criptoRSAQstring(QString::number(videoLista.tamMaxVar[0])));

    }else{
        stream.writeTextElement("ativado",rsa.criptoRSAQstring("false"));

        stream.writeTextElement("tamanho",rsa.criptoRSAQstring(QString::number(videoLista.tamMaxVar[0])));
    }


    stream.writeEndElement();



    stream.writeEndElement();


    stream.writeStartElement("areasDeInteresse");


    int ka,ja;


//qDebug()<<"6";

    int contRec=0;
    int contCir=0;
    for(ka=0; ka< videoLista.area[0].tipo.size();ka++){

        // if(videoLista.area[0].tipo[ka]== "circle"){

        stream.writeStartElement("area");
        stream.writeAttribute("id",rsa.criptoRSAQstring(QString::number(ka)));
        if(videoLista.area[0].tipo[ka]== "rectangle")
        {
            stream.writeAttribute("tipo",rsa.criptoRSAQstring("rectangle"));
            contRec++;
        }else{

            stream.writeAttribute("tipo",rsa.criptoRSAQstring("circle"));
            contCir++;
        }

        stream.writeTextElement("nomeFig",rsa.criptoRSAQstring( videoLista.area[0].nomeFig[ka]));
        stream.writeTextElement("oriX",rsa.criptoRSAQstring(QString::number(videoLista.area[0].oriX[ka])));
        stream.writeTextElement("oriY",rsa.criptoRSAQstring(QString::number(videoLista.area[0].oriY[ka])));





        if(videoLista.area[0].tipo[ka]== "rectangle")
        {
            stream.writeTextElement("height",rsa.criptoRSAQstring(QString::number(videoLista.area[0].height[contRec-1])));
            stream.writeTextElement("width",rsa.criptoRSAQstring(QString::number(videoLista.area[0].width[contRec-1])));

        }else{

            stream.writeTextElement("rad",rsa.criptoRSAQstring(QString::number(videoLista.area[0].raio[contCir-1])));
            //pq na verdade o que ele grava é o diametro

        }

        stream.writeEndElement();
    }




    stream.writeEndElement();



    stream.writeEndElement(); //abre o cadastroVideo
    //stream.writeEndDocument(); //fecha o documento


    stream.writeEndElement(); //fecha o elemento de informacoes //fechado video editado



    /*

        fim do video cego
        inicio do video original


*/
    stream.writeStartElement("videoOriginal"); //abre o cadastroVideo


//    stream.writeStartElement("key"); //abre o elemento de informacoes
//    stream.writeTextElement("a", key.senha);
//    stream.writeTextElement("b", key.lab);
//    stream.writeTextElement("c", key.nome);
//    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("videoEditado");
    stream.writeStartElement("dadoPesquisador"); //abre o elemento de informacoes

    stream.writeTextElement("nomePesquisador",rsa.criptoRSAQstring( experimentador.nome));
    stream.writeTextElement("laboratorio",rsa.criptoRSAQstring( experimentador.lab));

    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("dadoExperimento"); //abre o elemento de informacoes

    //    std::vector<QString> laboratorio;
    //    std::vector<QString> tituloExperimento;
    //    std::vector<QString> data;
    //    std::vector<QString> otherInfo;
    //    std::vector<QString> animalID;
    //    std::vector<QString> wight;
    //    std::vector<QString> animalSex;
    //    std::vector<QString> nomePesquisador;
    //    std::vector<QString> threatmen;

    //    std::vector<double> quantidadeFrames;
    //    std::vector<double> quantidadeTempo;
    //    std::vector<double> width;
    //    std::vector<double> height;
    stream.writeTextElement("tituloExperimento", rsa.criptoRSAQstring(videoLista.tituloExperimento[0]));
    stream.writeTextElement("data",  rsa.criptoRSAQstring(videoLista.data[0] ));
    stream.writeTextElement("otherInfo",rsa.criptoRSAQstring( videoLista.otherInfo[0]));
    stream.writeTextElement("animalID", rsa.criptoRSAQstring(videoLista.animalID[0]));
    stream.writeTextElement("wight",rsa.criptoRSAQstring(videoLista.wight[0]));
    stream.writeTextElement("animalSex", rsa.criptoRSAQstring(videoLista.animalSex[0]));
    stream.writeTextElement("threatmen", rsa.criptoRSAQstring(videoLista.threatmen[0]));

    stream.writeEndElement(); //fecha o elemento de informacoes

    //escrita dos valores antigos

    stream.writeStartElement("dadoOriginal"); //abre o elemento de dado original

    stream.writeTextElement("nomeOpencv", rsa.criptoRSAQstring(videoLista.nomeOpencv[0]));
    stream.writeTextElement("nomeArquivoVXML",rsa.criptoRSAQstring(videoLista.nomeArquivoVXML[0]));
    /*         stream.writeTextElement("caminho", videoLista.caminho);
         stream.writeTextElement("nomeOriginal", videoLista.nome[0]);
         stream.writeTextElement("extensao", videoLista.ext)*/;
    stream.writeTextElement("fps", rsa.criptoRSAQstring(QString::number(videoLista.fps[0])));
    stream.writeTextElement("quantidadeFrames",rsa.criptoRSAQstring(QString::number(videoLista.quantidadeFrames[0])));
    stream.writeTextElement("quantidadeTempo", rsa.criptoRSAQstring(QString::number(videoLista.quantidadeTempo[0])));
    stream.writeTextElement("width", rsa.criptoRSAQstring(QString::number(videoLista.width[0])));
    stream.writeTextElement("height",rsa.criptoRSAQstring(QString::number(videoLista.height[0])));


    stream.writeEndElement(); //fecha o elemento de dado original

    stream.writeStartElement("dadoCalibracaoEdicao");

    stream.writeTextElement("frameInicial", rsa.criptoRSAQstring(QString::number (videoLista.frameInicial[0])));
    stream.writeTextElement("frameBack",rsa.criptoRSAQstring( QString::number(videoLista.frameBack[0])));
    stream.writeTextElement("frameFinal",rsa.criptoRSAQstring(QString::number(videoLista.frameFinal[0])));
    stream.writeTextElement("frameProces",rsa.criptoRSAQstring(QString::number(videoLista.frameProces[0])));
    stream.writeTextElement("treshold",rsa.criptoRSAQstring(QString::number(videoLista.threshold[0])));
    stream.writeTextElement("erosao", rsa.criptoRSAQstring(QString::number(videoLista.erosao[0])));
    stream.writeTextElement("escala", rsa.criptoRSAQstring(QString::number(videoLista.escala[0])));


    if(videoLista.chProImaOn[0]){

        stream.writeTextElement("proImageOn", rsa.criptoRSAQstring("true"));

    }else{

        stream.writeTextElement("proImageOn", rsa.criptoRSAQstring("false"));
    }

    stream.writeStartElement("tratamentoRuido");

    stream.writeStartElement("janelaInteresse");
    if(videoLista.chaInteMoveAtivado[0]){// janela de interesse

        stream.writeTextElement("ativado",rsa.criptoRSAQstring("true"));
        if(videoLista.chaInteMove[0]){//
            stream.writeTextElement("movel",rsa.criptoRSAQstring("true"));
        }else{
            stream.writeTextElement("movel",rsa.criptoRSAQstring("false"));
        }

        std::vector<QString> tipo;

        int id;


        stream.writeTextElement("origX", rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].oriX[0] ))); //px
        stream.writeTextElement("origY",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].oriY[0]))); //px
        stream.writeTextElement("width",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].width[0]))); //px
        stream.writeTextElement("heigth",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].height[0]))); //px


    }else{
        stream.writeTextElement("ativado",rsa.criptoRSAQstring("false"));

        stream.writeTextElement("movel",rsa.criptoRSAQstring("false"));
        stream.writeTextElement("origX",rsa.criptoRSAQstring(QString::number(0)));
        stream.writeTextElement("origY",rsa.criptoRSAQstring(QString::number(0)));
        stream.writeTextElement("width",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].width[0]))); //px
        stream.writeTextElement("heigth",rsa.criptoRSAQstring(QString::number(videoLista.areaJanInte[0].height[0]))); //px



    }



    stream.writeEndElement();

    stream.writeStartElement("maximaVariacaoCentro");

    if(videoLista.chaMaxVar[0]){// habilita maxima variação

        stream.writeTextElement("ativado",rsa.criptoRSAQstring("true"));
        stream.writeTextElement("tamanho",rsa.criptoRSAQstring(QString::number(videoLista.tamMaxVar[0])));

    }else{
        stream.writeTextElement("ativado",rsa.criptoRSAQstring("false"));

        stream.writeTextElement("tamanho",rsa.criptoRSAQstring(QString::number(videoLista.tamMaxVar[0])));
    }


    stream.writeEndElement();



    stream.writeEndElement();


    stream.writeStartElement("areasDeInteresse");


    //int ka,ja;




     contRec=0;
     contCir=0;
    for(ka=0; ka< videoLista.area[0].tipo.size();ka++){

        // if(videoLista.area[0].tipo[ka]== "circle"){

        stream.writeStartElement("area");
        stream.writeAttribute("id",rsa.criptoRSAQstring(QString::number(ka)));
        if(videoLista.area[0].tipo[ka]== "rectangle")
        {
            stream.writeAttribute("tipo",rsa.criptoRSAQstring("rectangle"));
            contRec++;
        }else{

            stream.writeAttribute("tipo",rsa.criptoRSAQstring("circle"));
            contCir++;
        }

        stream.writeTextElement("nomeFig", rsa.criptoRSAQstring(videoLista.area[0].nomeFig[ka]));
        stream.writeTextElement("oriX",rsa.criptoRSAQstring(QString::number(videoLista.area[0].oriX[ka])));
        stream.writeTextElement("oriY",rsa.criptoRSAQstring(QString::number(videoLista.area[0].oriY[ka])));





        if(videoLista.area[0].tipo[ka]== "rectangle")
        {
            stream.writeTextElement("height",rsa.criptoRSAQstring(QString::number(videoLista.area[0].height[contRec-1])));
            stream.writeTextElement("width",rsa.criptoRSAQstring(QString::number(videoLista.area[0].width[contRec-1])));

        }else{

            stream.writeTextElement("rad",rsa.criptoRSAQstring(QString::number(videoLista.area[0].raio[contCir-1])));
            //pq na verdade o que ele grava é o diametro

        }

        stream.writeEndElement();
    }




    stream.writeEndElement();



    stream.writeEndElement(); //abre o cadastroVideo
    stream.writeEndDocument(); //fecha o documento


    stream.writeEndElement(); //fecha o elemento de informacoes //fechado video editado



    outputVideoEditado.close(); //termina a gravacao






}

void moduloEditaVideo::setKey(QString nom, QString la, QString senh)
{

    key.senha= senh;
    key.lab = la;
    key.nome = nom;

}

int moduloEditaVideo::getCodec(int indexCaixa)
{
    switch (indexCaixa)
    {
    case 0:

        return CV_FOURCC('M','R','L','E'); //Microsoft RLE
        //break;
    case 1:

        return CV_FOURCC('C','R','A','M'); //Microsoft Video 1

    case 2:

        return CV_FOURCC('I','Y','U','V'); //Intel IYUV Codec

    case 3:
        return CV_FOURCC('C','V','I','D'); //Cinepack Codec by radius
        //break;
    case 4:
        return CV_FOURCC('L','A','G','S'); //Lagarith Lossles Codec

    case 5:
        return CV_FOURCC('X','2','6','4'); //H264

    case 6:
        return CV_FOURCC('X','V','I','D');; //XVid MPeg-4 Codec
        //break;
    case -1:
        return -1;
        break;
    }
}


