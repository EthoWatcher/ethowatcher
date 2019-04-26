#include "telaetografia.h"
#include "ui_telaetografia.h"

telaEtografia::telaEtografia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaEtografia)
{
    ui->setupUi(this);
    ui->swPrincipal->setCurrentIndex(4);
    //connect(eto,SIGNAL(enviandoDadosEtograficos()),this,SLOT(receverAnaliseEtografia()));
    ui->swEtografia->setCurrentIndex(0);

    ui->pbEtoSem->setVisible(false);
}

telaEtografia::~telaEtografia()
{
    delete ui;
}

void telaEtografia::on_pbUnicoVideo_clicked()
{
    fonteVideoXML = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users//Bio//Desktop//videos//",
                "Video Files (*.vxml)"
                );

    videoLista.nomeVXML.push_back(fonteVideoXML);
    //se final vxml

    lerVXML(fonteVideoXML);
    videoLista.quantidadeDeDados++; //= contadorTamanho; //conta quantidade de dados;
    // se final vcxml
    //lerVCXML()

    ui->swPrincipal->setCurrentIndex(1);


}


//multi videos
void telaEtografia::on_pbMulti_clicked()
{

    nomeLVxml = QFileDialog::getOpenFileName(
                this,
                tr("Save File"),
                "C://etowatcher//listaDeVideos//",
               "Catalog files (*.lvxml)"
               );

    //abridno arquvio e epgando informações

    OutListavideo.setFileName(nomeLVxml);
    OutListavideo.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutListavideo); //passa o endereço

    QString conversor;

    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        if(streamReader.name()== "completo"){
        videoLista.nomeVXML.push_back(streamReader.readElementText());
           //qDebug() << leitorXML.readElementText();
         videoLista.quantidadeDeDados++; //= contadorTamanho; //conta quantidade de dados;
        }
    }
    for(int i=0;i<videoLista.quantidadeDeDados;i++){

        lerVXML(videoLista.nomeVXML[i]);

    }



    ui->swPrincipal->setCurrentIndex(1);
}

//cadastro
void telaEtografia::on_pbCadastroCatalago_clicked()
{

    //funcao para pegar o nome que sera gravado

    nomeGravarCatalago = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Catalog files (*.caxml)"
               );

    Output.setFileName(nomeGravarCatalago);


    Output.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&Output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento
    stream.writeStartElement("Catalago");
    stream.writeStartElement("Informacoes");
             stream.writeTextElement("experimentador","joao");
             stream.writeTextElement("laboratorio","IEB");
    stream.writeEndElement();//fecha informacoes

    stream.writeStartElement("Categorias");
    int contador=0;
    for(int i=0;i<dadosEto.quantidadeDeDados;i++){
        if(!dadosEto.dadoRemovido[i]){
       stream.writeStartElement("categoria");
       stream.writeAttribute("id", QString::number(contador));
       stream.writeTextElement("nome",dadosEto.nomeCategoria[i]);
       stream.writeTextElement("atalho",dadosEto.atalho[i]);
       stream.writeTextElement("descricao",dadosEto.descricao[i]);

        stream.writeEndElement();
            contador++;
        }


    }


    stream.writeEndElement();//fecha Categorias

    stream.writeEndElement();//fecha catalago
    stream.writeEndDocument();


    Output.close();

    //para colocar as variaveis dentro da variavel cAnaEto
    //que sera usada para fazer a analise etografica

    readCatalago();

    ui->swPrincipal->setCurrentIndex(1);

    if(!nomeGravarCatalago.isEmpty()){
    ui->pbEtografia->setEnabled(true);
    }
}

//analise
void telaEtografia::on_pbEtografia_clicked()
{
    QString text="Análise do video numero "+ QString::number(contadorDeVideo+1)+
            " de um total de " + QString::number(videoLista.quantidadeDeDados);
    ui->lblQuantiVideo->setText(text);
    ui->lblCatalago->setText(nomeGravarCatalago);
    if(ui->cbNested->isChecked()){
    ui->lblAuto->setText("Nested");
    }else{
     ui->lblAuto->setText("Auto ");
    }

  ui->swPrincipal->setCurrentIndex(3);
}


//criar um catalago
void telaEtografia::on_pbCriarCatalago_clicked()
{
    ui->swPrincipal->setCurrentIndex(2);
}

void telaEtografia::on_pbClearItem_clicked()
{
    int itemSelecionado = 0;


    for(int i=0;i<ui->tabDadCat->rowCount();i++)
    {
        if(ui->tabDadCat->item(i,0)->isSelected())
        {

            ui->tabDadCat->setRowHidden(i,true);
            dadosEto.dadoRemovido[i] = true; //diz que o dado foi removido
           // ui->tabDadCat->removeRow(i);
            itemSelecionado=1;
        }
    }


   if(itemSelecionado==0)
   {
        QMessageBox::information(this,"Atention!", "Não existe itens");
   }


}

void telaEtografia::on_pbAddCategoria_clicked()
{

    ui->tabDadCat->setColumnCount(2);


    //adicionando as variaveis a um vetor
    dadosEto.nomeCategoria.push_back(ui->leCategoria->text());
    dadosEto.atalho.push_back(ui->leAtalho->text());
    dadosEto.dadoRemovido.push_back(false);
    dadosEto.quantidadeDeDados=dadosEto.quantidadeDeDados+1;




    //forma de adquirir o QTextWidget
    QString descricao=ui->textDscElem->toPlainText().replace(QRegExp("[\\n\\t\\r]")," ");
    QString descricaoNulo;
    descricaoNulo=descricao.replace(" ","");
    if(descricaoNulo.count()==0)
        descricao=descricaoNulo;
    else
    {
        descricao=ui->textDscElem->toPlainText().replace(".\n",". ");
        descricao=descricao.replace(".\t",". ");
        descricao=descricao.replace(".\r",". ");
        descricao=descricao.replace(" \n"," ");
        descricao=descricao.replace(" \t"," ");
        descricao=descricao.replace(" \r"," ");
        descricao=descricao.replace("\n"," ");
        descricao=descricao.replace("\t"," ");
        descricao=descricao.replace("\r"," ");
        int i=descricao.count();
        while(i!=0)
        {
            descricao=descricao.replace("  "," ");
            i--;
        }
    }

    dadosEto.descricao.push_back(descricao);



    ui->tabDadCat->insertRow(ui->tabDadCat->rowCount());
    ui->tabDadCat->setItem(ui->tabDadCat->rowCount()-1,0,new QTableWidgetItem(ui->leCategoria->text()));
    ui->tabDadCat->setItem(ui->tabDadCat->rowCount()-1,1,new QTableWidgetItem(ui->leAtalho->text()));


    //configurando TableWidget
    ui->tabDadCat->resizeColumnsToContents();
    ui->tabDadCat->clearSelection();
    ui->tabDadCat->clearFocus();


    ui->textDscElem->setText("");
    ui->leAtalho->setText("");
    ui->leCategoria->setText("");

}


void telaEtografia::readCatalago(){


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
    leitura.close();



}

void telaEtografia::on_pbLerCatalago_clicked()
{
    nomeGravarCatalago= QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                   "Video Files (*.caxml)"
                    );

    readCatalago();

    if(!nomeGravarCatalago.isEmpty()){
    ui->pbEtografia->setEnabled(true);
    }
}

void telaEtografia::on_pbComecarAnalise_clicked()
{

    if(contadorDeVideo<=videoLista.quantidadeDeDados){
    eto= new Etografia();
    //conectando
    connect(eto,SIGNAL(enviandoDadosEtograficos()),this,SLOT(receverAnaliseEtografia()));

//    dados[0]=0;
//    dados[1]=1;
//    dados[2]=0;

    //eto->setTipoAnalise(dados);
    eto->setInfoCatalago(cAnaEto.nomeCategoria,cAnaEto.atalho,cAnaEto.quantidadeDeDados);
    //ta funcionando /\

    eto->setCatalago();

      if(ui->cbAuto->isChecked()){
       eto->setAutoNested(true);
    }
     if(ui->cbNested->isChecked()){
     eto->setAutoNested(false);

     }

     //seta o video e qual o frame inicial e final
    //eto->setInicioVideo("C://ethowatcher//videosOriginais//funcionaMarcela.avi",1,300);

     eto->setInicioVideo(videoLista.nomeOpencv[contadorDeVideo],
                         videoLista.frameInicial[contadorDeVideo],
                         videoLista.frameBack[contadorDeVideo],
                         videoLista.frameProces[contadorDeVideo],
                         videoLista.frameFinal[contadorDeVideo]);

     eto->setCalibracao(videoLista.threshold[contadorDeVideo],
                        videoLista.erosao[contadorDeVideo],
                        videoLista.escala[contadorDeVideo]);




     eto->setChavesPrograma(chaveEto,chaveProces);



     eto->setTratamentoRuido(videoLista.areaJanInte[contadorDeVideo].oriX[0],
             videoLista.areaJanInte[contadorDeVideo].oriY[0],
             videoLista.areaJanInte[contadorDeVideo].width[0],
             videoLista.areaJanInte[contadorDeVideo].height[0],
             videoLista.chaInteMove[contadorDeVideo],
             videoLista.tamMaxVar[contadorDeVideo]);










     // videoLista.chaInteMove[contadorDeVideo];



     eto->show();
    }


}

void telaEtografia::on_cbAuto_clicked()
{
    if(ui->cbNested->isChecked()){
       ui->cbNested->setChecked(false);

    }
       //       ui->cbNested->setChecked(false);

//    }else{
//           ui->cbAuto->setChecked(false);
//            ui->cbNested->setChecked(true);
//        }
}


void telaEtografia::on_cbNested_clicked()
{
    if(ui->cbAuto->isChecked()){
       ui->cbAuto->setChecked(false);
        }
}

//void telaEtografia::on_pushButton_clicked()
//{

//}

void telaEtografia::on_pbGravarAnalasiteEtografica_clicked()
{




    nomeGravarEtografia = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Catalog files (*.etoxml)"
               );



 if(!nomeGravarEtografia.isEmpty()){
   ui->pbGravarAnalasiteEtografica->setEnabled(false);



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
            stream.writeTextElement("frameFinal",QString::number(videoLista.frameFinal[contadorDeVideo]));
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
   for(int i=0;i<etografia.quantidadeDepontos;i++){

      stream.writeStartElement("analise");
      stream.writeAttribute("ponto", QString::number(i));
      stream.writeAttribute("id", QString::number(etografia.id[i]));
      stream.writeAttribute("frameInicial", QString::number( etografia.frameComeco[i]));
      stream.writeAttribute("frameFinal", QString::number(etografia.framFim[i]));

       stream.writeEndElement(); //fecha analise

       }

    stream.writeEndElement();//fecha analises

   stream.writeEndElement();// fecha dadosAnalise





   stream.writeEndElement();//fecha analiseEtografica
   stream.writeEndDocument();


   OutEtografia.close();






//   //gravar o resultado da etografia

//    //setar o proximo video
//     ui->pbComecarAnalise->setText("Nova Analise");


//     contadorDeVideo++;

//     if(contadorDeVideo<videoLista.quantidadeDeDados){
//     QString text="Análise do video numero "+ QString::number(contadorDeVideo+1)+
//             " de um total de " + QString::number(videoLista.quantidadeDeDados);
//     ui->lblQuantiVideo->setText(text);
//     }else{
//         ui->pbComecarAnalise->setEnabled(false);
//     }

//     ui->swEtografia->setCurrentIndex(0);



 }
}

void telaEtografia::receverAnaliseEtografia()
{


    ui->swEtografia->setCurrentIndex(1);

    etografia.id=eto->saida.id;
    etografia.frameComeco =eto->saida.frameComeco;
    etografia.framFim = eto->saida.framFim;
    etografia.quantidadeDepontos = eto->saida.quantidadeDepontos;

    ui->pbGravarAnalasiteEtografica->setEnabled(true);
}

void telaEtografia::on_pbRefazer_clicked()
{
    ui->pbComecarAnalise->setText("Refazer a analise");
    ui->swEtografia->setCurrentIndex(0);
}


void telaEtografia::lerVXML(QString nomeArquivoLer){


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

           if(streamReader.name()== "janelaInteresse"){

               if(chaJanInte==true){
                   chaJanInte=false;

               }else{
                   chaJanInte=true;

                   videoLista.areaJanInte.push_back(auxArea1);

               }
           }

           if(chaJanInte==true){
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



//    <frameInicial>116</frameInicial>
//    <frameBack>256</frameBack>
//    <frameFinal>999</frameFinal>
//    <erosao>0</erosao>
//    <escala>0.0490191</escala>



}

void telaEtografia::enconPontoArea()
{


    for(int ka=0; ka< videoLista.area[contadorDeVideo].oriX.size(); ka++ )
        {

        if(videoLista.area[contadorDeVideo].tipo[ka]=="circle"){
            chaTip=false;
            contCir++;

        }else{
            contRet++;
            chaTip=true;

        }

        for(int i=0; i< eto->reMorfo.area.size();i++){
            if(chaTip){ //se é quadrado

                if((eto->reMorfo.centroidX[i]>=videoLista.area[contadorDeVideo].oriX[contRet-1])
                        &&(eto->reMorfo.centroidX[i]<=(videoLista.area[contadorDeVideo].oriX[contRet-1]+videoLista.area[contadorDeVideo].width[contRet-1]))&&
                        (eto->reMorfo.centroidY[i]>=videoLista.area[contadorDeVideo].oriY[contRet-1])
                        &&(eto->reMorfo.centroidY[i]<=(videoLista.area[contadorDeVideo].oriY[ka]+videoLista.area[contadorDeVideo].height[contRet-1])))
                {

                    objDentro.push_back(true);


                }else{

                    objDentro.push_back(false);

                }


            }else{ //se é circulo

                raioTest=0;
                raioTest = qPow(eto->reMorfo.centroidX[i]-videoLista.area[contadorDeVideo].oriX[contCir-1],2)+
                            qPow(eto->reMorfo.centroidY[i]-videoLista.area[contadorDeVideo].oriY[contCir-1],2);

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



}//fim função




void telaEtografia::setExperimentador(QString nome1,QString lab1){

    experimentador.nome =nome1;
    experimentador.lab = lab1;


}

//etografia baseado em video normal
void telaEtografia::on_pbEtoVideo_clicked()
{
    chaveEto=true;
    chaveProces=false;
    ui->swPrincipal->setCurrentIndex(0);
    ui->pbGravarAnalasiProces->setVisible(false);
}

//etografia baseada em vido com processamento de imagme
void telaEtografia::on_pbEtoProce_clicked()
{
    chaveEto=false;
    chaveProces=true;
    ui->swPrincipal->setCurrentIndex(0);
}

//etografia baseada num timer
void telaEtografia::on_pbEtoSem_clicked()
{

    //a ser implementada

}

void telaEtografia::on_pbGravarAnalasiProces_clicked()
{

    nomeGravarProcesImagem = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Catalog files (*.etoxml)"
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

    for(int ja=0; ja< videoLista.area[contadorDeVideo].oriX.size(); ja++ ){

        stream.writeStartElement("infoArea");
        stream.writeAttribute("id", QString::number(ja));

        if(videoLista.area[contadorDeVideo].tipo[ja]=="circle"){

        stream.writeAttribute("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
        stream.writeTextElement("centX",QString::number(videoLista.area[contadorDeVideo].oriX[ja]));
        stream.writeTextElement("centY",QString::number(videoLista.area[contadorDeVideo].oriY[ja]));

        stream.writeTextElement("raio",QString::number(videoLista.area[contadorDeVideo].raio[conCir2]));

        conCir2++;

        }else{
            stream.writeAttribute("tipoArea",videoLista.area[contadorDeVideo].tipo[ja]);
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
     for(int i=0; i< eto->reMorfo.area.size();i++){

         if(matObjDentro[ka][i]){

         stream.writeStartElement("proce");
         fraNumero=i+ videoLista.frameProces[contadorDeVideo];

         stream.writeAttribute("f",QString::number(fraNumero));
         stream.writeAttribute("arP",QString::number(eto->reMorfo.area[i]));
         stream.writeAttribute("arM",QString::number(eto->reMorfo.area[i]*videoLista.escala[contadorDeVideo]));
         stream.writeAttribute("ceX",QString::number(eto->reMorfo.centroidX[i]));
         stream.writeAttribute("ceY",QString::number(eto->reMorfo.centroidY[i]));
         stream.writeAttribute("taP",QString::number(eto->reMorfo.tamanhoObj[i]));
         stream.writeAttribute("taM",QString::number(eto->reMorfo.tamanhoObj[i]*videoLista.escala[contadorDeVideo]));
         stream.writeAttribute("an",QString::number(eto->reMorfo.anguloObj[i]));

         stream.writeAttribute("Var",QString::number(eto->reCinema.varArea[i]));
         stream.writeAttribute("Van",QString::number(eto->reCinema.varAngular[i]));
         stream.writeAttribute("Vd",QString::number(eto->reCinema.varDistancia[i]));



         stream.writeEndElement(); //fecha proce

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



     }

    }


void telaEtografia::on_pbNextAnali_clicked()
{


    //gravar o resultado da etografia

     //setar o proximo video
      ui->pbComecarAnalise->setText("Nova Analise");


      contadorDeVideo++;

      if(contadorDeVideo<videoLista.quantidadeDeDados){
      QString text="Análise do video numero "+ QString::number(contadorDeVideo+1)+
              " de um total de " + QString::number(videoLista.quantidadeDeDados);
      ui->lblQuantiVideo->setText(text);
      }else{
          ui->pbComecarAnalise->setEnabled(false);
      }

      ui->swEtografia->setCurrentIndex(0);

}
