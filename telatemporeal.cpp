#include "telatemporeal.h"
#include "ui_telatemporeal.h"

telaTempoReal::telaTempoReal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaTempoReal)
{
    ui->setupUi(this);

    captadorDeVideo = new moduloCaptador();
    captadorThread = new QThread();

    captadorDeVideo->moveToThread(captadorThread);
    //connect(captadorThread,SIGNAL(started()),captadorDeVideo,SLOT(configurando()));
    connect(captadorThread,SIGNAL(started()),captadorDeVideo,SLOT(captandoRealTime()));
   // connect(captadorDeVideo,SIGNAL(fimConfiguracao()),captadorDeVideo,SLOT(captandoRealTime()));
    connect(captadorDeVideo,SIGNAL(enviaInformacoes(int,QImage,float)),this,SLOT(atualizaImagem(int,QImage,float)));
    connect(this,SIGNAL(desliga()),captadorDeVideo,SLOT(desligando()));
    //connect(captadorDeVideo,SIGNAL(entrouNoTermino()),this,SLOT(on_pbTerminarVideo_clicked()));

    connect(captadorDeVideo, SIGNAL(fimPrograma()), captadorThread, SLOT(quit()));
    connect(captadorDeVideo, SIGNAL(fimPrograma()), captadorDeVideo, SLOT(deleteLater()));
    connect(captadorThread, SIGNAL(finished()), captadorThread, SLOT(deleteLater()));



    dados = new moduloProcessamento();
    thrProce = new QThread();

    //dados->moveToThread(thrProce);

    ui->swPrincipal->setCurrentIndex(0); //começar no zero
    ui->widAquisi->setVisible(false);
    ui->widRegistro->setVisible(false);
    ui->widCapturaVide->setVisible(false);
    ui->widParadaFrame->setVisible(false);
    ui->widProceImagem->setVisible(false);

    ui->pbStarrFilming->setEnabled(false);
    ui->pbStopFilming->setEnabled(false);

    ui->pbTerminaGrava->setEnabled(false);


    ui->tabWControlador->setTabEnabled(0,false);
    ui->tabWControlador->setTabEnabled(1,false);
    ui->tabWControlador->setTabEnabled(2,false);
    ui->tabWControlador->setTabEnabled(3,false);

    chDesenhar=false;
    ui->staWidImgExibi->setCurrentIndex(0);


    captador = new moduloCaptador();

    escolheSelecao=false;  //true apenas um botão por vez
                          //false pode apertar todos os botões
    frame_atual=0;
    ui->pbGravaRelatorioFPS->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->pbPlanoFundo->setVisible(false);
    frameInicioGravacao=0;
    ui->pbSaveTraking->setVisible(false);
//    ui->tabWidget->set
    ui->tabWidget->setVisible(false);
}

telaTempoReal::~telaTempoReal()
{
    qDebug() << "terminando com o captadorthread0";

//    emit desliga();
//    captadorThread->deleteLater();
//    captadorThread->exit();
//    captadorDeVideo->deleteLater();
    delete captador;
    captadorDeVideo->desligando();
    delete ui;
    //delete this;
    qDebug() << "terminando com o captadorthread1";
}

//void telaTempoReal::on_pbTeste_clicked()
//{
//    captadorDeVideo->setCaptador(0);
//    int codi= CV_FOURCC('x', '2', '6', '4');
//    captadorDeVideo->confGravador("C:\\filmes\\treadfuncionando26.avi",30,300,false,codi);
//    //captadorDeVideo->setCapOn(false);



//    captadorThread->start();


//    std::cout <<"receptor esta na thread " << QThread::currentThreadId()  <<std::endl;
//    std::cout <<"receptor esta na thread " << QThread::currentThread()  <<std::endl;
//}

void telaTempoReal::atualizaImagem(int numeroFrame, QImage qimFoto,float Tempo)
{
    cv::Mat troca= captadorDeVideo->conQim2Mat(qimFoto);
    contTempo++;

    if(ui->cbCapturaVideo->isChecked()){

        frame_atual=contNumeroGrava;


    }else{


        frame_atual= numeroFrame;


    }

    if(!troca.empty()){

        cv::cvtColor(troca,troca,CV_BGR2RGB);

        QImage imgLida((uchar*)troca.data, troca.cols, troca.rows, troca.step, QImage::Format_RGB888);

       // qimFoto = imgLida.scaled(320,240,Qt::KeepAspectRatio);

        qimFoto = imgLida.scaled(640,480,Qt::KeepAspectRatio);
        //numeroFrameGlobal= numeroFrame;

        ui->lblNumero->setText(QString::number(numeroFrame));
        somaTempo=somaTempo+Tempo;
        ui->lblTempo->setText(QString::number(somaTempo));

        if(ui->cbRegistro->isChecked()){

            if(!ui->pbEtographyStart->isEnabled()){
               ui->lblTempoEto->setText("Time = "+QString::number(somaTempo-vetorTempoFrame[frameInicioRegistro])+"s");
            }

        }


        vetorTempoFrame.push_back(somaTempo);


        ui->lblFpsIsnta->setText(QString::number(1/Tempo));

    //    if(chFilmando){
    //        vetorFrameAquisicao.push_back(numeroFrame);
    //        vetorTempoAquisicao.push_back(Tempo);

    //    }


        //saida software
        if(!chDesenhar){

          ui->lblFoto->setPixmap(QPixmap::fromImage(qimFoto));
        }




        if((!ui->pbStarrFilming->isEnabled())&&(chTermina))
        {
             contNumeroGrava= contNumeroGrava+1;


             if((contNumeroGrava<ui->leFrameTotal->text().toInt())||(ui->cbParadaFrame->isChecked())){

                 ui->lblNumeroFilmin->setText(QString::number(contNumeroGrava));

                 somaTempoFilming= somaTempoFilming+Tempo;
                 ui->lblTempoFilming->setText(QString::number(somaTempoFilming));

                 if(!ui->pbEtographyStart->isEnabled()){
                      ui->lblTempoEto->setText("Time = "+QString::number(somaTempoFilming-vetorTempoFrame[frameInicioRegistro])+"s");
                 }

                 //ui->lblTempoEto->setText(QString::number(somaTempoFilming-frameInicioRegistro));

                 vetorFrameAquisicao.push_back(numeroFrame);
                 vetorTempoAquisicao.push_back(Tempo);


             }else{

                 ui->pbTerminaGrava->setEnabled(false);

                 ui->widBotFilming->setEnabled(false);
                 ui->widTextoFilming->setEnabled(false);
                 ui->pbTerminaGrava->setText("terminou");
                 ui->pbGravaRelatorioFPS->setEnabled(true);



             }

        }


    }


    if(ui->cbRegistro->isChecked()){

        if(contTempo%40==0){
           atualizaRegistro();
        }
       // atualizaRegistro();
    }




}

void telaTempoReal::on_pbStoCap_clicked()
{
    captadorDeVideo->setCapOn(false);

    ui->pbStartCaptador->setEnabled(true);
    ui->pbStoCap->setEnabled(false);
}

void telaTempoReal::on_pbStartCaptador_clicked()
{
    captadorDeVideo->getParamVideo();

    video_height = captadorDeVideo->video_heigth;
    video_width = captadorDeVideo->video_width;



    captadorDeVideo->setCapOn(true);
    ui->pbStartCaptador->setEnabled(false);
    ui->pbStoCap->setEnabled(true);
    ui->pbStarrFilming->setEnabled(true);



}

//void telaTempoReal::on_pushButton_clicked()
//{

//}

void telaTempoReal::on_pbPlanoFundo_clicked()
{
    thrProce->start();

    captadorDeVideo->getPlanoFundo();

    dados->frameBackground = captadorDeVideo->frameBackground.clone();

    cv::Mat frameDisplay=  dados->frameBackground .clone();
    cv::cvtColor(frameDisplay,frameDisplay,CV_BGR2RGB );
   // resultado.frameProces=frame_atual;
    //resultado.matProce= frameReduzido;
//        resultado.background=frame;

    cv::resize(frameDisplay,frameDisplay, cv::Size(160,120),0,0,cv::INTER_LANCZOS4);
    QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);

    ui->lblFundo->setPixmap(QPixmap::fromImage(imgLida));


    dados->setCalibracao(20,0);
    dados->setParametrosVideo(640,480);
    dados->confiCameraVir(0,0,640,480,false,false);

    qDebug() <<"error se passar";



    // dados->setBackground();



}

void telaTempoReal::on_pushButton_4_clicked()
{

    chDesenhar=true;
    ui->staWidImgExibi->setCurrentIndex(1);
    connect(captadorDeVideo,SIGNAL(enviaInformacoes(int,QImage,float)),dados,SLOT(processamentoDeVideoRealTime(int,QImage,float)));

    //connect(dados,SIGNAL(enviaQimage(QImage)),this,SLOT(recebeDesenho(QImage)));

    connect(dados,SIGNAL(desenhaFigura(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)),
            this,SLOT(recebeDesenho(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)));




    connect(dados,SIGNAL(dadosMorfoCinematico(QImage,bool,double,double,double,float,float,float,double,double,double,double,double,double,float,float,bool)),
                        this,SLOT(gravaDadosMorfoCinematico(QImage,bool,double,double,double,float,float,float,double,double,double,double,double,double,float,float,bool)));


    frameInicioPro = frame_atual;

    ui->pbFimProcessamento->setEnabled(true);



    if(ui->cbCapturaVideo->isChecked()){

        ui->pbStarrFilming->click();
    }

}

void telaTempoReal::recebeDesenho(QImage des1, bool desenhar, double centX, double centY, double poLongeX, double poLongey, double agulhX, double agulhy, double pRetaA1X, double pRetaA1Y, double pRetaA2X, double pRetaA2Y, double vtxX1, double vtxY1, double vtxX2, double vtxY2, double vtxX3, double vtxY3, double vtxX4, double vtxY4)
{

    widthPanProcess=ui->panProcess->size().width();
    heightPanProcess=ui->panProcess->size().height();
    contTempo++;

    if(chDesenhar){

         QPainter painter(&des1); //o pintor vai pintar nesse inderesso
         //define qual sera a caneta que ira pintar
         QPen canetaVermelha;
         canetaVermelha.setWidth(8);
         canetaVermelha.setColor(Qt::red);

         if(ui->chbCentroide->isChecked()){

             painter.setPen(canetaVermelha);
             painter.drawPoint(centX,centY);
         }

//         if(ui->chbTamnho->isChecked()){

//         QPen canetaPreta;
//         canetaPreta.setWidth(10);
//         canetaPreta.setColor(QColor(0,0,0));
//         painter.setPen(canetaPreta);
//         painter.drawPoint(agulhX,agulhy);

//         }



         if(ui->chbTamnho->isChecked()){

         QPen canetaAmarela;
         canetaAmarela.setWidth(4);
         canetaAmarela.setColor(QColor(0,255,255));
         painter.setPen(canetaAmarela);
         //painter.drawPoint(poLongeX,poLongey);

         painter.drawLine(QPointF(pRetaA1X,pRetaA1Y),
                          QPointF(pRetaA2X,pRetaA2Y));
//         painter.drawPoint(pRetaA1X,pRetaA1Y);
//         painter.drawPoint(pRetaA2X,pRetaA2Y);

         }


         //desenha o centro de massa


         if(ui->chbArea->isChecked()){
         QPen canetaQuadro;
         canetaQuadro.setWidth(6);
         canetaQuadro.setColor(QColor(255,100,255));
         painter.setPen(canetaQuadro);
         painter.drawPoint(vtxX1,vtxY1);
         painter.drawPoint(vtxX2,vtxY2);
         painter.drawPoint(vtxX3,vtxY3);
         painter.drawPoint(vtxX4,vtxY4);


         }

         int contCircle=0;
         int contREct=0;
         for(int ka1=0; ka1 < videoLista.area[contadorDeVideo].nomeFig.size(); ka1++){

             if(cheboxList[ka1]->isChecked()){

                 if(videoLista.area[contadorDeVideo].tipo[ka1]=="circle"){

                     painter.drawEllipse(videoLista.area[contadorDeVideo].oriX[ka1],
                                         videoLista.area[contadorDeVideo].oriY[ka1],
                                         videoLista.area[contadorDeVideo].raio[contCircle]*2,
                                         videoLista.area[contadorDeVideo].raio[contCircle]*2);



                 }else{

                     painter.drawRect(videoLista.area[contadorDeVideo].oriX[ka1],
                                      videoLista.area[contadorDeVideo].oriY[ka1],
                                      videoLista.area[contadorDeVideo].width[contREct],
                                      videoLista.area[contadorDeVideo].height[contREct]);






                 }


             }


             if(videoLista.area[contadorDeVideo].tipo[ka1]=="circle"){

                 contCircle++;

             }else{

                contREct++;

             }

         }




         QImage qimDisplay= des1.scaled(widthPanProcess,heightPanProcess,Qt::IgnoreAspectRatio);
         ui->panProcess->setPixmap(QPixmap::fromImage(qimDisplay));
    }



//    //qiFundo = qiCaptador;

//     QPainter painter(&qiCaptador); //o pintor vai pintar nesse inderesso
//     //define qual sera a caneta que ira pintar


//     if(ui->chbCentroide->isChecked()){

//         painter.setPen(canetaVermelha);
//         painter.drawPoint((int) dados->desenhoSaida.cmX[numFrame-videoLista.frameProces[0]],(int)dados->desenhoSaida.cmY[numFrame-videoLista.frameProces[0]]);


//     }




//     if(ui->chbTamnho->isChecked()){
//         painter.setPen(canetaPreta);
//         painter.drawPoint(dados->desenhoSaida.agulhX[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.agulhY[numFrame-videoLista.frameProces[0]]);
//         painter.setPen(canetaAmarela);
//         painter.drawLine(QPointF(dados->desenhoSaida.pob1X[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.pob1Y[numFrame-videoLista.frameProces[0]]),
//                 QPointF(dados->desenhoSaida.pob2X[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.pob2Y[numFrame-videoLista.frameProces[0]]));

//     }

////                 painter.drawPoint(poLongeX,poLongey);
////                 painter.drawPoint(pRetaA1X,pRetaA1Y);
////                 painter.drawPoint(pRetaA2X,pRetaA2Y);



////                 //desenha o centro de massa

//     if(ui->chbArea->isChecked()){

//         painter.setPen(canetaQuadro);
////                 painter.drawLine(QPoint(dados->desenhoSaida.vtxX1[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY1[numFrame-videoLista.frameProces[0]]),
////                                   QPoint(dados->desenhoSaida.vtxX2[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY2[numFrame-videoLista.frameProces[0]] ));

//       painter.drawPoint(dados->desenhoSaida.vtxX1[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY1[numFrame-videoLista.frameProces[0]]);
//       painter.drawPoint(dados->desenhoSaida.vtxX2[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY2[numFrame-videoLista.frameProces[0]]);
//       painter.drawPoint(dados->desenhoSaida.vtxX3[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY3[numFrame-videoLista.frameProces[0]]);
//       painter.drawPoint(dados->desenhoSaida.vtxX4[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY4[numFrame-videoLista.frameProces[0]]);


//     }

//     painter.setPen(canetaAmarela);

//     int contCircle=0;
//     int contREct=0;
//     for(int ka1=0; ka1 < videoLista.area[contadorDeVideo].nomeFig.size(); ka1++){

//         if(cheboxList[ka1]->isChecked()){

//             if(videoLista.area[contadorDeVideo].tipo[ka1]=="circle"){

//                 painter.drawEllipse(videoLista.area[contadorDeVideo].oriX[ka1],
//                                     videoLista.area[contadorDeVideo].oriY[ka1],
//                                     videoLista.area[contadorDeVideo].raio[contCircle]*2,
//                                     videoLista.area[contadorDeVideo].raio[contCircle]*2);



//             }else{

//                 painter.drawRect(videoLista.area[contadorDeVideo].oriX[ka1],
//                                  videoLista.area[contadorDeVideo].oriY[ka1],
//                                  videoLista.area[contadorDeVideo].width[contREct],
//                                  videoLista.area[contadorDeVideo].height[contREct]);






//             }


//         }


//         if(videoLista.area[contadorDeVideo].tipo[ka1]=="circle"){

//             contCircle++;

//         }else{

//            contREct++;

//         }

//     }


//    // painter.drawPoint(vtxX3,vtxY3);
//    // painter.drawPoint(vtxX4,vtxY4);

//     QImage qimDisplay= qiCaptador.scaled(widthPanProcess,heightPanProcess,Qt::KeepAspectRatio);
//     ui->imgResultado->setPixmap(QPixmap::fromImage(qimDisplay));

    if(ui->cbRegistro->isChecked()){

        if(contTempo%40==0){
           atualizaRegistro();
        }
    }








}

void telaTempoReal::recebeDadosMorfologicos(QImage imReceb, bool objetoEnco, double areaRecebida, double centroideX, double centroideY, float angObjeto, float tamObjet)
{

}

void telaTempoReal::gravaDadosMorfoCinematico(QImage imaProc, bool objeto, double area1, double mcX, double mcY, float anguloObjeto, float alturaObjeto, float larguraObjeto, double varAngular, double varArea, double VarCenX, double VarCenY, double VarDistancia, double VarOBjeto, float VarAltura, float VarLargura, bool ruidoOn)
{
//    qDebug()<< mcX << "  " << mcY ;
//    reMorfo.objetoEncontrado.push_back(objeto);
//    reMorfo.area.push_back(area1);
//    reMorfo.centroidX.push_back(mcX);
//    reMorfo.centroidY.push_back(mcY);
//    reMorfo.anguloObj.push_back(anguloObjeto);
//    reMorfo.tamanhoObj.push_back(tamanhoObjeto);
//    reCinema.varAngular.push_back(varAngular);
//    reCinema.varArea.push_back(varArea);
//    reCinema.varCenX.push_back(VarCenX);
//    reCinema.varCenY.push_back(VarCenY);
//    reCinema.varDistancia.push_back(VarDistancia);
//    reCinema.varTamObjeto.push_back(VarOBjeto);
//    reCinema.ruidoMaxVaria.push_back(ruidoOn);

    //qDebug() <<"entrou";

    reMorfo.objetoEncontrado.push_back(objeto);
    reMorfo.area.push_back(area1);
    reMorfo.centroidX.push_back(mcX);
    reMorfo.centroidY.push_back(mcY);
    reMorfo.anguloObj.push_back(anguloObjeto);
    //reMorfo.tamanhoObj.push_back(alturaObjeto);
    reMorfo.altura.push_back(alturaObjeto);
    reMorfo.largura.push_back(larguraObjeto);
    reCinema.varAngular.push_back(varAngular);
    reCinema.varArea.push_back(varArea);
    reCinema.varCenX.push_back(VarCenX);
    reCinema.varCenY.push_back(VarCenY);
    reCinema.varDistancia.push_back(VarDistancia);
    reCinema.varTamObjeto.push_back(VarOBjeto);
    reCinema.varAltura.push_back(VarAltura);
    reCinema.varLargura.push_back(VarLargura);
    reCinema.ruidoMaxVaria.push_back(ruidoOn);


    //qDebug()<<"chegou aqui lul" << reMorfo.objetoEncontrado.size();

}



void telaTempoReal::on_chAImage_clicked(bool checked)
{
    ui->widAquisi->setVisible(checked);


    ui->tabWControlador->setTabEnabled(0,checked);

    if(checked){




    }else{




    }

}

void telaTempoReal::on_cbRegistro_clicked(bool checked)
{
    ui->widRegistro->setVisible(checked);
    if(checked){

        ui->pbConfig->setEnabled(false);



    }else{

        ui->pbConfig->setEnabled(true);

    }



}

void telaTempoReal::on_pbConfig_clicked()
{

    if(ui->chAImage->isChecked()){ //se quer aquisiçaõ de iamgem

        captadorDeVideo->setCaptador(ui->leNumeroCamera->text().toInt());
//        int codi= CV_FOURCC('x', '2', '6', '4');
//        captadorDeVideo->confGravador("C:\\filmes\\treadfuncionando26.avi",30,300,false,codi);

        captadorDeVideo->setCapOn(false);
        captadorDeVideo->setGraOn(false);

        ui->swImage->setCurrentIndex(2); //setando para ver o video

    //find codec;






    //se quer a gravação do video
      if(ui->cbCapturaVideo->isChecked()){


          if(!nomeArquivoOpenCV.isEmpty()){ //testa se ta tudo certo

              fpsGravado= ui->leFps->text().toInt();

//              int codi= CV_FOURCC('x', '2', '6', '4');
//              codi=-1;

              //fourCodec=-1;

              fourCodec = getCodec(ui->comboBoX->currentIndex());


              captadorDeVideo->confGravador(nomeArquivoOpenCV,
                                            ui->leFps->text().toInt(),
                                            ui->leFrameTotal->text().toInt()
                                            ,ui->cbParadaFrame->isChecked() // verdadeiro ele nunca para
                                                                            //falso ele para por determinado numero de frame
                                            ,fourCodec);//,codi);  //codi  é o codec



          }else{

              //erro falta de nome no video

          }


      }//fimg gravação de video



      if(ui->cbProcessInagem->isChecked()){


      qDebug()<<"setado o processamendo de imagem";
      }




        captadorThread->start();


       // ui->pbStartCaptador->click();


    }else{ //se o usuario não quiser aquisição de imamge

        ui->staWidImgExibi->setCurrentIndex(2);
        //ui->swImage->setCurrentIndex(0); //setando para ver o video

    }





    ui->swPrincipal->setCurrentIndex(1); //1 é igual a janela do processamento

    if(ui->cbRegistro->isChecked()){
        if(!ui->pbLerCatalogo->isEnabled()){

            QVBoxLayout *vlay = new QVBoxLayout(ui->widBotoes);

         //  QPushButton *buttonList[numeroDeBotoes];


            QSignalMapper *mapperCategorias = new QSignalMapper(this);

            for(int j=0; j<numeroDeBotoes;j++){

                //criar um novo botão
                pb = new QPushButton();
              buttonList.append(pb);

                //buttonList[j]->setText(nomeCate[j]); //seta o nome
                buttonList[j]->setText(cAnaEto.nomeCategoria[j]+ "("+cAnaEto.atalho[j]+")"+"(ready)");
                buttonList[j]->setFixedHeight(30);
                //buttonList[j]->setFont();
                //buttonList[j]->setFont(QFont("MS Shell Dlg 2",12,-1,false, true));
                buttonList[j]->setStyleSheet("background-color: green;""color: black;" "font: bold");// "font: bold");
    //                                         "font-size: 12px" "font-style: bold;");

                clicado.push_back(false); //false funciona
                //fazendo o buffer
                saida.frameFinalBuffer.push_back(0); //coloca o valor de zero
                saida.pontosPostos.push_back(0);

                vlay->addWidget(buttonList[j]);

            //colocando os botões no layute faz aparecer na tela
            ui->widBotoes->setLayout(vlay);

            //conecta o sinal de clicar no slot de mapa
            connect(buttonList[j], SIGNAL(clicked()), mapperCategorias, SLOT(map()));

            //colocar o botão no int
            mapperCategorias->setMapping(buttonList[j],j);



           // ui->pbGravarAnalasiteEtografica->setEnabled(true);

            }

         connect(mapperCategorias, SIGNAL(mapped(int)), this, SLOT(slotMapeado(int)));

                 if(ui->cbNested->isChecked()){
                      escolheSelecao=false;  //true apenas um botão por vez
                                 //false pode apertar todos os botões
                }else{

                     escolheSelecao=true;  //true apenas um botão por vez
                                           //false pode apertar todos os botões

                 }

                 //criando o atalho para os botoes
                 for(int ji=0; ji< cAnaEto.atalho.size(); ji++ ){
                     creatShortCurt(cAnaEto.atalho[ji],buttonList[ji]);

                 }


            //conectando os botões criados
            //primeiro se mapeia
         //   QSignalMapper *mapperCategorias = new QSignalMapper(this);

           // connect(buttonList[numeroDeBotoes], SIGNAL(clicked()), mapperCategorias, SLOT(map()));
            //depois coneta os sinal de clique de cada botão no mapa
            //connect(button, SIGNAL(clicked()), mapperCategorias, SLOT(map()));
           // connect(button1, SIGNAL(clicked()), mapperCategorias, SLOT(map()));
           // connect(button2, SIGNAL(clicked()), mapperCategorias, SLOT(map()));

            //depois seta o index de cada botão
           // mapperCategorias->setMapping(button,0);
           // mapperCategorias->setMapping(button1,1);
           // mapperCategorias->setMapping(button2,2);

            //e depois conecta para aonde deve ser enviado o sinal do slotMapeado


           //ui->btPlay->setEnabled(true);

                 ui->widBotoes->setEnabled(false);
                 ui->lblEtographiOn->setText("Etographia is not Avaible");
                 ui->lblEtographiOn->setStyleSheet("background-color: red;""color: black; " "font: bold;");
                 ui->widBotoes->setVisible(false);



                 ui->tabWControlador->setTabEnabled(3,true);



        }else{
            //mensagem de error pq nao ta com o catalogo habilitado



        }




    }



//    if(ui->cbRegistro->isEnabled()){




//       if(ui->chAImage->isEnabled()){

//           if(ui->cbCapturaVideo->isEnabled()){

//               ui->tabWControlador->setCurrentIndex(2);

//           }




//            ui->tabWControlador->setCurrentIndex(2);


//        }else{


//            ui->tabWControlador->setCurrentIndex(2);

//        }



//    }else{


//    }



}

void telaTempoReal::on_cbCapturaVideo_clicked(bool checked)
{
    ui->widCapturaVide->setVisible(checked);

    ui->tabWControlador->setTabEnabled(1,checked);


    ui->pbConfig->setEnabled(!checked);

}

void telaTempoReal::on_pbConfigurarVideo_clicked()
{
    nomeArquivo = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://filmes",
               "Video Format (*.avi)"
               );
    //ageitando a extensão apara a opencv
    //abre janela para encontrar os videos
        //transforma o caminho lido pela janela em um arquivo de string


    if(nomeArquivo != "")
    {
   nomeArquivoBit = nomeArquivo.toLatin1();

    int  k=0;
    int ka=0;

    while(nomeArquivoBit[k] != 0) //enquanto não tem string nula ou seja não é o fim do arquivo
    {


        if(nomeArquivoBit[k] == 47){ //47 esta relacionado com a barra


            fonteVideoBitOpenCV[ka] = 92; //47;
            ka++;
            fonteVideoBitOpenCV[ka] = 92; //47;
            ka++;
            k++;
        }else{

            fonteVideoBitOpenCV[ka] = nomeArquivoBit[k];
            ka++;
            k++;

        }


    }

    }



    //transformando QByteArray para QString
    nomeArquivoOpenCV = QString::fromLatin1(fonteVideoBitOpenCV);

    ui->lblNameVideo->setText(nomeArquivo);
    ui->pbConfig->setEnabled(true);

   // int Four = CV_FOURCC(CV_FOURCC_PROMPT);

    //int four= CV_FOURCC("0","0","0","0");

    //CV_FOURCC_PROMPT(-1);



    //cv::VideoWriter::open("ad",
//    ui->lblNomeCaminho->setText(nomeArquivoOpenCV);
//    ui->stackedWidget_2->setCurrentIndex(2);
//    ui->pbGravarVideo->setEnabled(true);
}



void telaTempoReal::on_cbParadaFrame_clicked(bool checked)
{
    ui->widParadaFrame->setVisible(!checked);
}

void telaTempoReal::on_leFrameTotal_editingFinished()
{
    if(!ui->leFrameTotal->text().isEmpty()){

        ui->lblFrameTotalSec->setText(QString::number(
                                          ui->leFrameTotal->text().toDouble()/ui->leFps->text().toDouble())+" seg");


    }
}

void telaTempoReal::on_pbStarrFilming_clicked()
{
    chTermina=true;
    chFilmando=true;
    captadorDeVideo->setGraOn(true);
    ui->lblFilmando->setText("ON");

    ui->pbStarrFilming->setEnabled(false);
    ui->pbStopFilming->setEnabled(true);
    ui->pbTerminaGrava->setEnabled(false);

    if(ui->cbCapturaVideo->isChecked()){

        frameInicioGravacao = frame_atual;

    }


    if(ui->cbProcessInagem->isChecked()){

         ui->pbStopFilming->setEnabled(false);


    }

}

void telaTempoReal::on_pbStopFilming_clicked()
{
    chFilmando=false;
    captadorDeVideo->setGraOn(false);
    ui->lblFilmando->setText("OFF");

     if(ui->cbRegistro->isChecked()){
         //se esta habilitado o registro comporamental só pode uma ver ligar a camera

        // ui->pbStarrFilming->setEnabled(true);
         ui->pbStopFilming->setEnabled(false);
         ui->pbTerminaGrava->setEnabled(true);

     }else{

         ui->pbStarrFilming->setEnabled(true);
         ui->pbStopFilming->setEnabled(false);
         ui->pbTerminaGrava->setEnabled(true);

     }



}

void telaTempoReal::on_pbTerminaGrava_clicked()
{

    ui->pbStoCap->click(); //para o captador
    chFilmando=false;
    captadorDeVideo->terminaGravador();
    ui->pbStarrFilming->setEnabled(false);
    ui->pbStopFilming->setEnabled(false);
    chTermina= false;


    ui->pbTerminaGrava->setEnabled(false);
    ui->pbGravaRelatorioFPS->setEnabled(true);

    ui->pbGravaRelatorioFPS->click();

    //escreveFPS();

}

void telaTempoReal::on_cbProcessInagem_clicked(bool checked)
{
    ui->tabWControlador->setTabEnabled(2,checked);

    ui->widProceImagem->setVisible(checked);

    ui->pbConfig->setEnabled(!checked);


}

void telaTempoReal::on_telaTempoReal_destroyed()
{
    qDebug()<<"destruindo";
}




void telaTempoReal::lerVXML(QString nomeArquivoLer)
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

void telaTempoReal::enconPontoArea()
{
    for(int ka=0; ka< videoLista.area[contadorDeVideo].oriX.size(); ka++ )
        {

        if(videoLista.area[contadorDeVideo].tipo[ka]=="circle"){
            chaTip=false;
            contCir++;

        }else{
            //contRet=ka;
            contRet++;
            chaTip=true;

        }

        for(int i=0; i< reMorfo.area.size();i++){
            if(chaTip){ //se é quadrado

                if((reMorfo.centroidX[i]>=videoLista.area[contadorDeVideo].oriX[ka])
                        &&(reMorfo.centroidX[i]<=(videoLista.area[contadorDeVideo].oriX[ka]+videoLista.area[contadorDeVideo].width[contRet-1]))&&
                        (reMorfo.centroidY[i]>=videoLista.area[contadorDeVideo].oriY[ka])
                        &&(reMorfo.centroidY[i]<=(videoLista.area[contadorDeVideo].oriY[ka]+videoLista.area[contadorDeVideo].height[contRet-1])))
                {

                    objDentro.push_back(true);
                   // qDebug()<<"o ponto esta dentro" << i;


                }else{

                    objDentro.push_back(false);

                }


            }else{ //se é circulo

                raioTest=0;
                raioTest = qPow(reMorfo.centroidX[i]-
                                (videoLista.area[contadorDeVideo].oriX[ka]+ videoLista.area[contadorDeVideo].raio[contCir-1]),2)+
                            qPow(reMorfo.centroidY[i]-
                                 (videoLista.area[contadorDeVideo].oriY[ka]+ videoLista.area[contadorDeVideo].raio[contCir-1]),2);

                        //se soma por causa que oriX é o ponto de origem da figura nao o seu centro

                raioTest= qSqrt(raioTest);
                if(raioTest<=videoLista.area[contadorDeVideo].raio[contCir-1]){


                    objDentro.push_back(true);

                }else{

                    objDentro.push_back(false);
                }


            }



    //        stream.writeStartElement("proce");
    //        fraNumero=i+ videoLista.frameProces[contadorDeVideo];

    //        stream.writeAttribute("f",QString::number(fraNumero));
    //        stream.writeAttribute("arP",QString::number(eto->reMorfo.area[i]));
    //        stream.writeAttribute("arM",QString::number(eto->reMorfo.area[i]*videoLista.escala[contadorDeVideo]));
    //        stream.writeAttribute("ceX",QString::number(eto->reMorfo.centroidX[i]));
    //        stream.writeAttribute("ceY",QString::number(eto->reMorfo.centroidY[i]));
    //        stream.writeAttribute("taP",QString::number(eto->reMorfo.tamanhoObj[i]));
    //        stream.writeAttribute("taM",QString::number(eto->reMorfo.tamanhoObj[i]*videoLista.escala[contadorDeVideo]));
    //        stream.writeAttribute("an",QString::number(eto->reMorfo.anguloObj[i]));

    //        stream.writeAttribute("Var",QString::number(eto->reCinema.varArea[i]));
    //        stream.writeAttribute("Van",QString::number(eto->reCinema.varAngular[i]));
    //        stream.writeAttribute("Vd",QString::number(eto->reCinema.varDistancia[i]));



    //        stream.writeEndElement(); //fecha proce


        }

        matObjDentro.push_back(objDentro);
        objDentro.clear();



    }
}

void telaTempoReal::escreveFPS()
{
    ui->pbStoCap->clicked(); //pausa

//    nomeGravarFPS = QFileDialog::getSaveFileName(
//                this,
//                tr("Save File"),
//                "C://",
//               "FPS Files (*.fps)"
//               );


    nomeGravarFPS = nomeArquivo;
    QByteArray nomeGravarFPSByte = nomeGravarFPS.toLatin1();

    nomeGravarFPSByte.truncate(nomeGravarFPSByte.indexOf("."));   //  nomeGravarFPSByte.indexOf(".");
    nomeGravarFPSByte.append(".fps");


    nomeGravarFPS =  QString::fromLatin1(nomeGravarFPSByte);
//    qDebug()<<"oi 1";

//    enconPontoArea();

//    qDebug()<<"oi 2";

    if(!nomeGravarFPS.isEmpty()){
    OutEtografia2.setFileName(nomeGravarFPS);

    qDebug()<<"oi 2.1";
    OutEtografia2.open(QIODevice::WriteOnly);
    qDebug()<<"oi 2.1.a";
    QXmlStreamWriter stream(&OutEtografia2); //passa o endereço
    qDebug()<<"oi 2.1.b";
    stream.setAutoFormatting(true);

//    qDebug()<<"oi 2.1.c";
    stream.writeStartDocument();//começa o documento
    stream.writeStartElement("fpsVideoGravado");
//    stream.writeStartElement("dadosExperimentador");
//             stream.writeTextElement("experimentador",experimentador.nome);
//             stream.writeTextElement("laboratorio",experimentador.lab);
//    stream.writeEndElement();//fecha analiseEtografica

//     qDebug()<<"oi 2.1.d";
    stream.writeStartElement("dadosVideoGravado");
             stream.writeTextElement("nomeVxml",nomeArquivo);
//             stream.writeTextElement("videoHeight",ui->lblHeight->text()); //QString::number( captadorDeVideo->video_heigth));
//             stream.writeTextElement("videoWidht", ui->lblWidth->text());//QString::number(captadorDeVideo->video_width));
             stream.writeTextElement("fpsConfiGravar", QString::number(fpsGravado));


             double fpsMedio =0;
             for(int ka=0; ka< vetorTempoAquisicao.size(); ka++){
                 fpsMedio= fpsMedio+ (1/vetorTempoAquisicao[ka])/vetorTempoAquisicao.size();

             }

             stream.writeTextElement("fpsMedioAdquirido",QString::number(fpsMedio));

             long double somatorio=0;

             for(int ka=0; ka< vetorTempoAquisicao.size(); ka++){

                 somatorio = somatorio + qPow( 1/vetorTempoAquisicao[ka] -fpsMedio,2);


             }

             double variancia=0;
             double desvioPadrao=0;

             variancia = (vetorTempoAquisicao.size() -1);
             variancia = 1/variancia;
             variancia= variancia* somatorio;
             desvioPadrao = qSqrt(variancia);

             stream.writeTextElement("variancia",QString::number(variancia));
             stream.writeTextElement("desvioPadrao",QString::number(desvioPadrao));





//             stream.writeTextElement("frameInicial",QString::number(videoLista.frameInicial[contadorDeVideo]));
//             stream.writeTextElement("frameBack",QString::number(videoLista.frameBack[contadorDeVideo]));
//             stream.writeTextElement("frameProces",QString::number(videoLista.frameProces[contadorDeVideo]));
//             stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]));
//             stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
//              stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
    stream.writeEndElement();//fecha informacoes

//    qDebug()<<"oi 2.1.e";

//    stream.writeStartElement("dadosCatalago");
//    stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);



//     qDebug()<<"oi 2.2";
//    stream.writeStartElement("Categorias");
//    int contador=0;

//    for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

//       stream.writeStartElement("categoria");
//       stream.writeAttribute("id", QString::number(i));
//       stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
//       stream.writeEndElement();

//       }
//    stream.writeEndElement();


    qDebug()<<"oi 2.3";
    stream.writeStartElement("videoFps");

    for(int ja=0; ja< vetorTempoAquisicao.size(); ja++ ){


        stream.writeStartElement("frame");
        stream.writeAttribute("id", QString::number(ja));
        stream.writeAttribute("frame", QString::number(vetorFrameAquisicao[ja]));
        stream.writeAttribute("fps", QString::number(1/vetorTempoAquisicao[ja]));
        stream.writeEndElement();


    }


     stream.writeEndElement(); //fecha caminho Ext



    stream.writeEndElement();//fecha analiseEtografica
    stream.writeEndDocument();


    OutEtografia2.close();


    qDebug()<<"oi 2.4";


    ui->pbGravaRelatorioFPS->setEnabled(false);

    }//fecha o if que se o nome estiver fora
}

void telaTempoReal::readCatalago()
{
    QFile leitura;
    leitura.setFileName(nomeGravarCatalago);
    leitura.open(QIODevice::ReadOnly| QIODevice::Text);

    QXmlStreamReader leitorXML(&leitura);
    int contadorTamanho=0;
    bool controle=true;

    while(!leitorXML.atEnd() && !leitorXML.hasError()){


        leitorXML.readNext();

        if(leitorXML.name() == "categoria"){
            if(controle){

                cAnaEto.id.push_back(leitorXML.attributes().value("id").toInt());
            contadorTamanho++;
            }
            controle=!controle;
           //qDebug() << leitorXML.attributes().value("id").toInt();

        }
        if(leitorXML.name()== "nome"){
        cAnaEto.nomeCategoria.push_back(leitorXML.readElementText());
           //qDebug() << leitorXML.readElementText();

        }


           if(leitorXML.name()== "atalho"){
        cAnaEto.atalho.push_back(leitorXML.readElementText());
              // qDebug() << leitorXML.readElementText();
           }

           if(leitorXML.name()== "descricao"){
        cAnaEto.descricao.push_back(leitorXML.readElementText());
              // qDebug() << leitorXML.readElementText();
           }

        }



    cAnaEto.quantidadeDeDados= contadorTamanho; //conta quantidade de dados;

    numeroDeBotoes= contadorTamanho;
    nomeCate=cAnaEto.nomeCategoria;
    leitura.close();




}

void telaTempoReal::creatShortCurt(QString atalho, QPushButton *pushBut)
{
    atalho = atalho.toLower();

    if(atalho == "a"){

        new QShortcut( Qt::Key_A, pushBut, SLOT(click()));

    }else if(atalho == "b"){

       new QShortcut( Qt::Key_B, pushBut, SLOT(click()));

    }else if(atalho == "c"){
        new QShortcut( Qt::Key_C, pushBut, SLOT(click()));

     }else if(atalho == "d"){
        new QShortcut( Qt::Key_D, pushBut, SLOT(click()));

     }else if(atalho == "e"){
        new QShortcut( Qt::Key_E, pushBut, SLOT(click()));

     }else if(atalho == "f"){
        new QShortcut( Qt::Key_F, pushBut, SLOT(click()));

     }else if(atalho == "g"){
        new QShortcut( Qt::Key_G, pushBut, SLOT(click()));

     }else if(atalho == "h"){
        new QShortcut( Qt::Key_H, pushBut, SLOT(click()));

     }else if(atalho == "i"){
        new QShortcut( Qt::Key_I, pushBut, SLOT(click()));

     }else if(atalho == "j"){
        new QShortcut( Qt::Key_J, pushBut, SLOT(click()));

     }else if(atalho == "k"){
        new QShortcut( Qt::Key_K, pushBut, SLOT(click()));

     }else if(atalho == "l"){
        new QShortcut( Qt::Key_L, pushBut, SLOT(click()));

     }else if(atalho == "m"){
        new QShortcut( Qt::Key_M, pushBut, SLOT(click()));

     }else if(atalho == "n"){
        new QShortcut( Qt::Key_N, pushBut, SLOT(click()));

     }else if(atalho == "o"){
        new QShortcut( Qt::Key_O, pushBut, SLOT(click()));

     }else if(atalho == "p"){
        new QShortcut( Qt::Key_P, pushBut, SLOT(click()));

     }else if(atalho == "q"){
        new QShortcut( Qt::Key_Q, pushBut, SLOT(click()));

     }else if(atalho == "r"){
        new QShortcut( Qt::Key_R, pushBut, SLOT(click()));

     }else if(atalho == "s"){
        new QShortcut( Qt::Key_S, pushBut, SLOT(click()));

     }else if(atalho == "t"){
        new QShortcut( Qt::Key_T, pushBut, SLOT(click()));

     }else if(atalho == "u"){
        new QShortcut( Qt::Key_U, pushBut, SLOT(click()));

     }else if(atalho == "v"){
        new QShortcut( Qt::Key_V, pushBut, SLOT(click()));

     }else if(atalho == "w"){
        new QShortcut( Qt::Key_W, pushBut, SLOT(click()));

     }else if(atalho == "x"){
        new QShortcut( Qt::Key_X, pushBut, SLOT(click()));

     }else if(atalho == "y"){
        new QShortcut( Qt::Key_Y, pushBut, SLOT(click()));

     }else if(atalho == "z"){
        new QShortcut( Qt::Key_Z, pushBut, SLOT(click()));

     }else if(atalho == "1"){
        new QShortcut( Qt::Key_1, pushBut, SLOT(click()));

     }else if(atalho == "2"){
        new QShortcut( Qt::Key_2, pushBut, SLOT(click()));

     }else if(atalho == "3"){
        new QShortcut( Qt::Key_3, pushBut, SLOT(click()));

     }else if(atalho == "4"){
        new QShortcut( Qt::Key_4, pushBut, SLOT(click()));

     }else if(atalho == "5"){
        new QShortcut( Qt::Key_5, pushBut, SLOT(click()));

     }else if(atalho == "6"){
        new QShortcut( Qt::Key_6, pushBut, SLOT(click()));

     }else if(atalho == "7"){
        new QShortcut( Qt::Key_7, pushBut, SLOT(click()));

     }else if(atalho == "8"){
        new QShortcut( Qt::Key_8, pushBut, SLOT(click()));

     }else if(atalho == "9"){
        new QShortcut( Qt::Key_9, pushBut, SLOT(click()));

     }else if(atalho == "0"){
        new QShortcut( Qt::Key_0, pushBut, SLOT(click()));

     }




}

int telaTempoReal::getCodec(int indexCaixa)
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

void telaTempoReal::atualizaRegistro()
{

    if(chNovoValor){

        chNovoValor=false;

        bool chvEscreRow=true;

        while(chvEscreRow){
        //0 > 0
        //2 > 2

        if(saida.quantidadeDepontos > ui->tabRegistro->rowCount()){

            ui->tabRegistro->insertRow(ui->tabRegistro->rowCount());
            ui->tabRegistro->setItem (ui->tabRegistro->rowCount()-1,0,new QTableWidgetItem(
                                         cAnaEto.nomeCategoria[saida.id[ui->tabRegistro->rowCount()-1]] ) );
            ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,1,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.frameComeco[ui->tabRegistro->rowCount()-1]]
                                     -vetorTempoFrame[frameInicioRegistro])));
            ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,2,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.framFim[ui->tabRegistro->rowCount()-1]]
                                     -vetorTempoFrame[frameInicioRegistro])));

            saida.chPontoValido.push_back(true);


            //configurando TableWidget
            ui->tabRegistro->resizeColumnsToContents();
            ui->tabRegistro->clearSelection();
            ui->tabRegistro->clearFocus();


        }else{

            chvEscreRow= false;


        }

        for(int ka=0; ka< ui->tabRegistro->rowCount();ka++ ){

    //                ui->tabRegistro->setRowCount(ka);
    //                ui->tabRegistro->setColumnCount(1);
    //                ui->tabRegistro->setItem();

//            ui->tabRegistro->insertRow(ui->tabRegistro->rowCount());
            ui->tabRegistro->setItem (ka,0,new QTableWidgetItem(
                                         cAnaEto.nomeCategoria[saida.id[ka]] ) );
            ui->tabRegistro->setItem(ka,1,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.frameComeco[ka]]
                                     -vetorTempoFrame[frameInicioRegistro])));
            ui->tabRegistro->setItem(ka,2,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.framFim[ka]]
                                     -vetorTempoFrame[frameInicioRegistro])));

          //  saida.chPontoValido.push_back(true);


            //configurando TableWidget
            ui->tabRegistro->resizeColumnsToContents();
            ui->tabRegistro->clearSelection();
            ui->tabRegistro->clearFocus();



        }


    }

   }
}

void telaTempoReal::on_pbLerArquivoVxml_clicked()
{
    fonteVideoXML = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users//Bio//Desktop//videos//",
                "Video Files (*.vxml)"
                );


    if(!fonteVideoXML.isEmpty()){

    lerVXML(fonteVideoXML);
    videoLista.nomeVXML.push_back(fonteVideoXML);
    captador = new moduloCaptador();

    captador->setCaptador(videoLista.nomeOpencv[0]);
    //dados->frameBackground = conQim2Mat( captador->pegaPlanoFundoQImage(videoLista.frameBack[0]));
    //dados->setFrameFundo(captador->pegaPlanoFundoQImage(videoLista.frameBack[0]));
    dados->setBackground(captador->pegaPlanoFundo(videoLista.frameBack[0]));

//    captador->setCaptador(videoLista.nomeOpencv[0]);


    dados->moveToThread(thrProce);

//    dados->frameBackground = captador->pegaPlanoFundo(videoLista.frameBack[0]);


    //cv::Mat frameDisplay = captadorDeVideo->frameBackground;

    //cv::imshow("oi",frameDisplay);

    //cv::waitKey(10);
   // QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);

    //qiFundo = imgLida;
    captador->getParamVideo();
    dados->setCalibracao(videoLista.threshold[0],videoLista.erosao[0]);
    dados->setParametrosVideo(captador->video_width,captador->video_heigth);
    dados->confiCameraVir(videoLista.areaJanInte[0].oriX[0],
            videoLista.areaJanInte[0].oriY[0],
            videoLista.areaJanInte[contadorDeVideo].width[0],
            videoLista.areaJanInte[contadorDeVideo].height[0],
            videoLista.chaInteMoveAtivado[0],videoLista.chaInteMove[0]);
    dados->setMaxVariacao(videoLista.tamMaxVar[0]);


    //mostra fundo na tela


    cv::Mat frameDisplay=  dados->frameBackground .clone();
    cv::cvtColor(frameDisplay,frameDisplay,CV_BGR2RGB );
    cv::resize(frameDisplay,frameDisplay, cv::Size(160,120),0,0,cv::INTER_LANCZOS4);
    QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);
    ui->lblFundo->setPixmap(QPixmap::fromImage(imgLida));

    captador->captadorVideoRelease(); //para desligar e dar release

    thrProce->start();

    ui->lblErode->setText(QString::number(videoLista.erosao[0]));
    ui->lblThre->setText(QString::number(videoLista.threshold[0]));

//    dados->setCalibracao(20,0);
//    dados->setParametrosVideo(640,480);
//    dados->confiCameraVir(0,0,640,480,false,false);

    ui->pbLerArquivoVxml->setEnabled(false);
    ui->pbConfig->setEnabled(true);
    ui->cbProcessInagem->setEnabled(false);

    QVBoxLayout *vBoxLay = new QVBoxLayout(ui->widCheckBox);

    for(int ka=0; ka< videoLista.area[contadorDeVideo].nomeFig.size(); ka++){

        chebox = new QCheckBox();
        chebox->setChecked(true);
        chebox->setText(videoLista.area[contadorDeVideo].nomeFig[ka]);
        cheboxList.push_back(chebox);
        vBoxLay->addWidget(cheboxList[ka]);

    }


    ui->widCheckBox->setLayout(vBoxLay);




    }




}

void telaTempoReal::on_cbProcessInagem_clicked()
{

}

void telaTempoReal::on_pbFimProcessamento_clicked()
{

    //ui->pbPlanoFundo->click();

    ui->pbStoCap->click();
    disconnect(captadorDeVideo,SIGNAL(enviaInformacoes(int,QImage,float)),dados,SLOT(processamentoDeVideoRealTime(int,QImage,float)));
    chDesenhar=false; //serve para controlar o desenho na tela;
    ui->staWidImgExibi->setCurrentIndex(0);
    ui->pbGravarAnalasiProces->setEnabled(true);


    if(ui->cbCapturaVideo->isChecked()){
//        ui->pbStoCap->click();
//        cv::waitKey(20);
        ui->pbStopFilming->click();
        cv::waitKey(20);

        ui->pbStoCap->click(); //para o captador
        chFilmando=false;
        captadorDeVideo->terminaGravador();
        ui->pbStarrFilming->setEnabled(false);
        ui->pbStopFilming->setEnabled(false);
        chTermina= false;


        ui->pbTerminaGrava->setEnabled(false);
        ui->pbGravaRelatorioFPS->setEnabled(true);

        ui->pbGravaRelatorioFPS->click();

        qDebug()<<"gravou";
        //ui->pbTerminaGrava->click();
    }

}

void telaTempoReal::on_pbSaveTraking_clicked()
{

    ui->pbStoCap->clicked(); //pausa

    nomeGravarProcesImagem = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                fonteVideoXML,
               "Traking Files (*.tkin)"
               );




    enconPontoArea();


    if(!nomeGravarProcesImagem.isEmpty()){
    OutEtografia.setFileName(nomeGravarProcesImagem);

    OutEtografia.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&OutEtografia); //passa o endereço
    stream.setAutoFormatting(true);

    stream.writeStartDocument();//começa o documento
    stream.writeStartElement("analiseProcessaImage");
    stream.writeStartElement("dadosExperimentador");
             stream.writeTextElement("experimentador",experimentador.nome);
             stream.writeTextElement("laboratorio",experimentador.lab);
    stream.writeEndElement();//fecha analiseEtografica


    if(ui->cbCapturaVideo->isChecked()){
        stream.writeStartElement("dadosVideoAnalisado");
                 stream.writeTextElement("nomeVxml",videoLista.nomeVXML[contadorDeVideo]);
                 stream.writeTextElement("nomeArquivoVideo", nomeArquivo);
                 stream.writeTextElement("frameInicial",QString::number(0));
                 stream.writeTextElement("frameBack",QString::number(0));
                 stream.writeTextElement("frameProces", QString::number(contNumeroGrava-videoLista.area.size()));   //QString::number(videoLista.frameProces[contadorDeVideo]-frameInicioGravacao-frameInicioPro));
                 stream.writeTextElement("frameFinal",QString::number(contNumeroGrava));
                 stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
                  stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
                  stream.writeTextElement("tempoTotalProcessamento", ui->lblTime->text());
                  double perFrame =  ui->lblTime->text().toDouble();
                  perFrame = perFrame/(videoLista.frameFinal[contadorDeVideo]-videoLista.frameProces[contadorDeVideo]);
                  stream.writeTextElement("tempoPorFrame", QString::number(perFrame)  );
        stream.writeEndElement();//fecha informacoes

    }else{
        stream.writeStartElement("dadosVideoAnalisado");
                 stream.writeTextElement("nomeVxml",videoLista.nomeVXML[contadorDeVideo]);
                 stream.writeTextElement("frameInicial",QString::number(videoLista.frameInicial[contadorDeVideo]));
                 stream.writeTextElement("frameBack",QString::number(videoLista.frameBack[contadorDeVideo]));
                 stream.writeTextElement("frameProces",QString::number(videoLista.frameProces[contadorDeVideo]));
                 stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]));
                 stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
                  stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
                  stream.writeTextElement("tempoTotalProcessamento", ui->lblTime->text());
                  double perFrame =  ui->lblTime->text().toDouble();
                  perFrame = perFrame/(videoLista.frameFinal[contadorDeVideo]-videoLista.frameProces[contadorDeVideo]);
                  stream.writeTextElement("tempoPorFrame", QString::number(perFrame)  );
        stream.writeEndElement();//fecha informacoes
    }

//    stream.writeStartElement("dadosVideoAnalisado");
//             stream.writeTextElement("nomeVxml",videoLista.nomeVXML[contadorDeVideo]);
//             stream.writeTextElement("frameInicial",QString::number(videoLista.frameInicial[contadorDeVideo]-frameInicioGravacao));
//             stream.writeTextElement("frameBack",QString::number(videoLista.frameBack[contadorDeVideo]));
//             stream.writeTextElement("frameProces", QString::number(frameInicioPro-frameInicioGravacao));   //QString::number(videoLista.frameProces[contadorDeVideo]-frameInicioGravacao-frameInicioPro));
//             stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]-frameInicioGravacao));
//             stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
//              stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
//              stream.writeTextElement("tempoTotalProcessamento", ui->lblTime->text());
//              double perFrame =  ui->lblTime->text().toDouble();
//              perFrame = perFrame/(videoLista.frameFinal[contadorDeVideo]-videoLista.frameProces[contadorDeVideo]);
//              stream.writeTextElement("tempoPorFrame", QString::number(perFrame)  );
//    stream.writeEndElement();//fecha informacoes

    stream.writeStartElement("dadosCatalago");
    stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);



    stream.writeStartElement("Categorias");
    int contador=0;

    for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

       stream.writeStartElement("categoria");
       stream.writeAttribute("id", QString::number(i));
       stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
       stream.writeEndElement();

       }
    stream.writeEndElement();

    stream.writeStartElement("areasDeInteresse");

    for(int ja=0; ja< videoLista.area[contadorDeVideo].tipo.size(); ja++ ){

        stream.writeStartElement("infoArea");
        stream.writeAttribute("id", QString::number(ja));
        stream.writeTextElement("figName",videoLista.area[contadorDeVideo].nomeFig[ja]);
        if(videoLista.area[contadorDeVideo].tipo[ja]=="circle"){

        stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
        stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
        stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

        stream.writeTextElement("raio",QString::number(videoLista.area[contadorDeVideo].raio[conCir2]));

        conCir2++;

        }else{
            stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
            stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
            stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

            stream.writeTextElement("width",QString::number(videoLista.area[contadorDeVideo].width[conRet2]));
            stream.writeTextElement("heigth",QString::number(videoLista.area[contadorDeVideo].height[conRet2]));
        conRet2++;

        }
        //stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
        //        stream.writeAttribute("tipo",videoLista.area[contadorDeVideo].oriX[ja];
        stream.writeEndElement();

    }


     stream.writeEndElement(); //fecha caminho Ext


    stream.writeEndElement();//fecha Categorias
   // stream.writeEndElement();//fecha dadosCatalago

    stream.writeStartElement("dadosAnalise");

    if(ui->cbAuto->isChecked()){
     stream.writeTextElement("tipoAnalise","Autoesclusiva" );
    }

    if(ui->cbNested->isChecked()){
     stream.writeTextElement("tipoAnalise","sobreposta" );
    }


     stream.writeStartElement("anaProceImagem");


     for(int ka=0; ka< videoLista.area[contadorDeVideo].oriX.size(); ka++ ){



     stream.writeStartElement("area");


     stream.writeAttribute("id",QString::number(ka));

     //stream.writeAttribute("");
     int fraNumero=0;

     if(ui->cbCapturaVideo->isChecked()){

         fraNumero= contNumeroGrava - reMorfo.area.size();


         for(int i=0; i<  reMorfo.area.size();i++){

             if(matObjDentro[ka][i]){

             stream.writeStartElement("proce");
             fraNumero=i+ fraNumero;

             stream.writeAttribute("f",QString::number(fraNumero));
             stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
             stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
             stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
             stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
             stream.writeAttribute("altP",QString::number(reMorfo.altura[i]));
             stream.writeAttribute("altM",QString::number(reMorfo.altura[i]/videoLista.escala[contadorDeVideo]));
             stream.writeAttribute("larP",QString::number(reMorfo.largura[i]));
             stream.writeAttribute("larM",QString::number(reMorfo.largura[i]/videoLista.escala[contadorDeVideo]));
             stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i])); //angulo do objeto



    //         stream.writeAttribute("taP",QString::number(dados->reMorfo.tamanhoObj[i]));
    //         stream.writeAttribute("taM",QString::number(dados->reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


    //         double tamanhoObjeto=0;

    //         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
    //         tamanhoObjeto = qSqrt(tamanhoObjeto);

    //         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


    //         //novo





             stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
             stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
             stream.writeAttribute("Valt",QString::number(reCinema.varAltura[i]));
             stream.writeAttribute("Vlar",QString::number(reCinema.varLargura[i]));

             stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));


             std::vector<float> varAltura;
             std::vector<float> varLargura;

             if(reCinema.ruidoMaxVaria[i]){
                 stream.writeAttribute("rMinV","true");

             }else{
                 stream.writeAttribute("rMinV","false");
             }
             if(reMorfo.objetoEncontrado[i]){

                 stream.writeAttribute("OE","true");

             }else{

                 stream.writeAttribute("OE","false");
             }



             stream.writeEndElement(); //fecha proce

             }
         }



     }else{ //caso nao tenha selecionado gravar o video com o processamento

         for(int i=0; i<  reMorfo.area.size();i++){

             if(matObjDentro[ka][i]){

             stream.writeStartElement("proce");
             fraNumero=i+ videoLista.frameProces[contadorDeVideo];

             stream.writeAttribute("f",QString::number(fraNumero));
             stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
             stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
             stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
             stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
             stream.writeAttribute("altP",QString::number(reMorfo.altura[i]));
             stream.writeAttribute("altM",QString::number(reMorfo.altura[i]/videoLista.escala[contadorDeVideo]));
             stream.writeAttribute("larP",QString::number(reMorfo.largura[i]));
             stream.writeAttribute("larM",QString::number(reMorfo.largura[i]/videoLista.escala[contadorDeVideo]));
             stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i])); //angulo do objeto



    //         stream.writeAttribute("taP",QString::number(dados->reMorfo.tamanhoObj[i]));
    //         stream.writeAttribute("taM",QString::number(dados->reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


    //         double tamanhoObjeto=0;

    //         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
    //         tamanhoObjeto = qSqrt(tamanhoObjeto);

    //         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


    //         //novo





             stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
             stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
             stream.writeAttribute("Valt",QString::number(reCinema.varAltura[i]));
             stream.writeAttribute("Vlar",QString::number(reCinema.varLargura[i]));

             stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));


             std::vector<float> varAltura;
             std::vector<float> varLargura;

             if(reCinema.ruidoMaxVaria[i]){
                 stream.writeAttribute("rMinV","true");

             }else{
                 stream.writeAttribute("rMinV","false");
             }
             if(reMorfo.objetoEncontrado[i]){

                 stream.writeAttribute("OE","true");

             }else{

                 stream.writeAttribute("OE","false");
             }



             stream.writeEndElement(); //fecha proce

             }
         }


     }





//     etografia.framFim;
//    for(int i=0;i<etografia.quantidadeDepontos;i++){

//       stream.writeStartElement("analise");
//       stream.writeAttribute("ponto", QString::number(i));
//       stream.writeAttribute("id", QString::number(etografia.id[i]));
//       stream.writeAttribute("frameInicial", QString::number( etografia.frameComeco[i]));

//       stream.writeAttribute("frameFinal", QString::number(etografia.framFim[i]));

//        stream.writeEndElement(); //fecha analise

//        }



     stream.writeEndElement();//fecha analises

     }

    stream.writeEndElement();//fecha area
    stream.writeEndElement();// fecha dadosAnalise





    stream.writeEndElement();//fecha analiseEtografica
    stream.writeEndDocument();


    OutEtografia.close();

    //converte o xml para csv
    parser = new parserXMLtoCSV();
    parser->converteArquivo(nomeGravarProcesImagem);


     }
//    nomeGravarProcesImagem = QFileDialog::getSaveFileName(
//                this,
//                tr("Save File"),
//                "C://",
//               "Traking Files (*.tkin)"
//               );



//    qDebug()<<"oi 1";

//    enconPontoArea();

//    qDebug()<<"oi 2";

//    if(!nomeGravarProcesImagem.isEmpty()){
//    OutEtografia2.setFileName(nomeGravarProcesImagem);

//    qDebug()<<"oi 2.1";
//    OutEtografia2.open(QIODevice::WriteOnly);
//    qDebug()<<"oi 2.1.a";
//    QXmlStreamWriter stream(&OutEtografia2); //passa o endereço
//    qDebug()<<"oi 2.1.b";
//    stream.setAutoFormatting(true);

//    qDebug()<<"oi 2.1.c";
//    stream.writeStartDocument();//começa o documento
//    stream.writeStartElement("analiseProcessaImage");
//    stream.writeStartElement("dadosExperimentador");
//             stream.writeTextElement("experimentador",experimentador.nome);
//             stream.writeTextElement("laboratorio",experimentador.lab);
//    stream.writeEndElement();//fecha analiseEtografica

//     qDebug()<<"oi 2.1.d";
//    stream.writeStartElement("dadosVideoAnalisado");
//             stream.writeTextElement("nomeVxml",videoLista.nomeVXML[contadorDeVideo]);
//             stream.writeTextElement("frameInicial",QString::number(videoLista.frameInicial[contadorDeVideo]));
//             stream.writeTextElement("frameBack",QString::number(videoLista.frameBack[contadorDeVideo]));
//             stream.writeTextElement("frameProces",QString::number(videoLista.frameProces[contadorDeVideo]));
//             stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]));
//             stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
//              stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
//    stream.writeEndElement();//fecha informacoes

//    qDebug()<<"oi 2.1.e";

//    stream.writeStartElement("dadosCatalago");
//    stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);



//     qDebug()<<"oi 2.2";
//    stream.writeStartElement("Categorias");
//    int contador=0;

//    for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

//       stream.writeStartElement("categoria");
//       stream.writeAttribute("id", QString::number(i));
//       stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
//       stream.writeEndElement();

//       }
//    stream.writeEndElement();


//    qDebug()<<"oi 2.3";
//    stream.writeStartElement("areasDeInteresse");

//    for(int ja=0; ja< videoLista.area[contadorDeVideo].tipo.size(); ja++ ){

//        stream.writeStartElement("infoArea");
//        stream.writeAttribute("id", QString::number(ja));
//        stream.writeTextElement("figName",videoLista.area[contadorDeVideo].nomeFig[ja]);
//        if(videoLista.area[contadorDeVideo].tipo[ja]=="circle"){

//        stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
//        stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
//        stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

//        stream.writeTextElement("raio",QString::number(videoLista.area[contadorDeVideo].raio[conCir2]));

//        conCir2++;

//        }else{
//            stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
//            stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
//            stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

//            stream.writeTextElement("width",QString::number(videoLista.area[contadorDeVideo].width[conRet2]));
//            stream.writeTextElement("heigth",QString::number(videoLista.area[contadorDeVideo].height[conRet2]));
//        conRet2++;

//        }
//        //stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
//        //        stream.writeAttribute("tipo",videoLista.area[contadorDeVideo].oriX[ja];
//        stream.writeEndElement();

//    }


//     stream.writeEndElement(); //fecha caminho Ext


//    stream.writeEndElement();//fecha Categorias
//   // stream.writeEndElement();//fecha dadosCatalago

//    stream.writeStartElement("dadosAnalise");

//    if(ui->cbAuto->isChecked()){

//        stream.writeTextElement("tipoAnalise","Autoesclusiva" );
//    }else{

//         stream.writeTextElement("tipoAnalise","sobreposta" );
//    }

////    if(ui->cbNested->isChecked()){
////     stream.writeTextElement("tipoAnalise","sobreposta" );
////    }


//     stream.writeStartElement("anaProceImagem");


//     for(int ka=0; ka< videoLista.area[contadorDeVideo].oriX.size(); ka++ ){



//     stream.writeStartElement("area");


//     stream.writeAttribute("id",QString::number(ka));

//      qDebug()<<"oi 3";

//     //stream.writeAttribute("");
//     int fraNumero=0;
//     for(int i=0; i< reMorfo.area.size();i++){

//         if(matObjDentro[ka][i]){

//         stream.writeStartElement("proce");
//         fraNumero=i+ videoLista.frameProces[contadorDeVideo];

//         stream.writeAttribute("f",QString::number(fraNumero));
//         stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
//         stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
//         stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
//         stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
//         stream.writeAttribute("taP",QString::number(reMorfo.tamanhoObj[i]));
//         stream.writeAttribute("taM",QString::number(reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));
//         stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i]));

//         stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
//         stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));
//         stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
//         stream.writeAttribute("VtoP",QString::number(reCinema.varTamObjeto[i]));

//         if(reCinema.ruidoMaxVaria[i]){
//             stream.writeAttribute("rMV","true");

//         }else{
//             stream.writeAttribute("rMV","false");
//         }
//         if(reMorfo.objetoEncontrado[i]){

//             stream.writeAttribute("OE","true");

//         }else{

//             stream.writeAttribute("OE","false");
//         }



//         stream.writeEndElement(); //fecha proce

//         }
//     }


//     qDebug()<<"oi 4";

////     etografia.framFim;
////    for(int i=0;i<etografia.quantidadeDepontos;i++){

////       stream.writeStartElement("analise");
////       stream.writeAttribute("ponto", QString::number(i));
////       stream.writeAttribute("id", QString::number(etografia.id[i]));
////       stream.writeAttribute("frameInicial", QString::number( etografia.frameComeco[i]));

////       stream.writeAttribute("frameFinal", QString::number(etografia.framFim[i]));

////        stream.writeEndElement(); //fecha analise

////        }



//     stream.writeEndElement();//fecha analises

//     }

//    stream.writeEndElement();//fecha area
//    stream.writeEndElement();// fecha dadosAnalise





//    stream.writeEndElement();//fecha analiseEtografica
//    stream.writeEndDocument();


//    OutEtografia2.close();
//qDebug()<<"oi 5";


//     }
}

void telaTempoReal::on_pbGravaRelatorioFPS_clicked()
{
    ui->pbStoCap->clicked(); //pausa

//    nomeGravarFPS = QFileDialog::getSaveFileName(
//                this,
//                tr("Save File"),
//                "C://",
//               "FPS Files (*.fps)"
//               );


    nomeGravarFPS = nomeArquivo;
    QByteArray nomeGravarFPSByte = nomeGravarFPS.toLatin1();

    nomeGravarFPSByte.truncate(nomeGravarFPSByte.indexOf("."));   //  nomeGravarFPSByte.indexOf(".");
    nomeGravarFPSByte.append(".fps");


    nomeGravarFPS =  QString::fromLatin1(nomeGravarFPSByte);
//    qDebug()<<"oi 1";

//    enconPontoArea();

//    qDebug()<<"oi 2";

    if(!nomeGravarFPS.isEmpty()){
    OutEtografia2.setFileName(nomeGravarFPS);

    qDebug()<<"oi 2.1";
    OutEtografia2.open(QIODevice::WriteOnly);
    qDebug()<<"oi 2.1.a";
    QXmlStreamWriter stream(&OutEtografia2); //passa o endereço
    qDebug()<<"oi 2.1.b";
    stream.setAutoFormatting(true);

//    qDebug()<<"oi 2.1.c";
    stream.writeStartDocument();//começa o documento
    stream.writeStartElement("fpsVideoGravado");
//    stream.writeStartElement("dadosExperimentador");
//             stream.writeTextElement("experimentador",experimentador.nome);
//             stream.writeTextElement("laboratorio",experimentador.lab);
//    stream.writeEndElement();//fecha analiseEtografica

//     qDebug()<<"oi 2.1.d";
    stream.writeStartElement("dadosVideoGravado");
             stream.writeTextElement("nomeVxml",nomeArquivo);
             stream.writeTextElement("codecSet",ui->comboBoX->currentText());
             stream.writeTextElement("videoHeight",QString::number(video_height)); //QString::number( captadorDeVideo->video_heigth));
             stream.writeTextElement("videoWidht", QString::number(video_width));//QString::number(captadorDeVideo->video_width));
             stream.writeTextElement("fpsConfiGravar", QString::number(fpsGravado));



             for(int ka=0; ka< vetorTempoAquisicao.size(); ka++){
                 fpsMedio= fpsMedio+ (1/vetorTempoAquisicao[ka])/vetorTempoAquisicao.size();

             }

             stream.writeTextElement("fpsMedio",QString::number(fpsMedio));

             long double somatorio=0;

             for(int ka=0; ka< vetorTempoAquisicao.size(); ka++){

                 somatorio = somatorio + qPow( 1/vetorTempoAquisicao[ka] -fpsMedio,2);


             }


             variancia = (vetorTempoAquisicao.size() -1);
             variancia = 1/variancia;
             variancia= variancia* somatorio;
             desvioPadrao = qSqrt(variancia);

             stream.writeTextElement("variancia",QString::number(variancia));
             stream.writeTextElement("desvioPadrao",QString::number(desvioPadrao));





//             stream.writeTextElement("frameInicial",QString::number(videoLista.frameInicial[contadorDeVideo]));
//             stream.writeTextElement("frameBack",QString::number(videoLista.frameBack[contadorDeVideo]));
//             stream.writeTextElement("frameProces",QString::number(videoLista.frameProces[contadorDeVideo]));
//             stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]));
//             stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
//              stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
    stream.writeEndElement();//fecha informacoes

//    qDebug()<<"oi 2.1.e";

//    stream.writeStartElement("dadosCatalago");
//    stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);



//     qDebug()<<"oi 2.2";
//    stream.writeStartElement("Categorias");
//    int contador=0;

//    for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

//       stream.writeStartElement("categoria");
//       stream.writeAttribute("id", QString::number(i));
//       stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
//       stream.writeEndElement();

//       }
//    stream.writeEndElement();


    qDebug()<<"oi 2.3";
    stream.writeStartElement("videoFps");

    for(int ja=0; ja< vetorTempoAquisicao.size(); ja++ ){


        stream.writeStartElement("frame");
        stream.writeAttribute("id", QString::number(ja));
        stream.writeAttribute("frame", QString::number(vetorFrameAquisicao[ja]));
        stream.writeAttribute("fps", QString::number(1/vetorTempoAquisicao[ja]));
        stream.writeEndElement();


    }


     stream.writeEndElement(); //fecha caminho Ext



    stream.writeEndElement();//fecha analiseEtografica
    stream.writeEndDocument();


    OutEtografia2.close();


    qDebug()<<"oi 2.4";


    ui->pbGravaRelatorioFPS->setEnabled(false);

     }//fecha o if que se o nome estiver fora
}

void telaTempoReal::on_pbLerCatalogo_clicked()
{
    nomeGravarCatalago= QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                   "Video Files (*.caxml)"
                    );



    if(!nomeGravarCatalago.isEmpty())
    {

        //ui->lblCatalogo->setText(nomeGravarCatalago);
        readCatalago();
        ui->pbLerCatalogo->setEnabled(false);
        ui->cbRegistro->setEnabled(false);
        ui->pbConfig->setEnabled(true);

        //ui->gbStep5->setVisible(true);
    }
}

void telaTempoReal::on_cbAuto_clicked(bool checked)
{
//    if(checked){

        ui->cbAuto->setChecked(checked);
        ui->cbNested->setChecked(!checked);

//    }else{




//    }
}

void telaTempoReal::on_cbNested_clicked(bool checked)
{
    ui->cbAuto->setChecked(!checked);
    ui->cbNested->setChecked(checked);
}

void telaTempoReal::slotMapeado(int a)
{
    chNovoValor=true;
    //frame_atual = ui->labelFrames->text().toDouble();
    double finalframe1 =1000;// videoLista.frameFinal[0];

    //escolheSelecao=false; //true é auto
    //false nested
    if(!escolheSelecao){ //se pode clicar mais de um botão por vez
        for(int i=0; i<numeroDeBotoes; i++){
            if(i==a){

                if(!clicado[i]){
                    //se o botão nao estiver clicado
                    clicado[i]=true;
                    buttonList[i]->setStyleSheet("background-color: yellow;""color: blue;" "font: bold;");
                    buttonList[i]->setText(nomeCate[i]+ "(" + cAnaEto.atalho[i] +")" + " (Marking)");

                    //criando novo ponto apos clique
                    saida.id.push_back(a);
                    saida.frameComeco.push_back( frame_atual);
                    //saida.frameFinalBuffer[i]=frame_atual;
                    saida.framFim.push_back(finalframe1);
                    saida.pontosPostos[i]=count;
                    count++;

                    saida.quantidadeDepontos=count;



                }else {
                    //se o posição estiver clicado
                    clicado[i]=false;
                    // for(int k=0;k<numeroDeBotoes;k++){
                    buttonList[i]->setStyleSheet("background-color: green;""color: black; " "font: bold;");
                    buttonList[i]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")" +" (Ready)");
                    //saida.frameComeco.push_back(frame_atual);
                    //    }

                    saida.frameFinalBuffer[i]=frame_atual;
                    //if(botaoJaClicado){
                    int valorSaida;
                    valorSaida= saida.pontosPostos[i];
                    saida.framFim[valorSaida]=frame_atual;
                    //}
                    //        saida.frameFinalBuffer[i]=frame_atual;
                }
            }


        }
    }else{ //se for apenas um botao por vez (auto esclusivo


        //nenhum botão precionado
        //algum botão precionado
        //precionado outro botão



        if((compAnterior==-1) || (chCorrigir)){ //para o primeiro comportamento

            for(int i=0; i<numeroDeBotoes; i++){
                clicado[i]=false;
                buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
                buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                buttonList[i]->setEnabled(true);

            }


            for(int i=0; i<numeroDeBotoes; i++){
                if(i==a){

                    //diferencia se o botão esta clicado esta release
                    if(!clicado[i]){
                        clicado[i]=true;
                        buttonList[i]->setStyleSheet("background-color: red;""color: black;" "font: bold;");
                        buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                        buttonList[i]->setEnabled(false);

                        //dados
                        saida.id.push_back(a);
                        saida.frameComeco.push_back( frame_atual);
                        //dados
                        //saida.frameFinalBuffer[i]=frame_atual;
                        saida.framFim.push_back(finalframe1);
                        saida.pontosPostos[i]=count;
                        count++;
                        saida.quantidadeDepontos= count;
                        compAnterior=a;
                        contAtivoReg++;

                    }else {
                        clicado[i]=false;
                        // for(int k=0;k<numeroDeBotoes;k++){
                        buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
                        buttonList[i]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")");
                        buttonList[i]->setEnabled(true);

                        saida.frameFinalBuffer[i]=frame_atual;
                        //if(botaoJaClicado){
                        int valorSaida;
                        valorSaida= saida.pontosPostos[i];
                        //dados
                        saida.framFim[valorSaida]=frame_atual;
                        //dados

                    }

                }

            }




        }else{ //para os demais comportamentos

            //primeiro tem que encerrar o comportamento anterior


//            for(int i=0; i<numeroDeBotoes; i++){

//                 if(compAnterior==i){




//                 }



//            }

            contAtivoReg++;

//            if(chCorrigir){
//               for(int i=0; i<numeroDeBotoes; i++){
//                   clicado[i]=false;
//                   buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
//                   buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
//                   buttonList[i]->setEnabled(true);

//               }

//            }

            //clicado[compAnterior]=false;
            //if(!chCorrigir){

                //logica para o botão que tinha sido apertado anteriormente
            clicado[compAnterior]=false;
                // for(int k=0;k<numeroDeBotoes;k++){
    //            buttonList[compAnterior]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
    //            buttonList[compAnterior]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")");
    //            buttonList[compAnterior]->setEnabled(true);

                saida.frameFinalBuffer[compAnterior]=frame_atual;
                //if(botaoJaClicado){
                int valorSaida;
                valorSaida= saida.pontosPostos[compAnterior];
                //dados
                saida.framFim[valorSaida]=frame_atual;
                qDebug()<< "id " << saida.id[valorSaida] << "inicio "<< saida.frameComeco[valorSaida] << "saida " <<saida.framFim[valorSaida];



           // }
          //  chCorrigir=false; //para nao permitir a parte do codigo de cima rodar
                              //eh usado para nao deixar




            //logica para o botão apertado
            clicado[a]=true;
//            buttonList[a]->setStyleSheet("background-color: yellow;""color: black;" "font: bold;");
//            buttonList[a]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")" +" (Marking)");
//            buttonList[a]->setEnabled(false);

            //dados
            saida.id.push_back(a);
            saida.frameComeco.push_back( frame_atual);
            //dados
            //saida.frameFinalBuffer[i]=frame_atual;
            saida.framFim.push_back(finalframe1);
            saida.pontosPostos[a]=count;
            count++;
            saida.quantidadeDepontos= count;
            compAnterior=a;




            for(int i=0; i<numeroDeBotoes; i++){

                if(clicado[i]){

                    buttonList[i]->setStyleSheet("background-color: red;""color: black;" "font: bold;");
                    buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                    buttonList[i]->setEnabled(false);



                }else{

                    buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
                    buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                    buttonList[i]->setEnabled(true);
                }

            }


//            for(int i=0; i<numeroDeBotoes; i++){
//                if(i==a){

//                    //diferencia se o botão esta clicado esta release
//                    if(!clicado[i]){
//                        clicado[i]=true;
//                        buttonList[i]->setStyleSheet("background-color: yellow;""color: black;" "font: bold;");
//                        buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")" +" (Marking)");
//                        buttonList[i]->setEnabled(false);

//                        //dados
//                        saida.id.push_back(a);
//                        saida.frameComeco.push_back( frame_atual);
//                        //dados
//                        //saida.frameFinalBuffer[i]=frame_atual;
//                        saida.framFim.push_back(finalframe1);
//                        saida.pontosPostos[i]=count;
//                        count++;
//                        saida.quantidadeDepontos= count;
//                        compAnterior=a;

//                    }else {
//                        clicado[i]=false;
//                        // for(int k=0;k<numeroDeBotoes;k++){
//                        buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
//                        buttonList[i]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")");
//                        buttonList[i]->setEnabled(true);

//                        saida.frameFinalBuffer[i]=frame_atual;
//                        //if(botaoJaClicado){
//                        int valorSaida;
//                        valorSaida= saida.pontosPostos[i];
//                        //dados
//                        saida.framFim[valorSaida]=frame_atual;
//                        //dados

//                    }

//                }

//            }









        }

        chCorrigir=false;

//faz os controlador ficare enabled
            //pq sao setados false quando é excluido algum ponto
        //ui->widControes->setEnabled(true);
     //   ui->widControle1->setEnabled(true);



    }//fim da logica para botões auto-exclusivos






        //encontra o botão precionado
//        for(int i=0; i<numeroDeBotoes; i++){
//            if(i==a){

//                //diferencia se o botão esta clicado esta release
//                if(!clicado[i]){
//                    clicado[i]=true;
//                    buttonList[i]->setStyleSheet("background-color: yellow;""color: black;" "font: bold;");
//                    buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")" +" (Marking)");

//                    //dados
//                    saida.id.push_back(a);
//                    saida.frameComeco.push_back( frame_atual);
//                    //dados
//                    //saida.frameFinalBuffer[i]=frame_atual;
//                    saida.framFim.push_back(finalframe1);
//                    saida.pontosPostos[i]=count;
//                    count++;
//                    saida.quantidadeDepontos= count;
//                    compAnterior=a;

//                }else {
//                    clicado[i]=false;
//                    // for(int k=0;k<numeroDeBotoes;k++){
//                    buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
//                    buttonList[i]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")" +" (Ready)");

//                    saida.frameFinalBuffer[i]=frame_atual;
//                    //if(botaoJaClicado){
//                    int valorSaida;
//                    valorSaida= saida.pontosPostos[i];
//                    //dados
//                    saida.framFim[valorSaida]=frame_atual;
//                    //dados

//                }

//            }

//        }


        //controla as propiedade dos bo~toes

//        if(habilita){
//            habilita=false;
//            for(int k=0;k<numeroDeBotoes;k++){
//                if(k==a){
//                    //clicado[k]=true;
//                    buttonList[k]->setStyleSheet("background-color: yellow;""color: black;" "font: bold;");
//                    buttonList[k]->setText(nomeCate[k] +"(" + cAnaEto.atalho[k] +")" + " (Marking)");
//                    buttonList[k]->setEnabled(true);

//                }else{
//                    //clicado[k]=false;
//                    buttonList[k]->setStyleSheet("background-color: red;""color: black;" "font: bold;");
//                    buttonList[k]->setText(nomeCate[k]+ "(" + cAnaEto.atalho[k] +")" +" (blocked)");
//                    buttonList[k]->setEnabled(false);

//                }
//            }

//        } else {
//            habilita=true;
//            for(int k=0;k<numeroDeBotoes;k++){
//                //clicado[k]=true; /fase
//                buttonList[k]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
//                buttonList[k]->setText(nomeCate[k]+ "(" + cAnaEto.atalho[k] +")"+" (ready)");
//                buttonList[k]->setEnabled(true);
//            }
//        }





   // } //fim da logica para botões auto-exclusivos


    //ve se algum botão esta ativado

    bool chEditaOn=true;

//    for(int ka=0; ka <numeroDeBotoes;ka++){

//        if(clicado[ka]){

//            chEditaOn=false;
//           // break;

//        }

//    }

    ui->tabButtons->setTabEnabled(1,chEditaOn);




    //fim do antigo
//    //frame_atual = ui->labelFrames->text().toDouble();
//    double finalframe1 = 1000; //videoLista.frameFinal[0];

//    //escolheSelecao=false; //true é auto
//    //false nested
//    if(!escolheSelecao){ //se pode clicar mais de um botão por vez
//        for(int i=0; i<numeroDeBotoes; i++){
//            if(i==a){

//                if(!clicado[i]){
//                    //se o botão nao estiver clicado
//                    clicado[i]=true;
//                    buttonList[i]->setStyleSheet("background-color: yellow;""color: blue;" "font: bold;");
//                    buttonList[i]->setText(nomeCate[i]+ "(" + cAnaEto.atalho[i] +")" + " (Marking)");

//                    //criando novo ponto apos clique
//                    saida.id.push_back(a);
//                    saida.frameComeco.push_back( frame_atual);
//                    //saida.frameFinalBuffer[i]=frame_atual;
//                    saida.framFim.push_back(finalframe1);
//                    saida.pontosPostos[i]=count;
//                    count++;

//                    saida.quantidadeDepontos=count;



//                }else {
//                    //se o posição estiver clicado
//                    clicado[i]=false;
//                    // for(int k=0;k<numeroDeBotoes;k++){
//                    buttonList[i]->setStyleSheet("background-color: green;""color: black; " "font: bold;");
//                    buttonList[i]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")" +" (Ready)");
//                    //saida.frameComeco.push_back(frame_atual);
//                    //    }

//                    saida.frameFinalBuffer[i]=frame_atual;
//                    //if(botaoJaClicado){
//                    int valorSaida;
//                    valorSaida= saida.pontosPostos[i];
//                    saida.framFim[valorSaida]=frame_atual;
//                    //}
//                    //        saida.frameFinalBuffer[i]=frame_atual;
//                }
//            }


//        }
//    }else{ //se for apenas um botao por vez (auto esclusivo

//        //encontra o botão precionado
//        for(int i=0; i<numeroDeBotoes; i++){
//            if(i==a){

//                //diferencia se o botão esta clicado esta release
//                if(!clicado[i]){
//                    clicado[i]=true;
//                    buttonList[i]->setStyleSheet("background-color: yellow;""color: black;" "font: bold;");
//                    buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")" +" (Marking)");

//                    //dados
//                    saida.id.push_back(a);
//                    saida.frameComeco.push_back( frame_atual);
//                    //dados
//                    //saida.frameFinalBuffer[i]=frame_atual;
//                    saida.framFim.push_back(finalframe1);
//                    saida.pontosPostos[i]=count;
//                    count++;
//                    saida.quantidadeDepontos= count;

//                }else {
//                    clicado[i]=false;
//                    // for(int k=0;k<numeroDeBotoes;k++){
//                    buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
//                    buttonList[i]->setText(nomeCate[i]+"(" + cAnaEto.atalho[i] +")" +" (Ready)");

//                    saida.frameFinalBuffer[i]=frame_atual;
//                    //if(botaoJaClicado){
//                    int valorSaida;
//                    valorSaida= saida.pontosPostos[i];
//                    //dados
//                    saida.framFim[valorSaida]=frame_atual;
//                    //dados

//                }

//            }

//        }

//        if(habilita){
//            habilita=false;
//            for(int k=0;k<numeroDeBotoes;k++){
//                if(k==a){
//                    //clicado[k]=true;
//                    buttonList[k]->setStyleSheet("background-color: yellow;""color: black;" "font: bold;");
//                    buttonList[k]->setText(nomeCate[k] +"(" + cAnaEto.atalho[k] +")" + " (Marking)");
//                    buttonList[k]->setEnabled(true);

//                }else{
//                    //clicado[k]=false;
//                    buttonList[k]->setStyleSheet("background-color: red;""color: black;" "font: bold;");
//                    buttonList[k]->setText(nomeCate[k]+ "(" + cAnaEto.atalho[k] +")" +" (blocked)");
//                    buttonList[k]->setEnabled(false);

//                }
//            }

//        } else {
//            habilita=true;
//            for(int k=0;k<numeroDeBotoes;k++){
//                //clicado[k]=true; /fase
//                buttonList[k]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
//                buttonList[k]->setText(nomeCate[k]+ "(" + cAnaEto.atalho[k] +")"+" (ready)");
//                buttonList[k]->setEnabled(true);
//            }
//        }





//    }


//    //ve se algum botão esta ativado

//    bool chEditaOn=true;

//    for(int ka=0; ka <numeroDeBotoes;ka++){

//        if(clicado[ka]){

//            chEditaOn=false;
//           // break;

//        }

//    }

//    ui->tabButtons->setTabEnabled(1,chEditaOn);


}

void telaTempoReal::on_tabButtons_tabBarClicked(int index)
{
    if(index == 1){
    //ui->tabRegistro->setColumnCount(3);
        bool chvEscreRow=true;
        while(chvEscreRow){
            //0 > 0
            //2 > 2

            if(saida.quantidadeDepontos > ui->tabRegistro->rowCount()){

                ui->tabRegistro->insertRow(ui->tabRegistro->rowCount());
                ui->tabRegistro->setItem (ui->tabRegistro->rowCount()-1,0,new QTableWidgetItem(
                                             cAnaEto.nomeCategoria[saida.id[ui->tabRegistro->rowCount()-1]] ) );
                ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,1,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.frameComeco[ui->tabRegistro->rowCount()-1]]
                                         -vetorTempoFrame[frameInicioRegistro])));
                ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,2,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.framFim[ui->tabRegistro->rowCount()-1]]
                                         -vetorTempoFrame[frameInicioRegistro])));

                saida.chPontoValido.push_back(true);


                //configurando TableWidget
                ui->tabRegistro->resizeColumnsToContents();
                ui->tabRegistro->clearSelection();
                ui->tabRegistro->clearFocus();


            }else{

                chvEscreRow= false;


            }


        }

        for(int ka=0; ka< ui->tabRegistro->rowCount();ka++ ){

    //                ui->tabRegistro->setRowCount(ka);
    //                ui->tabRegistro->setColumnCount(1);
    //                ui->tabRegistro->setItem();

//            ui->tabRegistro->insertRow(ui->tabRegistro->rowCount());
            ui->tabRegistro->setItem (ka,0,new QTableWidgetItem(
                                         cAnaEto.nomeCategoria[saida.id[ka]] ) );
            ui->tabRegistro->setItem(ka,1,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.frameComeco[ka]]
                                     -vetorTempoFrame[frameInicioRegistro])));
            ui->tabRegistro->setItem(ka,2,new QTableWidgetItem(QString::number(vetorTempoFrame[saida.framFim[ka]]
                                     -vetorTempoFrame[frameInicioRegistro])));

          //  saida.chPontoValido.push_back(true);


            //configurando TableWidget
            ui->tabRegistro->resizeColumnsToContents();
            ui->tabRegistro->clearSelection();
            ui->tabRegistro->clearFocus();



        }



    }
}

void telaTempoReal::on_pbEtographyStart_clicked()
{
    //qDebug()<<"inicialixou aa";
    ui->pbEtographyStart->setEnabled(false);
    if(ui->chAImage->isChecked()){

          ui->tabWControlador->setCurrentIndex(0);
    }

    ui->tabButtons->setCurrentIndex(0);
    ui->widBotoes->setEnabled(true);
    ui->lblEtographiOn->setText("Etographia is Avaible");
    ui->lblEtographiOn->setStyleSheet("background-color: green;""color: black; " "font: bold;");
    ui->widBotoes->setVisible(true);


    if(ui->chAImage->isChecked()){

        frameInicioRegistro =frame_atual;



        if(ui->cbProcessInagem->isChecked()){
            //se esta habilitado o processamento de imagem
            ui->pushButton_4->clicked();
        }

//        if(ui->cbCapturaVideo->isChecked()){

//            ui->pbStarrFilming->click();

//        }

        //ui->lblEtogrStar->setText(QString::number(vetorTempoFrame[frameInicioRegistro]));




    }else{

        tempoLerFrame = new QTimer();
        connect(tempoLerFrame,SIGNAL(timeout()),this,SLOT(atualizaContadorRegistro()));

        frame_atual=0;
        frameInicioRegistro = frame_atual;
        tempoLerFrame->start(10);
        tinicial = clock();
        qDebug()<<"inicialixou o timer";

    }

      //ui->lblEtogrStar->setText(QString::number(vetorTempoFrame[frameInicioRegistro]));


}

void telaTempoReal::atualizaContadorRegistro()
{
    //qDebug()<<"tiimer iniciado";
    tfinal = clock();
    frame_atual = frame_atual+1;

    tresposta=(float) (tfinal-tinicial)/CLOCKS_PER_SEC;

    vetorTempoFrame.push_back(tresposta);
    ui->lblTime->setText(QString::number(tresposta) + " s");

    if(primeiraB){

        ui->lblEtogrStar->setText("Tempo inicial do processamento " + QString::number(vetorTempoFrame[frameInicioRegistro]) + " s");
        primeiraB=false;
    }
    atualizaRegistro();



}

void telaTempoReal::on_pbLerArquivoVxml_clicked(bool checked)
{

}

void telaTempoReal::on_pbEtographyEnd_clicked()
{



    saida.framFim[saida.framFim.size()-1] = frame_atual-1;
    //vetorTempoFrame[saida.quantidadeDepontos-1] = tresposta;
    atualizaRegistro();
    ui->pbEtographyStart->setEnabled(false);
    ui->pbGravarAnalasiteEtografica->setEnabled(true);

    ui->tabButtons->setCurrentIndex(3);
    ui->tabButtons->setTabEnabled(0,false);
    ui->tabButtons->setTabEnabled(1,false);

    if(!ui->chAImage->isChecked()){//entra quando s[p esta selecionado par aetografia
        tempoLerFrame->stop();


    }else{

        ui->pbStoCap->click();

    }

    if(ui->cbCapturaVideo->isChecked()){

        ui->pbStoCap->click();
        cv::waitKey(20);


        ui->pbStopFilming->click();
        cv::waitKey(20);

        ui->pbTerminaGrava->click();
            cv::waitKey(20);
        //ui->pbGravaRelatorioFPS->click();
        //cv::waitKey(20);


    }

    if(ui->chAImage->isChecked()){
        ui->pbStoCap->click();
        cv::waitKey(20);

    }


}

void telaTempoReal::on_pbGravarAnalasiteEtografica_clicked()
{




    nomeGravarEtografia = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "etography files (*.etoxml)"
               );



 if(!nomeGravarEtografia.isEmpty()){
//  // ui->pbGravarAnalasiteEtografica->setEnabled(false);

//     if(ui->chAImage->isChecked()){ //se esta setado para capturar imagem ou não





//     }else{



//     }




     if(!ui->cbCapturaVideo->isChecked()){ // quano não tem captura de video //só real time catalogo

         OutEtografia.setFileName(nomeGravarEtografia);


         OutEtografia.open(QIODevice::WriteOnly);

         QXmlStreamWriter stream(&OutEtografia); //passa o endereço
         stream.setAutoFormatting(true);

         stream.writeStartDocument();//começa o documento
         stream.writeStartElement("analiseEtografica");
         stream.writeStartElement("dadosExperimentador");
                  stream.writeTextElement("experimentador",experimentador.nome);
                  stream.writeTextElement("laboratorio",experimentador.lab);
         stream.writeEndElement();//fecha analiseEtografica

         stream.writeStartElement("dadosVideoAnalisado");
               //   stream.writeTextElement("nomeVxml",videoLista.nomeVXML[contadorDeVideo]);
                  stream.writeTextElement("frameInicial", "0");//QString::number(vetorTempoFrame[frameInicioRegistro]));
                  stream.writeTextElement("frameProces",QString::number(vetorTempoFrame[frameInicioRegistro]));
                  stream.writeTextElement("frameFinal", ui->lblTime->text()); //QString::number(vetorTempoFrame[vetorTempoFrame.size()-1]));
                  stream.writeTextElement("fps",QString::number(0.01)); //fps de 10ms
         stream.writeEndElement();//fecha informacoes

         stream.writeStartElement("dadosCatalago");
         stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);
         //stream.writeStartElement("informacoes");



         stream.writeStartElement("Categorias");
         int contador=0;

         for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

            stream.writeStartElement("categoria");
            stream.writeAttribute("id", QString::number(i));
            stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
            stream.writeEndElement();

            }


          stream.writeEndElement(); //fecha caminho Ext


         stream.writeEndElement();//fecha Categorias
        // stream.writeEndElement();//fecha dadosCatalago

         stream.writeStartElement("dadosAnalise");

         if(ui->cbAuto->isChecked()){
          stream.writeTextElement("tipoAnalise","Autoesclusiva" );
         }

         if(ui->cbNested->isChecked()){
          stream.writeTextElement("tipoAnalise","sobreposta" );
         }



         stream.writeStartElement("analises");

         int contEx=0;
         for(int i=0;i<saida.quantidadeDepontos;i++){



             if(saida.chPontoValido.size()!=0){ //erro por nao ter olhado os pontos
                 if(saida.chPontoValido[i]){

                     stream.writeStartElement("analise");
                     stream.writeAttribute("ponto", QString::number(contEx));
                     stream.writeAttribute("id", QString::number(saida.id[i]));
                     stream.writeAttribute("frameInicial", QString::number( vetorTempoFrame[saida.frameComeco[i]]));
                     stream.writeAttribute("frameFinal", QString::number(vetorTempoFrame[saida.framFim[i]]));

                      stream.writeEndElement(); //fecha analise

                      contEx++;

                 }

             }else{
                 stream.writeStartElement("analise");
                 stream.writeAttribute("ponto", QString::number(contEx));
                 stream.writeAttribute("id", QString::number(saida.id[i]));
                 stream.writeAttribute("frameInicial", QString::number( vetorTempoFrame[saida.frameComeco[i]]));
                 stream.writeAttribute("frameFinal", QString::number(vetorTempoFrame[saida.framFim[i]]));

                  stream.writeEndElement(); //fecha analise

                  contEx++;


             }




         }

          stream.writeEndElement();//fecha analises

         stream.writeEndElement();// fecha dadosAnalise





         stream.writeEndElement();//fecha analiseEtografica
         stream.writeEndDocument();


         OutEtografia.close();



     }else{ //se tiver marcado para gravar um video
//         nomeGravarEtografia = QFileDialog::getSaveFileName(
//                     this,
//                     tr("Save File"),
//                     "C://",
//                    "etography files (*.etoxml)"
//                    );



//      if(!nomeGravarEtografia.isEmpty()){
//       // ui->pbGravarAnalasiteEtografica->setEnabled(false);



        OutEtografia.setFileName(nomeGravarEtografia);


        OutEtografia.open(QIODevice::WriteOnly);

        QXmlStreamWriter stream(&OutEtografia); //passa o endereço
        stream.setAutoFormatting(true);

        stream.writeStartDocument();//começa o documento
        stream.writeStartElement("analiseEtografica");
        stream.writeStartElement("dadosExperimentador");
                 stream.writeTextElement("experimentador",experimentador.nome);
                 stream.writeTextElement("laboratorio",experimentador.lab);
        stream.writeEndElement();//fecha analiseEtografica

        stream.writeStartElement("dadosVideoAnalisado");
                 stream.writeTextElement("nomeVxml",nomeArquivo);
                 stream.writeTextElement("frameInicial",QString::number(0));
                 stream.writeTextElement("frameProces",QString::number(frameInicioRegistro-frameInicioGravacao));
                 stream.writeTextElement("frameFinal", QString::number(saida.framFim[saida.framFim.size()-1]-frameInicioGravacao));
                 stream.writeTextElement("fps", ui->leFps->text() ); //QString::number(videoLista.fps[contadorDeVideo]));
        stream.writeEndElement();//fecha informacoes

        stream.writeStartElement("dadosCatalago");
        stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);
        //stream.writeStartElement("informacoes");



        stream.writeStartElement("Categorias");
        int contador=0;

        for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

           stream.writeStartElement("categoria");
           stream.writeAttribute("id", QString::number(i));
           stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
           stream.writeEndElement();

           }


         stream.writeEndElement(); //fecha caminho Ext


        stream.writeEndElement();//fecha Categorias
       // stream.writeEndElement();//fecha dadosCatalago

        stream.writeStartElement("dadosAnalise");

        if(ui->cbAuto->isChecked()){
         stream.writeTextElement("tipoAnalise","Autoesclusiva" );
        }

        if(ui->cbNested->isChecked()){
         stream.writeTextElement("tipoAnalise","sobreposta" );
        }



        stream.writeStartElement("analises");

        int contEx=0;
        for(int i=0;i<saida.quantidadeDepontos;i++){



            if(saida.chPontoValido.size()!=0){ //erro por nao ter olhado os pontos
                if(saida.chPontoValido[i]){

                    stream.writeStartElement("analise");
                    stream.writeAttribute("ponto", QString::number(contEx));
                    stream.writeAttribute("id", QString::number(saida.id[i]));
                    stream.writeAttribute("frameInicial", QString::number( saida.frameComeco[i]-frameInicioRegistro-frameInicioGravacao));
                    stream.writeAttribute("frameFinal", QString::number(saida.framFim[i]-frameInicioRegistro-frameInicioGravacao));

                     stream.writeEndElement(); //fecha analise

                     contEx++;

                }

            }else{
                stream.writeStartElement("analise");
                stream.writeAttribute("ponto", QString::number(contEx));
                stream.writeAttribute("id", QString::number(saida.id[i]));
                stream.writeAttribute("frameInicial", QString::number( saida.frameComeco[i]-frameInicioRegistro-frameInicioGravacao));
                stream.writeAttribute("frameFinal", QString::number(saida.framFim[i]-frameInicioRegistro-frameInicioGravacao));

                 stream.writeEndElement(); //fecha analise

                 contEx++;


            }




        }

         stream.writeEndElement();//fecha analises

        stream.writeEndElement();// fecha dadosAnalise





        stream.writeEndElement();//fecha analiseEtografica
        stream.writeEndDocument();


        OutEtografia.close();



   //  }




     }



 }


}

void telaTempoReal::on_pbGravarAnalasiProces_clicked()
{
    ui->pbStoCap->clicked(); //pausa

    nomeGravarProcesImagem = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                fonteVideoXML,
               "Traking Files (*.tkin)"
               );



    qDebug()<<"0";
    enconPontoArea();
    qDebug()<<"1";


    if(!nomeGravarProcesImagem.isEmpty()){


      if( ui->cbCapturaVideo->isChecked()){

          OutEtografia.setFileName(nomeGravarProcesImagem);

          OutEtografia.open(QIODevice::WriteOnly);

          QXmlStreamWriter stream(&OutEtografia); //passa o endereço
          stream.setAutoFormatting(true);

          stream.writeStartDocument();//começa o documento
          stream.writeStartElement("analiseProcessaImage");
          stream.writeStartElement("dadosExperimentador");
                   stream.writeTextElement("experimentador",experimentador.nome);
                   stream.writeTextElement("laboratorio",experimentador.lab);
          stream.writeEndElement();//fecha analiseEtografica

          stream.writeStartElement("dadosVideoAnalisado");
                   stream.writeTextElement("nomeVxml",nomeArquivo);
                   stream.writeTextElement("frameInicial",QString::number(0));
                   stream.writeTextElement("frameBack",QString::number(-1));
                   stream.writeTextElement("frameProces",QString::number(contNumeroGrava-reMorfo.area.size()));
                   stream.writeTextElement("frameFinal",QString::number(contNumeroGrava));
                   stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
                    stream.writeTextElement("fps",ui->leFps->text());
                    stream.writeTextElement("tempoTotalProcessamento", ui->lblTime->text());
          stream.writeEndElement();//fecha informacoes

          stream.writeStartElement("dadosCatalago");
          stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);



          stream.writeStartElement("Categorias");
          int contador=0;

          for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

             stream.writeStartElement("categoria");
             stream.writeAttribute("id", QString::number(i));
             stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
             stream.writeEndElement();

             }
          stream.writeEndElement();

          stream.writeStartElement("areasDeInteresse");

          for(int ja=0; ja< videoLista.area[contadorDeVideo].tipo.size(); ja++ ){

              stream.writeStartElement("infoArea");
              stream.writeAttribute("id", QString::number(ja));
              stream.writeTextElement("figName",videoLista.area[contadorDeVideo].nomeFig[ja]);
              if(videoLista.area[contadorDeVideo].tipo[ja]=="circle"){

              stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
              stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
              stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

              stream.writeTextElement("raio",QString::number(videoLista.area[contadorDeVideo].raio[conCir2]));

              conCir2++;

              }else{
                  stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
                  stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
                  stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

                  stream.writeTextElement("width",QString::number(videoLista.area[contadorDeVideo].width[conRet2]));
                  stream.writeTextElement("heigth",QString::number(videoLista.area[contadorDeVideo].height[conRet2]));
              conRet2++;

              }
              //stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
              //        stream.writeAttribute("tipo",videoLista.area[contadorDeVideo].oriX[ja];
              stream.writeEndElement();

          }


           stream.writeEndElement(); //fecha caminho Ext


          stream.writeEndElement();//fecha Categorias
         // stream.writeEndElement();//fecha dadosCatalago

          stream.writeStartElement("dadosAnalise");

          if(ui->cbAuto->isChecked()){
           stream.writeTextElement("tipoAnalise","Autoesclusiva" );
          }

          if(ui->cbNested->isChecked()){
           stream.writeTextElement("tipoAnalise","sobreposta" );
          }


           stream.writeStartElement("anaProceImagem");


           for(int ka=0; ka< videoLista.area[contadorDeVideo].oriX.size(); ka++ ){



           stream.writeStartElement("area");


           stream.writeAttribute("id",QString::number(ka));

           //stream.writeAttribute("");
           int fraNumero=0;
           qDebug()<<"2";

           fraNumero= contNumeroGrava - reMorfo.area.size();


           for(int i=0; i<  reMorfo.area.size();i++){

               if(matObjDentro[ka][i]){

               stream.writeStartElement("proce");

               stream.writeAttribute("f",QString::number(fraNumero));
               stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
               stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
               stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
               stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
               stream.writeAttribute("altP",QString::number(reMorfo.altura[i]));
               stream.writeAttribute("altM",QString::number(reMorfo.altura[i]/videoLista.escala[contadorDeVideo]));
               stream.writeAttribute("larP",QString::number(reMorfo.largura[i]));
               stream.writeAttribute("larM",QString::number(reMorfo.largura[i]/videoLista.escala[contadorDeVideo]));
               stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i])); //angulo do objeto



      //         stream.writeAttribute("taP",QString::number(dados->reMorfo.tamanhoObj[i]));
      //         stream.writeAttribute("taM",QString::number(dados->reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


      //         double tamanhoObjeto=0;

      //         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
      //         tamanhoObjeto = qSqrt(tamanhoObjeto);

      //         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


      //         //novo





               stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
               stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
               stream.writeAttribute("Valt",QString::number(reCinema.varAltura[i]));
               stream.writeAttribute("Vlar",QString::number(reCinema.varLargura[i]));

               stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));


               std::vector<float> varAltura;
               std::vector<float> varLargura;

               if(reCinema.ruidoMaxVaria[i]){
                   stream.writeAttribute("rMinV","true");

               }else{
                   stream.writeAttribute("rMinV","false");
               }
               if(reMorfo.objetoEncontrado[i]){

                   stream.writeAttribute("OE","true");

               }else{

                   stream.writeAttribute("OE","false");
               }



               stream.writeEndElement(); //fecha proce

               }
               fraNumero++;
           }


//           for(int i=0; i< reMorfo.area.size();i++){

//               if(matObjDentro[ka][i]){

//               stream.writeStartElement("proce");
//               fraNumero=i+ videoLista.frameProces[contadorDeVideo];

//               stream.writeAttribute("f",QString::number(fraNumero));
//               stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
//               stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
//               stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
//               stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
//               stream.writeAttribute("taP",QString::number(reMorfo.tamanhoObj[i]));
//               stream.writeAttribute("taM",QString::number(reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


//      //         double tamanhoObjeto=0;

//      //         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
//      //         tamanhoObjeto = qSqrt(tamanhoObjeto);

//      //         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


//      //         //novo



//               stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i]));

//               stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
//               stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));
//               stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
//               stream.writeAttribute("VtoP",QString::number(reCinema.varTamObjeto[i]));

//               if(reCinema.ruidoMaxVaria[i]){
//                   stream.writeAttribute("rMV","true");

//               }else{
//                   stream.writeAttribute("rMV","false");
//               }
//               if(reMorfo.objetoEncontrado[i]){

//                   stream.writeAttribute("OE","true");

//               }else{

//                   stream.writeAttribute("OE","false");
//               }



//               stream.writeEndElement(); //fecha proce

//               }
//           }


      //     etografia.framFim;
      //    for(int i=0;i<etografia.quantidadeDepontos;i++){

      //       stream.writeStartElement("analise");
      //       stream.writeAttribute("ponto", QString::number(i));
      //       stream.writeAttribute("id", QString::number(etografia.id[i]));
      //       stream.writeAttribute("frameInicial", QString::number( etografia.frameComeco[i]));

      //       stream.writeAttribute("frameFinal", QString::number(etografia.framFim[i]));

      //        stream.writeEndElement(); //fecha analise

      //        }



           stream.writeEndElement();//fecha analises

           }

          stream.writeEndElement();//fecha area
          stream.writeEndElement();// fecha dadosAnalise





          stream.writeEndElement();//fecha analiseEtografica
          stream.writeEndDocument();


          OutEtografia.close();
          parser = new parserXMLtoCSV();
          parser->converteArquivo(nomeGravarProcesImagem);





        }else{ //se captura de video não esta setado

          OutEtografia.setFileName(nomeGravarProcesImagem);

          OutEtografia.open(QIODevice::WriteOnly);

          QXmlStreamWriter stream(&OutEtografia); //passa o endereço
          stream.setAutoFormatting(true);

          stream.writeStartDocument();//começa o documento
          stream.writeStartElement("analiseProcessaImage");
          stream.writeStartElement("dadosExperimentador");
                   stream.writeTextElement("experimentador",experimentador.nome);
                   stream.writeTextElement("laboratorio",experimentador.lab);
          stream.writeEndElement();//fecha analiseEtografica

          stream.writeStartElement("dadosVideoAnalisado");
                   stream.writeTextElement("nomeVxml",nomeArquivo);
                   stream.writeTextElement("frameInicial",QString::number(0));
                   stream.writeTextElement("frameBack",QString::number(0));
                   stream.writeTextElement("frameProces",QString::number(ui->lblNumero->text().toDouble()- reMorfo.area.size()));
                   stream.writeTextElement("frameFinal",ui->lblNumero->text());
                   stream.writeTextElement("escala",QString::number(videoLista.escala[contadorDeVideo]));
                    stream.writeTextElement("fps",QString::number(1/(somaTempo/ui->lblNumero->text().toDouble())));
                    stream.writeTextElement("tempoTotalProcessamento", ui->lblTime->text());
          stream.writeEndElement();//fecha informacoes

          stream.writeStartElement("dadosCatalago");
          stream.writeTextElement("nomeCaminhoExt", nomeGravarCatalago);



          stream.writeStartElement("Categorias");
          int contador=0;

          for(int i=0;i<cAnaEto.quantidadeDeDados;i++){

             stream.writeStartElement("categoria");
             stream.writeAttribute("id", QString::number(i));
             stream.writeAttribute("nome",cAnaEto.nomeCategoria[i]);
             stream.writeEndElement();

             }
          stream.writeEndElement();

          stream.writeStartElement("areasDeInteresse");

          for(int ja=0; ja< videoLista.area[contadorDeVideo].tipo.size(); ja++ ){

              stream.writeStartElement("infoArea");
              stream.writeAttribute("id", QString::number(ja));
              stream.writeTextElement("figName",videoLista.area[contadorDeVideo].nomeFig[ja]);
              if(videoLista.area[contadorDeVideo].tipo[ja]=="circle"){

              stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
              stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
              stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

              stream.writeTextElement("raio",QString::number(videoLista.area[contadorDeVideo].raio[conCir2]));

              conCir2++;

              }else{
                  stream.writeTextElement("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
                  stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
                  stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

                  stream.writeTextElement("width",QString::number(videoLista.area[contadorDeVideo].width[conRet2]));
                  stream.writeTextElement("heigth",QString::number(videoLista.area[contadorDeVideo].height[conRet2]));
              conRet2++;

              }
              //stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
              //        stream.writeAttribute("tipo",videoLista.area[contadorDeVideo].oriX[ja];
              stream.writeEndElement();

          }


           stream.writeEndElement(); //fecha caminho Ext


          stream.writeEndElement();//fecha Categorias
         // stream.writeEndElement();//fecha dadosCatalago

          stream.writeStartElement("dadosAnalise");

          if(ui->cbAuto->isChecked()){
           stream.writeTextElement("tipoAnalise","Autoesclusiva" );
          }

          if(ui->cbNested->isChecked()){
           stream.writeTextElement("tipoAnalise","sobreposta" );
          }


           stream.writeStartElement("anaProceImagem");


           for(int ka=0; ka< videoLista.area[contadorDeVideo].oriX.size(); ka++ ){



           stream.writeStartElement("area");


           stream.writeAttribute("id",QString::number(ka));

           //stream.writeAttribute("");


           int fraNumero= ui->lblNumero->text().toDouble()- reMorfo.area.size();
           qDebug()<<"2";

           //fraNumero= contNumeroGrava - reMorfo.area.size();


           for(int i=0; i<  reMorfo.area.size();i++){

               if(matObjDentro[ka][i]){

               stream.writeStartElement("proce");

               stream.writeAttribute("f",QString::number(fraNumero));
               stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
               stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
               stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
               stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
               stream.writeAttribute("altP",QString::number(reMorfo.altura[i]));
               stream.writeAttribute("altM",QString::number(reMorfo.altura[i]/videoLista.escala[contadorDeVideo]));
               stream.writeAttribute("larP",QString::number(reMorfo.largura[i]));
               stream.writeAttribute("larM",QString::number(reMorfo.largura[i]/videoLista.escala[contadorDeVideo]));
               stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i])); //angulo do objeto



      //         stream.writeAttribute("taP",QString::number(dados->reMorfo.tamanhoObj[i]));
      //         stream.writeAttribute("taM",QString::number(dados->reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


      //         double tamanhoObjeto=0;

      //         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
      //         tamanhoObjeto = qSqrt(tamanhoObjeto);

      //         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


      //         //novo





               stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
               stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
               stream.writeAttribute("Valt",QString::number(reCinema.varAltura[i]));
               stream.writeAttribute("Vlar",QString::number(reCinema.varLargura[i]));

               stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));


               std::vector<float> varAltura;
               std::vector<float> varLargura;

               if(reCinema.ruidoMaxVaria[i]){
                   stream.writeAttribute("rMinV","true");

               }else{
                   stream.writeAttribute("rMinV","false");
               }
               if(reMorfo.objetoEncontrado[i]){

                   stream.writeAttribute("OE","true");

               }else{

                   stream.writeAttribute("OE","false");
               }



               stream.writeEndElement(); //fecha proce

               }

               fraNumero++;


           }
//           int fraNumero=0;
//           for(int i=0; i< reMorfo.area.size();i++){

//               if(matObjDentro[ka][i]){

//               stream.writeStartElement("proce");
//               fraNumero=i+ videoLista.frameProces[contadorDeVideo];

//               stream.writeAttribute("f",QString::number(fraNumero));
//               stream.writeAttribute("arP",QString::number(reMorfo.area[i]));
//               stream.writeAttribute("arM",QString::number(reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
//               stream.writeAttribute("ceX",QString::number(reMorfo.centroidX[i]));
//               stream.writeAttribute("ceY",QString::number(reMorfo.centroidY[i]));
//               stream.writeAttribute("taP",QString::number(reMorfo.tamanhoObj[i]));
//               stream.writeAttribute("taM",QString::number(reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


//      //         double tamanhoObjeto=0;

//      //         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
//      //         tamanhoObjeto = qSqrt(tamanhoObjeto);

//      //         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


//      //         //novo



//               stream.writeAttribute("an",QString::number(reMorfo.anguloObj[i]));

//               stream.writeAttribute("Var",QString::number(reCinema.varArea[i]));
//               stream.writeAttribute("Van",QString::number(reCinema.varAngular[i]));
//               stream.writeAttribute("Vd",QString::number(reCinema.varDistancia[i]));
//               stream.writeAttribute("VtoP",QString::number(reCinema.varTamObjeto[i]));

//               if(reCinema.ruidoMaxVaria[i]){
//                   stream.writeAttribute("rMV","true");

//               }else{
//                   stream.writeAttribute("rMV","false");
//               }
//               if(reMorfo.objetoEncontrado[i]){

//                   stream.writeAttribute("OE","true");

//               }else{

//                   stream.writeAttribute("OE","false");
//               }



//               stream.writeEndElement(); //fecha proce

//               }
//           }


      //     etografia.framFim;
      //    for(int i=0;i<etografia.quantidadeDepontos;i++){

      //       stream.writeStartElement("analise");
      //       stream.writeAttribute("ponto", QString::number(i));
      //       stream.writeAttribute("id", QString::number(etografia.id[i]));
      //       stream.writeAttribute("frameInicial", QString::number( etografia.frameComeco[i]));

      //       stream.writeAttribute("frameFinal", QString::number(etografia.framFim[i]));

      //        stream.writeEndElement(); //fecha analise

      //        }



           stream.writeEndElement();//fecha analises

           }

          stream.writeEndElement();//fecha area
          stream.writeEndElement();// fecha dadosAnalise





          stream.writeEndElement();//fecha analiseEtografica
          stream.writeEndDocument();


          OutEtografia.close();




      }



     }
}

//void telaTempoReal::on_pushButton_2_clicked()
//{

//}

//void telaTempoReal::on_pbCodec_clicked()
//{

//    CV_FOURCC_MACRO(0,0,0,-1);

//  fourCodec= CV_FOURCC('0','0','0','-1');

//  qDebug() << "clicado ";
//}
