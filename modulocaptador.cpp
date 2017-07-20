#include "modulocaptador.h"
//#include "comum.h"


cv::Mat moduloCaptador::conQim2Mat(QImage imaEntrada) //converte qimage para cv::mat
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

moduloCaptador::moduloCaptador(QObject *parent) : QObject(parent)
{
    i=0;
    frameTotal=300;
    //codec = CV_FOURCC('x', '2', '6', '4');
    codec = CV_FOURCC('P','I','M','1');
    //fps=30;
    nomeVideo= "C:\\filmes\\treadfuncionando15.avi";
    entrou1=true;
    tempoLerFrame = new QTimer();
   //cv::namedWindow("teste",cv::WINDOW_NORMAL);
    cap = new cv::VideoCapture();
    gravadorVideo = new cv::VideoWriter();
}
moduloCaptador::~moduloCaptador(){

    qDebug() << "terminando com o moduloCaptador0";

    chLigaCaptador= false;
    //delete this;
    if(cap->isOpened()){


            tempoLerFrame->stop();

        cap->release();
        this->setCapOn(false);
        //tempoLerFrame->deleteLater();

    }


    if(gravadorVideo->isOpened()){

        if(chGravadorVideoRelease){
           gravadorVideo->release();
            qDebug() << "video terminado abruptamenete";
        }

    }

    qDebug() << "terminando com o moduloCaptador1";


}



void moduloCaptador::configurando(){
    //cap.open(0);

    //cap.open("C://ethowatcher//videosOriginais//funcionaMarcela.avi");
   // cap.set(CV_CAP_PROP_POS_FRAMES,0);

   // dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
   // dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
    //fps = cap.get(CV_CAP_PROP_FPS);
   // fps=30;
   // cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
    //codec = CV_FOURCC('x', 'v', 'i', 'd');
   // oVideoWriter.open(nomeVideo.toStdString(),codec, fps ,frameSize,true);





    emit fimConfiguracao();



}


void moduloCaptador::setGravador(int frameTotal1){


    frameTotal= frameTotal1;



}

void moduloCaptador::desligando(){

    chLigaCaptador=false;
    delete this;
    //emit fimPrograma();

}

void moduloCaptador::getPlanoFundo()
{

    cap->read(frameBackground);

}

cv::Mat moduloCaptador::pegaPlanoFundo(int numeroFrameFundo)
{

    //funcao que funciona
    cap->set(CV_CAP_PROP_POS_FRAMES,numeroFrameFundo);
    cap->read(frameBackground);

//    cv::imshow("testeFinalFundoAberto1", frameBackground);
//    cv::waitKey(20);

    return frameBackground.clone();
}

QImage moduloCaptador::pegaPlanoFundoQImage(int numeroFrameFundo)
{

    cap->set(CV_CAP_PROP_POS_FRAMES,numeroFrameFundo);
    cap->read(frameBackground);

    cv::imshow("testeFinalFundoAberto", frameBackground);
    cv::waitKey(20);


    cv::Mat frameEnviar;
    frameEnviar = frameBackground.clone();


   // cv::cvtColor(frameEnviar,frameEnviar,CV_BGR2RGB );

    QImage imgLida((uchar*)frameEnviar.data, frameEnviar.cols, frameEnviar.rows, frameEnviar.step, QImage::Format_RGB888);

    return  imgLida;


}


void moduloCaptador::mostraThread(){



    std::cout <<"CAPTADOR"<<i<< " p! "<<std::endl;
    std::cout <<"CAPTADOR esta na thread " << QThread::currentThreadId()  <<std::endl;
    std::cout <<"CAPTADOR esta na thread " << QThread::currentThread()  <<std::endl;

}


void moduloCaptador::captando(){
   // tinicial = clock();
    //while(true){

    if(i< video_frames){//    if(chaveVideo){


         tinicial = clock();
        cap->set(CV_CAP_PROP_POS_FRAMES,i);
        //freeBytes.acquire();
        cap->read(frameLido);
       // usedBytes.release();
       // oVideoWriter.write(bufferMat[i % tamanhoBuffer]);

        cv::cvtColor(frameLido,frameDisplay,CV_BGR2RGB );
       // resultado.frameProces=frame_atual;
        //resultado.matProce= frameReduzido;
    //        resultado.background=frame;
        QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);
    //    resultProce= QPixmap::fromImage(imgLida);
    //    resultado.matProce.release();
    //    resultado.matProce= cv::Mat(imgLida.height(),imgLida.width(),CV_8UC3, const_cast<uchar*>(imgLida.bits()), imgLida.bytesPerLine()).clone();

       // frameLido.release();

        emit enviaImagem(imgLida, i);

        frameDisplay.release();



         i++;

//         cv::imshow("teste",frameLido.clone());
//         cv::waitKey(10);

//         if(i>= video_frames){

//             chaveVideo=false;

//         }


    }


}

void moduloCaptador::setCapOn(bool liga)
{

    chCaptador= liga;



}

void moduloCaptador::captandoRealTime()
{
    mostraThread();

    while(chLigaCaptador){

        if(chCaptador){

            tinicial = clock();

            cap->read(frameLido);


            frameDisplay=frameLido.clone();

            cv::cvtColor(frameLido,frameDisplay,CV_BGR2RGB );
            QImage imgEnviada2((uchar*) frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);//1



            tfinal=clock();

            tresposta=(float) (tfinal-tinicial)/CLOCKS_PER_SEC;



            emit enviaInformacoes(i,imgEnviada2,tresposta);

            //frameDisplay.release();

           //  i++;


             if((gravadorVideo->isOpened())&&(chGravador)){



                 //se chParadaNegada for falsa ele para por numero
                 //se chPardaNegada foi verdadeira ele só para
                 if(((i<frameTotal)||(chParadaNegada))){



                     matGravAlex= conQim2Mat(imgEnviada2);
                     gravadorVideo->write(matGravAlex);

                     tfinalCaptura = clock();
                      trespostaCaptura=(float) (tfinalCaptura-tinicial)/CLOCKS_PER_SEC;

                     emit enviaTempoGravacao(i,  trespostaCaptura);

                      joao.timerInicial.push_back(tinicial);
                      joao.timerFinal.push_back(tfinalCaptura);

                     //qDebug()<< numFra;
                     matGravAlex.release();

                     //gravadorVideo.release();
                 }else{



                     terminaGravador();




                 }



             }


            i++;


        }
        //if(cap.isOpened()){




       // }



    } //termina o while

}

void moduloCaptador::confGravador(QString nomeVideo1,int framesPerSecond1, int quntFrames, bool chFormaParada, int codificador1)
{
    // se chFormaParada for verdadeira ele nao para por quantidades de frame
    //se chFormaParada for flsa ele para por quantidade de frames
    //configura o gravador
    mostraThread();
    if(cap->isOpened()){

        gravadorVideo = new cv::VideoWriter();

        codec = codificador1; //CV_FOURCC('x', '2', '6', '4');

        //fps=30;
        nomeVideo= nomeVideo1; //"C:\\filmes\\posAntiVirus.avi";
        chParadaNegada=chFormaParada; //true se escolhida apenas parada manual
        frameTotal=quntFrames; //300;
         dWidth = cap->get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
         dHeight = cap->get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
         //fps = cap.get(CV_CAP_PROP_FPS);
         fps=framesPerSecond1;//30;
         cv::Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
         //codec = CV_FOURCC('x', 'v', 'i', 'd');
         gravadorVideo->open(nomeVideo.toStdString(),codec, fps ,frameSize,true);


         connect(this,SIGNAL(enviaInformacoes(int,QImage,float)),this,SLOT(gravando(int,QImage,float)));

    chGravadorVideoRelease= true;
    }

}

void moduloCaptador::terminaGravador()
{

    qDebug() <<"release0";
    disconnect(this,SIGNAL(enviaInformacoes(int,QImage,float)),this,SLOT(gravando(int,QImage,float)));
    qDebug() <<"release1";
    matGravAlex.release();
    qDebug() <<"release2";
    gravadorVideo->release();

    qDebug() <<"release3";
    chGravadorVideoRelease= false;
}

void moduloCaptador::setGraOn(bool liga)
{

    chGravador= liga;

}



void moduloCaptador::gravando(int numFra, QImage imAdquirida, float tempo)
{


// if((gravadorVideo->isOpened())&&(chGravador)){



//     //se chParadaNegada for falsa ele para por numero
//     //se chPardaNegada foi verdadeira ele só para
//     if(((numFra<frameTotal)||(chParadaNegada))){



//         matGravAlex= conQim2Mat(imAdquirida);
//         gravadorVideo->write(matGravAlex);

//         tfinalCaptura = clock();
//          trespostaCaptura=(float) (tfinalCaptura-tinicial)/CLOCKS_PER_SEC;

//         emit enviaTempoGravacao(numFra,  trespostaCaptura);

//          joao.timerInicial.push_back(tinicial);
//          joao.timerFinal.push_back(tfinalCaptura);

//         //qDebug()<< numFra;
//         matGravAlex.release();

//         //gravadorVideo.release();
//     }else{



//         terminaGravador();




//     }



// }



}

void moduloCaptador::iniciandoTimer(double fatorAcele){
    tempoLerFrame = new QTimer();
    connect(tempoLerFrame,SIGNAL(timeout()),this,SLOT(captando()));

    tempoLerFrame->start(((1000*fatorAcele)/video_fps));


}

void moduloCaptador::finalizandoTimer()
{
    tempoLerFrame->stop();
}

void moduloCaptador::setFrame(int numeroFrame)
{

    i=numeroFrame;
    cap->set(CV_CAP_PROP_POS_FRAMES,i);


}




void moduloCaptador::setCaptador(QString fonteVideo)
{
    //set captador para um video


    if(!fonteVideo.isNull())
    {
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


    cap->open(fonteVideoOpenCVString);
    getParamVideo();
    chaveVideo=true;


    }

}

void moduloCaptador::setCaptador(int disp)
{
    cap->open(disp);
}

void moduloCaptador::getParamVideo()
{
    if(cap->isOpened()){
        video_fps = cap->get(CV_CAP_PROP_FPS);                 //captura frames por segundo
        video_frames = cap->get(CV_CAP_PROP_FRAME_COUNT);      //captura quantidade de frames
        video_tempo = (float) video_frames/video_fps;                   //calcula tempo do video
        video_width = cap->get(CV_CAP_PROP_FRAME_WIDTH);       //captura largura do video
        video_heigth = cap->get(CV_CAP_PROP_FRAME_HEIGHT);     //captura altura do video

    }

}

void moduloCaptador::setCaptadorRange(int inicio, int fim)
{

    frInicio= inicio;
    frFim= fim;


//    for(int c1=inicio; c1< fim; c1++){

//        i=c1;
//        cap->set(CV_CAP_PROP_POS_FRAMES,i);
//        //freeBytes.acquire();
//        cap->read(frameLido);
//       // usedBytes.release();
//       // oVideoWriter.write(bufferMat[i % tamanhoBuffer]);

//        cv::cvtColor(frameLido,frameDisplay,CV_BGR2RGB );
//       // resultado.frameProces=frame_atual;
//        //resultado.matProce= frameReduzido;
//    //        resultado.background=frame;
//        QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);
//    //    resultProce= QPixmap::fromImage(imgLida);
//    //    resultado.matProce.release();
//    //    resultado.matProce= cv::Mat(imgLida.height(),imgLida.width(),CV_8UC3, const_cast<uchar*>(imgLida.bits()), imgLida.bytesPerLine()).clone();

//       // frameLido.release();

//        emit enviaImagem(imgLida, i);

//        frameDisplay.release();



//         i++;
//    }



}

void moduloCaptador::setCaptaVideoTodo()
{
    //for(int c1=frInicio; c1< frFim; c1++){

    if(chInicio){
        i=frInicio;
        chInicio=false;
    }
    tfinal = clock();

    joao.timerFinal.push_back(tfinal);


    if(i<=frFim){ //ultimo frame de análise

   // while(i< frFim){
        //i=c1;
        tinicial =clock();
        joao.timerInicial.push_back(tinicial);
        cap->set(CV_CAP_PROP_POS_FRAMES,i);
        //freeBytes.acquire();
        cap->read(frameLido);
       // usedBytes.release();
       // oVideoWriter.write(bufferMat[i % tamanhoBuffer]);

        cv::cvtColor(frameLido,frameDisplay,CV_BGR2RGB );
       // resultado.frameProces=frame_atual;
        //resultado.matProce= frameReduzido;
    //        resultado.background=frame;
        QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);
    //    resultProce= QPixmap::fromImage(imgLida);
    //    resultado.matProce.release();
    //    resultado.matProce= cv::Mat(imgLida.height(),imgLida.width(),CV_8UC3, const_cast<uchar*>(imgLida.bits()), imgLida.bytesPerLine()).clone();

       // frameLido.release();
        emit enviaInt(i);

        if(!imgLida.isNull()){

            emit enviaImagem(imgLida, i);
            i++;

        }





        //frameDisplay.release();

    }else{





    }
}


void moduloCaptador::setOnOff(bool gravandoRecebi)
{

    chCaptador=gravandoRecebi;



}

void moduloCaptador::captadorVideoRelease()
{
    if(cap->isOpened()){

        cap->release();

    }


}

void moduloCaptador::setParada(int frame, bool parada){

    frameTotal=frame;
    entrou1=parada;


}





