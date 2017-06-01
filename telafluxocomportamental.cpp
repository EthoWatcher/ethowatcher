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
                        videoLido->fps= conversor.toDouble();
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

              //etografiaLida->frameFinal.push_back(streamReader.attributes().value("frameFinal").toDouble()-1);
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

    //correção
    //etografiaLida->frameFinal[etografiaLida->frameFinal.size()-1]++;


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


    //para cada categoria do catalogo
    for(int ja=0; ja< catalagoLido->nome.size(); ja++){

        if(listChek[ja]->isChecked()){

            //para cada quadro do video
            //vai ter o problema q para o mesmo frame tem duas categorias
            //e quando faz um univo vetor de pontos isso da problema
            //qualquer coisa usar os algoritmos de segmentação por tempo
            for(int jb=0; jb< etografiaLida->id.size(); jb++){

               // if(listChek[ja]->isChecked()){

                if(etografiaLida->id[jb]== ja){

                    editFrameInicio.push_back(etografiaLida->frameInicial[jb]);
                    editFrameFim.push_back(etografiaLida->frameFinal[jb]);
                    categoria.push_back(ja);


                }//fecha o if


            }//fecha o for

        }//fecha o if

    }//fecha o for

    qDebug()<< " encontrou os pontos aserem gravados" ;


    //algoritimo alternativo
//    bool chUnde=true;
//    //para cada quadro do v´deio

//    for(int rl=videoLido->frameProce; rl< videoLido->frameFinal ; rl++){

//        //tem que testar pra todas os pontos

//        //para cada transcrição lida
//        for(int rj=0;rj<etografiaLida->frameInicial.size();rj++){

//           if((rl>=etografiaLida->frameInicial[rj])&&(rl<etografiaLida->frameFinal[rj])){

//               qDebug() <<" frame" << rl << etografiaLida->id[rj] << "e a transcrição é a " << rj;

//               vetorPontos.push_back(etografiaLida->id[rj]);
//               quadrosPontos.push_back(rl);
//               chUnde=false;

//        }else{
//               //não categorizado

////                vetorPontos.push_back(-1);
////                quadrosPontos.push_back(rl);



//           }


//        }



//        if(chUnde==true){
//            //se não enocntrou nenhuma classificao é undefinido
//            //é caracterizado como menos 1

//            vetorPontos.push_back(-1);
//        }else{

//            chUnde=true;
//        }



//    }

//    chUnde=true;

//    for(int rj=0;rj<etografiaLida->frameInicial.size();rj++){

//       if((videoLido->frameFinal==etografiaLida->frameFinal[rj])){

//           qDebug() <<" frame" << videoLido->frameFinal << etografiaLida->id[rj] << "e a transcrição é a " << rj;

//           vetorPontos.push_back(etografiaLida->id[rj]);
//           quadrosPontos.push_back(videoLido->frameFinal);
//           chUnde=false;

//    }else{
//           //não categorizado

////            vetorPontos.push_back(-1);
////            quadrosPontos.push_back(videoLido->frameFinal);




//       }


//    }

//    if(chUnde==true){
//        //se não enocntrou nenhuma classificao é undefinido
//        //é caracterizado como menos 1

//        vetorPontos.push_back(-1);
//    }else{

//        chUnde=true;
//    }


//    //fim de encontrar os pontos do vídeo
//    //agora tem que segmentar pelo tempo

}

void telaFluxoComportamental::encontrarFrames()
{
    parserXML::dadosMorfo *parserMorfo;
     parserMorfo = new parserXML::dadosMorfo();
    parserXML::dadosCinema *parserCinema;
    parserCinema = new parserXML::dadosCinema();

//    editFrameInicio.push_back(etografiaLida->frameInicial[jb]);
//    editFrameFim.push_back(etografiaLida->frameFinal[jb]);

    for(int ka=0; ka< editFrameFim.size(); ka++){ //para cada um das marcações

        for(int ja=(editFrameInicio[ka]-videoLido->frameProce); ja< (editFrameFim[ka]-videoLido->frameProce); ja++ ){

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
            parserMorfo->objetoEncontrado.push_back(parserTCCM.matrizReMorfo[0].objetoEncontrado[ja]);


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

       qDebug() << "fim de encontrar os frames";

}

void telaFluxoComportamental::gravaXML(QString nomeArquivo)
{
   //gravar o xml

    QString nomeGravarCatalago;
    nomeGravarCatalago = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                nomeArquivo,
                "time budgets file (*.segc)"
                );

    Output.setFileName(nomeGravarCatalago);




    Output.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&Output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento
    //    if(ui->cbTTotal->isCheckable()){

    //       Output.write("\n<?xml-stylesheet type=\"text/xsl\" href=\" analiseTotalEstilo.xsl   \"?>");
    //        ui->wAlertTotal->setVisible(true);
    //    }



    stream.writeStartElement("analiseTotalSessao");

    stream.writeStartElement("dadosAnalisador");
    stream.writeTextElement("nomeAnalisador","joao antonio Marcolan");
    stream.writeTextElement("laboratorio","iebUFSC");
    stream.writeEndElement(); //fecha dadosAnalisador


    stream.writeStartElement("dadosAnaliseEtografica");

    stream.writeStartElement("dadosCatalagoUsado");
    stream.writeTextElement("caminhoCatalago",catalagoLido->caminhoArquivo);
    stream.writeStartElement("Categorias");
    int contador=0;


    for(int i=0;i<catalagoLido->quantidadeDeCategorias;i++){

        stream.writeStartElement("categoria");
        stream.writeAttribute("id", QString::number(i));
        stream.writeAttribute("nome",catalagoLido->nome[i]);
        stream.writeEndElement();

    }

    stream.writeEndElement(); //fecha caminho Ext

    stream.writeEndElement(); //fecha dadosCatalagoUsado

    stream.writeStartElement("dadosVideosUsados");
    stream.writeTextElement("caminhoVideo",videoLido->nome);
    stream.writeTextElement("frameInicial",QString::number( videoLido->frameInicial));
    stream.writeTextElement("frameProces", QString::number(videoLido->frameProce));
    stream.writeTextElement("frameFinal",QString::number(videoLido->frameFinal));
    stream.writeTextElement("fps",QString::number(videoLido->fps));


        stream.writeStartElement("categoria");
        stream.writeAttribute("id", 0);
        stream.writeAttribute("tipo",catalagoLido->tipoAnalise);
        stream.writeTextElement("caminhoAnaliseEto",fonteCaminhoArquivo);
        stream.writeEndElement();


    stream.writeEndElement(); //fecha dadosVideoUsados

    stream.writeStartElement("analises");

    //    for(int i=0;i<catalagoLido->quantidadeDeCategorias;i++){

//    stream.writeStartElement("categoria");
//    stream.writeAttribute("id", 0);
//    stream.writeAttribute("tipo",catalagoLido->tipoAnalise);
//    stream.writeTextElement("caminhoAnaliseEto",fonteVideoETOXML);
//    stream.writeEndElement();
    //    }


    for(int qDPontos=0; qDPontos<etografiaLida->quantidadeDePontos; qDPontos++){


        stream.writeStartElement("analise");
        stream.writeAttribute("ponto", QString::number(qDPontos));
        stream.writeAttribute("id", QString::number( etografiaLida->id[qDPontos]));
        stream.writeAttribute("frameInicial", QString::number( etografiaLida->frameInicial[qDPontos]));

        if(etografiaLida->id[qDPontos]-1==qDPontos){
            stream.writeAttribute("frameFinal", QString::number(etografiaLida->frameFinal[qDPontos]));
        }else{
            stream.writeAttribute("frameFinal", QString::number(etografiaLida->frameFinal[qDPontos]-1));
        }


    stream.writeEndElement(); //fecha analise

//        if(etografiaLida->id[qDPontos] ==m){
//            fInicial.push_back(etografiaLida->frameInicial[qDPontos]);
//            fFinal.push_back(etografiaLida->frameFinal[qDPontos]);
//            pontos++;
//        }



    }





    stream.writeEndElement(); //fecha analises


    stream.writeEndElement(); //fecha dadosAnaliseEtografica



    stream.writeStartElement("totalComportamento");



    //para cada segmento encontrado
    for(int cSeg =0; cSeg <segMorfo.size(); cSeg++ ){
        stream.writeStartElement("segmentacao");
        stream.writeAttribute("idcat", QString::number(categoria[cSeg]));
        stream.writeAttribute("name", catalagoLido->nome[categoria[cSeg]]);
        stream.writeAttribute("quadroInical",QString::number(editFrameInicio[cSeg]));


        stream.writeAttribute("quadroFinal",QString::number(editFrameFim[cSeg]-1));


        for(int cFaixa = 0 ; cFaixa < segMorfo[cSeg]->frame.size() ; cFaixa++ ){
//            int i = cFaixa -videoLido->frameProce;

            stream.writeStartElement("segmento");
           // stream.writeAttribute("f1", QString::number(cFaixa) );
            stream.writeAttribute("f",QString::number(segMorfo[cSeg]->frame[cFaixa]));

            stream.writeAttribute("arP",QString::number(segMorfo[cSeg]->area[cFaixa]));
            stream.writeAttribute("arM",QString::number(segMorfo[cSeg]->area[cFaixa]/(qPow(parserTCCM.videoLido->escala,2))));
            stream.writeAttribute("ceX",QString::number(segMorfo[cSeg]->centroidX[cFaixa]));
            stream.writeAttribute("ceY",QString::number(segMorfo[cSeg]->centroidY[cFaixa]));
            stream.writeAttribute("altP",QString::number(segMorfo[cSeg]->altura[cFaixa]));
            stream.writeAttribute("altM",QString::number(segMorfo[cSeg]->altura[cFaixa]/parserTCCM.videoLido->escala));
            stream.writeAttribute("larP",QString::number(segMorfo[cSeg]->largura[cFaixa]));
            stream.writeAttribute("larM",QString::number(segMorfo[cSeg]->largura[cFaixa]/parserTCCM.videoLido->escala));
            stream.writeAttribute("an",QString::number(segMorfo[cSeg]->anguloObj[cFaixa])); //angulo do objeto


            stream.writeAttribute("Var",QString::number(segCinema[cSeg]->varArea[cFaixa]));
            stream.writeAttribute("Vd",QString::number(segCinema[cSeg]->varDistancia[cFaixa]));
            stream.writeAttribute("Valt",QString::number(segCinema[cSeg]->varAltura[cFaixa]));
            stream.writeAttribute("Vlar",QString::number(segCinema[cSeg]->varLargura[cFaixa]));

           stream.writeAttribute("Van",QString::number(segCinema[cSeg]->varAngular[cFaixa]));



            if(segCinema[cSeg]->ruidoMaxVaria[cFaixa]){
                stream.writeAttribute("rMinV","true");

           }else{
                stream.writeAttribute("rMinV","false");
            }
           if(segMorfo[cSeg]->objetoEncontrado[cFaixa]){

                stream.writeAttribute("OE","true");

            }else{

                stream.writeAttribute("OE","false");

           }




            stream.writeEndElement(); //fecha segmentp


      }



        stream.writeEndElement(); //fecha segmentacao


    }


    chTCCon = true;

//    stream.writeAttribute("f",QString::number(fraNumero));
//    stream.writeAttribute("arP",QString::number(dados->reMorfo.area[i]));
//    stream.writeAttribute("arM",QString::number(dados->reMorfo.area[i]/(qPow(videoLista.escala[contadorDeVideo],2))));
//    stream.writeAttribute("ceX",QString::number(dados->reMorfo.centroidX[i]));
//    stream.writeAttribute("ceY",QString::number(dados->reMorfo.centroidY[i]));
//    stream.writeAttribute("altP",QString::number(dados->reMorfo.altura[i]));
//    stream.writeAttribute("altM",QString::number(dados->reMorfo.altura[i]/videoLista.escala[contadorDeVideo]));
//    stream.writeAttribute("larP",QString::number(dados->reMorfo.largura[i]));
//    stream.writeAttribute("larM",QString::number(dados->reMorfo.largura[i]/videoLista.escala[contadorDeVideo]));
//    stream.writeAttribute("an",QString::number(dados->reMorfo.anguloObj[i])); //angulo do objeto



////         stream.writeAttribute("taP",QString::number(dados->reMorfo.tamanhoObj[i]));
////         stream.writeAttribute("taM",QString::number(dados->reMorfo.tamanhoObj[i]/videoLista.escala[contadorDeVideo]));


////         double tamanhoObjeto=0;

////         tamanhoObjeto= qPow( dados->desenhoSaida.pob2X[i]-dados->desenhoSaida.pob1X[i],2) + qPow( dados->desenhoSaida.pob2Y[i]-dados->desenhoSaida.pob1Y[i],2);
////         tamanhoObjeto = qSqrt(tamanhoObjeto);

////         stream.writeAttribute("taM1", QString::number(tamanhoObjeto/videoLista.escala[contadorDeVideo]));


////         //novo









//    parserMorfo->frame.push_back(parserTCCM.matrizReMorfo[0].frame[ja]);
//    parserMorfo->area.push_back(parserTCCM.matrizReMorfo[0].area[ja]);
//    parserMorfo->areaM.push_back(parserTCCM.matrizReMorfo[0].areaM[ja]);
//    parserMorfo->centroidX.push_back(parserTCCM.matrizReMorfo[0].centroidX[ja]);
//    parserMorfo->centroidY.push_back(parserTCCM.matrizReMorfo[0].centroidY[ja]);
//    parserMorfo->altura.push_back(parserTCCM.matrizReMorfo[0].altura[ja]);
//    parserMorfo->alturaM.push_back(parserTCCM.matrizReMorfo[0].alturaM[ja]);
//    parserMorfo->largura.push_back(parserTCCM.matrizReMorfo[0].largura[ja]);
//    parserMorfo->larguraM.push_back(parserTCCM.matrizReMorfo[0].larguraM[ja]);
//    parserMorfo->anguloObj.push_back(parserTCCM.matrizReMorfo[0].anguloObj[ja]);


//    parserCinema->varArea.push_back(parserTCCM.matrizReCinema[0].varArea[ja]);
//    parserCinema->varDistancia.push_back(parserTCCM.matrizReCinema[0].varDistancia[ja]);
//    parserCinema->varAltura.push_back(parserTCCM.matrizReCinema[0].varAltura[ja]);
//    parserCinema->varLargura.push_back(parserTCCM.matrizReCinema[0].varLargura[ja]);
//    parserCinema->varAngular.push_back(parserTCCM.matrizReCinema[0].varAngular[ja]);
//    parserCinema->ruidoMaxVaria.push_back(parserTCCM.matrizReCinema[0].ruidoMaxVaria[ja]);

//    segMorfo.push_back(parserMorfo);
//    segCinema.push_back(parserCinema);

//    std::vector<double> inicioPeriodo;
//    std::vector<double> fimPeriodo;
//    latenciaTotal= latencia(vetorPontos);
//    duracaoTotalMatriz.push_back(duracaoTotal);
//    frequenciaTotalMatriz.push_back(frequenciaTotal);
    //arrumar hoje

//    stream.writeStartElement("sessao");
//    stream.writeAttribute("id", QString::number(0));
//    stream.writeAttribute("inicio",QString::number(videoLido->frameProce));
//    stream.writeAttribute("fim",QString::number(videoLido->frameFinal));

//    for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){
//        stream.writeStartElement("categoria");
//        stream.writeAttribute("idcat", QString::number(cat));
//        stream.writeAttribute("name", catalagoLido->nome[cat]);
//        stream.writeTextElement("duracao",QString::number(duracaoTotalMatriz[0][cat]*videoLido->fps));
//        stream.writeTextElement("frequencia",QString::number(frequenciaTotalMatriz[0][cat]*videoLido->fps));
//        stream.writeTextElement("latencia",QString::number(latenciaTotal[cat]*videoLido->fps));
//        stream.writeEndElement(); //fecha categoria
//    }
//     stream.writeEndElement(); //fecha sessao




//    editFrameInicio.push_back(etografiaLida->frameInicial[jb]);
//    editFrameFim.push_back(etografiaLida->frameFinal[jb]);
//    categoria.push_back(ja);



//    //quantidade de segmentação de tempo
//    for(int cSegTeg=0; cSegTeg<inicioPeriodo.size(); cSegTeg++ ){
//        stream.writeStartElement("sessao");
//        stream.writeAttribute("id", QString::number((cSegTeg)));
//        stream.writeAttribute("inicio",QString::number(inicioPeriodo[cSegTeg]));

////        if(cSegTeg==(inicioPeriodo.size()-1)){
////            //no ultimo
////            stream.writeAttribute("fim",QString::number(fimPeriodo[cSegTeg]+1));
////            qDebug()<< "entrou no ultimo";
////        }else{
//            stream.writeAttribute("fim",QString::number(fimPeriodo[cSegTeg]));
////        }



//        for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){
//            stream.writeStartElement("categoria");
//            stream.writeAttribute("idcat", QString::number(cat));
//            stream.writeAttribute("name", catalagoLido->nome[cat]);
//            stream.writeTextElement("duracao",QString::number(duracaoTotalMatriz[cSegTeg+1][cat]*videoLido->fps));
//            stream.writeTextElement("frequencia",QString::number(frequenciaTotalMatriz[cSegTeg+1][cat]));
//            stream.writeTextElement("latencia",QString::number(0));
//            stream.writeEndElement(); //fecha categoria
//        }

//        stream.writeEndElement(); //fecha sessao


//    }


//    for(int se2=0;se2<cViSeg;se2++){
//        stream.writeStartElement("sessao");
//        stream.writeAttribute("id", QString::number(se2));
//        stream.writeAttribute("inicio",QString::number(totInicio[se2]));
//        stream.writeAttribute("fim",QString::number(totFinal[se2]));

//        for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){
//            stream.writeStartElement("categoria");
//            stream.writeAttribute("idcat", QString::number(cat));
//            stream.writeAttribute("name", catalagoLido->nome[cat]);
//            stream.writeTextElement("duracao",QString::number(totalizacaoTot[se2].duracao[cat]));
//            stream.writeTextElement("frequencia",QString::number(totalizacaoTot[se2].freq[cat]));
//            stream.writeTextElement("latencia",QString::number(totalizacaoTot[se2].latencia[cat]));
//            stream.writeEndElement(); //fecha categoria
//        }
//        stream.writeEndElement(); //fecha sessao

//    }

    stream.writeEndElement();//fim das segmentaçãoes


    //magica acontece cViSeg



    stream.writeEndElement(); //fecha totalSessao





    stream.writeEndElement(); //fecha analiseTotalSessao
    stream.writeEndDocument();



    Output.close();






}





void telaFluxoComportamental::on_pbSaveFile_clicked()
{


    nomeFluxoComportamental= QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
                "AVI (*.avi)"
                );

    if(chTCCon){
        //caso o usuario tenha feito a TCCM isso aqui é posto

    }else{
      encontraPontosGravar();
    }



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



    //grava xml
    gravaXML(nomeFluxoComportamental);





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

    encontraPontosGravar(); //encontra qual os pontos a gravar da interface gráfica

     chTCCon = true;


     encontrarFrames();
}
