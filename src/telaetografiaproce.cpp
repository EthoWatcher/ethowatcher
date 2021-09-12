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
#include "telaetografiaproce.h"
#include "ui_telaetografiaproce.h"

telaEtografiaProce::telaEtografiaProce(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaEtografiaProce)
{
    ui->setupUi(this);

    ui->swPrincipal->setCurrentIndex(0);

    captadorDeVideo = new moduloCaptador();
    captador = new moduloCaptador();
    dados = new moduloProcessamento();

    chProceON=false;
    ui->pbStart->setEnabled(false);

    canetaQuadro.setWidth(3);
    canetaQuadro.setColor(QColor(255,0,0));


    canetaAmarela.setWidth(1);
    canetaAmarela.setColor(QColor(0,0,255));


    canetaPreta.setWidth(3);
    canetaPreta.setColor(QColor(0,0,0));


    canetaVermelha.setWidth(3);
    canetaVermelha.setColor(QColor(0,255,0));
    chEtografia= false;
    chProceON = false;
    escolheSelecao=false;  //true apenas um botão por vez
                          //false pode apertar todos os botões

    ui->gbStep2->setVisible(false);
    ui->gbStep3->setVisible(false);
    ui->gbStep4->setVisible(false);
    ui->gbStep5->setVisible(false);
    ui->gbStep6->setVisible(false);
    ui->tabButtons->setTabEnabled(2,false);

    new QShortcut( Qt::Key_Right, this, SLOT(on_btAvancar_clicked()));
    new QShortcut( Qt::Key_Left, this, SLOT(on_btVoltar_clicked()));
    ui->widBotoes->setVisible(false);

    captador = new moduloCaptador();
    dados = new moduloProcessamento();
    captadorDeVideo = new moduloCaptador();

     chPriemira= true;

     contProce=0;
     contadorCirculo=0;
     contadorRetangulo=0;

      ui->lieTime->setEnabled(ui->cb_temporal_segmentation->isChecked());
      ui->pb_generate_grafic->setEnabled(ui->cb_seq_analyses->isChecked());

}

void telaEtografiaProce::closeEvent(QCloseEvent *event)
{
    qDebug() << "fechou a tela ";
    delete this;
}

telaEtografiaProce::~telaEtografiaProce()
{
    qDebug() << "destrutor da etrografia baseada em vídeo ativada ";
    delete captador;
    delete dados;
    delete captadorDeVideo;
    delete ui;
}

//void telaEtografiaProce::set_usuario(QString nome, QString laboratorio)
//{
//    this->nome_usuario = nome;
//    this->nome_lab = laboratorio;

//}

/**
 *Função para setar o experimentador
 * @brief telaEtografiaProce::setExperimentador Função para setar o experimentador
 * @param nome1 Nome do experimentador
 * @param lab1 Laboratório do experimenatdor.
 */
void telaEtografiaProce::setExperimentador(QString nome1, QString lab1)
{
    experimentador.nome = nome1;
    experimentador.lab = lab1;
}

cv::Mat telaEtografiaProce::conQim2Mat(QImage imaEntrada)
{
    cv::Mat matSaida;
//    resultado.frameProces=frame_atual;
//    resultado.matProce= frameReduzido;
////        resultado.background=frame;
//    QImage resultadoBackground((uchar*)resultado.matProce.data, resultado.matProce.cols, resultado.matProce.rows, resultado.matProce.step, QImage::Format_RGB888);
//    resultProce= QPixmap::fromImage(resultadoBackground);
//    resultado.matProce.release();
    matSaida= cv::Mat(imaEntrada.height(),imaEntrada.width(),CV_8UC3, const_cast<uchar*>(imaEntrada.bits()), imaEntrada.bytesPerLine()).clone();

    return matSaida;
}

void telaEtografiaProce::startVideoTodo()
{

}

void telaEtografiaProce::recebeContadorMorfo(int contador)
{
    //qDebug() << contador;
    ui->progressBar->setValue(contador);
    //ui->progressBar->setValue(contador+ videoLista.frameProces[0]);

    if((contador)== (videoLista.frameFinal[0])){
    //if((contador+ videoLista.frameProces[0])>= (videoLista.frameFinal[0]-1)){

//        ui->pbStart->setEnabled(true);
        //se chegou no fim cahma outuro processamento;
        reiniciaProcessamento();


    }


    if(chPriemira){
        chPriemira = false;

        tinicial = clock();

    }else{

        tfinal = clock();

        tresposta=(float) (tfinal-tinicial)/CLOCKS_PER_SEC;
        //somatTresposta = somatTresposta + tresposta;

        ui->lblTime->setText(QString::number(tresposta));


    }

}

void telaEtografiaProce::recebeImagem(QImage qiCaptador, int numFrame)
{

    atualizaRegistro();
    QString red_color= "";

    if(numFrame>= videoLista.frameProces[0]){

        ui->widBotoes->setEnabled(true);
        ui->lblEtographiOn->setText("Etographia is Avaible");
        ui->lblEtographiOn->setStyleSheet("background-color: rgb(212, 212, 212);""color: black; " "font: bold;");
        ui->widBotoes->setVisible(true);





    }else{
        ui->widBotoes->setEnabled(false);
        ui->lblEtographiOn->setText("Etographia is not Avaible");
        ui->lblEtographiOn->setStyleSheet(red_color + "color: black; " "font: bold;");
        ui->widBotoes->setVisible(false);


    }
    if(ui->labelFrames->text().toInt() < videoLista.frameFinal[0]){

        int hei = ui->imgResultado->height();
        int wid = ui->imgResultado->width();

        ui->labelFrames->setText(QString::number(numFrame));
        ui->labelFramesTotal->setText(QString::number(videoLista.frameFinal[0]));
        ui->labelTempo->setText(QString::number( numFrame/videoLista.fps[0]));
        ui->labelTempoTotal->setText(QString::number(videoLista.frameFinal[0]/videoLista.fps[0]));

        ui->hsTimer->setValue(numFrame);


//se esta ligado o processamento de imagem
        if(chProceON){
            for(int i=0; i<cheboxList.size();i++){

                if(cheboxList[i]->isChecked()){
                    dados = listaProcessamento[i];
                }

            }



            atualizaProcess(numFrame-videoLista.frameProces[0]);

            widthPanProcess=ui->imgResultado->size().width();
            heightPanProcess=ui->imgResultado->size().height();

            if(numFrame>videoLista.frameProces[0]){
                //qiFundo = qiCaptador;

                 QPainter painter(&qiCaptador); //o pintor vai pintar nesse inderesso
                 //define qual sera a caneta que ira pintar


                 if(ui->chbCentroide->isChecked()){

                     painter.setPen(canetaVermelha);
                     painter.drawPoint((int) dados->desenhoSaida.cmX[numFrame-videoLista.frameProces[0]],(int)dados->desenhoSaida.cmY[numFrame-videoLista.frameProces[0]]);


                 }

                 QPoint vetPont[4];

//                 vetPont[0].setX(vtxX1);
//                 vetPont[0].setY(vtxY1);
//                 vetPont[1].setX(vtxX2);
//                 vetPont[1].setY(vtxY2);
//                 vetPont[2].setX(vtxX3);
//                 vetPont[2].setY(vtxY3);
//                 vetPont[3].setX(vtxX4);
//                 vetPont[3].setY(vtxY4);


                 vetPont[0].setX(dados->desenhoSaida.vtxX1[numFrame-videoLista.frameProces[0]]);
                 vetPont[0].setY(dados->desenhoSaida.vtxY1[numFrame-videoLista.frameProces[0]]);
                 vetPont[1].setX(dados->desenhoSaida.vtxX2[numFrame-videoLista.frameProces[0]]);
                 vetPont[1].setY(dados->desenhoSaida.vtxY2[numFrame-videoLista.frameProces[0]]);
                 vetPont[2].setX(dados->desenhoSaida.vtxX3[numFrame-videoLista.frameProces[0]]);
                 vetPont[2].setY(dados->desenhoSaida.vtxY3[numFrame-videoLista.frameProces[0]]);
                 vetPont[3].setX(dados->desenhoSaida.vtxX4[numFrame-videoLista.frameProces[0]]);
                 vetPont[3].setY(dados->desenhoSaida.vtxY4[numFrame-videoLista.frameProces[0]]);


        //                 ponto1=vetPont[0];

        //                 for(int ja=0; ja< 4; ja++){

        //                     if((ponto1.x()< vetPont[ja]) &&)


        //                 }

                 QPoint desenho1,desenho2,desenho3,desenho4;
                 //esquerda
                 desenho1.setX((vetPont[0].x()+vetPont[1].x())/2);
                 desenho1.setY((vetPont[0].y()+vetPont[1].y())/2);

                 //direita
                 desenho2.setX((vetPont[1].x()+vetPont[2].x())/2);
                 desenho2.setY((vetPont[1].y()+vetPont[2].y())/2);
                 desenho3.setX((vetPont[2].x()+vetPont[3].x())/2);
                 desenho3.setY((vetPont[2].y()+vetPont[3].y())/2);
                 desenho4.setX((vetPont[3].x()+vetPont[0].x())/2);
                 desenho4.setY((vetPont[3].y()+vetPont[0].y())/2);


                 if(ui->chbAltLarg->isChecked()){

                     painter.setPen(QColor(255,34,23));
                     painter.drawLine(desenho1,desenho3);
                     painter.setPen(QColor(255,244,23));
                     painter.drawLine(desenho2,desenho4);


                 }


                 if(ui->chbAngulo->isChecked()){

                     QPen canetaQuadro1;
                     canetaQuadro1.setWidth(2);
                     canetaQuadro1.setColor(QColor(50,50,255));
                     painter.setPen(canetaQuadro1);
                     painter.drawLine(desenho1,desenho3);

                 }

                 if(ui->chbArea->isChecked()){
                     QPen canetaQuadro;
                     canetaQuadro.setWidth(2);
                     canetaQuadro.setColor(QColor(255,100,255));
                     painter.setPen(canetaQuadro);

                     painter.drawLine(vetPont[0],vetPont[1]);
                     painter.drawLine(vetPont[1],vetPont[2]);
                     painter.drawLine(vetPont[2],vetPont[3]);
                     painter.drawLine(vetPont[3],vetPont[0]);
//                     painter.drawLine(vtxX1,vtxY1,vtxX2,vtxY2);
//                     painter.drawLine(vtxX2,vtxY2,vtxX3,vtxY3);
//                     painter.drawLine(vtxX3,vtxY3,vtxX4,vtxY4);
//                     painter.drawLine(vtxX4,vtxY4,vtxX1,vtxY1);

                 }




//                 if(ui->chbTamnho->isChecked()){
//                     painter.setPen(canetaPreta);
//                     painter.drawPoint(dados->desenhoSaida.agulhX[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.agulhY[numFrame-videoLista.frameProces[0]]);
//                     painter.setPen(canetaAmarela);
//                     painter.drawLine(QPointF(dados->desenhoSaida.pob1X[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.pob1Y[numFrame-videoLista.frameProces[0]]),
//                             QPointF(dados->desenhoSaida.pob2X[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.pob2Y[numFrame-videoLista.frameProces[0]]));

//                 }

//                 painter.drawPoint(poLongeX,poLongey);
//                 painter.drawPoint(pRetaA1X,pRetaA1Y);
//                 painter.drawPoint(pRetaA2X,pRetaA2Y);


//                 double ponto1, ponto2, ponto3, ponto4

//                 //desenha o centro de massa
//                 ponto1=

//                 if(ui->chbArea->isChecked()){

//                     painter.setPen(canetaQuadro);
//    //                 painter.drawLine(QPoint(dados->desenhoSaida.vtxX1[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY1[numFrame-videoLista.frameProces[0]]),
//    //                                   QPoint(dados->desenhoSaida.vtxX2[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY2[numFrame-videoLista.frameProces[0]] ));

//                   painter.drawPoint(dados->desenhoSaida.vtxX1[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY1[numFrame-videoLista.frameProces[0]]);
//                   painter.drawPoint(dados->desenhoSaida.vtxX2[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY2[numFrame-videoLista.frameProces[0]]);
//                   painter.drawPoint(dados->desenhoSaida.vtxX3[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY3[numFrame-videoLista.frameProces[0]]);
//                  // painter.drawPoint(dados->desenhoSaida.vtxX4[numFrame-videoLista.frameProces[0]],dados->desenhoSaida.vtxY4[numFrame-videoLista.frameProces[0]]);


//                 }

//                 QPoint ponto1,ponto2; //ponto 1 é o da cima e esquerda
//                                       //o ponto 2 é o ponto de cima e da direita
//                                       // o ponto 4 é o ponto de baixo e da direita
//                                       //o ponto 3 é o ponto de biaxo mas da esquerda
//                 //QPoint ponto3,ponto4;
//                 QPoint vetPont[4];

//                 vetPont[0].setX(dados->desenhoSaida.vtxX1[numFrame-videoLista.frameProces[0]]);
//                 vetPont[0].setY(dados->desenhoSaida.vtxY1[numFrame-videoLista.frameProces[0]]);
//                 vetPont[1].setX(dados->desenhoSaida.vtxX2[numFrame-videoLista.frameProces[0]]);
//                 vetPont[1].setY(dados->desenhoSaida.vtxY2[numFrame-videoLista.frameProces[0]]);
//                 vetPont[2].setX(dados->desenhoSaida.vtxX3[numFrame-videoLista.frameProces[0]]);
//                 vetPont[2].setY(dados->desenhoSaida.vtxY3[numFrame-videoLista.frameProces[0]]);
//                 vetPont[3].setX(dados->desenhoSaida.vtxX4[numFrame-videoLista.frameProces[0]]);
//                 vetPont[3].setY(dados->desenhoSaida.vtxY4[numFrame-videoLista.frameProces[0]]);


////                 ponto1=vetPont[0];

////                 for(int ja=0; ja< 4; ja++){

////                     if((ponto1.x()< vetPont[ja]) &&)


////                 }

//                 QPoint desenho1,desenho2,desenho3,desenho4;
//                 //esquerda
//                 desenho1.setX((vetPont[0].x()+vetPont[1].x())/2);
//                 desenho1.setY((vetPont[0].y()+vetPont[1].y())/2);

//                 //direita
//                 desenho2.setX((vetPont[1].x()+vetPont[2].x())/2);
//                 desenho2.setY((vetPont[1].y()+vetPont[2].y())/2);



//                 desenho3.setX((vetPont[2].x()+vetPont[3].x())/2);
//                 desenho3.setY((vetPont[2].y()+vetPont[3].y())/2);

//                 desenho4.setX((vetPont[3].x()+vetPont[0].x())/2);
//                 desenho4.setY((vetPont[3].y()+vetPont[0].y())/2);
////                 desenho1.setX(ponto4.x()+ (ponto4.x()-ponto1.x())/2);
////                 desenho1.setY(ponto1.y());
//                 //painter.drawLine(desenho1,desenho2);

//                 //painter.drawPoint(desenho1);
//                 painter.drawLine(desenho1,desenho3);
//                 painter.setPen(QColor(20,244,23));
//                 painter.drawLine(desenho2,desenho4);
//                // painter.drawLine(vetPont[1],vetPont[2]);




                //area




                 painter.setPen(canetaAmarela);

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


                // painter.drawPoint(vtxX3,vtxY3);
                // painter.drawPoint(vtxX4,vtxY4);

                 QImage qimDisplay= qiCaptador.scaled(widthPanProcess,heightPanProcess,Qt::KeepAspectRatio);
                 ui->imgResultado->setPixmap(QPixmap::fromImage(qimDisplay));


            }else{

                QImage small = qiCaptador.scaled(widthPanProcess, heightPanProcess,Qt::KeepAspectRatio);
            //    QImage small = qiCaptador.scaled(480, 360,Qt::KeepAspectRatio);
                ui->imgResultado->setPixmap(QPixmap::fromImage(small));

            }

        }else{

            QImage small = qiCaptador.scaled(wid, hei,Qt::KeepAspectRatio);
        //    QImage small = qiCaptador.scaled(480, 360,Qt::KeepAspectRatio);
            ui->imgResultado->setPixmap(QPixmap::fromImage(small));

        }









    }else{


        captadorDeVideo->finalizandoTimer();
    }

}

void telaEtografiaProce::on_pbEtoProce_clicked()
{
//    chaveEto=false;
    //    chaveProces=true;

    captador = new moduloCaptador();
    captadorThread = new QThread();
    captador->moveToThread(captadorThread); //a


    connect(this,SIGNAL(reiniciaProce()),captador,SLOT(setReinicio()));
    captador->setCaptador(videoLista.nomeOpencv[0]);
    //dados->frameBackground = conQim2Mat( captador->pegaPlanoFundoQImage(videoLista.frameBack[0]));
    //dados->setFrameFundo(captador->pegaPlanoFundoQImage(videoLista.frameBack[0]));

    captador->getParamVideo();
    //connect(captadorThread,SIGNAL(started()),captador,SLOT(setCaptaVideoTodo()));
    connect(this,SIGNAL(reiniciaProce()),captador,SLOT(setCaptaVideoTodo()));

    captador->setCaptadorRange(videoLista.frameProces[0],videoLista.frameFinal[0]);



   // for(int i=0; i<videoLista.area[0].nomeFig.size(); i++){

        thrProce = new QThread();



        setProcessamento();







    //ui->probCaptador->setRange(videoLista.frameProces[0],videoLista.frameFinal[0]-1);
    ui->progressBar->setRange(videoLista.frameProces[0],videoLista.frameFinal[0]);


//    captador->setCaptaVideoTodo(); //b
    //para thread
    captadorThread->start();//a

//    reiniciaProcessamento();
   emit reiniciaProce();


    //
    ui->gbStep2->setEnabled(false);



    chProceON=true;
    chEtografia=true;

    QVBoxLayout *vBoxLay = new QVBoxLayout(ui->widCheckBox);

    for(int ka=0; ka< videoLista.area[contadorDeVideo].nomeFig.size(); ka++){

        chebox = new QCheckBox();
        if(ka==0){
           chebox->setChecked(true);
        }else{
            chebox->setChecked(false);
        }
        chebox->setAutoExclusive(true);

        chebox->setText(videoLista.area[contadorDeVideo].nomeFig[ka]);
        cheboxList.push_back(chebox);
        vBoxLay->addWidget(cheboxList[ka]);

    }


    ui->widCheckBox->setLayout(vBoxLay);



//    captador->captadorVideoRelease();




//    captadorDeVideo = new moduloCaptador();
//    //captadorThread = new QThread();

//    //captadorDeVideo->moveToThread(captadorThread);
//    connect(captadorDeVideo,SIGNAL(enviaImagem(QImage,int)),this,SLOT(recebeImagem(QImage,int)));

//    captadorDeVideo->setCaptador(videoLista.nomeOpencv[0]);




//    dados->setCalibracao(20,0);
//    dados->setParametrosVideo(640,480);
//    dados->confiCameraVir(0,0,640,480,false);



    ui->gbStep3->setVisible(true);
    ui->gbStep4->setVisible(true);
    ui->gbStep6->setVisible(true);








}

void telaEtografiaProce::readCatalago()
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

void telaEtografiaProce::lerVXML(QString nomeArquivoLer)
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
        videoLista.fps.push_back(conversor.toDouble());

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

void telaEtografiaProce::lerVCXML(QString nomeArquivoLer)
{

    OutVideo.setFileName(nomeArquivoLer);
    OutVideo.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutVideo); //passa o endereço

    QString conversor;

    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();



        if(streamReader.name()== "videoCegoEditado"){

            if(chVideoEditado==true){
                chVideoEditado=false;

            }else{
                chVideoEditado=true;

               // videoLista.areaJanInte.push_back(auxArea1);

            }
        }


        if(chVideoEditado){

            if(streamReader.name()== "nomeOpencv"){
            videoLista.nomeOpencv.push_back(rsaCon.decriptoRSAQstring(  streamReader.readElementText()));
               //qDebug() << leitorXML.readElementText();

            }


               if(streamReader.name()== "frameInicial"){

             conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
            videoLista.frameInicial.push_back(conversor.toInt());
                  // qDebug() << leitorXML.readElementText();
               }

               if(streamReader.name()== "frameFinal"){
                   conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
            videoLista.frameFinal.push_back(conversor.toInt());
                  // qDebug() << leitorXML.readElementText();
               }



               if(streamReader.name() == "frameProces"){
                   conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
            videoLista.frameProces.push_back(conversor.toInt());


               }
                if(streamReader.name() == "frameBack"){

                    conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
             videoLista.frameBack.push_back(conversor.toInt());

                }



                if(streamReader.name() == "treshold"){

                           conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());

                           videoLista.threshold.push_back(conversor.toInt());

                  }

               if(streamReader.name() == "erosao"){

                   conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
            videoLista.erosao.push_back(conversor.toInt());

               }


               if(streamReader.name() == "escala"){

                   conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
            videoLista.escala.push_back(conversor.toDouble());

               }

               if(streamReader.name() == "fps"){

                   conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
            videoLista.fps.push_back(conversor.toDouble());

               }

               if(streamReader.name()== "proImageOn"){ //se foi cadastrado para o processamento de imagem

                   conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
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

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());

                       if(conversor=="false"){
                         videoLista.chaInteMoveAtivado.push_back(false);
                       }else{
                         videoLista.chaInteMoveAtivado.push_back(true);
                       }


                   }


                   if(streamReader.name() == "movel"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());

                       if(conversor=="false"){
                         videoLista.chaInteMove.push_back(false);
                       }else{
                         videoLista.chaInteMove.push_back(true);
                       }


                   }

                   if(streamReader.name() == "origX"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());

                         videoLista.areaJanInte[contadorDeVideo].oriX.push_back(conversor.toDouble());

                   }
                   if(streamReader.name() == "origY"){

                    conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                    videoLista.areaJanInte[contadorDeVideo].oriY.push_back(conversor.toDouble());

                   }

                   if(streamReader.name() == "width"){

                    conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                    videoLista.areaJanInte[contadorDeVideo].width.push_back(conversor.toDouble());

                   }
                   if(streamReader.name() == "heigth"){

                    conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
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

                    conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
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

                   QString conversora= rsaCon.decriptoRSAQstring(streamReader.attributes().value("tipo").toString());
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

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                       videoLista.area[contadorDeVideo].nomeFig.push_back(conversor);
                       //auxArea.oriX =  conversor.toDouble();

                   }


                   if(streamReader.name() == "oriX"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                       videoLista.area[contadorDeVideo].oriX.push_back(conversor.toDouble());
                       //auxArea.oriX =  conversor.toDouble();

                   }

                   if(streamReader.name() == "oriY"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                       videoLista.area[contadorDeVideo].oriY.push_back(conversor.toDouble());
                       //auxArea.oriY =  conversor.toDouble();

                   }

                   if(streamReader.name() == "height"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                       videoLista.area[contadorDeVideo].height.push_back(conversor.toDouble());
                       //auxArea.height =  conversor.toDouble();

                   }

                   if(streamReader.name() == "width"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                       videoLista.area[contadorDeVideo].width.push_back(conversor.toDouble());
                      // auxArea.width =  conversor.toDouble();

                   }

                   if(streamReader.name() == "rad"){

                       conversor = rsaCon.decriptoRSAQstring(streamReader.readElementText());
                       videoLista.area[contadorDeVideo].raio.push_back(conversor.toDouble());
                       //auxArea.raio =  conversor.toDouble();

                   }//fim if rad




               }//fim chave das areas


        } //fim video editado









        }//fim while



    //videoLista.quantidadeDeDados++; //= contadorTamanho; //conta quantidade de dados;


   OutVideo.close();



}

void telaEtografiaProce::enconPontoArea()
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

        for(int i=0; i< dados->reMorfo.area.size();i++){
            if(chaTip){ //se é quadrado

                if((dados->reMorfo.centroidX[i]>=videoLista.area[contadorDeVideo].oriX[ka])
                        &&(dados->reMorfo.centroidX[i]<=(videoLista.area[contadorDeVideo].oriX[ka]+videoLista.area[contadorDeVideo].width[contRet-1]))&&
                        (dados->reMorfo.centroidY[i]>=videoLista.area[contadorDeVideo].oriY[ka])
                        &&(dados->reMorfo.centroidY[i]<=(videoLista.area[contadorDeVideo].oriY[ka]+videoLista.area[contadorDeVideo].height[contRet-1])))
                {

                    objDentro.push_back(true);


                }else{

                    objDentro.push_back(false);

                }


            }else{ //se é circulo

                raioTest=0;
                raioTest = qPow(dados->reMorfo.centroidX[i]-
                                (videoLista.area[contadorDeVideo].oriX[ka]+ videoLista.area[contadorDeVideo].raio[contCir-1]),2)+
                            qPow(dados->reMorfo.centroidY[i]-
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

void telaEtografiaProce::creatShortCurt(QString atalho, QPushButton *pushBut)
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


//    std::string atalhoSrting = atalho.toStdString();
//    tecla atalhu;
//    atalhu = atalho;


//    switch(atalhoSrting){
//        case a :
//        new QShortcut( Qt::Key_A, buttonList[0], SLOT(click()));
//        break;



//    }


}

void telaEtografiaProce::atualizaRegistro()
{
    if(chNovoValor){
        chNovoValor=false;
    //ui->tabRegistro->setColumnCount(3);
        bool chvEscreRow=true;
        while(chvEscreRow){
            //0 > 0
            //2 > 2

            if(saida.quantidadeDepontos > ui->tabRegistro->rowCount()){

                ui->tabRegistro->insertRow(ui->tabRegistro->rowCount());
                ui->tabRegistro->setItem (ui->tabRegistro->rowCount()-1,0,new QTableWidgetItem(
                                             cAnaEto.nomeCategoria[saida.id[ui->tabRegistro->rowCount()-1]] ) );
                ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,1,new QTableWidgetItem(QString::number(saida.frameComeco[ui->tabRegistro->rowCount()-1]/videoLista.fps[0])));
                ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,2,new QTableWidgetItem(QString::number(saida.framFim[ui->tabRegistro->rowCount()-1]/videoLista.fps[0])));

                saida.chPontoValido.push_back(true);


                //configurando TableWidget
                ui->tabRegistro->resizeColumnsToContents();
                ui->tabRegistro->clearSelection();
                ui->tabRegistro->clearFocus();


            }else{

                chvEscreRow= false;


            }





        }








    }

    for(int ka=0; ka< ui->tabRegistro->rowCount();ka++ ){

//                ui->tabRegistro->setRowCount(ka);
//                ui->tabRegistro->setColumnCount(1);
//                ui->tabRegistro->setItem();

        ui->tabRegistro->setItem(ka,1,new QTableWidgetItem(QString::number(saida.frameComeco[ka]/videoLista.fps[0])));
        ui->tabRegistro->setItem(ka,2,new QTableWidgetItem(QString::number(saida.framFim[ka]/videoLista.fps[0])));



    }


}

void telaEtografiaProce::reiniciaProcessamento()
{
    if(contPrcessamento< (videoLista.area[0].nomeFig.size()-1)){


        disconnect(captador,SIGNAL(enviaImagem(QImage,int)),listaProcessamento[contPrcessamento],SLOT(processamentoDeVideoTodo(QImage,int)));
        disconnect(listaProcessamento[contPrcessamento],SIGNAL(fimProce()),captador,SLOT(setCaptaVideoTodo()));
        connect(listaProcessamento[contPrcessamento],SIGNAL(enviaMorfInt(int)), this,SLOT(recebeContadorMorfo(int)));
       qDebug() << contPrcessamento<< " foi proximo";
        contPrcessamento++;

        setProcessamento();

//        connect(captador,SIGNAL(enviaImagem(QImage,int)),listaProcessamento[contPrcessamento],SLOT(processamentoDeVideoTodo(QImage,int)));
//        captador->setCaptaVideoTodo(); //b
        emit reiniciaProce();


    }else{
        ui->pbStart->setEnabled(true);
    }

}

//void telaEtografiaProce::totalizacoesEtografia()
//{
//    for(int ka=0; ka<cAnaEto->id.size(); ka++){
//        //cada categoria
//        frequencia=0;

//        for(int ja=0; ja<etografia->id.size(); ja++){

//            if(etografiaLida->id[ja]==ka){

//               frequencia=frequencia+1;
//            }
//        }
//        vetorFrequencia.push_back(frequencia);
//    }

//    //encontra latencia
//    int primeiraOcorrencia=0;
//    bool chLate;


//    for(int ka=0; ka<catalagoLido->id.size(); ka++){
//        //cada categoria
//        //latencia
//        latencia=videoLido->frameFinal;
//        chLate=true;

//        //encontra a primeria vez que aconteceu
//        for(int ja=0; ja<etografiaLida->id.size(); ja++){

//            if( (etografia->id[ja]==ka) &&(chLate)){

//               primeiraOcorrencia= ja;
//               chLate=false;

//            }

//        }

//        latencia= etografia->frameInicial[primeiraOcorrencia] - videoLido->frameProce;
//        vetorLatencia.push_back(latencia/videoLido->fps);
//    }


//    //encontra duracao;

//    for(int ka=0; ka<catalagoLido->id.size(); ka++){
//        //cada categoria
//        duracao=0;

//        for(int ja=0; ja<etografiaLida->id.size(); ja++){

//            if(etografiaLida->id[ja]==ka){

//               duracao= etografiaLida->frameFinal[ja]- etografiaLida->frameInicial[ja] + duracao;

//            }
//        }
//        vetorDuracao.push_back(duracao/videoLido->fps);
//    }



//    chLate=false;



//}

//void telaEtografiaProce::escreverEtografiaCsv()
//{
//    nomeGravarEtografiaCSV =  nomeGravarEtografia;
//    QByteArray nomeGravarFPSByte = nomeGravarEtografiaCSV .toLatin1();

//    nomeGravarFPSByte.truncate(nomeGravarFPSByte.indexOf("."));   //  nomeGravarFPSByte.indexOf(".");
//    nomeGravarFPSByte.append("Eto.fps");

//    nomeGravarEtografiaCSV  =  QString::fromLatin1(nomeGravarFPSByte);

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

//    outGravador.close();

//}

//void telaEtografiaProce::gravarCSV()
//{

//    nomeGravarFPS = nomeArquivo;
//    QByteArray nomeGravarFPSByte = nomeGravarFPS.toLatin1();

//    nomeGravarFPSByte.truncate(nomeGravarFPSByte.indexOf("."));   //  nomeGravarFPSByte.indexOf(".");
//    nomeGravarFPSByte.append("Cam.fps");

//    nomeGravarFPS =  QString::fromLatin1(nomeGravarFPSByte);





//}

void telaEtografiaProce::on_pbUnicoVideo_clicked()
{
    fonteVideoXML = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users//Bio//Desktop//videos//",
                "Video Files (*.vxml , *.vcxml)"
                );


    if(!fonteVideoXML.isEmpty()){




        ui->lblVideoName->setText(fonteVideoXML);

        videoLista.nomeVXML.push_back(fonteVideoXML);
        //se final vxml
        QByteArray fonteVideoBit,fonteVideoBitExtInv,fonteVideoBitExt;

        fonteVideoBit = fonteVideoXML.toLatin1();

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



        if(fonteVideoBitExt==".vxml"){

            //se final for vxml
           lerVXML(fonteVideoXML);

        }else{

            lerVCXML(fonteVideoXML);

        }






        videoLista.quantidadeDeDados++; //= contadorTamanho; //conta quantidade de dados;
        ui->pbUnicoVideo->setEnabled(false);

        ui->gbStep2->setVisible(true);






        if(videoLista.chProImaOn[0]){

            ui->pbEtoProce->setEnabled(true);
            ui->pbTraking->setEnabled(true);
        }else{

            ui->pbEtoProce->setEnabled(false);
            ui->pbTraking->setEnabled(false);

        }


        ui->pbUnicoVideo->setEnabled(false);
    }


//    captadorDeVideo->moveToThread(captadorThread);
//    //connect(captadorThread,SIGNAL(started()),captadorDeVideo,SLOT(configurando()));
//    connect(captadorThread,SIGNAL(started()),captadorDeVideo,SLOT(captandoRealTime()));
//   // connect(captadorDeVideo,SIGNAL(fimConfiguracao()),captadorDeVideo,SLOT(captandoRealTime()));
//    connect(captadorDeVideo,SIGNAL(enviaInformacoes(int,QImage,float)),this,SLOT(atualizaImagem(int,QImage,float)));
//    connect(this,SIGNAL(desliga()),captadorDeVideo,SLOT(desligando()));
//    //connect(captadorDeVideo,SIGNAL(entrouNoTermino()),this,SLOT(on_pbTerminarVideo_clicked()));

//    connect(captadorDeVideo, SIGNAL(fimPrograma()), captadorThread, SLOT(quit()));
//    connect(captadorDeVideo, SIGNAL(fimPrograma()), captadorDeVideo, SLOT(deleteLater()));
//    connect(captadorThread, SIGNAL(finished()), captadorThread, SLOT(deleteLater()));



//    dados = new moduloProcessamento();
//    thrProce = new QThread();

//    dados->moveToThread(thrProce);





}

void telaEtografiaProce::on_pbStart_clicked()
{
    ui->swPrincipal->setCurrentIndex(1);

    if(chProceON){// para quando o processamento for on

        captador->captadorVideoRelease();

            captadorDeVideo = new moduloCaptador();
            //captadorThread = new QThread();

            //captadorDeVideo->moveToThread(captadorThread);
            connect(captadorDeVideo,SIGNAL(enviaImagem(QImage,int)),this,SLOT(recebeImagem(QImage,int)));

            captadorDeVideo->setCaptador(videoLista.nomeOpencv[0]);

            ui->btPlay->setEnabled(true);

            captadorDeVideo->setFrame(videoLista.frameProces[0]);
            ui->hsTimer->setRange(videoLista.frameProces[0],videoLista.frameFinal[0]);
            ui->hsTimer->setEnabled(true);

            ui->pbGravarAnalasiProces->setEnabled(true);
            ui->pbSaveImage->setEnabled(true);
            ui->tabButtons->setTabEnabled(2,true);

    }

    // QString valor = "4";
    // numeroDeBotoes= 6;

    if(chEtografia){
        QVBoxLayout *vlay = new QVBoxLayout(ui->widBotoes);

     //  QPushButton *buttonList[numeroDeBotoes];


        QSignalMapper *mapperCategorias = new QSignalMapper(this);
        // construindo os botões da análise.
        for(int j=0; j<numeroDeBotoes;j++){

            //criar um novo botão
            pb = new QPushButton();
          buttonList.append(pb);

            //buttonList[j]->setText(nomeCate[j]); //seta o nome
            buttonList[j]->setText(cAnaEto.nomeCategoria[j]+ "("+cAnaEto.atalho[j]+")"+"(ready)");
            buttonList[j]->setFixedHeight(40);
            //buttonList[j]->setFont();
            //buttonList[j]->setFont(QFont("MS Shell Dlg 2",12,-1,false, true));
            buttonList[j]->setStyleSheet("background-color: rgb(123, 245, 39);"  "color: black;"  "font-size: 18px");// "font: bold");
//                                         "font-style: bold;");

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



        ui->pbGravarAnalasiteEtografica->setEnabled(true);

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





    }

}

void telaEtografiaProce::on_btPlay_clicked()
{
    captadorDeVideo->iniciandoTimer(qPow(2,ui->SliderVelocidade->value()));
    ui->btPlay->setEnabled(false);
    ui->btStop->setEnabled(true);
    ui->hsTimer->setEnabled(false);
}

void telaEtografiaProce::on_pbEtoVideo_clicked()
{
    captadorDeVideo = new moduloCaptador();
    //captadorThread = new QThread();

    //captadorDeVideo->moveToThread(captadorThread);
    connect(captadorDeVideo,SIGNAL(enviaImagem(QImage,int)),this,SLOT(recebeImagem(QImage,int)));

    captadorDeVideo->setCaptador(videoLista.nomeOpencv[0]);

    ui->btPlay->setEnabled(true);

    captadorDeVideo->setFrame(videoLista.frameProces[0]);
    ui->hsTimer->setRange(videoLista.frameProces[0],videoLista.frameFinal[0]);
    ui->hsTimer->setEnabled(true);

    chEtografia = true;
    ui->pbStart->setEnabled(true);


    ui->gbStep3->setVisible(true);
    ui->gbStep4->setVisible(true);
    ui->gbStep2->setEnabled(false);

    ui->tabButtons->setTabEnabled(1,false);
    //captadorThread->start();

}

void telaEtografiaProce::on_btStop_clicked()
{
    captadorDeVideo->finalizandoTimer();
    ui->btPlay->setEnabled(true);
    ui->btStop->setEnabled(false);
    ui->hsTimer->setEnabled(true);
}

void telaEtografiaProce::on_SliderVelocidade_sliderReleased()
{
   // fatorVeloc=

    if(!ui->btPlay->isEnabled()){

        captadorDeVideo->finalizandoTimer();

        //Reinicia o contador de controle de reprodução e processamento do video com a nova velocidade.
        //Calcula o tempo de disparo igual ao tempo de reprodução de 1 frame (1000ms/fps) multiplicado
        //pelo novo fator de velocidade(aceleração/desaceleração) do video
        captadorDeVideo->iniciandoTimer(qPow(2,ui->SliderVelocidade->value()));

    }
    //Pausa o contador de controle de reprodução e processamento do video

}

void telaEtografiaProce::on_btAvancar_clicked()
{
    if((ui->labelFrames->text().toInt()-ui->edtFatordesloc->value())<videoLista.frameFinal[0]){

        ui->hsTimer->setEnabled(false);
        captadorDeVideo->setFrame(ui->labelFrames->text().toInt()+ui->edtFatordesloc->value());
        ui->labelFrames->setText(QString::number(ui->labelFrames->text().toInt()+ui->edtFatordesloc->value()));
        ui->hsTimer->setValue(ui->labelFrames->text().toInt());
        captadorDeVideo->captando();
        ui->hsTimer->setEnabled(true);
    }

}

void telaEtografiaProce::on_btVoltar_clicked()
{
    if((ui->labelFrames->text().toInt()-ui->edtFatordesloc->value())>videoLista.frameProces[0]){
    ui->hsTimer->setEnabled(false);
     captadorDeVideo->setFrame(ui->labelFrames->text().toInt()-ui->edtFatordesloc->value());
     ui->labelFrames->setText(QString::number(ui->labelFrames->text().toInt()-ui->edtFatordesloc->value()));
     ui->hsTimer->setValue(ui->labelFrames->text().toInt());
     captadorDeVideo->captando();
     ui->hsTimer->setEnabled(true);
    }

}

void telaEtografiaProce::on_hsTimer_valueChanged(int value)
{
    if(ui->hsTimer->isEnabled()){
        captadorDeVideo->setFrame(ui->hsTimer->value());
//        frame_atual=ui->hsTimer->value();
        ui->labelFrames->setText(QString::number(value));
        captadorDeVideo->captando();
    }
}

void telaEtografiaProce::on_pbLerCatalago_clicked()
{
    nomeGravarCatalago= QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                   "Video Files (*.caxml)"
                    );



    if(!nomeGravarCatalago.isEmpty())
    {

        ui->lblCatalogo->setText(nomeGravarCatalago);
        readCatalago();
        ui->pbLerCatalago->setEnabled(false);
        ui->gbStep5->setVisible(true);
    }
}

void telaEtografiaProce::slotMapeado(int a)
{
    chNovoValor=true;
    frame_atual = ui->labelFrames->text().toDouble();
    double finalframe1 = videoLista.frameFinal[0];
    QString green = "background-color: rgb(123, 245, 39);";
    QString red = "background-color: rgb(254,153, 0);";


    //escolheSelecao=false; //true é auto
    //false nested
    if(!escolheSelecao){ //se pode clicar mais de um botão por vez
        for(int i=0; i<numeroDeBotoes; i++){
            if(i==a){

                if(!clicado[i]){
                    //se o botão nao estiver clicado
                    clicado[i]=true;
                    buttonList[i]->setStyleSheet(green + "color: blue;" +  "font-size: 18px");
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
                    buttonList[i]->setStyleSheet(green + "color: black; " + "font-size: 18px");
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
                buttonList[i]->setStyleSheet(green + "color: black;"  "font-size: 18px"); //green
                buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                buttonList[i]->setEnabled(true);

            }


            for(int i=0; i<numeroDeBotoes; i++){
                if(i==a){

                    //diferencia se o botão esta clicado esta release
                    if(!clicado[i]){
                        clicado[i]=true;
                        buttonList[i]->setStyleSheet(red + "color: black;" +  "font-size: 18px"); //red
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
                        buttonList[i]->setStyleSheet(green + "color: black;" +  "font-size: 18px");
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

                    buttonList[i]->setStyleSheet(red + "color: black;" + "font-size: 18px");
                    buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                    buttonList[i]->setEnabled(false);



                }else{

                    buttonList[i]->setStyleSheet(green + "color: black;" +  "font-size: 18px");
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
        ui->widControes->setEnabled(true);
        ui->widControle1->setEnabled(true);



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

    ui->tabButtons->setTabEnabled(2,chEditaOn);




}

void telaEtografiaProce::on_cbAuto_clicked(bool checked)
{
    if(ui->cbAuto->isEnabled()){
        ui->cbNested->setChecked(false);

    }else{

        ui->cbNested->setChecked(true);

    }
}

void telaEtografiaProce::on_cbNested_clicked(bool checked)
{
    if(ui->cbNested->isEnabled()){
        ui->cbAuto->setChecked(false);

    }else{

        ui->cbAuto->setChecked(true);

    }
}



// gravar etografia
void telaEtografiaProce::on_pbGravarAnalasiteEtografica_clicked()
{

    nomeGravarEtografia = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
                "ethography files (*.etoxml)"
               );



    if(!nomeGravarEtografia.isEmpty()){
        // ui->pbGravarAnalasiteEtografica->setEnabled(false);
         QString texto_seg ="";
        if(ui->cb_temporal_segmentation->isChecked()){
            telaSegementacao *segment;
            segment = new telaSegementacao();
            texto_seg = segment->gera_segmentacao_texto(
                        ui->lieTime->text().toDouble(),
                        videoLista.frameProces[contadorDeVideo],
                        videoLista.frameFinal[contadorDeVideo],
                        videoLista.fps[contadorDeVideo],

                        saida.frameComeco,
                        saida.framFim,
                        saida.id,

                        cAnaEto.nomeCategoria,
                        cAnaEto.quantidadeDeDados);



            qDebug() <<texto_seg;
        }
        QString text_sencia = "";
        if(ui->cb_seq_analyses->isChecked()){
            text_sencia = transi->calcular_analise_sequencial(cAnaEto.quantidadeDeDados,
                                                cAnaEto.nomeCategoria,
                                                saida.id.size(),
                                                saida.id);

            qDebug() << text_sencia;

        }

        QString text_eto = this->gera_csv_eto(nomeGravarEtografia,

                          videoLista.frameProces[contadorDeVideo],
                          videoLista.frameFinal[contadorDeVideo],
                          videoLista.fps[contadorDeVideo],

                          videoLista.nomeVXML[contadorDeVideo],

                          nomeGravarCatalago,
                          cAnaEto.nomeCategoria,
                          cAnaEto.id,

                          saida.frameComeco,
                          saida.framFim,
                          saida.id);


        auto gera_cabecalho =[&](QString nome_caminho_video,
                                int frameProces,
                                int frameFinal,
                                double fps){

            QString t_saida ="";



            t_saida = t_saida + "sep=; \n";
            t_saida = t_saida + "EthoWatcher Open Source \n";
            t_saida = t_saida + "Observer;" + experimentador.nome.toLatin1() + "\n";
            t_saida = t_saida + "Lab;" + experimentador.lab.toLatin1() + "\n";


            t_saida = t_saida + "Registred video file are locate in " + nome_caminho_video + "\n";

            t_saida = t_saida + "Analysis initiated at " + QString::number( frameProces / fps) + " (seconds) of the video file \n ";
            t_saida = t_saida + "Analysis terminated at " + QString::number( frameFinal / fps) + " (seconds) of the video file \n";
            t_saida = t_saida + "\n";

            t_saida = t_saida + "The selected catalog are : " + ";" + nomeGravarCatalago + "\n";
            t_saida = t_saida + "\n";
            t_saida = t_saida + "\n";
            t_saida = t_saida + "\n";

            return t_saida;
        };

        QString cabecalho = gera_cabecalho(nomeGravarEtografia,
                                           videoLista.frameProces[contadorDeVideo],
                                           videoLista.frameFinal[contadorDeVideo],
                                           videoLista.fps[contadorDeVideo]);


        auto alinha_tabela = [](QString texto_eto, QString texto_seg){
            QString saida_texto ="";
            QStringList ls_eto = texto_eto.split("\n");
            QStringList ls_seg = texto_seg.split("\n");

            bool r_continua = true;
            int i_ls_eto = 0;
            int i_ls_seg = 0;
            while(r_continua){
                bool r_d_eto = i_ls_eto < ls_eto.size();
                bool r_d_seg = i_ls_seg < ls_seg.size();
                if(r_d_eto){
                    saida_texto  = saida_texto + ls_eto[i_ls_eto];


                }

                if(r_d_seg){
                    saida_texto = saida_texto + ";;;;";
                    saida_texto  = saida_texto + ls_seg[i_ls_seg];
                }


                saida_texto = saida_texto + "\n";
                i_ls_eto++;
                i_ls_seg++;
                r_continua = r_d_eto || r_d_seg;
            }

            return saida_texto;
        };


        QString texto = cabecalho + alinha_tabela(text_eto , text_sencia) + texto_seg;



        this->_gravar_csv(nomeGravarEtografia, texto);


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
        stream.writeTextElement("nomeVxml",videoLista.nomeVXML[contadorDeVideo]);
        stream.writeTextElement("frameInicial",QString::number(videoLista.frameInicial[contadorDeVideo]));
        stream.writeTextElement("frameProces",QString::number(videoLista.frameProces[contadorDeVideo]));
        stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]));
        stream.writeTextElement("fps",QString::number(videoLista.fps[contadorDeVideo]));
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
                    stream.writeAttribute("frameInicial", QString::number( saida.frameComeco[i]));
                    stream.writeAttribute("frameFinal", QString::number(saida.framFim[i]));

                    stream.writeEndElement(); //fecha analise

                    contEx++;

                }

            }else{
                stream.writeStartElement("analise");
                stream.writeAttribute("ponto", QString::number(contEx));
                stream.writeAttribute("id", QString::number(saida.id[i]));
                stream.writeAttribute("frameInicial", QString::number( saida.frameComeco[i]));
                stream.writeAttribute("frameFinal", QString::number(saida.framFim[i]));

                stream.writeEndElement(); //fecha analise

                contEx++;


            }




        }

        stream.writeEndElement();//fecha analises

        stream.writeEndElement();// fecha dadosAnalise





        stream.writeEndElement();//fecha analiseEtografica
        stream.writeEndDocument();


        OutEtografia.close();


//        parser = new parserXMLtoCSV();
//        parser->converteArquivo(nomeGravarEtografia);



        //    totalizacoesEtografia();

        //    escreverEtografiaCsv();


    }

}

void telaEtografiaProce::on_pbGravarAnalasiProces_clicked()
{
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


         dados= listaProcessamento[ka];

     stream.writeStartElement("area");


     stream.writeAttribute("id",QString::number(ka));

     //stream.writeAttribute("");
     int fraNumero=0;
     for(int i=0; i< dados->reMorfo.area.size();i++){

 //        if(matObjDentro[ka][i]){

         stream.writeStartElement("proce");
         fraNumero=i+ videoLista.frameProces[contadorDeVideo];

         stream.writeAttribute("f",QString::number(fraNumero));
         stream.writeAttribute("arP",QString::number(dados->reMorfo.area[i]));
         stream.writeAttribute("arM",QString::number(dados->reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
         stream.writeAttribute("ceX",QString::number(dados->reMorfo.centroidX[i]));
         stream.writeAttribute("ceY",QString::number(dados->reMorfo.centroidY[i]));
         stream.writeAttribute("altP",QString::number(dados->reMorfo.altura[i]));
         stream.writeAttribute("altM",QString::number(dados->reMorfo.altura[i]/videoLista.escala[contadorDeVideo]));
         stream.writeAttribute("larP",QString::number(dados->reMorfo.largura[i]));
         stream.writeAttribute("larM",QString::number(dados->reMorfo.largura[i]/videoLista.escala[contadorDeVideo]));
         stream.writeAttribute("an",QString::number(dados->reMorfo.anguloObj[i])); //angulo do objeto



//         stream.writeAttribute("taP",QString::number(dados->reMorfo.tamanhoObj[i]));
//         stream.writeAttribute("taM",QString::number(dados->reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


//         double tamanhoObjeto=0;

//         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
//         tamanhoObjeto = qSqrt(tamanhoObjeto);

//         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


//         //novo





         stream.writeAttribute("Var",QString::number(dados->reCinema.varArea[i]));
         stream.writeAttribute("Vd",QString::number(dados->reCinema.varDistancia[i]));
         stream.writeAttribute("Valt",QString::number(dados->reCinema.varAltura[i]));
         stream.writeAttribute("Vlar",QString::number(dados->reCinema.varLargura[i]));

         stream.writeAttribute("Van",QString::number(dados->reCinema.varAngular[i]));


         std::vector<float> varAltura;
         std::vector<float> varLargura;

         if(dados->reCinema.ruidoMaxVaria[i]){
             stream.writeAttribute("rMinV","true");

         }else{
             stream.writeAttribute("rMinV","false");
         }
         if(dados->reMorfo.objetoEncontrado[i]){

             stream.writeAttribute("OE","true");

         }else{

             stream.writeAttribute("OE","false");
         }



         stream.writeEndElement(); //fecha proce

       //  }
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

    QMessageBox::information(this,tr("Message"),tr("Saved successfully"));


     }

    }
//fica o alerta

void telaEtografiaProce::on_tabButtons_tabBarClicked(int index)
{


//    if(index == 1){
//    //ui->tabRegistro->setColumnCount(3);
//        bool chvEscreRow=true;
//        while(chvEscreRow){
//            //0 > 0
//            //2 > 2

//            if(saida.quantidadeDepontos > ui->tabRegistro->rowCount()){

//                ui->tabRegistro->insertRow(ui->tabRegistro->rowCount());
//                ui->tabRegistro->setItem (ui->tabRegistro->rowCount()-1,0,new QTableWidgetItem(
//                                             cAnaEto.nomeCategoria[saida.id[ui->tabRegistro->rowCount()-1]] ) );
//                ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,1,new QTableWidgetItem(QString::number(saida.frameComeco[ui->tabRegistro->rowCount()-1]/videoLista.fps[0])));
//                ui->tabRegistro->setItem(ui->tabRegistro->rowCount()-1,2,new QTableWidgetItem(QString::number(saida.framFim[ui->tabRegistro->rowCount()-1]/videoLista.fps[0])));

//                saida.chPontoValido.push_back(true);


//                //configurando TableWidget
//                ui->tabRegistro->resizeColumnsToContents();
//                ui->tabRegistro->clearSelection();
//                ui->tabRegistro->clearFocus();


//            }else{

//                chvEscreRow= false;


//            }





//        }

//        for(int ka=0; ka< ui->tabRegistro->rowCount();ka++ ){

////                ui->tabRegistro->setRowCount(ka);
////                ui->tabRegistro->setColumnCount(1);
////                ui->tabRegistro->setItem();

//            ui->tabRegistro->setItem(ka,1,new QTableWidgetItem(QString::number(saida.frameComeco[ka]/videoLista.fps[0])));
//            ui->tabRegistro->setItem(ka,2,new QTableWidgetItem(QString::number(saida.framFim[ka]/videoLista.fps[0])));



//        }






//    }
}

void telaEtografiaProce::on_pbDeleteRegistros_clicked()
{
    int itemSelecionado = 0;
    int ultimoValor=-1;
    bool algumClicado=false;

    QString red_color = "background-color: rgb(224,56,16);";
    QString green_color = "background-color: rgb(39,245,108);";


    if(ui->cbNested->isChecked()){

        int itemSelecionado = 0;

        for(int i=0; i<numeroDeBotoes; i++){

            if(clicado[i]){

                algumClicado=true;



            }


        }

        if(!algumClicado){
            for(int i=0;i<ui->tabRegistro->rowCount();i++)
            {
                if(ui->tabRegistro->item(i,0)->isSelected())
                {
                    saida.chPontoValido[i] = false; //falso se o ponto for deleteado
                    ui->tabRegistro->setRowHidden(i,true);
                    //dadosEto.dadoRemovido[i] = true; //diz que o dado foi removido
                   // ui->tabDadCat->removeRow(i);
                    itemSelecionado=1;
                }
            }


        }else{

//            if(itemSelecionado==0)
//            {
                 QMessageBox::information(this,"Atention!", "Descelecione o botão");
 //           }

        }



        if(itemSelecionado==0)
        {
             QMessageBox::information(this,"Atention!", "Sem nenhum item selecionado");
        }





    }

    if(ui->cbAuto->isChecked()){

        for(int i= ui->tabRegistro->rowCount()-1 ;i>=0;i--){

            if(saida.chPontoValido[i]){
               ultimoValor= i;
                break;

            }
           // ui->tabRegistro->item(i,1)->
    //        if(ui->tabRegistro->setRow)


        }
        qDebug()<<"ultimo valor " << ultimoValor;





        if(ultimoValor!=-1){




                ui->widControes->setEnabled(true); //libera a interface
                ui->widControle1->setEnabled(true);//libera a interface


                if(ui->btStop->isEnabled()){

                    ui->btStop->click();
                }


                contAtivoReg--;

            if(contAtivoReg>0){

                if(ui->cbAuto->isChecked()){

                    saida.chPontoValido[ultimoValor] = false; //falso se o ponto for deleteado
                    ui->tabRegistro->setRowHidden(ultimoValor,true);
                    //ui->hsTimer->setEnabled(true);
                    ui->hsTimer->setValue(saida.frameComeco[ultimoValor]);



                    for(int i=0; i<numeroDeBotoes; i++){

                        if(i==saida.id[ultimoValor-1]){

                            buttonList[i]->setStyleSheet(red_color + "color: black;" "font: bold;");
                            buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                            buttonList[i]->setEnabled(false);
                            clicado[i]=true;



                        }else{

                            buttonList[i]->setStyleSheet(green_color + "color: black;" "font: bold;");
                            buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                            buttonList[i]->setEnabled(true);
                            clicado[i]=false;
                        }

                    }







                }

                ui->widControes->setEnabled(false);
                ui->widControle1->setEnabled(false);



            }else{//se tem 0 contador ativos ele tem que deixar

                qDebug()<< 0;
                saida.chPontoValido[ultimoValor] = false; //falso se o ponto for deleteado
                ui->tabRegistro->setRowHidden(ultimoValor,true);
                //ui->hsTimer->setEnabled(true);
                ui->hsTimer->setValue(saida.frameComeco[ultimoValor]);


                compAnterior=-1;
                 for(int i=0; i<numeroDeBotoes; i++){


                     buttonList[i]->setStyleSheet("background-color: green;""color: black;" "font: bold;");
                     buttonList[i]->setText(nomeCate[i] +"(" + cAnaEto.atalho[i] +")");
                     buttonList[i]->setEnabled(true);
                     clicado[i]=false;


                 }


            }


            chCorrigir=true;


        }
    //        else{ //se o valor






    }






}





   // for(int i=0;i<ui->tabRegistro->rowCount();i++)
   // {
      //  if(ui->tabRegistro->rowCount()-1) //ui->tabRegistro->item(i,0)->isSelected()
      //  {
//            saida.chPontoValido[ultimoValor] = false; //falso se o ponto for deleteado
//            ui->tabRegistro->setRowHidden(ultimoValor,true);
//            //dadosEto.dadoRemovido[i] = true; //diz que o dado foi removido
//           // ui->tabDadCat->removeRow(i);
//            itemSelecionado=1;
     //   }
   // }


//   if(itemSelecionado==0)
//   {
//        QMessageBox::information(this,"Atention!", "Nenhum item selecionado");
//   }

//}

void telaEtografiaProce::on_pbSaveImage_clicked()
{
    QString nomeImagem;
    nomeImagem = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Portable Network Graphics (*.png)"
               );


    nomeImagem.chop(4);

//    QImage imageTotalSaidaCentroide;

//    imageTotalSaidaCentroide = qiFundo;

//   // dados->frameBackground = captadorDeVideo->pegaPlanoFundo(videoLista.frameBack[0]);
//    cv::Mat frameDisplay = captadorDeVideo->frameBackground;

//    cv::imshow("oi",frameDisplay);
//    cv::waitKey(10);

    //  estruturaa
    for(int ja=0; ja< videoLista.area[contadorDeVideo].tipo.size(); ja++ ){
//        [=](std::vector<QString> *nome_figura, std::vector<double> *centroid_x, std::vector<double> *centroid_y){

           QString nome_figura = videoLista.area[contadorDeVideo].nomeFig[ja];
           moduloProcessamento *dados_processados = listaProcessamento[ja];
           std::vector<double> centroid_x = dados_processados->reMorfo.centroidX;
           std::vector<double> centroid_y = dados_processados->reMorfo.centroidY;

//

           cv::Mat frameDisplay;
           frameDisplay= captadorDeVideo->pegaPlanoFundo(videoLista.frameBack[0]);

           QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);





           QPainter painter1(&imgLida);
           QPen caneta1;
           caneta1.setWidth(1);
           caneta1.setColor(QColor(0,0,255));

           painter1.setPen(caneta1);
           for(int i=1; i< centroid_x.size();i++){

               painter1.drawLine(centroid_x[i-1], centroid_y[i-1],
                                 centroid_x[i],   centroid_y[i]);

   //            painter1.drawLine(dados->reMorfo.centroidX[i-1],dados->reMorfo.centroidY[i-1],
   //                              dados->reMorfo.centroidX[i],dados->reMorfo.centroidY[i]);
                                 //);

               //painter1.drawPoint(dados->reMorfo.centroidX[i],dados->reMorfo.centroidY[i]);

           }


           QString  nome_imagem_area = nomeImagem + "_" +nome_figura +".png" ;

           if(imgLida.save( nome_imagem_area , "PNG")){

              qDebug() << "imagem Salvou";

           }else{

              qDebug() << "imagem não Salvou";
           }
//        }(videoLista.area[contadorDeVideo].nomeFig[ja],
//                    videoLista.area[contadorDeVideo].oriX[ja],
//                    videoLista.area[contadorDeVideo].oriY[ja]);



    }

////        stream.writeAttribute("ceX",QString::number());
////        stream.writeAttribute("ceY",QString::number(dados->reMorfo.centroidY[i]));



}

void telaEtografiaProce::setProcessamento()
{
    moduloProcessamento *dados1;

    captador->getParamVideo();

    dados1 = new moduloProcessamento();
    dados1->setBackground(captador->pegaPlanoFundo(videoLista.frameBack[0]));

    dados1->setCalibracao(videoLista.threshold[0],videoLista.erosao[0]);
    dados1->setParametrosVideo(captador->video_width,captador->video_heigth);
    dados1->confiCameraVir(videoLista.areaJanInte[0].oriX[0],
            videoLista.areaJanInte[0].oriY[0],
            videoLista.areaJanInte[contadorDeVideo].width[0],
            videoLista.areaJanInte[contadorDeVideo].height[0],
            videoLista.chaInteMoveAtivado[0],videoLista.chaInteMove[0]);
    dados1->setMaxVariacao(videoLista.tamMaxVar[0]);
    if(videoLista.area[contadorDeVideo].tipo[contPrcessamento]=="circle"){


        dados1->setAreaInteresse(videoLista.area[0].oriX[contPrcessamento], videoLista.area[0].oriY[contPrcessamento], videoLista.area[0].raio[contadorCirculo]);
        dados1->setNomeFigura(videoLista.area[contadorDeVideo].nomeFig[contPrcessamento]);
        contadorCirculo++;


    }else{

        dados1->setAreaInteresse(videoLista.area[0].oriX[contPrcessamento], videoLista.area[0].oriY[contPrcessamento], videoLista.area[0].height[contadorRetangulo],videoLista.area[0].width[contadorRetangulo]);
        dados1->setNomeFigura(videoLista.area[contadorDeVideo].nomeFig[contPrcessamento]);
        //caso for retangulo
        contadorRetangulo++;

    }


    //frInicio
    listaProcessamento.push_back(dados1);
    listaThreadProcessamento.push_back(thrProce);
//        delete dados;
//        delete thrProce;

    listaProcessamento[contPrcessamento]->moveToThread(listaThreadProcessamento[contPrcessamento]);//


//        connect(captador,SIGNAL(enviaImagem(QImage,int)),listaProcessamento[i],SLOT(processamentoDeVideoTodo(QImage,int)));


    connect(listaProcessamento[contPrcessamento],SIGNAL(fimProce()),captador,SLOT(setCaptaVideoTodo()));
    connect(listaProcessamento[contPrcessamento],SIGNAL(enviaMorfInt(int)), this,SLOT(recebeContadorMorfo(int)));

    listaThreadProcessamento[contPrcessamento]->start();

connect(captador,SIGNAL(enviaImagem(QImage,int)),listaProcessamento[contPrcessamento],SLOT(processamentoDeVideoTodo(QImage,int)));
}

void telaEtografiaProce::on_pbTraking_clicked()
{
    captador = new moduloCaptador();
    captadorThread = new QThread();
    captador->moveToThread(captadorThread); //a


    connect(this,SIGNAL(reiniciaProce()),captador,SLOT(setReinicio()));
    captador->setCaptador(videoLista.nomeOpencv[0]);
    //dados->frameBackground = conQim2Mat( captador->pegaPlanoFundoQImage(videoLista.frameBack[0]));
    //dados->setFrameFundo(captador->pegaPlanoFundoQImage(videoLista.frameBack[0]));

    captador->getParamVideo();
    //connect(captadorThread,SIGNAL(started()),captador,SLOT(setCaptaVideoTodo()));
    connect(this,SIGNAL(reiniciaProce()),captador,SLOT(setCaptaVideoTodo()));

    captador->setCaptadorRange(videoLista.frameProces[0],videoLista.frameFinal[0]);



   // for(int i=0; i<videoLista.area[0].nomeFig.size(); i++){

        thrProce = new QThread();



        setProcessamento();







    //ui->probCaptador->setRange(videoLista.frameProces[0],videoLista.frameFinal[0]-1);
    ui->progressBar->setRange(videoLista.frameProces[0], videoLista.frameFinal[0]);


//    captador->setCaptaVideoTodo(); //b
    //para thread
    captadorThread->start();//a

//    reiniciaProcessamento();
    emit reiniciaProce();
//    thrProce->start();//a


    //
    ui->gbStep2->setEnabled(false);



    chProceON=true;
    chEtografia=false;

    QVBoxLayout *vBoxLay = new QVBoxLayout(ui->widCheckBox);

    for(int ka=0; ka< videoLista.area[contadorDeVideo].nomeFig.size(); ka++){

        chebox = new QCheckBox();
        if(ka==0){
           chebox->setChecked(true);
        }else{
            chebox->setChecked(false);
        }
        chebox->setAutoExclusive(true);

        chebox->setText(videoLista.area[contadorDeVideo].nomeFig[ka]);
        cheboxList.push_back(chebox);
        vBoxLay->addWidget(cheboxList[ka]);

    }


    ui->widCheckBox->setLayout(vBoxLay);



    ui->gbStep6->setVisible(true);
    ui->gbStep5->setVisible(true);
    ui->tabButtons->setCurrentIndex(1);
    ui->tabButtons->setTabEnabled(0,false);
//    ui->tabButtons->setTabEnabled(1,false);




}

void telaEtografiaProce::on_chbTamnho_clicked()
{

}

void telaEtografiaProce::atualizaProcess(int numFrame)
{

    for(int i=0; i<cheboxList.size();i++){

        if(cheboxList[i]->isChecked()){
            dados = listaProcessamento[i];
        }

    }



    if(dados->reMorfo.objetoEncontrado[numFrame]){
         ui->tabWDesc->setItem(0,0,new QTableWidgetItem("true" ) );
    }else{
        ui->tabWDesc->setItem(0,0,new QTableWidgetItem("false" ) );
    }

//    dados = listaProcessamento[2];
    //dados->reMorfo.objetoEncontrado[numFrame].push_back(objeto);
   // reMorfo.area.push_back(area1);
  // dados->reMorfo.centroidX[numFrame].push_back(mcX);
   // dados->reMorfo.centroidY[numFrame].push_back(mcY);
    //dados->reMorfo.anguloObj[numFrame]push_back(anguloObjeto);
    //reMorfo.tamanhoObj.push_back(alturaObjeto);
  // dados->reMorfo.altura[numFrame].push_back(alturaObjeto);
    //dados->reMorfo.largura[numFrame].push_back(larguraObjeto);
   // dados->reCinema.varAngular[numFrame].push_back(varAngular);
   // dados->reCinema.varArea[numFrame].push_back(varArea);
   // dados->reCinema.varCenX[numFrame].push_back(VarCenX);
   // dados->reCinema.varCenY[numFrame].push_back(VarCenY);
   //dados-> reCinema.varDistancia[numFrame].push_back(VarDistancia);
    //dados->reCinema.varTamObjeto[numFrame].push_back(VarOBjeto);
  // dados-> reCinema.varAltura[numFrame].push_back(VarAltura);
  //  dados->reCinema.varLargura[numFrame].push_back(VarLargura);
  //  dados->reCinema.ruidoMaxVaria[numFrame].push_back(ruidoOn); //minima variação

    ui->tabWDesc->setItem(0,1,new QTableWidgetItem(QString::number(dados->reMorfo.area[numFrame]/(qPow(videoLista.escala[contadorDeVideo],2)) ) ));
     ui->tabWDesc->setItem(0,2,new QTableWidgetItem(QString::number(dados->reMorfo.centroidX[numFrame]) ));
      ui->tabWDesc->setItem(0,3,new QTableWidgetItem(QString::number(dados->reMorfo.centroidY[numFrame]) ));
       ui->tabWDesc->setItem(0,4,new QTableWidgetItem(QString::number(dados->reMorfo.anguloObj[numFrame] ) ));
       ui->tabWDesc->setItem(0,5,new QTableWidgetItem(QString::number(dados->reMorfo.altura[numFrame]/videoLista.escala[contadorDeVideo]) ) );
        ui->tabWDesc->setItem(0,6,new QTableWidgetItem(QString::number(dados->reMorfo.largura[numFrame]/videoLista.escala[contadorDeVideo]) ));

        ui->tabWDesc->setItem(0,7,new QTableWidgetItem(QString::number(dados->reCinema.varAngular[numFrame]) ) );
         ui->tabWDesc->setItem(0,8,new QTableWidgetItem(QString::number(dados->reCinema.varArea[numFrame]) ));
          ui->tabWDesc->setItem(0,9,new QTableWidgetItem(QString::number(dados->reCinema.varCenX[numFrame]) ));
           ui->tabWDesc->setItem(0,10,new QTableWidgetItem(QString::number(dados->reCinema.varCenY[numFrame]) ));
           ui->tabWDesc->setItem(0,11,new QTableWidgetItem(QString::number(dados-> reCinema.varDistancia[numFrame]) ) );
           // ui->tabWDesc->setItem(0,12,new QTableWidgetItem(QString::number(VarOBjeto) ));
            ui->tabWDesc->setItem(0,12,new QTableWidgetItem(QString::number(dados-> reCinema.varAltura[numFrame] ) ));
            ui->tabWDesc->setItem(0,13,new QTableWidgetItem(QString::number(dados->reCinema.varLargura[numFrame]) ) );

             if(dados->reCinema.ruidoMaxVaria[numFrame]){

                 ui->tabWDesc->setItem(0,14,new QTableWidgetItem("true" ));

             }else{
                 ui->tabWDesc->setItem(0,14,new QTableWidgetItem("false" ));

             }
}

void telaEtografiaProce::on_cb_temporal_segmentation_clicked()
{

    ui->lieTime->setEnabled(ui->cb_temporal_segmentation->isChecked());

}

QString telaEtografiaProce::gera_csv_eto(QString nomeGravarEtografia,
                                     int frameProces,
                                     int frameFinal,
                                     double fps,
                                     QString nome_caminho_video,

                                     QString nomeGravarCatalago,
                                     std::vector<QString> nomeCategoria,
                                     std::vector<int> catalogo_id,

                                     std::vector<double> eto_frameComeco,
                                     std::vector<double> eto_framFim,
                                     std::vector<int> eto_id
                                     )
{



    QString t_saida ="Sequence  and moment of occurrence of the categories recorded\n";


    double duracao=0;
    t_saida = t_saida + " Time (s)" + ";" + "Categories" + ";" + "Duration(s)" + "\n";

    for(int ka1=0; ka1< eto_frameComeco.size(); ka1++){

        t_saida = t_saida + QString::number( eto_frameComeco[ka1] / fps);
        //csvGravador << etografiaLida->frameInicial[ka1] / videoLido->fps;

        t_saida = t_saida + ";";
        t_saida = t_saida + nomeCategoria[eto_id[ka1]];
        t_saida = t_saida + ";";


        t_saida = t_saida + QString::number( (eto_framFim[ka1]- eto_frameComeco[ka1])/ fps);
//        t_saida = t_saida + QString::number( duracao / fps);
        t_saida = t_saida + "\n";

    }

    this->totalizacoesEtografia(frameFinal, frameProces, fps,
                                catalogo_id,
                                eto_frameComeco, eto_framFim, eto_id);

    t_saida = t_saida +  "RESULTS FOR THE ENTIRE PERIOD of ANALYSIS \n\n";

    t_saida = t_saida + "Category" + ";" + "Duration(s)" + ";" + "Freq." + ";" + "Latency(s)" + "\n";

    for(int ka2=0; ka2< nomeCategoria.size(); ka2++){
        t_saida = t_saida + nomeCategoria[ka2] + ";"
                     + QString::number( vetorDuracao[ka2]) + ";"
                     + QString::number( vetorFrequencia[ka2]) + ";"
                     + QString::number( vetorLatencia[ka2]) + ";" ;
        t_saida = t_saida + "\n";

    }


    return t_saida;



}


void telaEtografiaProce::_gravar_csv(QString path_eto, QString t_saida){
    QFile outGravador_csv;
    QStringList list1 = path_eto.split(".etoxml"); // nomeGravarEtografia
    QString csv_path = list1[0] + "_csv.csv";
    outGravador_csv.setFileName(csv_path);
    outGravador_csv.open(QIODevice::WriteOnly | QIODevice::Text );
    QTextStream csvGravador(&outGravador_csv);


    csvGravador << t_saida;
    outGravador_csv.close();
}


void telaEtografiaProce::totalizacoesEtografia(int vl_frameFinal,
                                               int frameProces,
                                               double fps,
                                               std::vector<int> catalogo_id,

                                               std::vector<double> eto_frameComeco,
                                               std::vector<double> eto_framFim,
                                               std::vector<int> eto_id
                                               )
{
//encontra frequencia
    for(int ka=0; ka< catalogo_id.size(); ka++){
        //cada categoria
        frequencia=0;

        for(int ja=0; ja<eto_id.size(); ja++){

            if(eto_id[ja]==ka){

               frequencia=frequencia+1;
            }
        }
        vetorFrequencia.push_back(frequencia);
    }

    //encontra latencia
    int primeiraOcorrencia=0;
    bool chLate;


    for(int ka=0; ka< catalogo_id.size(); ka++){
        //cada categoria
        //latencia
        latencia= vl_frameFinal;
        chLate=true;

        //encontra a primeria vez que aconteceu
        for(int ja=0; ja< eto_id.size(); ja++){

            if( (eto_id[ja]==ka) &&(chLate)){

               primeiraOcorrencia= ja;
               chLate=false;

            }

        }

        latencia= eto_frameComeco[primeiraOcorrencia] - frameProces;
        vetorLatencia.push_back(latencia/fps);
    }


    //encontra duracao;

    for(int ka=0; ka< catalogo_id.size(); ka++){
        //cada categoria
        duracao=0;

        for(int ja=0; ja< eto_id.size(); ja++){

            if(eto_id[ja]==ka){

               duracao= eto_framFim[ja]- eto_frameComeco[ja] + duracao;

            }
        }
        vetorDuracao.push_back(duracao/fps);
    }



    chLate=false;





}

void telaEtografiaProce::on_cb_seq_analyses_clicked()
{

    transi= new telaMatrizTransicao();

    ui->pb_generate_grafic->setEnabled(ui->cb_seq_analyses->isChecked());




//    texto_seg = segment->gera_segmentacao_texto(
//                ui->lieTime->text().toDouble(),
//                videoLista.frameProces[contadorDeVideo],
//                videoLista.frameFinal[contadorDeVideo],
//                videoLista.fps[contadorDeVideo],

//                saida.frameComeco,
//                saida.framFim,
//                saida.id,

//                cAnaEto.nomeCategoria,
//                cAnaEto.quantidadeDeDados);


}

void telaEtografiaProce::on_pb_generate_grafic_clicked()
{
    transi->mostra_gerar_grafico(cAnaEto.nomeCategoria);
}
