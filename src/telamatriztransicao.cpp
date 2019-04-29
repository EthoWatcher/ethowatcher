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
#include "telamatriztransicao.h"
#include "ui_telamatriztransicao.h"

telaMatrizTransicao::telaMatrizTransicao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaMatrizTransicao)
{
    ui->setupUi(this);
    //ui->swAnaSeq->setCurrentIndex(0);
}

telaMatrizTransicao::~telaMatrizTransicao()
{
    delete ui;
}

void telaMatrizTransicao::on_pbSeqCarregar_clicked()
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

    ui->pbAnaliseSeq->setEnabled(true);
    ui->teTutor->setText(" Passo 2: Clique em `Analisar` para fazer a análise de transição e "
                         "gerar seu gráfico");
}

void telaMatrizTransicao::on_pbAnaliseSeq_clicked()
{
    int valorMatriz=qPow(catalagoLido->quantidadeDeCategorias,2);

    for(int i=0; i<valorMatriz;i++){

        analiseSequencial.dados.push_back(0);


    }

    double quantidadeDePontos=0;

    int contador=0;
    int testeFinal=0;
    int valorAdd=0;
    for(int k=0;k<catalagoLido->quantidadeDeCategorias;k++){



        for(int j=0; j<etografiaLida->quantidadeDePontos;j++){


            testeFinal=j+1;
            //para nao entrar no ultimo
            if(testeFinal<etografiaLida->quantidadeDePontos){

                if(etografiaLida->id[j]==k){
                    //for(int m=0; m<catalagoLido.quantidadeDeCategorias;m++){
                    valorAdd= etografiaLida->id[j+1];
                    quantidadeDePontos= quantidadeDePontos+1;
                    //if(k==m){
                    analiseSequencial.dados[contador+valorAdd]= analiseSequencial.dados[contador+valorAdd]+1;
                }
                // }
                // }

            }



        }

        contador +=catalagoLido->quantidadeDeCategorias;


    }





    //ui->tabDadSeq->insertColumn(3);
    QStringList titulos;

    ui->tabDadSeq->setColumnCount(catalagoLido->quantidadeDeCategorias);

    for(int k=0; k<catalagoLido->quantidadeDeCategorias; k++){


        titulos << catalagoLido->nome[k];
    }


    ui->tabDadSeq->setHorizontalHeaderLabels(titulos);


    int loopContador=0;

    for(int k=0;k<catalagoLido->quantidadeDeCategorias;k++){
        ui->tabDadSeq->insertRow(ui->tabDadSeq->rowCount());
        //categoria


        for(int j=0; j<catalagoLido->quantidadeDeCategorias; j++){

            ui->tabDadSeq->setItem(ui->tabDadSeq->rowCount()-1
                                   ,j,new QTableWidgetItem(
                                       QString::number(analiseSequencial.dados[loopContador])));

            loopContador++;
        }

    }

    loopContador=0;






    for(int m=0;m<catalagoLido->quantidadeDeCategorias;m++){

        //categoria


        for(int l=0; l<catalagoLido->quantidadeDeCategorias; l++){
                porcentagemMatrix.push_back(analiseSequencial.dados[loopContador]/quantidadeDePontos);

            loopContador++;
        }

    }







    ui->tabDadSeq->setVerticalHeaderLabels(titulos);
    //ui->swAnaSeq->setCurrentIndex(1);

    ui->pbMakeGraph->setEnabled(true);
    ui->pbGeraRelaSeq->setEnabled(true);
    ui->teTutor->setText("<p> Passo 3: Clique no botão 'Make graph' para editar e gerar um gráfico referente a matriz "
                         "de transição analisada</p>"
                         "<p> Passo 4: Clique no botão 'Gerar relatório' para gerar relatório em '.csv' e '.aseq'</p>");



}

void telaMatrizTransicao::on_pbGeraRelaSeq_clicked()
{
    //funcao para pegar o nome que sera gravado

    nomeGravarCatalago = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "analise Sequencial (*.aseq)"
               );

    Output.setFileName(nomeGravarCatalago);


    Output.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&Output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento
//    if(ui->cbTSequencial->isChecked()){

//       Output.write("\n<?xml-stylesheet type=\"text/xsl\" href=\"analiseSequencialEstilo.xsl\"?>");
//        ui->wAlertTotal1->setVisible(true);
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
    stream.writeTextElement("frameFinal",QString::number(videoLido->frameFinal));
    stream.writeTextElement("fps",QString::number(videoLido->fps));



    stream.writeEndElement(); //fecha dadosVideoUsados

    stream.writeStartElement("analises");

//    for(int i=0;i<catalagoLido->quantidadeDeCategorias;i++){

       stream.writeStartElement("categoria");
       stream.writeAttribute("id", 0);
       stream.writeAttribute("tipo",catalagoLido->tipoAnalise);
       stream.writeTextElement("caminhoAnaliseEto",fonteVideoETOXML);
       stream.writeEndElement();
//    }

    stream.writeEndElement(); //fecha analises


    stream.writeEndElement(); //fecha dadosAnaliseEtografica



    stream.writeStartElement("analiseSequencial");

     stream.writeStartElement("sessoes");

     //analiseSequencial.dados
//    for(int se2=0;se2<cViSeg;se2++){
        stream.writeStartElement("sessao");
        stream.writeAttribute("id", QString::number(0));

        int contadorQuant=0;
        for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){

            stream.writeStartElement("categoria");
            stream.writeAttribute("idcat", QString::number(cat));
            stream.writeAttribute("name", catalagoLido->nome[cat]);
            for(int cata=0; cata<(catalagoLido->quantidadeDeCategorias);cata++){
                stream.writeStartElement("caAnaSeg");
                stream.writeAttribute("idcat", QString::number(cata));
                stream.writeAttribute("quant", QString::number(analiseSequencial.dados[cata+contadorQuant]));
                stream.writeEndElement(); //fecha categoria

            }

            contadorQuant+=catalagoLido->quantidadeDeCategorias;

            stream.writeEndElement(); //fecha sessao

        }
    stream.writeEndElement(); //fecha sessao



    //porcentagem nova
    stream.writeStartElement("sessaoPorce");
    stream.writeAttribute("id", QString::number(0));

    contadorQuant=0;
    for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){

        stream.writeStartElement("categoriaPorce");
        stream.writeAttribute("idcat", QString::number(cat));
        stream.writeAttribute("name", catalagoLido->nome[cat]);
        for(int cata=0; cata<(catalagoLido->quantidadeDeCategorias);cata++){
            stream.writeStartElement("caAnaSegPorce");
            stream.writeAttribute("idcat", QString::number(cata));
            stream.writeAttribute("quant", QString::number(porcentagemMatrix[cata+contadorQuant]));
            stream.writeEndElement(); //fecha categoria

        }

        contadorQuant+=catalagoLido->quantidadeDeCategorias;

        stream.writeEndElement(); //fecha sessao

    }
stream.writeEndElement(); //fecha sessao





//    }

    stream.writeEndElement();


    //magica acontece cViSeg



    stream.writeEndElement(); //fecha totalSessao





    stream.writeEndElement(); //fecha analiseTotalSessao
    stream.writeEndDocument();



    Output.close();

    parser = new parserXMLtoCSV();

    qDebug() <<"gravou o xml";

    parser->converteArquivo(nomeGravarCatalago);



}

void telaMatrizTransicao::lerETOXML(QString nomeArquivo)
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

          if(streamReader.name() == "frameFinal"){
           videoLido->frameFinal= streamReader.readElementText().toInt();

            videoLido->controle=false;
        }

        }

    }



   OutEtografia.close();
}

//void telaMatrizTransicao::on_pushButton_2_clicked()
//{



//}

void telaMatrizTransicao::on_pbMakeGraph_clicked()
{
    matriz= new figuraMatriz();

    for(int c1=0; c1< catalagoLido->nome.size(); c1++){


        matriz->setNovoCirculo(catalagoLido->nome[c1]);

    }

    //analiseSequencial.dados

    matriz->recebeDadosSeq(porcentagemMatrix);


    matriz->show();
}
