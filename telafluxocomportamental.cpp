#include "telafluxocomportamental.h"
#include "ui_telafluxocomportamental.h"

telaFluxoComportamental::telaFluxoComportamental(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaFluxoComportamental)
{
    ui->setupUi(this);
    catalagoLido = new catalago();
    videoLido= new dadosVideo();
    etografiaLida= new analiseEtografica();
    chEtr=true;
    chTCCon = false;
}

telaFluxoComportamental::~telaFluxoComportamental()
{
    delete ui;
}

void telaFluxoComportamental::on_pbAnaliseFile_clicked()
{
    fonteCaminhoArquivo = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://EthoWatcherOS",
                "Ethowatcher Files (*.etoxml )"
                );



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

       // totalizacoesEtografia();


        }


        geraTabela(0);
//        geraTabela(1);
//        geraTabela(2);
//        geraTabela(3);
        //gera os botoes



    }







}

void telaFluxoComportamental::lerTimeXml(int qualLer)
{
   // qDebug()<< qualLer << " oi 0 ";
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

                if(entrou){
                    entrou=false;

                }else{
                    entrou=true;
                }
               // entrou=~entrou;
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
                        videoLido->frameInicial= conversor.toInt();
                    }}
                if(xmlReader.name()== "frameProces"){
                    QString conversor= xmlReader.readElementText();
                    if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
                        videoLido->frameProce= conversor.toInt();
                    }}
                if(xmlReader.name()== "frameFinal"){
                    QString conversor= xmlReader.readElementText();
                    if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
                        videoLido->frameFinal= conversor.toInt();
                    }}
                if(xmlReader.name()== "fps"){
                    QString conversor= xmlReader.readElementText();
                    if(!conversor.isEmpty()){//ele acaba entrando daus vez pra cada tag
                        videoLido->fps= conversor.toInt();
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

    output.close();
   // qDebug()<< qualLer << " oi 1 ";

}

void telaFluxoComportamental::lerETOXML(QString nomeArquivo)
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

        if((streamReader.name() == "dadosVideoAnalisado")||(videoLido->controle)){


          if(streamReader.name() == "nomeVxml"){

              videoLido->nome= streamReader.readElementText();

          }

          if(streamReader.name() == "frameInicial"){


              videoLido->frameInicial= streamReader.readElementText().toInt();

          }

          if(streamReader.name() == "frameProces"){


              videoLido->frameProce= streamReader.readElementText().toInt();

          }

          if(streamReader.name() == "frameFinal"){
           videoLido->frameFinal= streamReader.readElementText().toInt();

            //videoLido->controle=false;
        }

          if(streamReader.name() == "fps"){
           videoLido->fps= streamReader.readElementText().toInt();

            videoLido->controle=false;
        }

        }

    }



    OutEtografia.close();
}

void telaFluxoComportamental::geraTabela(int numero)
{




//    //de dentro pra fora


   //wid1 = new QWidget();






//    wid1->setMinimumHeight(20);
//    wid1->setMinimumWidth(100);

//    vetorListaWid0.push_back(wid1);



    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){


        chek = new QCheckBox(catalagoLido->nome[ka]);
//        label2 = new QLabel(catalagoLido->nome[ka]);
//        label2->setMinimumHeight(20);
//        label2->setMinimumWidth(100);
                listChek.push_back(chek);

      //  listlblCategorias.push_back(label2);


    }

    layout3 = new QVBoxLayout(ui->widCatego);

    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){

       // label2 = new QLabel(catalagoLido->nome[ka]);

        layout3->addWidget(listChek[ka]);


    }



//    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){

//        label1 = new QLabel("0");
//        label1->setMinimumHeight(20);
//        label1->setMinimumWidth(100);

//        listlblPorcento.push_back(label1);



//    }
//    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){

//      slider = new QSlider(Qt::Horizontal);
//            slider->setFixedHeight(20);
//            slider->setFixedWidth(100);
//            slider->setRange(0,100);



//        listSlider.push_back(slider);


//    }


//    for(int ka=0; ka<catalagoLido->nome.size();ka++){

//        connect(listSlider[ka],SIGNAL(valueChanged(int)),listlblPorcento[ka],SLOT(setNum(int)));
//    }




//    tela = new QWidget();
//    listaWidColuna1Cate.push_back(tela);

//    layout1 = new QVBoxLayout(listaWidColuna1Cate[numero]);
//    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){
//        layout1->addWidget(listlblCategorias[ka]);

//    }



//    tela1 = new QWidget();
//    listaWidColuna3Porcento.push_back(tela1);

//    layout2 = new QVBoxLayout(listaWidColuna3Porcento[numero]);
//    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){
//        layout2->addWidget(listlblPorcento[ka]);

//    }


//    tela2 = new QWidget();
//    listaWidColuna2Slider.push_back(tela2);

//    layout3 = new QVBoxLayout(listaWidColuna2Slider[numero]);
//    for(int ka=0; ka<catalagoLido->nome.size(); ka++ ){
//        layout3->addWidget(listSlider[ka]);

//    }




//  //  if(chEtr){
//    tela = new QWidget();
//     vetorListaWid1.push_back(tela);
//    layoutHorizontal= new QHBoxLayout(vetorListaWid1[numero]);
//   //     chEntr=false;
//  //  }

//    layoutHorizontal->addWidget(listaWidColuna1Cate[numero]);
//    layoutHorizontal->addWidget(listaWidColuna2Slider[numero]);
//    layoutHorizontal->addWidget(listaWidColuna3Porcento[numero]);



//    //vetorListaWid1[numero]->show();


//    if(chEtr){
//    vLay = new QVBoxLayout(vetorListaWid0[numero]);
//    chEtr=false;
//     }

//    vLay->addWidget(vetorListaWid1[numero]);

//    vetorListaWid0[numero]->show();

//    qDebug() << numero;





















//    //QWidget *wid2= new QWidget(ui->wTabTotal);



//    QSlider *slider;

//    slider = new QSlider(Qt::Horizontal);
//    slider->setFixedHeight(100);
//    slider->setFixedWidth(100);


//     QSlider *slider2;
//     slider2 = new QSlider(Qt::Horizontal);
//     slider2->setFixedHeight(100);
//     slider2->setFixedWidth(100);










//   wid1->setLayout(layout);
//   wid2->setLayout(layout2);

//   wid1->show();
//   wid2->show();



}

void telaFluxoComportamental::encontraPontosGravar()
{


    for(int ja=0; ja< catalagoLido->nome.size(); ja++){

        if(listChek[ja]->isChecked()){


            for(int jb=0; jb< etografiaLida->id.size(); jb++){

               // if(listChek[ja]->isChecked()){

                if(etografiaLida->id[jb]== ja){

                    editFrameInicio.push_back(etografiaLida->frameInicial[jb]);
                    editFrameFim.push_back(etografiaLida->frameFinal[jb]);



                }//fecha o if


            }//fecha o for

        }//fecha o if

    }//fecha o for

    qDebug()<< " encontrou os aserem gravados" ;

}

void telaFluxoComportamental::encontrarFrames()
{
    parserXML::dadosMorfo *parserMorfo;
     parserMorfo = new parserXML::dadosMorfo();
    parserXML::dadosCinema *parserCinema;
    parserCinema = new parserXML::dadosCinema();
    for(int ka=0; editFrameFim.size(); ka++){ //para cada um das marcações

        for(int ja=(editFrameInicio[ka]-parserTCCM.videoLido->frameProce); ja< (editFrameFim[ka]-parserTCCM.videoLido->frameProce); ja++ ){

            parserMorfo->frame.push_back(parserTCCM.matrizReMorfo[0].frame[ja]);
            parserMorfo->area.push_back(parserTCCM.matrizReMorfo[0].area[ja]);
            parserMorfo->areaM.push_back(parserTCCM.matrizReMorfo[0].areaM[ja]);
            parserMorfo->centroidX.push_back(parserTCCM.matrizReMorfo[0].centroidX[ja]);
            parserMorfo->centroidY.push_back(parserTCCM.matrizReMorfo[0].centroidY[ja]);
            parserMorfo->altura.push_back(parserTCCM.matrizReMorfo[0].altura[ja]);
            parserMorfo->alturaM.push_back(parserTCCM.matrizReMorfo[0].alturaM[ja]);
            parserMorfo->largura.push_back(parserTCCM.matrizReMorfo[0].largura[ja]);
            parserMorfo->larguraM.push_back(parserTCCM.matrizReMorfo[0].larguraM[ja]);
            parserMorfo->anguloObj.push_back(parserTCCM.matrizReMorfo[0].anguloObj[ja]);


            parserCinema->varArea.push_back(parserTCCM.matrizReCinema[0].varArea[ja]);
            parserCinema->varDistancia.push_back(parserTCCM.matrizReCinema[0].varDistancia[ja]);
            parserCinema->varAltura.push_back(parserTCCM.matrizReCinema[0].varAltura[ja]);
            parserCinema->varLargura.push_back(parserTCCM.matrizReCinema[0].varLargura[ja]);
            parserCinema->varAngular.push_back(parserTCCM.matrizReCinema[0].varAngular[ja]);
            parserCinema->ruidoMaxVaria.push_back(parserTCCM.matrizReCinema[0].ruidoMaxVaria[ja]);

        }
       segMorfo.push_back(parserMorfo);
       segCinema.push_back(parserCinema);

       parserMorfo = new parserXML::dadosMorfo();
       parserCinema = new parserXML::dadosCinema();

    }



}





void telaFluxoComportamental::on_pbSaveFile_clicked()
{


    nomeFluxoComportamental= QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
                "AVI (*.avi)"
                );



    encontraPontosGravar();

    editaVideo = new moduloEditaVideo();
    novaThread = new QThread();

    //registraa os meta tipo para ser usado entre threads.
    qRegisterMetaType<QList<int> >();




    connect(this,SIGNAL(enviaInicioFluxo(QString,QString,QList<int>,QList<int>,int)),editaVideo,SLOT(iniGraFluxoComportamento(QString,QString,QList<int>,QList<int>,int)));
    connect(editaVideo,SIGNAL(setProgres(int,int)),ui->progressBar,SLOT(setRange(int,int)));
    connect(editaVideo,SIGNAL(frame(int)),ui->progressBar,SLOT(setValue(int)));

    editaVideo->moveToThread(novaThread);
    novaThread->start();


    emit enviaInicioFluxo(videoLido->nome,nomeFluxoComportamental,editFrameInicio, editFrameFim, ui->comboBoX->currentIndex());
//    listaEditaVideo[jl]->setKey(expKey.nome, expKey.lab, expKey.senha);
//     connect(this,SIGNAL(enviIncio(QString,QString,QString)),listaEditaVideo[jl],SLOT(iniGraVidoCego(QString,QString,QString)));
//     connect(listaEditaVideo[jl],SIGNAL(setProgres(int,int)),listaPB[jl],SLOT(setRange(int,int)));
//     connect(listaEditaVideo[jl],SIGNAL(frame(int)),listaPB[jl],SLOT(setValue(int)));
//     listaEditaVideo[jl]->moveToThread(listaDeThread[jl]);

    //geraTabela();
}

void telaFluxoComportamental::on_pbOpenTCCM_clicked()
{

    fonteCaminhoTCCM = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://EthoWatcherOS",
                "Ethowatcher Files (*.tkin )"
                );

    parserTCCM.readTCCM(fonteCaminhoTCCM);

    encontraPontosGravar();

     chTCCon = true;

     encontrarFrames();
}
