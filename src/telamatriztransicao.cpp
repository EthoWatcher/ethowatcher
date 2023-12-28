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

void telaMatrizTransicao::setExperimentador(QString nome1, QString lab1)
{
       experimentador.nome = nome1;
       experimentador.lab = lab1;
}

QList<Cell> telaMatrizTransicao::calcular_analise_sequencial(int ctl_qnt_categorias,
                                                         std::vector<QString> ctl_nome,
                                                         int etog_qnt_de_pontos,
                                                         std::vector<int> etl_id)
{
    //limpando caso tenha adicionado antes.
//    for (int kk = 0; kk < analiseSequencial.dados.size(); kk++) {
//      analiseSequencial.dados.pop_back();
//    }
    analiseSequencial.dados.clear();

    int valorMatriz=qPow(ctl_qnt_categorias,2);

    for(int i=0; i<valorMatriz;i++){

        analiseSequencial.dados.push_back(0);
    }



    double quantidadeDePontos=0;

    int contador=0;
    int testeFinal=0;
    int valorAdd=0;
    for(int k=0;k< ctl_qnt_categorias;k++){

        for(int j=0; j< etog_qnt_de_pontos;j++){

            testeFinal=j+1;
            //para nao entrar no ultimo
            if(testeFinal< etog_qnt_de_pontos){

                if(etl_id[j]==k){
                    //for(int m=0; m<catalagoLido.quantidadeDeCategorias;m++){
                    valorAdd= etl_id[j+1];
                    quantidadeDePontos= quantidadeDePontos+1;
                    //if(k==m){
                    analiseSequencial.dados[contador+valorAdd]= analiseSequencial.dados[contador+valorAdd]+1;
                }
                // }
                // }

            }



        }

        contador +=ctl_qnt_categorias;


    }





    //ui->tabDadSeq->insertColumn(3);
    QStringList titulos;

    ui->tabDadSeq->setColumnCount(ctl_qnt_categorias);

    for(int k=0; k< ctl_qnt_categorias; k++){
        titulos << ctl_nome[k];
    }


    ui->tabDadSeq->setHorizontalHeaderLabels(titulos);


    int loopContador=0;
    std::vector<std::vector<int> > matrix_sequencial;


    for(int k=0;k< ctl_qnt_categorias;k++){
        ui->tabDadSeq->insertRow(ui->tabDadSeq->rowCount());
        //categoria

        std::vector<int> line_seq;
        for(int j=0; j<ctl_qnt_categorias; j++){

            ui->tabDadSeq->setItem(ui->tabDadSeq->rowCount()-1
                                   ,j,new QTableWidgetItem(
                                       QString::number(analiseSequencial.dados[loopContador])));


            line_seq.push_back(analiseSequencial.dados[loopContador]);
            loopContador++;
        }
        matrix_sequencial.push_back(line_seq);

    }

    loopContador=0;

    for(int m=0;m<ctl_qnt_categorias;m++){

        //categoria


        for(int l=0; l<ctl_qnt_categorias; l++){
                porcentagemMatrix.push_back(analiseSequencial.dados[loopContador]/quantidadeDePontos*100);

            loopContador++;
        }

    }




    auto gera_csv = [&](){
//        QString str_csv_completo = "";
//        QString str_titulo = ";";
        QList<Cell> saida;
        int linha_cont = 15;
        QString letter= "L";

        add_cell(&saida, letter+QString::number(linha_cont), "Transition frequencies matrix (Percent)");
        linha_cont += 1;
        letter= "M";
        add_cell(&saida, letter+QString::number(linha_cont),"Following Behavior");
        for(int i=0; i< titulos.size(); i++){
            letter = next_letter(letter);
            add_cell(&saida, letter+QString::number(linha_cont),titulos[i]);
        }

        letter = next_letter(letter);
        add_cell(&saida, letter+QString::number(linha_cont),"Total");

        linha_cont += 1;
//        linha_cont += 1;

//        str_titulo = str_titulo+  "\n";


//        str_csv_completo = ";;;;Transition frequencies matrix\n\n;Following Category" + str_titulo;

        // preenche os numeros;
        int loopContador_array=0;
        for(int i=0; i< ctl_qnt_categorias; i++){
            if(i==0){
                letter= "L";
                add_cell(&saida, letter+QString::number(linha_cont),"Preceding");

            }else if(i==1){
                letter= "L";
                add_cell(&saida, letter+QString::number(linha_cont),"Behavior");
            }else{
//                linha =";";
            }

            letter = "M";
            add_cell(&saida, letter+QString::number(linha_cont),titulos[i]);

            for(int j=0; j<ctl_qnt_categorias; j++){
                letter = next_letter(letter);
                add_cell(&saida, letter+QString::number(linha_cont),QString::number( porcentagemMatrix[loopContador_array]), true);
                loopContador_array++;
            }

            letter = next_letter(letter);
            int sum =0;
            for(int i: matrix_sequencial[i]){
                sum = sum + i;
            }

            add_cell(&saida, letter+QString::number(linha_cont),QString::number( sum/quantidadeDePontos*100), true);

//            str_csv_completo = str_csv_completo + linha + "\n";
                linha_cont += 1;
        }

        letter = "M";
        add_cell(&saida, letter+QString::number(linha_cont),"Total");

        for(int i=0; i< ctl_qnt_categorias; i++){
            int sum = 0;
            for(std::vector<int> line: matrix_sequencial){
                sum = sum + line[i];
            }
            letter = next_letter(letter);
            add_cell(&saida, letter+QString::number(linha_cont),QString::number( sum/quantidadeDePontos*100), true);

         }

        letter = next_letter(letter);
        add_cell(&saida, letter+QString::number(linha_cont),QString::number(100), true);

        //------------------------------- doing again
        linha_cont += 2;
        letter= "L";

        add_cell(&saida, letter+QString::number(linha_cont), "Transition frequencies matrix");
        linha_cont += 1;
        letter= "M";
        add_cell(&saida, letter+QString::number(linha_cont),"Following Behavior");
        for(int i=0; i< titulos.size(); i++){
            letter = next_letter(letter);
            add_cell(&saida, letter+QString::number(linha_cont),titulos[i]);
        }

        letter = next_letter(letter);
        add_cell(&saida, letter+QString::number(linha_cont),"Total");

        linha_cont += 1;

        // preenche os numeros;
        loopContador_array=0;
        for(int i=0; i< ctl_qnt_categorias; i++){
            if(i==0){
                letter= "L";
                add_cell(&saida, letter+QString::number(linha_cont),"Preceding");

            }else if(i==1){
                letter= "L";
                add_cell(&saida, letter+QString::number(linha_cont),"Behavior");
            }else{
//                linha =";";
            }

            letter = "M";
            add_cell(&saida, letter+QString::number(linha_cont),titulos[i]);

            for(int j=0; j<ctl_qnt_categorias; j++){
                letter = next_letter(letter);
                add_cell(&saida, letter+QString::number(linha_cont),QString::number( analiseSequencial.dados[loopContador_array]), true);
                loopContador_array++;
            }

            letter = next_letter(letter);
            int sum =0;
            for(int i: matrix_sequencial[i]){
                sum = sum + i;
            }

            add_cell(&saida, letter+QString::number(linha_cont),QString::number( sum), true);

//            str_csv_completo = str_csv_completo + linha + "\n";
                linha_cont += 1;
        }

        letter = "M";
        add_cell(&saida, letter+QString::number(linha_cont),"Total");

        for(int i=0; i< ctl_qnt_categorias; i++){
            int sum = 0;
            for(std::vector<int> line: matrix_sequencial){
                sum = sum + line[i];
            }
            letter = next_letter(letter);
            add_cell(&saida, letter+QString::number(linha_cont),QString::number( sum), true);

         }
        letter = next_letter(letter);
        add_cell(&saida, letter+QString::number(linha_cont),QString::number(quantidadeDePontos), true);
        linha_cont += 1;




        return saida;


    };


    ui->tabDadSeq->setVerticalHeaderLabels(titulos);
    //ui->swAnaSeq->setCurrentIndex(1);
    ui->pbMakeGraph->setEnabled(true);
    ui->pbGeraRelaSeq->setEnabled(true);


    QList<Cell> saida_txt_csv = gera_csv();
    return saida_txt_csv;

}

void telaMatrizTransicao::mostra_gerar_grafico(std::vector<QString> nomeCategoria)
{
    catalagoLido = new catalago();
    catalagoLido->nome = nomeCategoria;
    ui->pbSeqCarregar->setEnabled(false);



    this->show();
//    on_pbMakeGraph_clicked

    auto mostra_matrix = [&](){
        matriz= new figuraMatriz();

        for(int c1=0; c1< catalagoLido->nome.size(); c1++){


            matriz->setNovoCirculo(catalagoLido->nome[c1]);

        }

        //analiseSequencial.dados

        matriz->recebeDadosSeq(porcentagemMatrix);


        matriz->show();
        return true;
    };

    bool mostra = mostra_matrix();
//    emit ui->pbMakeGraph->click();
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

//    ui->pbAnaliseSeq->setEnabled(true);

    saida_analise_seq = this->calcular_analise_sequencial(catalagoLido->quantidadeDeCategorias,
                                      catalagoLido->nome,
                                      etografiaLida->quantidadeDePontos,
                                      etografiaLida->id);



    add_cell(&saida_analise_seq, "A10", "Registred video file are locate in " + videoLido->nome); //+ nome_caminho_video);
//    ui->teTutor->setText(" Passo 2: Clique em `Analisar` para fazer a análise de transição e "
//                         "gerar seu gráfico");
}

void telaMatrizTransicao::on_pbAnaliseSeq_clicked()
{

//    saida_analise_seq = this->calcular_analise_sequencial(catalagoLido->quantidadeDeCategorias,
//                                      catalagoLido->nome,
//                                      etografiaLida->quantidadeDePontos,
//                                      etografiaLida->id);


//    qDebug() << texto;

//    int valorMatriz=qPow(catalagoLido->quantidadeDeCategorias,2);

//    for(int i=0; i<valorMatriz;i++){

//        analiseSequencial.dados.push_back(0);


//    }

//    double quantidadeDePontos=0;

//    int contador=0;
//    int testeFinal=0;
//    int valorAdd=0;
//    for(int k=0;k<catalagoLido->quantidadeDeCategorias;k++){



//        for(int j=0; j<etografiaLida->quantidadeDePontos;j++){


//            testeFinal=j+1;
//            //para nao entrar no ultimo
//            if(testeFinal<etografiaLida->quantidadeDePontos){

//                if(etografiaLida->id[j]==k){
//                    //for(int m=0; m<catalagoLido.quantidadeDeCategorias;m++){
//                    valorAdd= etografiaLida->id[j+1];
//                    quantidadeDePontos= quantidadeDePontos+1;
//                    //if(k==m){
//                    analiseSequencial.dados[contador+valorAdd]= analiseSequencial.dados[contador+valorAdd]+1;
//                }
//                // }
//                // }

//            }



//        }

//        contador +=catalagoLido->quantidadeDeCategorias;


//    }





//    //ui->tabDadSeq->insertColumn(3);
//    QStringList titulos;

//    ui->tabDadSeq->setColumnCount(catalagoLido->quantidadeDeCategorias);

//    for(int k=0; k<catalagoLido->quantidadeDeCategorias; k++){


//        titulos << catalagoLido->nome[k];
//    }


//    ui->tabDadSeq->setHorizontalHeaderLabels(titulos);


//    int loopContador=0;

//    for(int k=0;k<catalagoLido->quantidadeDeCategorias;k++){
//        ui->tabDadSeq->insertRow(ui->tabDadSeq->rowCount());
//        //categoria


//        for(int j=0; j<catalagoLido->quantidadeDeCategorias; j++){

//            ui->tabDadSeq->setItem(ui->tabDadSeq->rowCount()-1
//                                   ,j,new QTableWidgetItem(
//                                       QString::number(analiseSequencial.dados[loopContador])));

//            loopContador++;
//        }

//    }

//    loopContador=0;






//    for(int m=0;m<catalagoLido->quantidadeDeCategorias;m++){

//        //categoria


//        for(int l=0; l<catalagoLido->quantidadeDeCategorias; l++){
//                porcentagemMatrix.push_back(analiseSequencial.dados[loopContador]/quantidadeDePontos);

//            loopContador++;
//        }

//    }








////    ui->teTutor->setText("<p> Passo 3: Clique no botão 'Make graph' para editar e gerar um gráfico referente a matriz "
////                         "de transição analisada</p>"
////                         "<p> Passo 4: Clique no botão 'Gerar relatório' para gerar relatório em '.csv' e '.aseq'</p>");



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

//    QList<Cell> saida;
    QList<QList<Cell> > ls_gravar;

    auto gera_cabecalho = [&](QString nome_caminho_video,
                            int frameProces,
                            int frameFinal,
                            double fps){

//            QString t_saida ="";


        QList<Cell> saida;


        add_cell(&saida, "A1","EthoWatcher Open Source");

        add_cell(&saida, "A2","Observer");
        add_cell(&saida, "B2",experimentador.nome.toLatin1());

        add_cell(&saida, "A3","Lab");
        add_cell(&saida, "B3",experimentador.lab.toLatin1());

//        add_cell(&saida, "A4","Experiment info");

//        add_cell(&saida, "A5","Experiment");
//        add_cell(&saida, "B5","Date");
//        add_cell(&saida, "C5","Other Info");

//        add_cell(&saida, "A6", dado_experimento.tituloExperimento);
//        add_cell(&saida, "B6", dado_experimento.data);
//        add_cell(&saida, "C6", dado_experimento.otherInfo);


//        add_cell(&saida, "A7","Animal Info");
//        add_cell(&saida, "A8","Animal ID");
//        add_cell(&saida, "B8","Weight");
//        add_cell(&saida, "C8","Sex");

//        add_cell(&saida, "A9", dado_experimento.animalID);
//        add_cell(&saida, "B9", dado_experimento.wight);
//        add_cell(&saida, "C9", dado_experimento.animalSex);

        add_cell(&saida, "A10", "Registred video file are locate in " + nome_caminho_video);

        add_cell(&saida, "A11", "Analysis initiated at " + QString::number( frameProces / fps) + " (seconds) of the video file");
        add_cell(&saida, "A12", "Analysis terminated at " + QString::number( frameFinal / fps) + " (seconds) of the video file");

        add_cell(&saida, "A13", "The selected catalog are : " + catalagoLido->caminhoArquivo);

//            t_saida = t_saida + "sep=; \n";
//            t_saida = t_saida + "EthoWatcher Open Source \n";
//            t_saida = t_saida + "Observer;" + experimentador.nome.toLatin1() + "\n";
//            t_saida = t_saida + "Lab;" + experimentador.lab.toLatin1() + "\n";

//            t_saida = t_saida + "Experiment info\n";
//            t_saida = t_saida + "Experiment; Date; Other Info\n";
//            t_saida = t_saida + dado_experimento.tituloExperimento + ";"+
//                    dado_experimento.data + ";" + dado_experimento.otherInfo + "\n";

//            t_saida = t_saida + "Animal Info\n";
//            t_saida = t_saida + "Animal ID; Weight; Sex\n";
//            t_saida = t_saida + dado_experimento.animalID + ";" + dado_experimento.wight + ";"+ dado_experimento.animalSex +"\n";


//            t_saida = t_saida + "Registred video file are locate in " + nome_caminho_video + "\n";

//            t_saida = t_saida + "Analysis initiated at " + QString::number( frameProces / fps) + " (seconds) of the video file \n ";
//            t_saida = t_saida + "Analysis terminated at " + QString::number( frameFinal / fps) + " (seconds) of the video file \n";
//            t_saida = t_saida + "\n";

//            t_saida = t_saida + "The selected catalog are : " + ";" + nomeGravarCatalago + "\n";
//            t_saida = t_saida + "\n";
//            t_saida = t_saida + "\n";
//            t_saida = t_saida + "\n";

        return saida;
    };






    ls_gravar.append(gera_cabecalho(videoLido->nome, videoLido->frameProce, videoLido->frameFinal, videoLido->fps));



    ls_gravar.append(saida_analise_seq);



    parser->converteArquivo(nomeGravarCatalago, ls_gravar);



}

void telaMatrizTransicao::lerETOXML(QString nomeArquivo)
{
    OutEtografia.setFileName(nomeArquivo);
    OutEtografia.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutEtografia); //passa o endereço

    QString conversor;


    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        if(streamReader.name().toString() == "analise"){

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


        if(streamReader.name().toString() == "categoria"){

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

        if(streamReader.name().toString() == "nomeCaminhoExt"){
            catalagoLido->caminhoArquivo= streamReader.readElementText();


        }

        if(streamReader.name().toString() == "tipoAnalise"){
            catalagoLido->tipoAnalise= streamReader.readElementText();


        }

        if((streamReader.name().toString() == "dadosVideoAnalisado")||(videoLido->controle)){


          if(streamReader.name().toString() == "nomeVxml"){
           videoLido->nome= streamReader.readElementText();

          }

          if(streamReader.name().toString() == "frameInicial"){

              videoLido->frameInicial= streamReader.readElementText().toInt();

          }
          if(streamReader.name().toString() == "frameProces"){


              videoLido->frameProce= streamReader.readElementText().toInt();

          }

          if(streamReader.name().toString() == "frameFinal"){
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
