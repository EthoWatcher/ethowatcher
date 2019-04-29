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
#include "moduloprocessamento.h"
//#include "comum.h"
//namespace cv
//{
//    using std::vector;
//} //fazer a conversao da 2.4.11 para a 3.2

moduloProcessamento::moduloProcessamento(QObject *parent) : QObject(parent)
{
    a=0;
    entrou1=true;
    entrou2=true;
    entrada=true;
    novaOrigem.x=0;
    novaOrigem.y=0;


//    connect(this,SIGNAL(dadosMorfologicos(QImage,bool,double,double,double,float,float)),
//            this,SLOT(recebeDadosMorfologicos(QImage,bool,double,double,double,float,float)));
    chPrimeiroVideoTodo= true;

//    double antigaArea1;
//    cv::Point2f antigaMc1, antigaVtx[4];
//    float antigaAnguloVetor1, antigaMaiorTamanho1;
//    cv::Point antigaPontoLongeCentro, antigaPontoR, antigaPobjeto1,antigaPobjeto2;

    antigaArea1=0;//a area é zero;
    antigaMc1.x=0;
    antigaMc1.y=0;
    antigaAnguloVetor1=0;
    antigaMaiorTamanho1=0;
    antigaPontoLongeCentro.x=0;
    antigaPontoLongeCentro.y=0;
    antigaPontoR.x=0;
    antigaPontoR.y=0;
    antigaPobjeto1.x=0;
    antigaPobjeto1.y=0;
    antigaPobjeto2.x=0;
    antigaPobjeto2.y=0;
    for(int pa=0;pa<4;pa++){
        antigaVtx[pa].y=0;
        antigaVtx[pa].x=0;

    }



}

moduloProcessamento::~moduloProcessamento(){
qDebug() << "terminando com o moduloProcessador0";


qDebug() << "terminando com o moduloProcessador1";
    //delete this;

}

void moduloProcessamento::setParametrosVideo(double videoWidth, double videoHeig)
{
    video_heigth= videoHeig;  //240;
    video_width = videoWidth; //320;
}

void moduloProcessamento::setFrameFundo(QImage imaEntrada)
{

    qDebug() << "ola";
    cv::Mat matSaida;
//    resultado.frameProces=frame_atual;
//    resultado.matProce= frameReduzido;
////        resultado.background=frame;
//    QImage resultadoBackground((uchar*)resultado.matProce.data, resultado.matProce.cols, resultado.matProce.rows, resultado.matProce.step, QImage::Format_RGB888);
//    resultProce= QPixmap::fromImage(resultadoBackground);
//    resultado.matProce.release();
    matSaida= cv::Mat(imaEntrada.height(),imaEntrada.width(),CV_8UC3, const_cast<uchar*>(imaEntrada.bits()), imaEntrada.bytesPerLine()).clone();

    frameBackground = conQim2Mat(imaEntrada);

    //tesnte
    //frameBackground = matSaida.clone();
//    cv::imshow("framFun",matSaida);
//    cv::waitKey(20);
}


//ponto que esta configurando a camera virtual
void moduloProcessamento::confiCameraVir(double origX, double origY, double width, double height, bool chMove, bool chelaMove)
{
    //chMove é se esta ativa a janela movel
    //chElaMove é se a janela for movel se ela é fixa ou se ela move

    jaInte.origX=origX;
    jaInte.origY=origY;
    jaInte.width=width;
    jaInte.height=height;
    jaInte.chMobile=chelaMove;

    origiemRoi= cv::Point(jaInte.origX,jaInte.origY);
    //centro da tela
    double centroTelaX, centroTelaY;
    centroTelaX= origX+(width)/2;
    centroTelaY= origY+(height)/2;
    origiemObjeto= cv::Point(centroTelaX,centroTelaY);

//    entrada=false;

//    chaJanelaMovel= chMove;
    entrada=!chMove;//para ele entrar na janela movel //tem que trocar
}

void moduloProcessamento::setMaxVariacao(double max)
{
    maxVaria= max;
}

void moduloProcessamento::setAreaInteresse(double x, double y, double tamanho)
{
    qDebug() <<"o valor de x é " << x <<" o valor de Y é " << y <<
               "o valor de tamanho é" << tamanho;

     cv::Mat M( video_heigth, video_width, CV_8UC3, cv::Scalar(0,0,0));//cv::Mat::ones(cv::Size(video_width, video_heigth),CV_8UC3);
   frameAreaInteresse = M.clone();
     cv::ellipse(frameAreaInteresse,cv::Point(x+tamanho,y+tamanho),cv::Size(tamanho,tamanho),0,0,360,cv::Scalar(255,255,255),-1,8,0);

     cv::cvtColor( frameAreaInteresse.clone(), frameAreaInteresse, CV_RGB2GRAY );

     cv::threshold( frameAreaInteresse.clone(), frameAreaInteresseB, 100, 255,CV_THRESH_BINARY);


}
///
/// \brief moduloProcessamento::setAreaInteresse
/// \param x
/// \param y
/// \param height
/// \param width
///
void moduloProcessamento::setAreaInteresse(double x, double y, double height, double width){

    cv::Mat M( video_heigth, video_width, CV_8UC3, cv::Scalar(0,0,0));//cv::Mat::ones(cv::Size(video_width, video_heigth),CV_8UC3);

    frameAreaInteresse = M.clone();
//    qDebug() <<"o valor de x é " << x <<" o valor de Y é " << y <<
//               "o valor de HEIGHT é " << height << " e o valor de width é " <<  width;
    cv::rectangle(frameAreaInteresse,cv::Rect(x,y,width,height),cv::Scalar(255,255,255),-1,8,0);

    cv::cvtColor( frameAreaInteresse.clone(), frameAreaInteresse, CV_RGB2GRAY );

    cv::threshold( frameAreaInteresse.clone(), frameAreaInteresseB, 100, 255,CV_THRESH_BINARY);


}

void moduloProcessamento::setNomeFigura(QString nome)
{
    figuraNome = nome;
}

cv::Mat moduloProcessamento::conQim2Mat(QImage imaEntrada)
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

void moduloProcessamento::desenhaObjetoInterresse(cv::Mat frameErodido){

    cv::vector<cv::vector<cv::Point> > contours;
    cv::vector<cv::Vec4i> hierarchy;

    cv::findContours( frameErodido.clone(), contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    cv::Mat drawing = cv::Mat::zeros( frameErodido.size(), CV_8UC3 );
    cv::Mat frameContorno = cv::Mat::zeros( frameErodido.size(), CV_8UC3 );
    cv::Mat frameContornoBranco = cv::Mat::zeros( frameErodido.size(), CV_8UC3 );

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

        //cv::Mat frameAnimal2 = frameAnimal.clone();

    frameSegmentacao= drawing-frameContornoBranco+frameContorno;

    //cv::imshow("frame de erosao de interesse",frameSegmentacao.clone());
    cv::waitKey(15);

    }
}


void moduloProcessamento::processamentoDeVideoRealTime(int i, QImage imgRecegida, float temp)
{
    //fraRecebido= cv::Mat(imgRecegida.height(),imgRecegida.width(),CV_8UC3, const_cast<uchar*>(imgRecegida.bits()), imgRecegida.bytesPerLine()).clone();

    fraRecebido = conQim2Mat(imgRecegida);

//    if(!fraRecebido.empty()){
//        frameAnimal= fraRecebido.clone();

//        matOriginal= frameAnimal.clone();
//        //frameSubtracao= abs(frameAnimal-frameBackground);
////        //frameDisplay= frameSubtracao.clone();

////        cv::cvtColor( frameSubtracao.clone(), frameSubtracao_gray, CV_RGB2GRAY );
////        cv::threshold( frameSubtracao_gray, frameLimiarizacao, 10, 255,CV_THRESH_BINARY);

////       // resultado.frameProces=frame_atual;

//        //cv::cvtColor( frameSubtracao, frameSubtracao_gray, CV_RGB2GRAY );
//        //cv::threshold( frameSubtracao_gray, frameLimiarizacao, threshold_value, 255,CV_THRESH_BINARY);

//        //---------------------------------------------------------------------------------------------------
//        //------FrameErosao: Erosão da máscara do animal------------------------------------------------------
//       //  erosao=2; //0 até 10


//        processamentoMorfologico();

//       // cv::cvtColor(frameLimiarizacao.clone(),frameDisplay,CV_GRAY2BGR);
//        //resultado.matProce= frameReduzido;
//    //        resultado.background=frame;


//      // QImage imgLida((uchar*)frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);
//       // emit enviaQimage(imgLida);

//    }

       // fraRecebido.release();
    if(!fraRecebido.empty()){
        frameAnimal= fraRecebido.clone();

        matOriginal= frameAnimal.clone();


   // qDebug() << "entrou parte 2" << i;


        if(chPrimeiroVideoTodo){//primeira entrada

            connect(this,SIGNAL(desenhaFigura(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)),
                    this,SLOT(gravaDesenhoFigura(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)));

//            connect(this,SIGNAL(dadosMorfologicos(QImage,bool,double,double,double,float,float,float)),
//                    this,SLOT(recebeDadosMorfologicos(QImage,bool,double,double,double,float,float,float)));

            connect(this,SIGNAL(dadosMorfologicos(QImage,bool,double,double,double,float,float,float)),
                    this,SLOT(recebeDadosMorfologicos(QImage,bool,double,double,double,float,float,float)));

//            connect(this,SIGNAL(dadosMorfoCinematico(QImage,bool,double,double,double,float,float,double,double,double,double,double,double,bool)),
//                    this,SLOT(gravaDadosMorfoCinematico(QImage,bool,double,double,double,float,float,double,double,double,double,double,double,bool)));
            chPrimeiroVideoTodo=false;

            mc.x=jaInte.origX + jaInte.width/2 ;
            mc.y=jaInte.origY + jaInte.height/2;

            antigoMc = mc;
            processamentoMorfologico();
        }else{

            processamentoMorfologico();

        }

        emit fimProce();


}





    //cv::imshow("teste", fraRecebido.clone());
    //cv::waitKey(100);

//    matOriginal= fraRecebido.clone(); // bufferMat[a % tamanhoBuffer];

//    frameAnimal=matOriginal;

//  //if((frame_atual-(initialFrame-1)) >=centroMassa.count())
//   // {
//        //------subtração do plano de fundo-------------------------------------------------------------------

//        frameSubtracao= abs(frameAnimal-frameBackground);

//        //---------------------------------------------------------------------------------------------------------
//        //------FrameLimiarizcao: Máscara do animal (animal preto e fundo branco) - threshold --------------------
//       // threshold_value= 60; //0 até 255
//        cv::cvtColor( frameSubtracao, frameSubtracao_gray, CV_RGB2GRAY );
//        cv::threshold( frameSubtracao_gray, frameLimiarizacao, threshold_value, 255,CV_THRESH_BINARY);

//        //---------------------------------------------------------------------------------------------------
//        //------FrameErosao: Erosão da máscara do animal------------------------------------------------------
//       //  erosao=2; //0 até 10
//        cv::Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(2*erosao+1, 2*erosao+1),cv::Point(erosao, erosao));
//        cv::erode( frameLimiarizacao, frameErosao, element );

    //processamentoDeVideo();




}

void moduloProcessamento::processamentoDeVideoTodo( QImage imgRecegida,int i)
{

   // qDebug() << "entrou proce" << i;
    contGlobal=i;
    if(!imgRecegida.isNull()){

       // qDebug() << "entrou parte 0 " << i;
       // fraRecebido= cv::Mat(imgRecegida.height(),imgRecegida.width(),CV_8UC3, const_cast<uchar*>(imgRecegida.bits()), imgRecegida.bytesPerLine()).clone();

        fraRecebido= conQim2Mat(imgRecegida);
          //  qDebug() << "entrou parte 1" << i;

        if(!fraRecebido.empty()){
            frameAnimal= fraRecebido.clone();

            matOriginal= frameAnimal.clone();


       // qDebug() << "entrou parte 2" << i;


            if(chPrimeiroVideoTodo){//primeira entrada

                connect(this,SIGNAL(desenhaFigura(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)),
                        this,SLOT(gravaDesenhoFigura(QImage,bool,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double,double)));

                connect(this,SIGNAL(dadosMorfologicos(QImage,bool,double,double,double,float,float,float)),
                        this,SLOT(recebeDadosMorfologicos(QImage,bool,double,double,double,float,float,float)));

                connect(this,SIGNAL(dadosMorfoCinematico(QImage,bool,double,double,double,float,float,float,double,double,double,double,double,double,float,float ,bool)),
                        this,SLOT(gravaDadosMorfoCinematico(QImage,bool,double,double,double,float,float,float,double,double,double,double,double,double,float,float,bool)));
                chPrimeiroVideoTodo=false;

                mc.x=jaInte.origX + jaInte.width/2 ;
                mc.y=jaInte.origY + jaInte.height/2;

                antigoMc = mc;
                processamentoMorfologico();
            }else{

                processamentoMorfologico();

            }

//            emit fimProce();


    }

        //grava dado da imagem


    }else{
       qDebug() << "recebeu imagem nula" << i;
    }

    //qDebug() << "entrou saiu" << i;

}






void moduloProcessamento::mostraThread(){

   // std::cout <<"processamento "<<a<< " p! "<<std::endl;
    std::cout <<"preocessamento esta na thread " << QThread::currentThreadId()  <<std::endl;
   // std::cout <<"processamento esta na thread" << QThread::currentThread()  <<std::endl;


}


void moduloProcessamento::processamentoDeVideo(){

        //mostraThread();

       //semafaro
      // usedBytes.acquire();
       //lendo buffer
       matOriginal= fraRecebido; // bufferMat[a % tamanhoBuffer];
       //semafaro
      // freeBytes.release();

       //cv::imshow("ola",matOriginal);
      // cv::waitKey(10);

       //transformando em qimOriginal para enviar
       cv::cvtColor(matOriginal,matProcessado,CV_BGR2RGB);
       cv::cvtColor(matOriginal,matProcessado,CV_BGR2RGB);
       cv::resize(matProcessado,matProcessado, cv::Size(320,240),0,0,cv::INTER_LANCZOS4);
       QImage qimOriginal((uchar*) matProcessado.data, matProcessado.cols, matProcessado.rows, matProcessado.step, QImage::Format_RGB888);


       qDebug() << "o programa entrou aqui";

       //emit enviaQimage(qimOriginal);

       processamentoMorfologico();


        a++;

}


void moduloProcessamento::processamentoMorfologico(){


   // origiemRoi= cv::Point(0,0); //por enquano nao ta implmenteado
                                //o processamento de interesse
                                //entao a origem dele coincide com a origem
                                //da imagem

    //qDebug() << "processamento morfologico inicio" << contGlobal;

    if(entrou1){
    entrou1=false;

    tinicial= clock();

    }

    tinicial1 = clock();

    frameDoVideo=a+offset;

   // cv::Mat frameSubtracao;
   // cv::Mat frameSubtracao_gray;
   // cv::Mat frameLimiarizacao;
   // cv::Mat frameErosao;
    //cv::Mat frameSegmentacao;
   // cv::Mat frame_atual;
   // cv::Mat initialFrame;

    //video_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);       //captura largura do video
    //video_heigth = cap.get(CV_CAP_PROP_FRAME_HEIGHT);     //captura altura do video

    //frame_atual=matOriginal;
    //initialFrame=
    frameAnimal=matOriginal;

  //if((frame_atual-(initialFrame-1)) >=centroMassa.count())
   // {
        //------subtração do plano de fundo-------------------------------------------------------------------

        frameSubtracao= abs(frameAnimal-frameBackground);

        //---------------------------------------------------------------------------------------------------------
        //------FrameLimiarizcao: Máscara do animal (animal preto e fundo branco) - threshold --------------------
       // threshold_value= 60; //0 até 255
        cv::cvtColor( frameSubtracao.clone(), frameSubtracao_gray, CV_RGB2GRAY );
        cv::threshold( frameSubtracao_gray.clone(), frameLimiarizacao, threshold_value, 255,CV_THRESH_BINARY);

        cv::bitwise_and(frameAreaInteresseB.clone(),frameLimiarizacao.clone(),frameLimiarizacao);
//       frameLimiarizacao= cv::   abs(frameAreaInteresseB+frameLimiarizacao.clone());
//        qDebug() << reMorfo.area.size()%20;
//        if((reMorfo.area.size() % 30) == 0){
//            QString c;
//            c= figuraNome;

//            cv::imshow(c.toStdString()+"bir",frameAreaInteresse);
//            cv::imshow(c.toStdString(), frameLimiarizacao);
//            cv::waitKey(20);
//        }

//      qDebug()<< figuraNome << " na tarefa "<< QThread::currentThreadId() ;

        //---------------------------------------------------------------------------------------------------
        //------FrameErosao: Erosão da máscara do animal------------------------------------------------------
       //  erosao=2; //0 até 10
        cv::Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(2*erosao+1, 2*erosao+1),cv::Point(erosao, erosao));
        cv::erode( frameLimiarizacao.clone(), frameErosao, element );
        //qDebug() << erosao ;
//        cv::imshow("joao",frameSubtracao.clone());
//        cv::waitKey(15);


        //---------------------------------------------------------------------------------------------------
        //------Encontra e desenha contornos da máscara------------------------------------------------------------------------------

        cv::vector<cv::vector<cv::Point> > contours;
        cv::vector<cv::Vec4i> hierarchy;
        cv::Vec4f comprimento;
        QList <cv::Point2f> comprimentoAnimal;
        cv::RotatedRect caixaDelAnimal;




        if(entrada){ //if(entrada){
            imaInte = frameErosao; //se for escolhido sem janela movel de interesse
            origiemObjeto= mc;
           // entrada=false;
       // }
        }else{
            //se for escolhei janela movel o usuario pode escolher se é ela realmente movel
            //ou se ela é fixa

            if(jaInte.chMobile){

                imaInte = moveVirtCamera(frameErosao,cv::Point(antigoMc.x,antigoMc.y));

            }else{
                //se nao for cetado camera movel

                imaInte = moveVirtCamera(frameErosao,origiemObjeto);

            }


        }




        frameErosaoInterese=imaInte.clone();

              //funcao que server para colorir de azul o que o processamento esta considerando objeto
           desenhaObjetoInterresse(frameErosaoInterese.clone());



         cv::findContours( frameErosaoInterese, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
//
//        cv::findContours( frameErosao, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );






        cv::cvtColor(frameAnimal,frameDisplay1,CV_BGR2RGB );
       // cv::cvtColor(frameErosao,frameDisplay,CV_GRAY2RGB );
         cv::cvtColor(frameSubtracao,frameDisplay,CV_BGR2RGB );


         QImage imgEnviada2((uchar*) frameDisplay1.data, frameDisplay1.cols, frameDisplay1.rows, frameDisplay1.step, QImage::Format_RGB888);//1

        //cv::resize(frameDisplay,frameDisplay, cv::Size(320,240),0,0,cv::INTER_LANCZOS4);
         QImage imgEnviada((uchar*) frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);//1


        if(!contours.empty()){

            objetoEncontrado=true;
            int ponto=0;
            double maiorArea=0;
            area=0;

            //o objeto de interesse sempre é o objeto que tem o maior area
            //a area é definida pelo contorno

            for(int ka=0; ka<contours.size();ka++){

                area= cv::contourArea(contours[ka]); //encontra a area


                if(area>maiorArea){

                    ponto=ka;
                    maiorArea=area;
                }

            } //encontra a maior area de todos os contornos



            contornosRoi= contours[ponto];  
            area= cv::contourArea(contornosRoi); //encontra a area



                if(area!=0){

                     mu = cv::moments(contornosRoi);
                     mcRoi.x=mu.m10/mu.m00; //encontra o centro de massa em x
                     mcRoi.y= mu.m01/mu.m00;    //encontra o centro de massa em y

                     mc.x=mu.m10/mu.m00+ novaOrigem.x;// origiemRoi.x; //ponto de centro de massa da imagem original
                     mc.y= mu.m01/mu.m00+novaOrigem.y;//origiemRoi.y; //ponto do centro de massa da imagem origianl
                     caixaCirculo= cv::minAreaRect(contornosRoi);

//                     cv::Point2f vertices1[4];

//                     caixaCirculo.points(vertices1);

                     //qDebug()<< "o angulo da caixa" << caixaCirculo.angle;
                     //qDebug()<< frameDoVideo <<  " o height da caixa" << caixaCirculo.size.height;
                    // qDebug()<< frameDoVideo << " o width da caixa" << caixaCirculo.size.width;
                     //qDebug()<< frameDoVideo<<  " o angulo da caixa" << caixaCirculo.angle;
                   //  qDebug() << "mc x" << mc.x << " mc y " << mc.y;
                    // qDebug() << "mcRpo x" << mcRoi.x << " mcRoi y " << mcRoi.y;



                     antigoMc= mc;

                     //encontra os vertices da caixa que cabe na imagem
                     //relativo ao roi

//                     caixaCirculo.points(vtxRoi); //serve para desenhar
//                     for(int acerta=0;acerta<4;acerta++){
//                         vtx[acerta].x=0;
//                         vtx[acerta].y=0;
//                     }


//                     for(int pa=0;pa<4;pa++){
//                         deseOriginal.vtx[pa] = vtx[pa];
//                         deseRoi.vtx[pa] = vtxRoi[pa];

//                     }


         //          cv::line(animal,vtx[0],vtx[1],Scalar(0,255,0),1,100,0);
         //          cv::line(animal,vtx[1],vtx[2],Scalar(0,255,0),1,100,0);
         //          cv::line(animal,vtx[2],vtx[3],Scalar(0,255,0),1,100,0);
         //          cv::line(animal,vtx[3],vtx[0],Scalar(0,255,0),1,100,0);
                  // cv::rectangle(animal,caixaReta,Scalar(0,150,200),1,300,0);
                     //namedWindow("animalMarcado",CV_WINDOW_FREERATIO);
                     //imshow("animalMarcado",animal);
//                     cv::fitLine(cv::Mat(contours[ponto]),comprimento,CV_DIST_L2,0,0.01,0.01);
//                     int lefty = (-comprimento[2]*comprimento[1]/comprimento[0])+comprimento[3];
//                     int righty = ((frameErosao.cols-comprimento[2])*comprimento[1]/comprimento[0])+comprimento[3];

//                      caixaDelAnimal= cv::minAreaRect(cv::Mat(contours[ponto]));
//                      //caixaDelAnimal tem angle
//                                      //center x e y
//                                      //size height widht



                      caixaCirculo.points(vtxRoi);

                      for(int acerta=0;acerta<4;acerta++){
                          vtx[acerta].x=vtxRoi[acerta].x+novaOrigem.x;
                          vtx[acerta].y=vtxRoi[acerta].y+novaOrigem.y;
                      }


                      //marcela

//                      for( int i = 0; i < 4; i++ )
//                     {

//                          //entra origem 1, posicao 1 , origem 2,  posicao 2
//                          calculaIntersection(cv::Point(frameErosao.cols-1,righty),cv::Point(0,lefty),vtxRoi[i],vtxRoi[(i+1)%4]);

//                          if(intersection==true){

//                              comprimentoAnimal.insert(comprimentoAnimal.count(),pointIntersection);

//                            //comprimentoAnimal.insert(1,pointIntersection);

//                          }

//                      }




//                    if(intersection==true){

//                     if(comprimentoAnimal.count()!=2)
//                      {
//                         // d;
//                          dmax=0;
//                          //cv::Point2f p1, p2;
//                          for(int i=0; i<3;i++)
//                         {
//                             for(int j=i+1;j<4;j++)
//                             {
//                                d =   qSqrt( qPow( (comprimentoAnimal[i].x -comprimentoAnimal[j].x), 2 ) +
//                                            qPow( (comprimentoAnimal[i].y -comprimentoAnimal[j].y) ,2 ) );



//                                if(d>dmax)
//                                {
//                                    dmax=d;
//                                     p11=comprimentoAnimal[i]; //acha o ponto da extremidade
//                                     p21=comprimentoAnimal[j];
//                                }
//                                //
//                       }
//                     }

//                          comprimentoAnimal.removeOne(p11); //retira os pontos da extremidade
//                          comprimentoAnimal.removeOne(p21);

//                     }
//                    }









//                     //encontra o ponto mais longe do centro do objeto
//                     for(int k=0; k< contornosRoi.size(); k++){

//                        subX=(float) contornosRoi[k].x -mcRoi.x;
//                         subY=(float) contornosRoi[k].y -mcRoi.y;

//                         subX= subX * subX;
//                         subY= subY *subY;

//                         tamanho= qSqrt(subX+subY);

//                         if(tamanho>maiorTamanho2 ){

//                             maiorTamanho2= tamanho;
//                             ponto2=k;

//                         }

//                     }


//                     pontoLongeCentro= contornosRoi[ponto2];
//                     pontoLongeCentro.x= pontoLongeCentro.x + origiemRoi.x;
//                     pontoLongeCentro.y= pontoLongeCentro.y + origiemRoi.y;


//                   //maiorTamanho2 porque é o tamanho da

                    pontoR.x= mc.x+40;//+novaOrigem.x; //contornosRoi[ponto2].x;
                    pontoR.y= mc.y ;//+novaOrigem.y;
                     //pontoR.x= mcRoi.x+40+novaOrigem.x; //contornosRoi[ponto2].x;
                     //pontoR.y= mcRoi.y +novaOrigem.y;

//                     pobjeto1= comprimentoAnimal[0];
//                     pobjeto2= comprimentoAnimal[1];

                     pobjeto1.x= caixaCirculo.size.width+ novaOrigem.x;
                     pobjeto1.y=  caixaCirculo.size.height+ novaOrigem.y;

                     pobjeto2.x= caixaCirculo.size.width+ novaOrigem.x;
                     pobjeto2.y= caixaCirculo.size.height+ novaOrigem.y;

                     //pontoR é usado para desenhar a linha reta
//                     deseRoi.linhaAgulha= pontoR;
//                    pontoLongeCentro.x= comprimentoAnimal[1].x;
//                    pontoLongeCentro.y= comprimentoAnimal[1].y;


                pontoLongeCentro.x= pobjeto2.x+novaOrigem.x; //agulha
                pontoLongeCentro.y= pobjeto2.y+novaOrigem.y; //agulha

                     vetorMLC.x= pobjeto2.x-mc.x;  //comprimentoAnimal[1].x  ;    //mcRoi.x;
                     vetorMLC.y= pobjeto2.y- mc.y; //comprimentoAnimal[1].y ; // mcRoi.y;
                     vetorRC.x= pontoR.x- mc.x;
                     vetorRC.y= pontoR.y- mc.y;

                anguloVetor=(float)(vetorMLC.x*vetorRC.x) + (vetorMLC.y*vetorRC.y) ;
                anguloVetor= (float)anguloVetor/( qSqrt( qPow(vetorMLC.x ,2) + qPow(vetorMLC.y,2))*
                                           qSqrt( qPow(vetorRC.x,2) + qPow(vetorRC.y,2)));

                 anguloVetor= (float)qAcos(anguloVetor);
                 anguloVetor= (float) anguloVetor *180/M_PI;

                 //qDebug() <<"o angulo do vetor " << anguloVetor;

                 //qDebug()<<"o anguelo " << anguloVetor;

//                 if(contornosRoi[ponto2].y>mcRoi.y){
//                     anguloVetor= 360-anguloVetor; //angulo do animal

//                 }


//                 //encontra a o tamanho das retas da caixa inclinada


//                 for(int m=0; m< 4; m++)

//                 {
//                     if(m<3){
//                         tamanhoRetaCaixa[m]= qSqrt( qPow(vtxRoi[m].x - vtxRoi[m+1].x,2) + qPow(vtxRoi[m].y - vtxRoi[m+1].y,2) );
//                     }else{
//                         tamanhoRetaCaixa[m]= qSqrt( qPow(vtxRoi[3].x - vtxRoi[0].x,2) + qPow(vtxRoi[3].y - vtxRoi[0].y,2) );
//                     }



//                 }
//                //              float tamanhoRetaCaixa= qSqrt( qPow(vtxRoi[0].x - vtxRoi[1].x,2) + qPow(vtxRoi[0].y - vtxRoi[1].y,2) );
//                //              float tamanhoRetaCaixa2= qSqrt( qPow(vtxRoi[1].x - vtxRoi[2].x,2) + qPow(vtxRoi[1].y - vtxRoi[2].y,2) );

//                              //enconta a posicao da menor reta da caixa inclinada

//                 float menorRetaDaCaixaInclinado=100000;

//                 int posicaoDaMenorRetaDacaixa=0;

//                 for(int tam=0; tam<4;tam++){

//                     if(tamanhoRetaCaixa[tam]<menorRetaDaCaixaInclinado){

//                         menorRetaDaCaixaInclinado= tamanhoRetaCaixa[tam];

//                         posicaoDaMenorRetaDacaixa=tam;

//                     }


//                 }

//                              //encontra a inclinação dessa reta

//                 if(posicaoDaMenorRetaDacaixa<3){

//                     incliCaixa= inclinacaoReta(vtxRoi[posicaoDaMenorRetaDacaixa].x , vtxRoi[posicaoDaMenorRetaDacaixa+1].x,

//                             vtxRoi[posicaoDaMenorRetaDacaixa].y , vtxRoi[posicaoDaMenorRetaDacaixa+1].y  );


//                 }else{

//                     incliCaixa= inclinacaoReta(vtxRoi[3].x , vtxRoi[0].x,
//                             vtxRoi[3].y , vtxRoi[0].y  ); //radianos
//                 }





//                //encontra o ponto mais distante do ponto mais distante do centro
//                        for(int k=0; k< contornosRoi.size(); k++){

//                           subX=(float) contornosRoi[k].x -contornosRoi[ponto2].x;
//                            subY=(float) contornosRoi[k].y -contornosRoi[ponto2].y;

//                            subX= subX * subX;
//                            subY= subY *subY;

//                            tamanho= qSqrt(subX+subY);

//                            inclinacaoRetaAnimal=inclinacaoReta(contornosRoi[k].x, contornosRoi[ponto2].x,
//                                                               contornosRoi[k].y, contornosRoi[ponto2].y );

//                           // inclinacaoRetaAnimal=inclinacaoReta(contornosRoi[ponto2].x, contornosRoi[k].x,
//                            //                                   contornosRoi[ponto2].y,contornosRoi[k].y  );

//                                diferAngulo= diferencaDeAngulo(incliCaixa, inclinacaoRetaAnimal); //entre duas retas
//                            if((tamanho>maiorTamanho1)&&(diferAngulo>(90-tolerancia)) &&(diferAngulo<(90+tolerancia) )){
//                                maiorTamanho1= tamanho;
//                                ponto1=k;
//                                mrAnimal = inclinacaoRetaAnimal * 180/M_PI;

//                            }
//                        }

                 subX=(float) pobjeto2.x -pobjeto1.x;
                 subY=(float) pobjeto2.y -pobjeto1.y;

                 subX= subX * subX;
                 subY= subY *subY;


//                 double tamanhoObjeto=0;

//                 tamanhoObjeto= qPow( pobjeto2.x-pobjeto1.x,2) + qPow( pobjeto2.y-dados->desenhoSaida.pob1Y[i],2);
//                 tamanhoObjeto = qSqrt(tamanhoObjeto);

//                 stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));
                 //                            tamanho=

                 maiorTamanho1 = qSqrt(subX+subY);

               //  qDebug() << "tamanho do objeto " << maiorTamanho1;

                    //enciando o sinal para outro lugar
                     //qDebug() <<maiorArea;

//                 qDebug()<< "o height da caixa" << caixaCirculo.size.height;
//                 qDebug()<< "o width da caixa" << caixaCirculo.size.width;
//                 qDebug()<< "o angulo da caixa" << caixaCirculo.angle;

//                        emit dadosMorfologicos(imgEnviada,objetoEncontrado,area,
//                                            (double) mc.x, (double) mc.y,
//                                            anguloVetor,maiorTamanho1);

                 //qDebug() << "emitido os dados morfológicos";
                       emit dadosMorfologicos(imgEnviada,objetoEncontrado,area,
                                             (double) mc.x, (double) mc.y,
                                             caixaCirculo.angle,caixaCirculo.size.height,caixaCirculo.size.width);


                        emit desenhaFigura(imgEnviada2,true,mc.x,mc.y,
                                            pontoLongeCentro.x,  pontoLongeCentro.y,
                                           pontoR.x,pontoR.y,
                                           pobjeto1.x,pobjeto1.y, pobjeto2.x, pobjeto2.y,
                                           vtx[0].x,vtx[0].y,vtx[1].x,vtx[1].y,
                                            vtx[2].x,vtx[2].y,vtx[3].x,vtx[3].y);


                 antigaArea1=area;//a area é zero;
                 antigaMc1.x=mc.x;
                 antigaMc1.y=mc.y;
                 antigaAnguloVetor1=caixaCirculo.angle;
                 //float antigaAltur, antigaLargur;
                 antigaAltur=caixaCirculo.size.height;
                 antigaLargur=caixaCirculo.size.width;


                 antigaMaiorTamanho1=maiorTamanho1;
                 antigaPontoLongeCentro.x=pontoLongeCentro.x;
                 antigaPontoLongeCentro.y=pontoLongeCentro.y;
                 antigaPontoR.x=pontoR.x;
                 antigaPontoR.y=pontoR.y;
                 antigaPobjeto1.x=pobjeto1.x;
                 antigaPobjeto1.y=pobjeto1.y;
                 antigaPobjeto2.x=pobjeto2.x;
                 antigaPobjeto2.y=pobjeto2.y;
                 for(int pa=0;pa<4;pa++){
                     antigaVtx[pa].y=vtx[pa].y;
                     antigaVtx[pa].x=vtx[pa].x;

                 }






                 } //fim de area diferente de zero


                if(area==0){

                    objetoEncontrado=false;


                    emit dadosMorfologicos(imgEnviada,objetoEncontrado,area,
                                          (double) mc.x, (double) mc.y,
                                          caixaCirculo.angle,antigaAltur,antigaLargur);


                    emit desenhaFigura(imgEnviada2,false,antigaMc1.x,antigaMc1.y,
                                       antigaPontoLongeCentro.x,antigaPontoLongeCentro.y,
                                       antigaPontoR.x,antigaPontoR.y,
                                       antigaPobjeto1.x,antigaPobjeto1.y, antigaPobjeto2.x, antigaPobjeto2.y,
                                       antigaVtx[0].x,antigaVtx[0].y,antigaVtx[1].x,antigaVtx[1].y,
                                        antigaVtx[2].x,antigaVtx[2].y,antigaVtx[3].x,antigaVtx[3].y);

                }





        }else{ //se nao encontra objeto nenhum ou seja
                //se não há contornos

//            objetoEncontrado=false;
//            double antigaArea1;
//            cv::Point2f antigaMc1, antigaVtx[4];
//            float antigaAnguloVetor1, antigaMaiorTamanho1;
//            cv::Point antigaPontoLongeCentro, antigaPontoR, antigaPobjeto1,antigaPobjeto2;

            objetoEncontrado=false;
//            area=0;//a area é zero;
//            mc.x=0;
//            mc.y=0;
//            anguloVetor=0;
//            maiorTamanho1=0;
//            pontoLongeCentro.x=0;
//            pontoLongeCentro.y=0;
//            pontoR.x=0;
//            pontoR.y=0;
//            pobjeto1.x=0;
//            pobjeto1.y=0;
//            pobjeto2.x=0;
//            pobjeto2.y=0;
//            for(int pa=0;pa<4;pa++){
//                vtx[pa].y=0;
//                vtx[pa].x=0;

//            }

//            antigaArea1=area;//a area é zero;
//            antigaMc1.x=mc.x;
//            antigaMc1.y=mc.y;
//            antigaAnguloVetor1=anguloVetor;
//            antigaMaiorTamanho1=maiorTamanho1;
//            antigaPontoLongeCentro.x=pontoLongeCentro.x;
//            antigaPontoLongeCentro.y=pontoLongeCentro.y;
//            antigaPontoR.x=pontoR.x;
//            antigaPontoR.y=pontoR.y;
//            antigaPobjeto1.x=pobjeto1.x;
//            antigaPobjeto1.y=pobjeto1.y;
//            antigaPobjeto2.x=pobjeto2.x;
//            antigaPobjeto2.y=pobjeto2.y;
//            for(int pa=0;pa<4;pa++){
//                antigaVtx[pa].y=vtx[pa].y;
//                antigaVtx[pa].x=vtx[pa].x;

//            }

            emit dadosMorfologicos(imgEnviada,objetoEncontrado,area,
                                  (double) mc.x, (double) mc.y,
                                  caixaCirculo.angle,antigaAltur,antigaLargur);
//            emit dadosMorfologicos(imgEnviada,objetoEncontrado,antigaArea1,
//                                   (double)antigaMc1.x,(double)antigaMc1.y,
//                                   antigaAnguloVetor1,antigaMaiorTamanho1);


            emit desenhaFigura(imgEnviada2,false,antigaMc1.x,antigaMc1.y,
                               antigaPontoLongeCentro.x,antigaPontoLongeCentro.y,
                               antigaPontoR.x,antigaPontoR.y,
                               antigaPobjeto1.x,antigaPobjeto1.y, antigaPobjeto2.x, antigaPobjeto2.y,
                               antigaVtx[0].x,antigaVtx[0].y,antigaVtx[1].x,antigaVtx[1].y,
                                antigaVtx[2].x,antigaVtx[2].y,antigaVtx[3].x,antigaVtx[3].y);


            //cv::cvtColor(frameAnimal,frameDisplay,CV_BGR2RGB );frameSubtracao
//            cv::cvtColor(frameSubtracao,frameDisplay,CV_BGR2RGB );
//           // cv::cvtColor(frameErosao,frameDisplay,CV_GRAY2RGB );
//            QImage imgEnviada2((uchar*) frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);//1

//            cv::resize(frameDisplay,frameDisplay, cv::Size(320,240),0,0,cv::INTER_LANCZOS4);
//             QImage imgEnviada((uchar*) frameDisplay.data, frameDisplay.cols, frameDisplay.rows, frameDisplay.step, QImage::Format_RGB888);//1

//            emit dadosMorfologicos(imgEnviada,objetoEncontrado,area,
//                                   (double)mc.x,(double)mc.y,
//                                   anguloVetor,maiorTamanho1);
//             emit desenhaFigura(imgEnviada2,false,mc.x,mc.y,
//                                pontoLongeCentro.x,pontoLongeCentro.y,
//                                pontoR.x,pontoR.y,
//                                pobjeto1.x,pobjeto1.y, pobjeto2.x, pobjeto2.y,
//                                vtx[0].x,vtx[0].y,vtx[1].x,vtx[1].y,
//                                 vtx[2].x,vtx[2].y,vtx[3].x,vtx[3].y);

        }


//        imaInte = moveVirtCamera(frameLimiarizacao,cv::Point(0,0));

        cv::cvtColor(imaInte,imaInteDisplay,CV_GRAY2RGB );

         cv::resize(imaInteDisplay,imaInteDisplay, cv::Size(320,240),0,0,cv::INTER_LANCZOS4);
         QImage imgEnviada3((uchar*) imaInteDisplay.data, imaInteDisplay.cols, imaInteDisplay.rows, imaInteDisplay.step, QImage::Format_RGB888);//1

         emit roiImage(imgEnviada3);
         tfinal1 =clock();

         joao.timerInicial.push_back(tinicial1);
         joao.timerFinal.push_back(tfinal1);

   // qDebug() << "processamento morfologico fim" << contGlobal;

}

void moduloProcessamento::gravaDesenhoFigura(QImage imaPro, bool desenha, double cmX, double cmY, double pMDCX, double pMDCY, double agulhX, double agulhY, double pob1X, double pob1Y, double pob2X, double pob2Y, double vtxX1, double vtxY1, double vtxX2, double vtxY2, double vtxX3, double vtxY3, double vtxX4, double vtxY4)
{


//            double cmX,
//            double cmY,
//            double pMDCX,
//            double pMDCY,
//            double agulhX,
//            double agulhY,
//            double pob1X,
//            double pob1Y,
//            double pob2X,
//            double pob2Y,
//            double vtxX1,
//            double vtxY1,
//            double vtxX2,
//            double vtxY2,
//            double vtxX3,
//            double vtxY3,
//            double vtxX4,
//            double vtxY4

    desenhoSaida.cmX.push_back(cmX);
    desenhoSaida.cmY.push_back(cmY);
    desenhoSaida.pMDCX.push_back(pMDCX);
    desenhoSaida.pMDCY.push_back(pMDCY);
    desenhoSaida.agulhX.push_back(agulhX);
    desenhoSaida.agulhY.push_back(agulhY);
    desenhoSaida.pob1X.push_back(pob1X); //tamanho do objeto
    desenhoSaida.pob1Y.push_back(pob1Y); //tamanho do objeto
    desenhoSaida.pob2X.push_back(pob2X);
    desenhoSaida.pob2Y.push_back(pob2Y);
    desenhoSaida.vtxX1.push_back(vtxX1);
    desenhoSaida.vtxY1.push_back(vtxY1);
    desenhoSaida.vtxX2.push_back(vtxX2);
    desenhoSaida.vtxY2.push_back(vtxY2);
    desenhoSaida.vtxX3.push_back(vtxX3);
    desenhoSaida.vtxY3.push_back(vtxY3);
    desenhoSaida.vtxX4.push_back(vtxX4);
    desenhoSaida.vtxY4.push_back(vtxY4);



}

void moduloProcessamento::gravaDadosMorfoCinematico(QImage imaProc, bool objeto, double area1, double mcX, double mcY, float anguloObjeto, float alturaObjeto, float larguraObjeto, double varAngular, double varArea, double VarCenX, double VarCenY, double VarDistancia, double VarOBjeto, float VarAltura, float VarLargura, bool ruidoOn)
{
//    QImage imaProc,
//            bool objeto, //se o objeto foi encontrado

//            double area1,
//            double mcX,
//            double mcY,
//            float anguloObjeto,
//            float tamanhoObjeto,
//            double varAngular,
//            double varArea,
//            double VarCenX,
//            double VarCenY,
//            double VarDistancia,
//            double VarOBjeto;


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


    emit fimProce();







}//fim da ufnção de processamento


void moduloProcessamento::setBackground(cv::Mat planoFundo){

    //funcao que funciona

    frameBackground = planoFundo;

    //observar tem que debugar
    video_heigth= frameBackground.rows;
    video_width = frameBackground.cols;

//    cv::imshow("lalal", frameBackground);
//    cv::waitKey(20);


}


void moduloProcessamento::setCalibracao(int threshold, int erosaoCa){

    threshold_value = threshold;
    erosao= erosaoCa;

}


void moduloProcessamento::calculaIntersection(cv::Point2f o1, cv::Point2f p1, cv::Point2f o2, cv::Point2f p2)
{
    cv::Point2f x = o2 - o1;
    cv::Point2f d1 = p1 - o1;
    cv::Point2f d2 = p2 - o2;

    float cross = d1.x*d2.y - d1.y*d2.x;
    if (abs(cross) < /*EPS*/1e-8)
    {
        intersection=false;
        return;
    }

    double t1 = (x.x * d2.y - x.y * d2.x)/cross;
    pointIntersection = o1 + d1 * t1;
    intersection=true;
}



float moduloProcessamento::inclinacaoReta(float p1x, float p1y, float p2x, float p2y)
{
    float k1 = p1y - p2y;
    float k2 = p2x - p1x;
    float mr = k1/(-1*k2);



    //matrix
    //x y 1 ! x y !
    //a b 1 ! a b !
    //c d 1 ! c d !
    //k1 = b - d
    //k2= c-a
    //k3 = ad-cb
    // mr= k1/(-1* k2)

    //tg teta = (mr-ms)/(1+mr*ms)

    return mr;
}

float moduloProcessamento::diferencaDeAngulo(float mr, float ms)
{
    float teta = (mr-ms);
    teta= teta/(1+(mr*ms));
     teta = teta*teta;
     teta = qSqrt(teta);
     teta= qAtan(teta); //aqui esta tudo em radianos
     teta= teta* 180/M_PI; //converte para graus
    return teta;
}

void moduloProcessamento::desligando()
{

    delete this;
}

cv::Mat moduloProcessamento::setCameraVirtual(cv::Point centroObjetoInicial, cv::Point origenRoi, int alturaRoi, int larguraRoi)
{





}

cv::Mat moduloProcessamento::moveVirtCamera(cv::Mat imagemInteresse, cv::Point centroMassa)
{


    //na primeira vez que roda centro de massa é igual
    // planoFundo = imagem ;//imread("fundoFinalCerto.png"); //entrada
    cv:: Mat roiImage; //saida

    cv::Point roiPoint,objPoint,objPointNovo, variacaoPonto, novoPontoRoi;
    double height, widht;


    bool cameraDesajustouX0,cameraDesajustouXMax;
    cameraDesajustouX0=false;
     cameraDesajustouXMax=false;


    roiPoint= origiemRoi;//cv::Point(0,0); //ponto de origem do roi point ponto de origem da imagem de interesse
    objPoint= origiemObjeto;//cv::Point(148,127);  //o ponto original do objeto
    height=jaInte.height;//150;   //o tamanho da tela em y
    widht=jaInte.width;//150;     //o amanhao da tela em x
//    roiPoint.x=100;    //ponto do retangulo
//    roiPoint.y=100; //ponto do retangulo
//    objPoint.x=100; //ponto do objeto inial
//    objPoint.y=100; //ponto do objeto
   // Mat animal= imread("animalFinalCerto.png");
    //Mat animal= imread("animalTeste1.png");
   // Mat animal= imread("circunferencia.png");
 //   int tolerancia=25; //tolerancia de erro de graus
 //   //namedWindow("fundo",CV_WINDOW_FREERATIO);
 //   //imshow("fundo",planoFundo);

//    //namedWindow("animal",CV_WINDOW_FREERATIO);
//    //imshow("animal",animal);
     cv::Rect retangulo(roiPoint.x,roiPoint.y,widht,height);

   // rectangle(planoFundo,retangulo,Scalar(0,0,0),-1,8,0);
  //  //imshow("fundo",planoFundo);
//    //namedWindow("fundo1",CV_WINDOW_FULLSCREEN);
//    //namedWindow("roimovel",CV_WINDOW_FULLSCREEN);
  //o x é a posicao inicial do retangulo do eixo x; //como se fossem a nova origem
  //o y a posição inicial do retangulo do eixo y; //como se foce a origen
  //rect(x, y, width, height)

//   roiPoint.x=0;    //ponto do retangulo
//   roiPoint.y=500; //ponto do retangulo
//   objPoint.x=100; //ponto do objeto inial
//   objPoint.y=500; //ponto do objeto

     //para configurar corretamente precisa que venha da calibração
    //o ponto inical do roi
    //o width e o heigth do roi
    //o tamanho da tela
    //o ponto inicial do objeto de interesse

//   roiPoint.x=100;    //ponto do retangulo
//   roiPoint.y=100; //ponto do retangulo
//   objPoint.x=100; //ponto do objeto inial
//   objPoint.y=100; //ponto do objeto

//   distInicial.x=  objPoint.x -roiPoint.x; //distancia entre a borda da camera e o objeto de itnerese
//   distInicial.y=  objPoint.y -roiPoint.y;  //distancia entre a borda da demcera e o objeto de interese
//   distInicial.x= qSqrt( qPow(distInicial.x,2)); //modulo
//   distInicial.y= qSqrt( qPow(distInicial.y,2)); //modulo
    cv::Mat fundoDesenho;
    fundoDesenho = imagemInteresse;


    objPointNovo= centroMassa;

    //<algoritimo de movimento de roi inicio

   //primeira condição é que esse valores nunca podem ser negativo
   variacaoPonto.x=objPointNovo.x-objPoint.x; //ponto novo - ponto objeto inicial
   variacaoPonto.y=objPointNovo.y-objPoint.y;


   novoPontoRoi.x=roiPoint.x+ variacaoPonto.x; //ponto roi novo é o ponto inicial mais variacao
   novoPontoRoi.y=roiPoint.y+ variacaoPonto.y;

   if(novoPontoRoi.x<=0){

       novoPontoRoi.x=0;

       cameraDesajustouX0=true; //camera desajustou em 0;

   }else if((novoPontoRoi.x+ widht)>=video_width){


       novoPontoRoi.x=video_width-widht;
       cameraDesajustouXMax=true;



   }

   if(novoPontoRoi.y<=0){

       novoPontoRoi.y=0;

       cameraDesajustouX0=true; //camera desajustou em 0;

   }else if((novoPontoRoi.y+  height)>=video_heigth){ //retangulo é o do roi

       novoPontoRoi.y=video_heigth- height;             //planoFundo.cols é o tamanho da iamgem

       cameraDesajustouXMax=true;


   }



   roiImage= fundoDesenho(cv::Rect(novoPontoRoi.x,novoPontoRoi.y,widht,height));

   novaOrigem=novoPontoRoi;

//   cv::imshow( "Display window", roiImage);                   // Show our image inside it.

//   cv::waitKey(10);

    //imshow("saida do mov camera",roiImage);

 //  Mat enviaRoi;

 ////  cvtColor(roiImage,enviaRoi);



   return roiImage;






}

void moduloProcessamento::recebeDadosMorfologicos(QImage imReceb, bool objetoEnco, double areaRecebida, double centroideX, double centroideY, float angObjeto, float altura, float largura)
{
//qDebug() << "recebe os dados morfológicos";
//    qDebug() << tamObjet

    //maxVaria=1000;
    if(primeiroFrame){

        //logica para o primeiro frame a variação é igual a zero
           //deslocamento
           //variação angular
           //variação de tamnho
           //variação de area

        if(objetoEnco){

            antigoArea=areaRecebida;
            antigoCentroideX=centroideX;
            antigoCentroideY=centroideY;
            antigoAnguloObj=angObjeto;
            //antigoTamanhoObj=tamObjet;
            antigoAltura=altura;
            antigoLargura=largura;

            //aqui emite a variação igual a zero

            primeiroFrame=false;

        }
        //emite zero de variação

        //qDebug() << "emite os dadosMorfoCinematicos";

        emit dadosMorfoCinematico( imReceb , objetoEnco ,areaRecebida, //area
                                  centroideX, centroideY,
                                  angObjeto,
                                  altura,
                                  largura,
                                  0, 0,
                                  0, 0, 0, 0,0, 0, false); //centroide



    }else{ //se nao é o primeiro frame

        if(objetoEnco){

            novoArea=areaRecebida;
            novoCentroideX=centroideX;
            novoCentroideY=centroideY;
            novoAngObj=angObjeto;
            //novoTamanhoObj=tamObjet;
            novoAltura=altura;
            novoLargura=largura;

            moduloVaria= qSqrt( qPow(novoCentroideX - antigoCentroideX,2)+ qPow(novoCentroideY- antigoCentroideY,2) );

            if((maxVaria) < (moduloVaria) ){ //foi trocado o sinal para menor
            //se tudo ocorreu corretamente

                novaVarAngular= novoAngObj- antigoAnguloObj;
                //novaVarTamanhoObj= novoTamanhoObj - antigoTamanhoObj;
//                float novaVarAltura,novaVarLargura;

                novaVarAltura=novoAltura - antigoAltura;
                novaVarLargura=novoLargura - antigoLargura;


                novaVarArea= novoArea- antigoArea;
                novaVarCenX=novoCentroideX - antigoCentroideX;
                novaVarCenY=novoCentroideY - antigoCentroideY;

                novaVarDistancia =qSqrt( qPow(novaVarCenY,2)+ qPow(novaVarCenX,2)  );





                antigoArea=novoArea;
                antigoCentroideX=novoCentroideX;
                antigoCentroideY=novoCentroideY;
                antigoAnguloObj=novoAngObj;
                //antigoTamanhoObj=novoTamanhoObj;
                antigoAltura=novoAltura;
                antigoLargura=novoLargura;


                //atualiza o antigo
//                antigaVarAngular = novaVarAngular;
//                antigaVarArea=novaVarArea;
//                antigaVarCenY=novaVarCenY;
//                antigaVarCenX= novaVarCenX;
//                antigaVarDistancia=novaVarDistancia;
               // qDebug() << "emite os dadosMorfoCinematicos";
                emit dadosMorfoCinematico( imReceb , objetoEnco ,areaRecebida, //area
                                          centroideX, centroideY,
                                          angObjeto,
                                          altura,
                                           largura,
                                          novaVarAngular, novaVarArea,
                                          novaVarCenX, novaVarCenY, novaVarDistancia, novaVarTamanhoObj,novaVarAltura,novaVarLargura, false); //centroide
                                                                                                            //fasle o ruido nao aconteceu


            }else{
                //se aconteceu o ruido
                //ele coloca os pontos anteriores
                //aqui apenas emite os valores antigos porque houve o ruido
                //emite os valores antigos
              //  qDebug() << "emite os dadosMorfoCinematicos";
               emit dadosMorfoCinematico( imReceb , objetoEnco ,antigoArea, //area
                                          antigoCentroideX, antigoCentroideY,
                                          antigoAnguloObj,
                                          antigoAltura,
                                          antigoLargura,
                                          0, 0,
                                          0, 0, 0, 0,0, 0, true); //centroide



                qDebug() << "passou da maxima variacao" << contMorfo;
            }



        }else{ //se o objeto nao ebncontrado

            //emite os valores antigos

           // qDebug() << "emite os dadosMorfoCinematicos";
            emit dadosMorfoCinematico( imReceb , objetoEnco ,antigoArea, //area
                                      antigoCentroideX, antigoCentroideY,
                                      antigoAnguloObj,
                                      antigoAltura,
                                       antigoLargura,
                                      0, 0,
                                      0, 0, 0, 0, 0, 0, true); //centroide

            qDebug() << "objeto nao encotrnado" << contMorfo;


        }


    }

   // if(contMorfo%40){
 //       qDebug() << contGlobal << " da tarefa " << QThread::currentThreadId();
        emit enviaMorfInt(contGlobal);
        //qDebug() <<contGlobal;
       // emit enviaMorfInt(contMorfo);
  //  }


    contMorfo++;



}
