#include "telacadastrofilme.h"
#include "ui_telacadastrofilme.h"

//namespace cv
//{
//    using std::vector;
//} adequacão para a opencv 3.2

telaCadastroFilme::telaCadastroFilme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaCadastroFilme)
{
    ui->setupUi(this);
    countArea=0;
    itemSelecionado=0;

    areaInt = new itemAreaInte(true);
    triBlueMax = new areaTraingulo(false);
    triRedMax = new areaTraingulo(true);
    triBlueScala = new areaTraingulo(false);
    triRedScala = new areaTraingulo(true);

    ui->tabWPrincipal->setCurrentIndex(0);
    ui->tabWPrincipal->setTabEnabled(0,true);
    ui->tabWPrincipal->setTabEnabled(1,false);
    ui->tabWPrincipal->setTabEnabled(2,false);


    ui->tabWCalib->setTabEnabled(0,true);
    ui->tabWCalib->setTabEnabled(1,false);
    ui->tabWCalib->setTabEnabled(2,false);
    ui->tabWCalib->setTabEnabled(3,false);


    chaveBack=false;
    captador = new moduloCaptador();
    resultado.frameFundo=0;
    resultado.frameInicial=0;
//    //Inicializa itens da lista de cores de fundo para a segmentação
//    ui->comboBoxBackground->addItem("White");
//    ui->comboBoxBackground->addItem("Black");
    imageFundopixMap = new QGraphicsPixmapItem();

}

telaCadastroFilme::~telaCadastroFilme()
{
    qDebug() <<"destruindo telaCadastroVideo0 ";
    delete captador;
    delete ui;
    qDebug() <<"destruindo telaCadastroVideo1 ";
}

void telaCadastroFilme::recebeImagem(QImage qiCaptador, int numFrame)
{
    frame_atual=numFrame;
    ui->labelFrames->setText(QString::number(frame_atual));
    ui->labelTempo->setText(QString::number(frame_atual/video_fps));
    ui->hsTimer->setValue(numFrame);


    if(chVideo){
        //se for verdadeiro ele vai estar atualizando a imagem pela tab


      switch (ui->tabWCalib->currentIndex()){

      case 1:
          imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameBack));
          break;
      case 2:
          //primeiro vai permitir a imagem mudar;
          if(chRoi){
              imageFundopixMap->setPixmap( QPixmap::fromImage(qiCaptador.scaled(480, 360,Qt::KeepAspectRatio) ));

          }else{ //encontra a primeira posição
              imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameProce));
          }

          break;
      case 3:
          imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameBack));
          break;
      default:
          //imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameBack));
          qDebug() <<"erro pro";
          break;


      }






    }else{

        if(!chaveBack){

            QImage small = qiCaptador.scaled(480, 360,Qt::KeepAspectRatio);
            qiRecebida= small;
            //ui->imgResultado->setPixmap(QPixmap::fromImage(small));
            imageFundopixMap->setPixmap(QPixmap::fromImage(small));

        }else{

            QImage small2 = qiCaptador.scaled(480, 360,Qt::KeepAspectRatio);
            qiRecebida=small2;
            frameAnimal = conQim2Mat(qiRecebida);
            cv::Mat frameAnimal2 = frameAnimal.clone();

            frameSubtracao= abs(frameAnimal-frameBackground);

            //cv::imshow("olha",frameSubtracao);

    //---------------------------------------------------------------------------------------------------------
    //------FrameLimiarizcao: Máscara do animal (animal preto e fundo branco) - threshold --------------------

            threshold_value= ui->SliderThreshold->value();
            cv::cvtColor( frameSubtracao.clone(), frameSubtracao_gray, CV_RGB2GRAY );
            cv::threshold( frameSubtracao_gray, frameLimiarizacao, threshold_value, 255,CV_THRESH_BINARY);
            //cv::adaptiveThreshold(frameSubtracao_gray, frameLimiarizacao,255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 11, 2);

            qDebug()<<" o threshold ficou de " << threshold_value;
    //---------------------------------------------------------------------------------------------------
    //------FrameErosao: Erosão da máscara do animal------------------------------------------------------

            erosao=ui->spinBoxErosao->value();
            cv::Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(2*erosao+1, 2*erosao+1),cv::Point(erosao, erosao));
            cv::erode( frameLimiarizacao, frameErosao, element );
//            cv::imshow("fundo", frameSubtracao.clone());
//            cv::waitKey(15);

            cv::vector<cv::vector<cv::Point> > contours;
            cv::vector<cv::Vec4i> hierarchy;

            cv::findContours( frameErosao, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

            cv::Mat drawing = cv::Mat::zeros( frameErosao.size(), CV_8UC3 );
            cv::Mat frameContorno = cv::Mat::zeros( frameErosao.size(), CV_8UC3 );
            cv::Mat frameContornoBranco = cv::Mat::zeros( frameErosao.size(), CV_8UC3 );

            if( contours.size() != 0 )
            {
                int idx = 0, largestComp = 0;
                double maxArea = 0;

                for( ; idx >= 0; idx = hierarchy[idx][0] )
                {
                    const cv::vector<cv::Point>& c = contours[idx];
                    double area = fabs(cv::contourArea(cv::Mat(c)));
                    if( area > maxArea )
                    {
                        maxArea = area;
                        largestComp = idx;
                    }
                }

                cv::Scalar color = cv::Scalar( 255, 255, 255 );
                cv::Scalar color2 = cv::Scalar( 255, 0, 0 );
                cv::Scalar color3 = cv::Scalar( 0, 0, 255 ); //amarelo
                 cv::Scalar color4 = cv::Scalar( 0, 255,0 );

                for(int ja=0 ; ja< contours.size();ja++){

                    if(ja!=idx){

                        cv::drawContours( drawing, contours, ja, color2, CV_FILLED, 8, hierarchy );

                    }else{

                        cv::drawContours( drawing, contours, ja, color, CV_FILLED, 8, hierarchy );
                    }

                }

                cv::drawContours( drawing, contours, largestComp, color3, CV_FILLED, 8, hierarchy ); //selecione que fique a area amarela dentro do objeto de interese

                cv::threshold( drawing, drawing, 1, 255,CV_THRESH_BINARY_INV);
                cv::drawContours( frameContornoBranco, contours, largestComp, color, 1, 8, hierarchy );
                cv::drawContours( frameContorno, contours, largestComp, color2, 1, 8, hierarchy );


            frameSegmentacao= drawing+frameAnimal2-frameContornoBranco+frameContorno;


    //---------------------------------------------------------------------------------------------------
    //------Apenas para plotar na tela com fundo preto ou fundo branco-------------------------------------

            frameVisualizar=frameSegmentacao;
            if(ui->comboBoxBackground->currentIndex()==1)
            {
                //frameVisualizar=frameVisualizar-frameErosao;
                frameVisualizar=frameVisualizar-drawing-frameContornoBranco+frameContorno;
            }

            QImage imgSegmentacao((uchar*)frameVisualizar.data, frameVisualizar.cols,frameVisualizar.rows, frameVisualizar.step, QImage::Format_RGB888);

            //ui->imgResultado->setPixmap(QPixmap::fromImage(imgSegmentacao));
            imageFundopixMap->setPixmap(QPixmap::fromImage(imgSegmentacao));
            }
        }



    }


}

void telaCadastroFilme::on_pbAbreVideo_clicked()
{
    fonteVideo = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
               "C://Users//Bio//Desktop//videos//",
               "Video Files (*.avi *.mp4 *.mpeg *.mpg *.wmv *.flv *.mkv *.divx *.mp4)"
                );




            //transforma o caminho lido pela janela em um arquivo de string



    if(!fonteVideo.isNull())
        {

        captador = new moduloCaptador();

        connect(captador,SIGNAL(enviaImagem(QImage,int)),this,SLOT(recebeImagem(QImage,int)));

        captador->setCaptador(fonteVideo);


        fonteVideoBit = fonteVideo.toLatin1();


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

            //encontrar a ultima barra antes do nome
            int k=0;
            int ultimaPosicaoDaBarra=0;

            while(fonteVideoBit[k] != 0) //enquanto não tem string nula ou seja não é o fim do arquivo
            {

                if(fonteVideoBit[k] == 47){ //47 esta relacionado com a barra

                    ultimaPosicaoDaBarra = k;

                }
                k++;


            }


            //assim pode-se encontar o nome do arquivo
            int contadorNome=ultimaPosicaoDaBarra+1;
            int contadorNome2=0;

            for(contadorNome;
                contadorNome <(fonteVideoBit.length()-j);
                contadorNome++)
            {

                fonteVideoBitNomeArquivo[contadorNome2]= fonteVideoBit[contadorNome];
                contadorNome2++;
            }

            //assim pode-se encontrar o caminho do arquivo
            int contadorCaminho=0;


            for(contadorCaminho;
                contadorCaminho < ultimaPosicaoDaBarra;
                contadorCaminho++)
            {

                fonteVideoBitCaminhoArquivo[contadorCaminho]= fonteVideoBit[contadorCaminho];

            }


            //ageitando a extensão apara a opencv

            k=0;
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

            //jeito certo que tem que estar a string
          // video.open("C://Users//joao//Desktop//videos//funcionaMarcela.avi");

        fonteVideoOpenCVString=fonteVideoOpenCV.toStdString();

//                    video.open(fonteVideoOpenCVString); //isso aqui é muito delicado

        //if(video.isOpened()){
            video_fps = captador->video_fps;              //captura frames por segundo
            video_frames = captador->video_frames;      //captura quantidade de frames
            video_tempo = captador->video_tempo;                   //calcula tempo do video
            video_width = captador->video_width;       //captura largura do video
            video_heigth = captador->video_heigth;     //captura altura do video
           //escrita no gui o resultado da opencv tab2
            //ui->lblExtOpencv->setText(fonteVideoBitOpenCV);
           // ui->lblFPS->setText(QString::number(video_fps));
            //ui->lblFrames->setText(QString::number(video_frames));
            ui->labelFramesTotal->setText(QString::number(video_frames));
           // ui->lblTempo->setText(QString::number(video_tempo));
            ui->labelTempoTotal->setText(QString::number(video_tempo));
            ui->lblFps->setText(QString::number(video_fps));
            ui->lblWidth->setText(QString::number(video_width));
            ui->lblHeight->setText(QString::number(video_heigth));



        //}


            //escrita do gui na tab 1
            //ui->lblExt->setText(fonteVideoBitExt);
            ui->lblNomeVideo->setText(fonteVideoBitNomeArquivo);
            qDebug() << "fonteVideoBitNome";
            ui->lblCaminho->setText(fonteVideoBitCaminhoArquivo);

        //video.release();

    //    calibracaoVideo->fonteVideoBitOpenCV = fonteVideoBitOpenCV;

        captador->setCaptador(fonteVideo);

        //ui->pbAbreVideo->setEnabled(false);
        ui->btPlay->setEnabled(true);
        ui->btStop->setEnabled(false);
        ui->pbAbreVideo->setEnabled(false);


       // ui->tabWPrincipal->setTabEnabled(3,false);

        ui->gbControle->setEnabled(true);

        //resetaCorConfi();
        ui->swiTutorConfig->setCurrentIndex(1);

        //ui->groVideoInfo->setStyleSheet("font: bold;""background-color: #00ac00;");
        ui->hsTimer->setRange(0,(int)video_frames );

        imageFundopixMap = new QGraphicsPixmapItem();
        scene = new QGraphicsScene(0,0,480,360,ui->graphicsView);
        ui->graphicsView->setScene(scene);
        //imgResultado

        scene->addItem(imageFundopixMap);
        //setando o tamanho da cena
       // scene->setSceneRect(0,0,480,340);



        areaInt = new itemAreaInte(true);
        scene->addItem(areaInt);
        areaInt->setPos(100,200);
        areaInt->setSelecionado(true);
        areaInt->permitidoDoubleClick = false;

        connect(areaInt,SIGNAL(atualizoImage()),this,SLOT(on_sbP1XJanela_editingFinished()));
        connect(areaInt,SIGNAL(atualizoImage()),this,SLOT(on_sbP1YJanela_editingFinished()));


        triBlueScala = new areaTraingulo(false);
        triRedScala = new areaTraingulo(true);

        scene->addItem(triBlueScala);
        scene->addItem(triRedScala);

        triBlueScala->setPos(300,140);
        connect(triRedScala,SIGNAL(atualizoImage()),this,SLOT(on_sbScalP1X_editingFinished()));

        connect(triRedScala,SIGNAL(atualizoImage()),this,SLOT(on_sbScalP1Y_editingFinished()));
        connect(triBlueScala,SIGNAL(atualizoImage()),this,SLOT(on_sbScalP2X_editingFinished()));
        connect(triBlueScala,SIGNAL(atualizoImage()),this,SLOT(on_sbScalP2Y_editingFinished()));



        triRedScala->setPos(160,140);


        //para o maxima variacao
        triBlueMax = new areaTraingulo(false);
        triRedMax = new areaTraingulo(true);

        scene->addItem(triBlueMax);
        scene->addItem(triRedMax);

        triBlueMax->setPos(200,180);
        connect(triRedMax,SIGNAL(atualizoImage()),this,SLOT(on_sbJanelaP1X_editingFinished()));
        connect(triRedMax,SIGNAL(atualizoImage()),this,SLOT(on_sbJanelaP1Y_editingFinished()));
        connect(triBlueMax,SIGNAL(atualizoImage()),this,SLOT(on_sbJanelaP2X_editingFinished()));
        connect(triBlueMax,SIGNAL(atualizoImage()),this,SLOT(on_sbJanelaP2Y_editingFinished()));



        triRedMax->setPos(280,180);
        areaInt->setVisible(false);
        triRedMax->setVisible(false);
        triBlueMax->setVisible(false);
        triBlueScala->setVisible(false);
        triRedScala->setVisible(false);






         }




}

void telaCadastroFilme::on_btPlay_clicked()
{
    captador->iniciandoTimer(qPow(2,ui->SliderVelocidade->value()));
    ui->btPlay->setEnabled(false);
    ui->btStop->setEnabled(true);
    ui->hsTimer->setEnabled(false);
    ui->SliderVelocidade->setEnabled(true);

}

void telaCadastroFilme::on_btStop_clicked()
{
    captador->finalizandoTimer();
    ui->btPlay->setEnabled(true);
    ui->btStop->setEnabled(false);
    ui->hsTimer->setEnabled(true);
    ui->SliderVelocidade->setEnabled(false);

}

void telaCadastroFilme::on_btAvancar_clicked()
{
    if((frame_atual+ui->edtFatordesloc->text().toInt())<video_frames){


        ui->hsTimer->setEnabled(false);
        captador->setFrame(ui->labelFrames->text().toInt()+ui->edtFatordesloc->value());
        ui->labelFrames->setText(QString::number(ui->labelFrames->text().toInt()+ui->edtFatordesloc->value()));
        ui->hsTimer->setValue(ui->labelFrames->text().toInt());
        captador->captando();
        ui->hsTimer->setEnabled(true);


//        captador->setFrame(frame_atual+ui->edtFatordesloc->text().toInt());
//        frame_atual=frame_atual+ui->edtFatordesloc->text().toInt() ;
//        ui->labelFrames->setText(QString::number(frame_atual));

//        captador->captando();

    }
}

void telaCadastroFilme::on_btVoltar_clicked()
{


    if((ui->labelFrames->text().toInt()-ui->edtFatordesloc->value())>=0){
    ui->hsTimer->setEnabled(false);
     captador->setFrame(ui->labelFrames->text().toInt()-ui->edtFatordesloc->value());
     ui->labelFrames->setText(QString::number(ui->labelFrames->text().toInt()-ui->edtFatordesloc->value()));
     ui->hsTimer->setValue(ui->labelFrames->text().toInt());
     captador->captando();
     ui->hsTimer->setEnabled(true);
    }

//    if((frame_atual-ui->edtFatordesloc->text().toInt()) >=0){

//        captador->setFrame(frame_atual-ui->edtFatordesloc->text().toInt());
//        frame_atual=frame_atual-ui->edtFatordesloc->text().toInt() ;
//        ui->labelFrames->setText(QString::number(frame_atual));
//        captador->captando();

//   }
}

void telaCadastroFilme::on_SliderVelocidade_sliderReleased()
{
    fatorVeloc= qPow(2,ui->SliderVelocidade->value());

    //Pausa o contador de controle de reprodução e processamento do video
    captador->finalizandoTimer();

    //Reinicia o contador de controle de reprodução e processamento do video com a nova velocidade.
    //Calcula o tempo de disparo igual ao tempo de reprodução de 1 frame (1000ms/fps) multiplicado
    //pelo novo fator de velocidade(aceleração/desaceleração) do video
    captador->iniciandoTimer(fatorVeloc);
}

void telaCadastroFilme::on_pbAdquiriFrame_clicked()
{
    //captador->finalizandoTimer();

    resultado.frameInicial=frame_atual;

  // if(frame_atual)
    resultado.qiFrameInicial=qiRecebida;
    ui->lblFrameInicio->setText(QString::number(resultado.frameInicial));
   // ui->imgResultado->setPixmap(QPixmap::fromImage(resultado.qiFrameInicial));

   // ui->btPlay->setEnabled(true);
   // ui->btStop->setEnabled(false);
}
//escala
void telaCadastroFilme::on_pbConfEscala_clicked()
{
    ui->gbScale->setEnabled(false);
    disPonto = qPow(triRedScala->pos().x() - triBlueScala->pos().x(),2) +qPow( triRedScala->pos().y()- triBlueScala->pos().y(),2) ;

    disPonto= qSqrt(disPonto);

    scala= disPonto/ui->spinBoxScaleCm->value();

    ui->leScala->setText(QString::number(scala));
    videoCadastrado.resultado.escala=scala;
}

void telaCadastroFilme::on_tabWPrincipal_currentChanged(int index)
{

    qDebug()<< " passou pela tab principal";
    if(index==0){

        areaInt->setVisible(false);
        triRedMax->setVisible(false);
        triBlueMax->setVisible(false);
        triRedScala->setVisible(false);
        triBlueScala->setVisible(false);


    }

    if(index==1){

        ui->tabWCalib->setCurrentIndex(0);
        areaInt->setVisible(false);
        triRedMax->setVisible(false);
        triBlueMax->setVisible(false);
        triRedScala->setVisible(false);
        triBlueScala->setVisible(false);


    }
}

void telaCadastroFilme::on_tabWCalib_currentChanged(int index)
{
     qDebug()<< " passou pela tab de calibracao";

    triBlueScala->setVisible(false);
    triRedScala->setVisible(false);
    triBlueMax->setVisible(false);
    triRedMax->setVisible(false);
    areaInt->setVisible(false);

    for(int c1=0; c1 < listaAreaProce.size(); c1++){

        listaAreaProce[c1]->setVisible(false);

    }
    qDebug()<< " passou pela tab de calibracao1";

    if(index==0){


        chVideo=false;

    }


    if(index==1){

        chVideo=true;
        triBlueScala->setVisible(true);
        triRedScala->setVisible(true);

        imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameBack));


    }
    if(index==2){
        qDebug()<<"tab treatment noise";

        chVideo=true;
        ui->tabWNoise->setCurrentIndex(0);
        areaInt->setVisible(false);


        imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameProce));



    }

    if(index==3){
        chVideo=true;

        for(int c1=0; c1 < listaAreaProce.size(); c1++){
            if(listAreaBool[itemSelecionado]){

                listaAreaProce[c1]->setVisible(true);

            }

        }
        imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameBack));
    }

    qDebug()<< " passou pela tab de calibracao2";
}

void telaCadastroFilme::on_sbScalP1X_editingFinished()
{
    ui->sbScalP1X->setValue(triRedScala->pos().x());

    scalaP1.x = triRedScala->pos().x();
    disPonto= qSqrt(qPow(scalaP2.x-scalaP1.x,2)+qPow(scalaP2.y-scalaP1.y,2));
    ui->lineEditScalePx->setText(QString::number(disPonto));
}

void telaCadastroFilme::on_sbScalP1Y_editingFinished()
{
    ui->sbScalP1Y->setValue(triRedScala->pos().y());

    scalaP1.y = triRedScala->pos().y();
    disPonto= qSqrt(qPow(scalaP2.x-scalaP1.x,2)+qPow(scalaP2.y-scalaP1.y,2));
    ui->lineEditScalePx->setText(QString::number(disPonto));
}

void telaCadastroFilme::on_sbScalP2X_editingFinished()
{
    ui->sbScalP2X->setValue(triBlueScala->pos().x());



    scalaP2.x = triBlueScala->pos().x();
    disPonto= qSqrt(qPow(scalaP2.x-scalaP1.x,2)+qPow(scalaP2.y-scalaP1.y,2));
    ui->lineEditScalePx->setText(QString::number(disPonto));

}

void telaCadastroFilme::on_sbScalP2Y_editingFinished()
{
    ui->sbScalP2Y->setValue(triBlueScala->pos().y());

    scalaP2.y = triBlueScala->pos().y();
    disPonto= qSqrt(qPow(scalaP2.x-scalaP1.x,2)+qPow(scalaP2.y-scalaP1.y,2));
    ui->lineEditScalePx->setText(QString::number(disPonto));
}

void telaCadastroFilme::on_sbP1XJanela_editingFinished()
{
    janelaP1.x= areaInt->pos().x()/scala;
    ui->sbP1XJanela->setValue(janelaP1.x);
}

void telaCadastroFilme::on_sbP1YJanela_editingFinished()
{
    janelaP1.y = areaInt->pos().y() /scala;
    ui->sbP1YJanela->setValue(janelaP1.y);
}

void telaCadastroFilme::on_sbWidthJanela_valueChanged(double arg1)
{
    areaInt->setWid(ui->leVarMax->text().toDouble()*scala);
    //areaInt->setWid(ui->sbWidthJanela->value()*scala);
}

void telaCadastroFilme::on_sbHeiJanela_valueChanged(double arg1)
{
    areaInt->setHei(ui->leVarMax->text().toDouble()*scala);
    //areaInt->setHei(ui->sbHeiJanela->value()*scala);
}



void telaCadastroFilme::on_tabWNoise_currentChanged(int index)
{

//    if(index == 1 ){

//        areaInt->setVisible(true);
//        triRedMax->setVisible(false);
//        triBlueMax->setVisible(false);

//    }
//    if(index !=0){
//        //quando aperta o next ele muda
//        if(chRoi){
//            areaInt->setVisible(true);
//            triRedMax->setVisible(false);
//            triBlueMax->setVisible(false);

//        }else{

//            triRedMax->setVisible(true);
//            triBlueMax->setVisible(true);
//            areaInt->setVisible(false);

//        }

//    }



//    if(index==2){
//        triRedMax->setVisible(true);
//        triBlueMax->setVisible(true);
//        areaInt->setVisible(false);


//    }
}

void telaCadastroFilme::on_sbJanelaP1X_editingFinished()
{
    janelaMaxP1.x= triRedMax->pos().x()/scala;
    ui->sbJanelaP1X->setValue(janelaMaxP1.x);
    maxVaria= qSqrt(qPow(janelaMaxP2.x-janelaMaxP1.x,2)+qPow(janelaMaxP2.y-janelaMaxP1.y,2));
    ui->leVarMax->setText(QString::number(maxVaria));
}

void telaCadastroFilme::on_sbJanelaP2X_editingFinished()
{
    janelaMaxP2.x= triBlueMax->pos().x()/scala;
    ui->sbJanelaP2X->setValue(janelaMaxP2.x);
    maxVaria= qSqrt(qPow(janelaMaxP2.x-janelaMaxP1.x,2)+qPow(janelaMaxP2.y-janelaMaxP1.y,2));
    ui->leVarMax->setText(QString::number(maxVaria));
}

void telaCadastroFilme::on_sbJanelaP1Y_editingFinished()
{

    janelaMaxP1.y= triRedMax->pos().y()/scala;
     ui->sbJanelaP1Y->setValue(janelaMaxP1.y);
     maxVaria= qSqrt(qPow(janelaMaxP2.x-janelaMaxP1.x,2)+qPow(janelaMaxP2.y-janelaMaxP1.y,2));
     ui->leVarMax->setText(QString::number(maxVaria));

}

void telaCadastroFilme::on_sbJanelaP2Y_editingFinished()
{
    janelaMaxP2.y= triBlueMax->pos().y()/scala;
    ui->sbJanelaP2Y->setValue(janelaMaxP2.y);
    maxVaria= qSqrt(qPow(janelaMaxP2.x-janelaMaxP1.x,2)+qPow(janelaMaxP2.y-janelaMaxP1.y,2));
    ui->leVarMax->setText(QString::number(maxVaria));
}

void telaCadastroFilme::on_tabWCalib_tabBarClicked(int index)
{
    if(index==2){

        ui->tabWNoise->setCurrentIndex(0);
        areaInt->setVisible(true);
    }
}

void telaCadastroFilme::on_pbAddArea_clicked()
{
    ui->tabWidListAre->setColumnCount(1);

    chAddArea= true;
   if(ui->cbRetangle->isChecked()){

        novaArea = new itemAreaInte(true);
        nomeFigura="ret";

        //connect(novaArea,SIGNAL(atu)
   }else{ //adicionando novo circulo

       novaArea = new itemAreaInte(false);
       nomeFigura="cir";
      // listaAreaProce.push_back(novaArea);
   }


   listaAreaProce.push_back(novaArea);
   listAreaBool.push_back(true);

    novaArea->setTextFig(nomeFigura+QString::number(countArea));



 // connect(novaArea,SIGNAL(atualizoImage()),this,SLOT(on_sbAreaY_editingFinished()));
   connect(listaAreaProce[countArea],SIGNAL(atualizoImage()),this,SLOT(on_sbAreaX_editingFinished()));
   connect(listaAreaProce[countArea],SIGNAL(atualizoImage()),this,SLOT(on_sbAreaY_editingFinished()));
   connect(listaAreaProce[countArea],SIGNAL(atualizoImage()),this,SLOT(on_sbAreaWid_editingFinished()));
   connect(listaAreaProce[countArea],SIGNAL(atualizoImage()),this,SLOT(on_sbAreaHei_editingFinished()));
   connect(listaAreaProce[countArea],SIGNAL(atualizoImage()),this,SLOT(on_sbAreaRaio_editingFinished()));


   ui->tabWidListAre->insertRow(ui->tabWidListAre->rowCount());
   ui->tabWidListAre->setItem(ui->tabWidListAre->rowCount()-1,0,new QTableWidgetItem(nomeFigura+QString::number(countArea)));
   ui->tabWidListAre->resizeColumnsToContents();
   ui->tabWidListAre->clearSelection();
   ui->tabWidListAre->clearFocus();






   scene->addItem(listaAreaProce[countArea]);


//    ui->lisWidAreasPro->setItem(ui->lisWidAreasPro->rowCount()-1,1,new QTableWidgetItem(ui->leAtalho->text()));





   countArea++;

}

void telaCadastroFilme::on_cbCircle_clicked()
{
    if(ui->cbCircle->isChecked()){

        ui->cbRetangle->setChecked(false);
    }else{

        ui->cbRetangle->setChecked(true);
    }
}

void telaCadastroFilme::on_cbRetangle_clicked()
{
    if(ui->cbRetangle->isChecked()){

        ui->cbCircle->setChecked(false);
    }else{

        ui->cbCircle->setChecked(true);
    }
}

void telaCadastroFilme::on_tabWidListAre_cellPressed(int row, int column)
{
    itemSelecionado=row;
    listaAreaProce[itemSelecionado]->setSelecionado(true);



    if(listaAreaProce[row]->formaFigura){ //é retangulo

        ui->stackedParametros->setCurrentIndex(1);
        ui->sbAreaHei->setValue(listaAreaProce[itemSelecionado]->hei/scala);
        ui->sbAreaWid->setValue(listaAreaProce[itemSelecionado]->wid/scala);

    }else{ //é um circulo

        ui->stackedParametros->setCurrentIndex(0);
        ui->sbAreaRaio->setValue(listaAreaProce[itemSelecionado]->raio/scala/2);
        //ára mostrar para o o usuario como foi definido na verdade o dimaetro da figura
        // é o diametro/2
        chCirculoOn= true;

    }

   for(int c1=0; c1 < listaAreaProce.size() ; c1++){

        if(c1 == row){


        }else{

            listaAreaProce[c1]->setSelecionado(false);

        }

//            listaAreaProce[c1]->setSelecionado(true);


//            if(listaAreaProce[c1]->formaFigura){ //é retangulo

//                ui->stackedParametros->setCurrentIndex(1);


//            }else{ //é um circulo

//                ui->stackedParametros->setCurrentIndex(0);


   }


//        }else{

//

//        }

//    }

}

void telaCadastroFilme::on_sbAreaX_editingFinished()
{
    ui->sbAreaX->setValue(listaAreaProce[itemSelecionado]->pos().x()/scala);
//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();
}

void telaCadastroFilme::on_sbAreaY_editingFinished()
{
    ui->sbAreaY->setValue(listaAreaProce[itemSelecionado]->pos().y()/scala);
//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();
}

void telaCadastroFilme::on_sbAreaWid_editingFinished()
{
    //ui->sbAreaWid->setValue(listaAreaProce[itemSelecionado]->wid/scala);
//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();
}

void telaCadastroFilme::on_sbAreaHei_editingFinished()
{
//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();
    //ui->sbAreaHei->setValue(listaAreaProce[itemSelecionado]->hei/scala);
}

void telaCadastroFilme::on_sbAreaRaio_editingFinished()
{
//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();
   // ui->sbAreaRaio->setValue(listaAreaProce[itemSelecionado]->raio/scala);
}

void telaCadastroFilme::on_sbAreaWid_valueChanged(double arg1)
{

    listaAreaProce[itemSelecionado]->setWid(arg1*scala);  //setWidHei( (qreal) ui->sbAreaHei->value(), (qreal) arg1) ;
//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();
//    listaAreaProce[itemSelecionado]->setWidHei(ui->sbAreaWid->value(),
//                                               ui->sbAreaHei->value()) ;
}

void telaCadastroFilme::on_sbAreaHei_valueChanged(double arg1)
{
    listaAreaProce[itemSelecionado]->setHei(arg1*scala);  //Hei( arg1, (qreal) ui->sbAreaWid->value()) ;
    scene->update(scene->sceneRect());
    ui->graphicsView->setUpdatesEnabled(true);
    ui->graphicsView->update();
//    listaAreaProce[itemSelecionado]->hei = arg1;
}

void telaCadastroFilme::on_sbAreaRaio_valueChanged(double arg1)
{
//    listaAreaProce[itemSelecionado]->setWidHei( (qreal)ui->sbAreaRaio->value()*scala,
//                                                (qreal) ui->sbAreaRaio->value()*scala);

    listaAreaProce[itemSelecionado]->setRaio((qreal)ui->sbAreaRaio->value()*scala*2);
    //vc sempre seta o diametro da figura
    //sendo assim o diametro é duas vezes o raio
  //  scene->update(scene->sceneRect());
   // ui->graphicsView->setUpdatesEnabled(true);
   // ui->graphicsView->update();
}

void telaCadastroFilme::on_pushButtonDelArea_clicked()
{
    bool selecionado=false;
    for(int i=0;i<ui->tabWidListAre->rowCount();i++)
    {
        if(ui->tabWidListAre->item(i,0)->isSelected())
        {
            selecionado=true;
        }
    }
    if(selecionado){

        ui->tabWidListAre->hideRow(itemSelecionado);
        listaAreaProce[itemSelecionado]->setVisible(false);
        listAreaBool[itemSelecionado] = false;

        ui->sbAreaX->setValue(0);
        ui->sbAreaY->setValue(0);
        ui->sbAreaWid->setValue(0);
        ui->sbAreaHei->setValue(0);
        ui->sbAreaRaio->setValue(0);

        if(ui->cbCircle->isChecked()){

            ui-> stackedParametros-> setCurrentIndex(0);

        }else{
            ui-> stackedParametros-> setCurrentIndex(1);
        }

    }
}

void telaCadastroFilme::on_pushButtonCapture_clicked()
{
    //captador->finalizandoTimer();
    chaveBack=true;
    ui->chbPrevi->setChecked(true);

    resultado.frameFundo=frame_atual;
    resultado.qiFrameBack=qiRecebida;

    frameBackground = conQim2Mat(qiRecebida);
    ui->lblFrameBack->setText(QString::number(resultado.frameFundo));
   // ui->imgResultado->setPixmap(QPixmap::fromImage(resultado.qiFrameBack));

   // ui->btPlay->setEnabled(true);
   // ui->btStop->setEnabled(false);
}

void telaCadastroFilme::on_pbFrameProce_clicked()
{
    //captador->finalizandoTimer();
    //chaveBack=true;

    resultado.frameProces=frame_atual;
    resultado.qiFrameProce=qiRecebida;

//        frameProce = conQim2Mat(qiRecebida);
    ui->leFramePro->setText(QString::number(resultado.frameProces));
    //ui->imgResultado->setPixmap(QPixmap::fromImage(resultado.qiFrameProce));

   // ui->btPlay->setEnabled(true);
  //  ui->btStop->setEnabled(false);
}

void telaCadastroFilme::on_pbFrameFinal_clicked()
{
    //bFrameFinal=true;
    //pega o frame atual
 //    ui->tabWPrincipal->setTabEnabled(2,true);
//if(ui->cbFrameAtual->isChecked()){

        resultado.frameFinal=frame_atual;
        ui->leFrameFinal->setText(QString::number(resultado.frameFinal));

   // }

//        if(ui->cbFrameVideo->isChecked()){
//        resultado.frameFinal=video_frames;

//        ui->leFrameFinal->setText(QString::number(resultado.frameFinal));

//        }

//        if(ui->cbFramePersonalisado->isChecked()){
//        resultado.frameFinal=ui->leFrameFinal->text().toDouble();

//        ui->leFrameFinal->setText(QString::number(resultado.frameFinal));
//        ui->leFrameFinal->setEnabled(false);
//        }
}

void telaCadastroFilme::on_spinBoxScaleCm_valueChanged(double arg1)
{
    if(arg1!=0){
        disPonto = qPow(triRedScala->pos().x() - triBlueScala->pos().x(),2) +qPow( triRedScala->pos().y()- triBlueScala->pos().y(),2) ;

        disPonto= qSqrt(disPonto);
        scala= disPonto/ ui->spinBoxScaleCm->value();

     ui->leScala->setText(QString::number(scala));

    }
}

void telaCadastroFilme::on_sbP1XJanela_valueChanged(double arg1)
{

}

void telaCadastroFilme::on_pbCadastrar1_clicked()
{
    nomeArquivo = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                fonteVideo,
               "Videos Cadastrados (*.vxml)"
               );


    QFile output(nomeArquivo);
    //output.open(stdout, );
    output.open(QIODevice::WriteOnly);
//! [write output]
//! [start stream]
//!
//!

    double scalaFator;

    //scalaFator= video_width/video_heigth; //p1x original
    scalaFator= video_width; //escala video original

    double scalaFator2;

    //scalaFator2= (double)  frameBackground.cols/ frameBackground.rows; //p2x ajustado
    scalaFator2= 480 ; //escala da tela frameBackground.cols;


    scalTrans= scalaFator/scalaFator2; //transformando a escala da foto calibrada para a original


    QXmlStreamWriter stream(&output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento

    //passa dados para a variavel de saida
    videoCadastrado.ext= QString::fromLatin1(fonteVideoBitExt);
    videoCadastrado.nome= QString::fromLatin1(fonteVideoBitNomeArquivo);
    videoCadastrado.caminho= QString::fromLatin1(fonteVideoBitCaminhoArquivo);
    videoCadastrado.nomeOpencv= fonteVideo; //fonteVideoBitOpenCV;
    videoCadastrado.videoFps= video_fps;
    videoCadastrado.videoFrames= video_frames;
    videoCadastrado.videoTempo= video_tempo;
    videoCadastrado.video_heigth= video_heigth;
    videoCadastrado.video_width = video_width;
    videoCadastrado.resultado.escala= scala*scalTrans; // px/cm
    //videoCadastrado.resultado.escala= 1/videoCadastrado.resultado.escala; // cm/px
    //data calibração é atualizada em outra parte do codigo

    //data experimento
    videoCadastrado.idAnimal = ui->leIdentificador->text().toInt();
    videoCadastrado.tituloExperimento = ui->leTitutlo->text();
    videoCadastrado.observacoes = ui->leObsercacoes->text();

    //data aquisição
    //videoCadastrado.erroTempoAtrelado = ui->leErroTempo->text().toFloat();
   // videoCadastrado.fpsMedio = ui->leFpsMedio->text().toFloat();
   // videoCadastrado.tempoGastoAquisicao = ui->leTempoAquisicao->text().toFloat();
    //videoCadastrado.idCamera = ui->leCameraID->text().toInt();

    videoCadastrado.dataDia = ui->deData->date().day();
    videoCadastrado.dataMes = ui->deData->date().month();
    videoCadastrado.dataAno =  ui->deData->date().year();




    videoCadastrado.resultado.frameProce = resultado.frameProces; //calibracaoVideo->resultado.frameProces;

    videoCadastrado.resultado.background = resultado.background;//calibracaoVideo->resultado.background;

    videoCadastrado.resultado.erosao = ui->spinBoxErosao->value();
    videoCadastrado.resultado.threshold = ui->SliderThreshold->value();

    videoCadastrado.resultado.frameFinal = resultado.frameFinal;  ///calibracaoVideo->resultado.frameFinal;
//    ui->lblFrameFinal->setText(QString::number(videoCadastrado.resultado.frameFinal));
    videoCadastrado.resultado.frameFundo = resultado.frameFundo; // calibracaoVideo->resultado.frameFundo;
//    ui->lblFrameBack->setText(QString::number(videoCadastrado.resultado.frameFundo));
    videoCadastrado.resultado.frameInicial = resultado.frameInicial; //calibracaoVideo->resultado.frameInicial;


    stream.writeStartElement("cadastroVideo"); //abre o cadastroVideo

    stream.writeStartElement("dadoPesquisador"); //abre o elemento de informacoes

        stream.writeTextElement("nomePesquisador", videoCadastrado.experimentador.nome);
        stream.writeTextElement("laboratorio", videoCadastrado.experimentador.lab);

    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("dadoExperimento"); //abre o elemento de informacoes

        stream.writeTextElement("tituloExperimento", ui->leTitutlo->text());
        stream.writeTextElement("data",  ui->deData->text() );
        stream.writeTextElement("otherInfo", ui->leObsercacoes->text());
        stream.writeTextElement("animalID", ui->leIdentificador->text());
        stream.writeTextElement("wight",ui->leWeight->text());
        stream.writeTextElement("animalSex", ui->leSex->text());
        stream.writeTextElement("threatmen", ui->leThreatment->text());

    stream.writeEndElement(); //fecha o elemento de informacoes


    stream.writeStartElement("dadoOriginal"); //abre o elemento de dado original
         stream.writeTextElement("nomeOpencv", videoCadastrado.nomeOpencv);
         stream.writeTextElement("caminho", videoCadastrado.caminho);
         stream.writeTextElement("nomeOriginal", videoCadastrado.nome);
         stream.writeTextElement("extensao", videoCadastrado.ext);
         stream.writeTextElement("fps", QString::number(videoCadastrado.videoFps));
         stream.writeTextElement("quantidadeFrames",QString::number(videoCadastrado.videoFrames));
         stream.writeTextElement("quantidadeTempo", QString::number(videoCadastrado.videoTempo));
         stream.writeTextElement("width", QString::number(videoCadastrado.video_width));
         stream.writeTextElement("height",QString::number(videoCadastrado.video_heigth));


    stream.writeEndElement(); //fecha o elemento de dado original

    stream.writeStartElement("dadoCalibracaoEdicao");

    stream.writeTextElement("frameInicial", QString::number (videoCadastrado.resultado.frameInicial));

    if(ui->cbBlinding->isChecked()){
        stream.writeTextElement("blinding", "true");
    }else{

        stream.writeTextElement("blinding", "false");

    }


    stream.writeTextElement("frameBack", QString::number(videoCadastrado.resultado.frameFundo));
    stream.writeTextElement("frameFinal",QString::number(videoCadastrado.resultado.frameFinal));
    stream.writeTextElement("frameProces",QString::number(videoCadastrado.resultado.frameProce));
    stream.writeTextElement("treshold",QString::number(videoCadastrado.resultado.threshold));
    stream.writeTextElement("erosao", QString::number(videoCadastrado.resultado.erosao));
    stream.writeTextElement("escala", QString::number(videoCadastrado.resultado.escala));


    if(ui->cbPro->isChecked()){

        stream.writeTextElement("proImageOn", "true");

    }else{

        stream.writeTextElement("proImageOn", "false");
    }

    stream.writeStartElement("tratamentoRuido");

    stream.writeStartElement("janelaInteresse");
    if(ui->checkBox->isChecked()){// janela de interesse

       stream.writeTextElement("ativado","true");

       //if(ui->cbMovel->isChecked()){// sempre vai ser movel
          stream.writeTextElement("movel","true");
     //  }else{
    //     stream.writeTextElement("movel","false");
     // }

       stream.writeTextElement("origX",QString::number(areaInt->pos().x()*scalTrans)); //px
       stream.writeTextElement("origY",QString::number(areaInt->pos().y()*scalTrans)); //px
       stream.writeTextElement("width",QString::number(areaInt->wid*scalTrans)); //px
       stream.writeTextElement("heigth",QString::number(areaInt->hei*scalTrans)); //px


    }else{
        stream.writeTextElement("ativado","false");

//        if(ui->cbMovel->isChecked()){//
//           stream.writeTextElement("movel","true");
//        }else{
            stream.writeTextElement("movel","false");
//        }
        stream.writeTextElement("origX",QString::number(0));
        stream.writeTextElement("origY",QString::number(0));
        stream.writeTextElement("width",QString::number(videoCadastrado.video_width));
        stream.writeTextElement("heigth",QString::number(videoCadastrado.video_heigth));


    }




     stream.writeEndElement();

     stream.writeStartElement("maximaVariacaoCentro");

     if(ui->cbVariaca->isChecked()){// habilita minima variação

        stream.writeTextElement("ativado","true");
        stream.writeTextElement("tamanho",QString::number(minVaria*scala*scalTrans));

     }else{
         stream.writeTextElement("ativado","false");
         double varMax;
//         varMax= qPow(videoCadastrado.video_width,2)+ qPow(videoCadastrado.video_heigth,2);
//         varMax= qSqrt(varMax);
         //trocado para menor variação
         varMax =-1;
         stream.writeTextElement("tamanho",QString::number(varMax));
     }


      stream.writeEndElement();



    stream.writeEndElement();


    stream.writeStartElement("areasDeInteresse");

//    cv::Rect ls;

    int ka,ja;

    //tamanho do video
    stream.writeStartElement("area");
    stream.writeAttribute("id",QString::number(0));
    stream.writeAttribute("tipo","rectangle");
    stream.writeTextElement("nomeFig", "Total Area");
    stream.writeTextElement("oriX",QString::number(0));
    stream.writeTextElement("oriY",QString::number(0));
    stream.writeTextElement("height",QString::number(videoCadastrado.video_heigth));
    stream.writeTextElement("width",QString::number(videoCadastrado.video_width));


    stream.writeEndElement();



        for(ka=0; ka< listaAreaProce.size();ka++){

            if(listAreaBool[ka]){

                stream.writeStartElement("area");
                stream.writeAttribute("id",QString::number(ka+1));
                if(listaAreaProce[ka]->formaFigura)
                {
                   stream.writeAttribute("tipo","rectangle");
                }else{

                    stream.writeAttribute("tipo","circle");
                }

                stream.writeTextElement("nomeFig", listaAreaProce[ka]->texto);
                stream.writeTextElement("oriX",QString::number(listaAreaProce[ka]->pos().x()*scalTrans));
                stream.writeTextElement("oriY",QString::number(listaAreaProce[ka]->pos().y()*scalTrans));

                if(listaAreaProce[ka]->formaFigura)
                {
                    stream.writeTextElement("height",QString::number(listaAreaProce[ka]->hei*scalTrans));
                    stream.writeTextElement("width",QString::number(listaAreaProce[ka]->wid*scalTrans));

                }else{

                    stream.writeTextElement("rad",QString::number(listaAreaProce[ka]->raio*scalTrans/2));
                    //pq na verdade o que ele grava é o diametro

                }


            }


//                stream.writeTextElement("oriX",QString::number(videoCadastrado.resultado.retangulo[ka].x));
//                stream.writeTextElement("oriY",QString::number(videoCadastrado.resultado.retangulo[ka].y));
//                stream.writeTextElement("height",QString::number(videoCadastrado.resultado.retangulo[ka].height));
//                stream.writeTextElement("width",QString::number(videoCadastrado.resultado.retangulo[ka].width));


            stream.writeEndElement();
        }





//        for(ja=0; ja< videoCadastrado.resultado.tamCirculo.size(); ja++){

//            stream.writeStartElement("area");
//            stream.writeAttribute("id",QString::number(ka+ja+1));
//            stream.writeAttribute("tipo","circle");
//            stream.writeTextElement("oriX",QString::number(videoCadastrado.resultado.cenCirculo[ja].x));
//            stream.writeTextElement("oriY",QString::number(videoCadastrado.resultado.cenCirculo[ja].y));
//            stream.writeTextElement("rad",QString::number(videoCadastrado.resultado.tamCirculo[ja]));


//            stream.writeEndElement();




//        }



    stream.writeEndElement();


//    stream.writeStartElement("dadoAquisicao");

//        stream.writeTextElement("camera", QString::number(videoCadastrado.idCamera));
//        stream.writeTextElement("fpsMedio", QString::number(videoCadastrado.fpsMedio));
//        stream.writeTextElement("tempoProcessamento",QString::number(videoCadastrado.tempoGastoAquisicao));
//        stream.writeTextElement("erroDeTempo", QString::number(videoCadastrado.erroTempoAtrelado));

//    stream.writeEndElement();




    ////desse forma se coloca atributos no xml
   // stream.writeStartElement("nome");
   // stream.writeAttribute("id", "1000"); //escritor de atributos
   // stream.writeEndElement();


   // stream.writeTextElement("laboratorio", "lab");
   // stream.writeTextElement("idObservador", "1");





    stream.writeEndElement(); //abre o cadastroVideo
    stream.writeEndDocument(); //fecha o documento
    output.close(); //termina a gravacao


}

void telaCadastroFilme::on_hsTimer_sliderPressed()
{

}

void telaCadastroFilme::on_hsTimer_valueChanged(int value)
{
    // if(!ui->btPlay->isEnabled()){
         //aqui ta dando bug
     if(ui->hsTimer->isEnabled()){
         captador->setFrame(ui->hsTimer->value());
         frame_atual=ui->hsTimer->value();
         ui->labelFrames->setText(QString::number(frame_atual));
         ui->labelTempo->setText(QString::number(frame_atual));
         captador->captando();
     }
}

void telaCadastroFilme::on_pbConfigure1_clicked()
{

    if(ui->cbPro->isChecked()){

        ui->gbBack->setVisible(true);
        ui->tabWCalib->setTabEnabled(1,true);

    }else{
        ui->gbBack->setVisible(false);
    }

    if(!ui->cbBlinding->isChecked()){
        ui->gbBlinding->setVisible(false);
    }else{
        ui->gbBlinding->setVisible(true);
    }

    ui->tabWPrincipal->setTabEnabled(0,true);
    ui->tabWPrincipal->setTabEnabled(1,true);
    ui->tabWPrincipal->setTabEnabled(2,true);


    ui->pbConfigure1->setEnabled(false);
    ui->cbPro->setEnabled(false);
    ui->cbBlinding->setEnabled(false);

    //ui->btPlay->click();

    ui->tabWPrincipal->setCurrentIndex(1);


}

cv::Mat telaCadastroFilme::conQim2Mat(QImage imaEntrada)
{
    cv::Mat matSaida;
//    resultado.frameProces=frame_atual;
//    resultado.matProce= frameReduzido;
////        resultado.background=frame;
//    QImage resultadoBackground((uchar*)resultado.matProce.data, resultado.matProce.cols, resultado.matProce.rows, resultado.matProce.step, QImage::Format_RGB888);
//    resultProce= QPixmap::fromImage(resultadoBackground);
//    resultado.matProce.release();
    matSaida= cv::Mat(imaEntrada.height(),imaEntrada.width(),CV_8UC3, const_cast<uchar*>(imaEntrada.bits()), imaEntrada.bytesPerLine()).clone();


    cv::cvtColor(matSaida,matSaida,CV_RGB2BGR );
    return matSaida;
}

void telaCadastroFilme::on_pbConfigureNioseArea_clicked()
{
    if(ui->pbConfEscala->isEnabled()){


    }else{
        if(ui->cbNoise->isChecked()){

            ui->tabWCalib->setTabEnabled(2,true);

        }
        if(ui->cbArea->isChecked()){

            ui->tabWCalib->setTabEnabled(3,true);
        }


        ui->pbConfigureNioseArea->setEnabled(false);
        ui->cbNoise->setEnabled(false);
        ui->cbArea->setEnabled(false);

    }
}

void telaCadastroFilme::on_tabWidListAre_cellChanged(int row, int column)
{
    if(chAddArea){

        chAddArea= false; //isso aqui é para ele nao atualizar o nome quando adiciona uma nova area
    }else{

         listaAreaProce[itemSelecionado]->setTextFig(ui->tabWidListAre->item(row,column)->text());
    }



}

void telaCadastroFilme::on_chbPrevi_clicked(bool checked)
{
    chaveBack=checked;

    if(checked){

        ui->chbPrevi->setChecked(true);
    }else{
         ui->chbPrevi->setChecked(false);

    }

}

//void telaCadastroFilme::on_sbWidthJanela_editingFinished()
//{

//}

void telaCadastroFilme::on_pushButton_2_clicked()
{
    chRoi= false;
}

void telaCadastroFilme::on_pbNextRoi_clicked()
{
    chRoi=false;
    imageFundopixMap->setPixmap(QPixmap::fromImage(resultado.qiFrameProce));
    areaInt->setWid(ui->leVarMax->text().toDouble()*scala);
    areaInt->setHei(ui->leVarMax->text().toDouble()*scala);
    areaInt->setVisible(true);
    triRedMax->setVisible(false);
    triBlueMax->setVisible(false);

}

void telaCadastroFilme::on_pbConfigureTreatment_clicked()
{

    triRedMax->setVisible(true);
    triBlueMax->setVisible(true);
    areaInt->setVisible(false);
}

void telaCadastroFilme::on_pbConfRuidoInt_clicked()
{
    minVaria = ui->leMin->text().toDouble();
}
