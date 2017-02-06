#include "telasegementacao.h"
#include "ui_telasegementacao.h"

telaSegementacao::telaSegementacao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaSegementacao)
{
    ui->setupUi(this);
    ui->swToTotal->setCurrentIndex(0);


    layoutLblSeg= new QVBoxLayout(ui->wLblSeg);
    layoutLeFim= new QVBoxLayout(ui->wLeFim);
    layoutLeInicio= new QVBoxLayout(ui->wLeInicio);
}

telaSegementacao::~telaSegementacao()
{
    delete ui;
}

void telaSegementacao::on_pbCaTotalSe_clicked()
{
    fonteVideoETOXML = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users//Bio//Desktop//videos//",
                "Video Files (*.etoxml)"
                );

    //se final vxml
    etografiaLida = new analiseEtografica();
    catalagoLido = new catalago();
    videoLido = new dadosVideo();

    lerETOXML(fonteVideoETOXML);


    ui->lblFrameInicial->setText( QString::number(videoLido->frameProce/videoLido->fps)+ "(s)");
    ui->lblFrameFinal->setText( QString::number(videoLido->frameFinal/videoLido->fps)+ "(s)");
    ui->lblFrameNome->setText( fonteVideoETOXML);


    ui->wTotal->setEnabled(true);

    QLineEdit* lineEditInicio;
    QLineEdit* lineEditFim;
    QLineEdit* lineEditLabel;
    //QLabel* labelSegmenta;

    lineEditFim= new QLineEdit();
    lineEditInicio= new QLineEdit();
    lineEditLabel = new QLineEdit();


    lineEditFim->setText(QString::number(videoLido->frameFinal));
    lineEditInicio->setText(QString::number(videoLido->frameProce));
    lineEditLabel->setText("0");
    lineEditLabel->setEnabled(false);



    layoutLeFim->addWidget(lineEditFim);
    layoutLeInicio->addWidget(lineEditInicio);
    layoutLblSeg->addWidget(lineEditLabel);

    listaLineInicio.push_back(lineEditInicio);
    listaLineFim.push_back(lineEditFim);
    listaLineLabel.push_back(lineEditLabel);


    ui->pbTotaAdd->setEnabled(true);
    ui->pbTotalRes->setEnabled(true);

    cViSeg=cViSeg+1;
}

void telaSegementacao::on_pbTotaAdd_clicked()
{
    QLineEdit* lineEditInicio;
    QLineEdit* lineEditFim;
    QLineEdit* lineEditLabel;
    //QLabel* labelSegmenta;

    lineEditFim= new QLineEdit();
    lineEditInicio= new QLineEdit();
    lineEditLabel = new QLineEdit();


    int valorInicio = listaLineFim[cViSeg-1]->text().toInt() ;
    int valorFim = videoLido->frameFinal;
    lineEditFim->setText(QString::number(valorFim));
    lineEditInicio->setText(QString::number(valorInicio));
    lineEditLabel->setText(QString::number(cViSeg));
    lineEditLabel->setEnabled(false);



    layoutLeFim->addWidget(lineEditFim);
    layoutLeInicio->addWidget(lineEditInicio);
    layoutLblSeg->addWidget(lineEditLabel);

    listaLineInicio.push_back(lineEditInicio);
    listaLineFim.push_back(lineEditFim);
    listaLineLabel.push_back(lineEditLabel);
    cViSeg=cViSeg+1;
}

void telaSegementacao::on_pbTotalRes_clicked()
{
    // esse é o contador que contem o tamanho cViSeg
    //encontra os pontos iniciais e finais





    // esse é o contador que contem o tamanho cViSeg
    //vi1 = valor inicial primeiro
    if(ui->chbHetero->isChecked()){

        for(int vi1=0;vi1<cViSeg;vi1++){

            totInicio.push_back(listaLineInicio[vi1]->text().toInt());
            totFinal.push_back(listaLineFim[vi1]->text().toInt());


        }

    }


    ///double cViseg;
    double intervalo;

    if(ui->chbHomo->isChecked()){

        if(ui->lieTime->text()=="0"){


            QMessageBox::information(this,"ERROR", "homogenous time is equal to zero");

            return;
            //            QFileDialog dialog(this);
            //            dialog.setFileMode(QFileDialog::Reject);


        }

        intervalo =(double) videoLido->frameFinal/videoLido->fps - (double) videoLido->frameProce/videoLido->fps;
        cViSeg= intervalo/ ui->lieTime->text().toDouble();
        cViSegInteiro= intervalo/ ui->lieTime->text().toDouble(); // ta se utilizando do truncamento do inteiro
        dezenaCviSeg= cViSeg - cViSegInteiro ;
        chNumeroQuebrado=false;

        if(dezenaCviSeg!=0){
            cViSeg = (cViSeg - dezenaCviSeg)+1;
            chNumeroQuebrado=true;
        }



        totInicio.push_back(videoLido->frameProce);
        totFinal.push_back(videoLido->frameFinal);


        for(int jj=0; jj<cViSeg; jj++){

            if(jj== (cViSeg-1)){


                if(chNumeroQuebrado){


                    totInicio.push_back(totFinal[jj] );
                    totFinal.push_back(videoLido->frameFinal );


                }else{

                    totInicio.push_back(videoLido->frameProce + (jj* ui->lieTime->text().toDouble()* videoLido->fps) );
                    totFinal.push_back(videoLido->frameProce + ((jj+1)* ui->lieTime->text().toDouble()* videoLido->fps) );

                }


            }else{


                totInicio.push_back(videoLido->frameProce + (jj* ui->lieTime->text().toDouble()* videoLido->fps) );
                totFinal.push_back(videoLido->frameProce + ((jj+1)* ui->lieTime->text().toDouble()* videoLido->fps) );



            }





            // qDebug()<< "rolou" << totInicio[jj] << totFinal[jj];
        }





        //return;

        //      for(int lol=0; lol< cViSeg; lol++){

        //chave que faz entrar no ultimo elemento

        //   if(ka== (cViSeg-1)){

        //     if(chNumeroQuebrado){

        //         totInicio.push_back(videoLido->frameProce + (ka* ui->lieTime->text().toDouble()* videoLido->fps) );
        //        totFinal.push_back(videoLido->frameProce + ((ka+1)* ui->lieTime->text().toDouble()* videoLido->fps) );



        //   }else{
        //       totInicio.push_back(totFinal[ka-1] );
        //        totFinal.push_back(videoLido->frameFinal );
        //  }


        //  }else{
        //se nao é o ultimo elemento
        //          totInicio.push_back(videoLido->frameProce + (lol* ui->lieTime->text().toDouble()* videoLido->fps) );
        //          totFinal.push_back(videoLido->frameProce + ((lol+1)* ui->lieTime->text().toDouble()* videoLido->fps) );

        //  }


        //        }//fim do for

    }//fim de se for homo




    //lendo as posições iniciais que o usuario informou



    //conversão dos ponto
    int qDPontos=0;
    int pontos=0;
    //bool entrou= false;
    int v=0;
    int lido;
    //cria um vetor

    for(int m=0; m<catalagoLido->quantidadeDeCategorias; m++){

        //        std::vector<double> fInicial;
        //        std::vector<double> fFinal;
        fInicial.clear();
        fFinal.clear();
        frameInfo.clear();
        pontos=0;
        //encontra as regioões de determinada categoria do catalago
        //encontra de acordo com o valor de m
        for(qDPontos=0; qDPontos<etografiaLida->quantidadeDePontos; qDPontos++){


            if(etografiaLida->id[qDPontos] ==m){
                fInicial.push_back(etografiaLida->frameInicial[qDPontos]);
                fFinal.push_back(etografiaLida->frameFinal[qDPontos]);
                pontos++;
            }



        }
        //qDPontos é o numero de pontos postos

        //gera um for com um valor inicial igual ao frame inicial do video
        //gera umf or com um valor final de acordo com o valor final do video
        for(int frame= videoLido->frameInicial; frame <
            videoLido->frameFinal; frame++){
            //para cada frame do video lido
            //o video lido é de acorodo com valor v
            for(int geraVetor=0; geraVetor<pontos; geraVetor++){

                // ele testa o frame para cada intervalo de pontos lido
                // se encontrar ele coloca um  ponto com o valor do id da categoria
                if(((frame>=fInicial[geraVetor])&&(frame<=fFinal[geraVetor]))){

                    frameInfo.push_back(m);
                    entrou= true;
                }

            }
            //se o frame nao estiver dentro do intervalo o programa coloca o valor de -1
            //-1 porque os id do catalago são sempre valores positivos

            if(!entrou){
                frameInfo.push_back(-1); //quer dissser que o usuario nao deixou precionado o botão

            }
            entrou= false;


        }

        //ao fim dos looping  de encontras os valores das categorias
        //ele grava o vetor em uma matrix de pontos
        frameTotOriginal.push_back(frameInfo);
        frameInfo.clear();
        fInicial.clear();
        fFinal.clear();

    }







    //    //el = etografia lida
    //    //se = segmentacao

    //corte das sesões para serem analisados
    for(int se=0;se<(cViSeg+1);se++){

        //        pontosTot.clear();
        frameTotCortado.clear();
        for(int cat=0;cat<catalagoLido->quantidadeDeCategorias;cat++){

            frameInfo.clear();
            for(int el1=(totInicio[se]-videoLido->frameInicial);el1<(totFinal[se]-videoLido->frameInicial);el1++){



                frameInfo.push_back(frameTotOriginal[cat][el1]);

            }

            frameTotCortado.push_back(frameInfo);

        }





        matrixframeTotCortado.push_back(frameTotCortado);


    }



    //faz o zero

    for(int i=0;i<catalagoLido->quantidadeDeCategorias;i++){

        totalizacao1.freq.push_back(0);
        totalizacao1.latencia.push_back(videoLido->frameFinal);
        totalizacao1.duracao.push_back(0);
        totalizacao1.componente.push_back(catalagoLido->nome[i]);
        totalizacao1.clicado.push_back(false);
        totalizacao1.bordaSubida.push_back(false);

    }

    for(int se1=0;se1<(cViSeg+1);se1++){

        //        matrixframeTotCortado[a][b][c]
        //        [a]= numero de segmentacao
        //        [b]= numero da catecotira
        //        [c]= frame numero;
        //zerando
        //        totalizacaoTot.clear();

        for(int i=0;i<catalagoLido->quantidadeDeCategorias;i++){

            totalizacao1.freq[i] = 0;
            totalizacao1.latencia[i] = matrixframeTotCortado[se1][i].size();
            totalizacao1.duracao[i] = 0 ;
            totalizacao1.componente[i] =catalagoLido->nome[i];
            totalizacao1.clicado[i]=false;
            totalizacao1.bordaSubida[i]=false;

        }




        for(int cat1=0;cat1<catalagoLido->quantidadeDeCategorias;cat1++){

            int tamanha=matrixframeTotCortado[se1][cat1].size();



            for(int el2= 0 ;el2<= tamanha  ;el2++){


                //tamanho
                if(matrixframeTotCortado[se1][cat1][el2]== cat1){

                    totalizacao1.duracao[cat1]= totalizacao1.duracao[cat1]+ 1;


                }

                //latencia

                if((matrixframeTotCortado[se1][cat1][el2]== cat1)
                        &&(!totalizacao1.clicado[cat1])){
                    totalizacao1.clicado[cat1]= true;

                    totalizacao1.latencia[cat1]= el2;


                }


                //freq
                if((!totalizacao1.bordaSubida[cat1])
                        &&(matrixframeTotCortado[se1][cat1][el2]== cat1))
                {
                    totalizacao1.bordaSubida[cat1]= true;
                    totalizacao1.freq[cat1]=totalizacao1.freq[cat1] +1;


                }


                if((totalizacao1.bordaSubida[cat1])
                        &&(matrixframeTotCortado[se1][cat1][el2]== -1))
                {

                    totalizacao1.bordaSubida[cat1]= false;

                }





            }


        }






        totalizacaoTot.push_back(totalizacao1);



    }





    // bool clicado = totalizacaoTot[0].clicado[0]; //forma de acessar o std vector



    QStringList listaString;
    QStringList listaString2;
    QStringList listaString3;
    QLabel* jo1;
    QTableWidget* lista1;
    QWidget* lWid;

    lWid= new QWidget(ui->wTabTotal);


    jo1 = new QLabel();




    listaString << "Category"<< "Duration(s)" << "Frequency" ;//<< "Latencia";
    listaString3 << "Category"<< "Duration(s)" << "Frequency" << "Latency(s)";

    for(int cat23;cat23<catalagoLido->quantidadeDeCategorias;cat23++){


        listaString2 << catalagoLido->nome[cat23];
    }


    //colcoa a tabela
    for(int se=0;se<(cViSeg+1);se++ ){
        jo1 = new QLabel();
        lista1 = new QTableWidget();
        //jo1 = new QLabel();

        if(se==0){

            lista1->setColumnCount(4);

        }else{

            lista1->setColumnCount(3);
        }




        for(int k=0;k<catalagoLido->quantidadeDeCategorias;k++){
            lista1->insertRow(lista1->rowCount());
            //categoria
            lista1->setItem(lista1->rowCount()-1
                            ,0,new QTableWidgetItem(
                                catalagoLido->nome[k]));
            //duracao
            lista1->setItem(lista1->rowCount()-1,
                            1,new QTableWidgetItem(
                                QString::number(totalizacaoTot[se].duracao[k]/videoLido->fps)));
            //frequencia
            lista1->setItem(lista1->rowCount()-1,
                            2,new QTableWidgetItem(
                                QString::number(totalizacaoTot[se].freq[k])));

            if(se==0){

                lista1->setHorizontalHeaderLabels(listaString3);
                //latencia
                lista1->setItem(lista1->rowCount()-1,
                                3,new QTableWidgetItem(
                                    QString::number(totalizacaoTot[se].latencia[k]/videoLido->fps)));



            }else{

                lista1->setHorizontalHeaderLabels(listaString);
            }




        }


        lista1->setVerticalHeaderLabels(listaString2);
        lista1->setFixedHeight(100);

        listaTabelaTotal.push_back(lista1);



        jo1->setText("|| Segmentation number "+ QString::number(se)+
                     " || Begin Time " + QString::number(totInicio[se]/videoLido->fps)+
                     " (s) ||  End Time " + QString::number(totFinal[se]/videoLido->fps)+ " (s) ||");
        jo1->setFixedHeight(30);
        // jo1->setFixedHeight(200);
        listaLabel.push_back(jo1);



    }


    layoutTabWid = new QVBoxLayout(ui->wTabTotal);

    for(int se1=0 ; se1<(cViSeg+1); se1++ ){


        //listaTabelaTotal.push_back(lista1);



        //jo1->setText("Segmento "+ QString::number(se1));


        //         layoutTabWid->addWidget(listaLabel[se1]);

        //         layoutTabWid->addWidget(listaTabelaTotal[se1]);


        //        layoutMut = new QVBoxLayout();

        //        layoutMut->addWidget(listaLabel[se1]);

        //        layoutMut->addWidget(listaTabelaTotal[se1]);


        layoutTabWid->addWidget(listaLabel[se1]);

        layoutTabWid->addWidget(listaTabelaTotal[se1]);


        //        layoutTabWid->addWidget(*layoutMut);



    }




    //    layoutTabWid->addWidget(jo1);

    //    layoutTabWid->addWidget(listaTabelaTotal[0]);




    //magica acontece








    // listaTabelaTotal



    //listaLineFim[0]->setText("123123");
    ui->pbTotGravar->setEnabled(true);

    ui->swToTotal->setCurrentIndex(1);
}

void telaSegementacao::on_pbTotGravar_clicked()
{
    //funcao para pegar o nome que sera gravado

    nomeGravarCatalago = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
                "time budgets file (*.tbf)"
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
        stream.writeTextElement("caminhoAnaliseEto",fonteVideoETOXML);
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
        stream.writeAttribute("frameFinal", QString::number(etografiaLida->frameFinal[qDPontos]));

    stream.writeEndElement(); //fecha analise

//        if(etografiaLida->id[qDPontos] ==m){
//            fInicial.push_back(etografiaLida->frameInicial[qDPontos]);
//            fFinal.push_back(etografiaLida->frameFinal[qDPontos]);
//            pontos++;
//        }



    }





    stream.writeEndElement(); //fecha analises


    stream.writeEndElement(); //fecha dadosAnaliseEtografica



    stream.writeStartElement("totalSessao");

    stream.writeStartElement("sessoes");

    for(int se2=0;se2<cViSeg;se2++){
        stream.writeStartElement("sessao");
        stream.writeAttribute("id", QString::number(se2));
        stream.writeAttribute("inicio",QString::number(totInicio[se2]));
        stream.writeAttribute("fim",QString::number(totFinal[se2]));

        for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){
            stream.writeStartElement("categoria");
            stream.writeAttribute("idcat", QString::number(cat));
            stream.writeAttribute("name", catalagoLido->nome[cat]);
            stream.writeTextElement("duracao",QString::number(totalizacaoTot[se2].duracao[cat]));
            stream.writeTextElement("frequencia",QString::number(totalizacaoTot[se2].freq[cat]));
            stream.writeTextElement("latencia",QString::number(totalizacaoTot[se2].latencia[cat]));
            stream.writeEndElement(); //fecha categoria
        }
        stream.writeEndElement(); //fecha sessao

    }

    stream.writeEndElement();


    //magica acontece cViSeg



    stream.writeEndElement(); //fecha totalSessao





    stream.writeEndElement(); //fecha analiseTotalSessao
    stream.writeEndDocument();



    Output.close();
}

void telaSegementacao::lerETOXML(QString nomeArquivo)
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

void telaSegementacao::on_chbHomo_clicked(bool checked)
{
    if(checked){

        ui->chbHetero->setChecked(false);
        ui->widHetero->setEnabled(false);
        ui->widHomo->setEnabled(true);
    }
}

void telaSegementacao::on_chbHetero_clicked(bool checked)
{
    if(checked){

        ui->chbHomo->setChecked(false);
        ui->widHetero->setEnabled(true);
        ui->widHomo->setEnabled(false);
    }
}