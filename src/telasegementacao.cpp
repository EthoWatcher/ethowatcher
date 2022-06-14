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
    ui->stackedWidget->setCurrentIndex(1);
    chTCCon= true;
    ui->pbGravarTCCM->setVisible(false);

    ui->pbTotalRes->setVisible(false);
}

telaSegementacao::~telaSegementacao()
{
    delete ui;
}

void telaSegementacao::liga_sementacao_etografia()
{
    //precisa ler
}

// USANDO ESSA FUNCAO
QList<Cell> telaSegementacao::gera_segmentacao_texto(double tamanho_janela_s, int q_proce, int q_final,
                                    double fps,
                                    std::vector<double> frameInicial,
                                    std::vector<double> frameFinal,
                                    std::vector<int> id,
                                    std::vector<QString> nome,
                                    int qnt_categorias, int linha=0)
{


    //preparando a execução
    chTCCon = true;
    ui->lieTime->setText(QString::number(tamanho_janela_s));



    videoLido = new dadosVideo();
    videoLido->frameProce = q_proce;
    videoLido->frameFinal = q_final;
    videoLido->fps = fps;

     etografiaLida = new analiseEtografica();

     etografiaLida->frameInicial = frameInicial;
     etografiaLida->frameFinal = frameFinal;
     etografiaLida->id = id;

     catalagoLido = new catalago();
     catalagoLido->quantidadeDeCategorias = qnt_categorias;
     catalagoLido->nome  = nome;


//     std::vector<int> ponto;
//     std::vector<int> id;
//     std::vector<double> frameInicial;
//     std::vector<double> frameFinal;




    //executando

    this->_calcula();

    // resultado
    QString texto_saida ="";


    saida_segm = this->_gera_lis_segmetacao(linha);
//    QString teste2;

//    teste2 = QFileDialog::getSaveFileName(
//                this,
//                tr("Save File"),
//                fonteVideoETOXML,
//                "Video Files (*.csv)"
//                );
//    outGravador.setFileName(teste2);
//    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

//    QTextStream csvGravador(&outGravador);

//    csvGravador <<"sep=; \n";
//    csvGravador << texto_saida;



//   outGravador.close();




    return saida_segm;



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
    ui->pbCaTotalSe->setEnabled(false);

    ui->pbTotGravar->setEnabled(true);
    ui->pbTotGravar->setVisible(true);

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


void telaSegementacao::_calcula(){

    vetorPontos = [](int q_processamento, int q_final, analiseEtografica *etografia ){

       std::vector<int> catego_por_quadro;

       bool chUnde=true;
       for(int rl= q_processamento; rl< q_final ; rl++){

           //tem que testar pra todas os pontos

           //para cada transcrição lida
           for(int rj=0;rj<etografia->frameInicial.size();rj++){

               if((rl>=etografia->frameInicial[rj])&&(rl<etografia->frameFinal[rj])){

//                        qDebug() <<" frame" << rl << etografia->id[rj] << "e a transcrição é a " << rj;

                   catego_por_quadro.push_back(etografia->id[rj]);
//                        quadrosPontos.push_back(rl);
                   chUnde=false;

               }


           }



           if(chUnde==true){
               //se não enocntrou nenhuma classificao é undefinido
               //é caracterizado como menos 1

               catego_por_quadro.push_back(-1);
           }else{

               chUnde=true;
           }



       }

       return catego_por_quadro;

   }(videoLido->frameProce, videoLido->frameFinal, etografiaLida );


  // double framesTotaisAnalise = videoLido->frameFinal - videoLido->frameProce;


//        bool chUnde=true;
//        //para cada quadro do v´deio

//        for(int rl=videoLido->frameProce; rl< videoLido->frameFinal ; rl++){

//            //tem que testar pra todas os pontos

//            //para cada transcrição lida
//            for(int rj=0;rj<etografiaLida->frameInicial.size();rj++){

//               if((rl>=etografiaLida->frameInicial[rj])&&(rl<etografiaLida->frameFinal[rj])){

//                   qDebug() <<" frame" << rl << etografiaLida->id[rj] << "e a transcrição é a " << rj;

//                   vetorPontos.push_back(etografiaLida->id[rj]);
//                   quadrosPontos.push_back(rl);
//                   chUnde=false;

//            }else{
//                   //não categorizado

////                vetorPontos.push_back(-1);
////                quadrosPontos.push_back(rl);



//               }


//            }



//            if(chUnde==true){
//                //se não enocntrou nenhuma classificao é undefinido
//                //é caracterizado como menos 1

//                vetorPontos.push_back(-1);
//            }else{

//                chUnde=true;
//            }



//        }

//        chUnde=true;

//        for(int rj=0;rj<etografiaLida->frameInicial.size();rj++){

//           if((videoLido->frameFinal==etografiaLida->frameFinal[rj])){

//               qDebug() <<" frame" << videoLido->frameFinal << etografiaLida->id[rj] << "e a transcrição é a " << rj;

//               vetorPontos.push_back(etografiaLida->id[rj]);
//               quadrosPontos.push_back(videoLido->frameFinal);
//               chUnde=false;

//        }else{
//               //não categorizado

////            vetorPontos.push_back(-1);
////            quadrosPontos.push_back(videoLido->frameFinal);




//           }


//        }

//        if(chUnde==true){
//            //se não enocntrou nenhuma classificao é undefinido
//            //é caracterizado como menos 1

//            vetorPontos.push_back(-1);
//        }else{

//            chUnde=true;
//        }

     auto gera_lista_segmentos = [](double tamanho, double fps, int q_inicial, int q_final, bool r_vetor_entrada){
         std::vector<double> vetor_saida;

         double varia = tamanho * fps; //frames
         double frameInico = q_inicial;

         do{
             if(r_vetor_entrada){
                 vetor_saida.push_back(frameInico);


             }else{
                 vetor_saida.push_back(frameInico+varia);
             }

             frameInico= frameInico+varia;

         }while (frameInico<=q_final);

         return vetor_saida;
    };

     double tamanho_janela =ui->lieTime->text().toDouble(); //frames

     inicioPeriodo = gera_lista_segmentos(tamanho_janela, videoLido->fps,  videoLido->frameProce,videoLido->frameFinal , true);
     fimPeriodo = gera_lista_segmentos(tamanho_janela, videoLido->fps,  videoLido->frameProce, videoLido->frameFinal , false);


   //fim de encontrar os pontos do vídeo
   //agora tem que segmentar pelo tempo

//         double varia =ui->lieTime->text().toDouble() * videoLido->fps; //frames
//         double frameInico = videoLido->frameProce;
//         do{

//             inicioPeriodo.push_back(frameInico);
//             fimPeriodo.push_back(frameInico+varia);

//             frameInico= frameInico+varia;

//         }while (frameInico<=videoLido->frameFinal);


    //tenho todos os peridos agora tem que fazer os vetores de cada periodo
       //para depois contabilizar

    //para todos os segmentoss
    auto gera_lista_contendo_segmentos = [](int q_inicial, int q_final, std::vector<double> inicioPeriodo, std::vector<double> fimPeriodo,  std::vector<int> vetorPontos){
        std::vector<int> s_vetorPontosSegmentados;
        std::vector<std::vector<int> > s_vetorPontosSegmentadosMatriz;

        for(int ka=0; ka<fimPeriodo.size(); ka++){

            //para todos os quadros
            for(int kb=q_inicial; kb<q_final;kb++){

                //vou testar se esta dentro da segmentação
                //se estiver dentro da segmentação ele pega o valor de pontos
                if((kb>=inicioPeriodo[ka]) && (kb<fimPeriodo[ka])){

                   s_vetorPontosSegmentados.push_back(vetorPontos[kb-q_inicial]);

                }

                //para quando ser o ultimo frma ele estar incluso dentro dos pontos segmentados
                if(kb==q_final){

                    s_vetorPontosSegmentados.push_back(vetorPontos[kb-q_inicial]);

                    qDebug() << "ultimo frame colocado dentro do vetor de segmentação";
                }






            }//fim dos testes dos quadros

            s_vetorPontosSegmentadosMatriz.push_back(s_vetorPontosSegmentados);
            s_vetorPontosSegmentados.clear();


        }


       return s_vetorPontosSegmentadosMatriz;
    };

   // parei por aqui.
   vetorPontosSegmentadosMatriz = gera_lista_contendo_segmentos(videoLido->frameProce, videoLido->frameFinal,
                                                                inicioPeriodo, fimPeriodo, vetorPontos);




//         std::vector<double> latenciaTotal;
//         std::vector<double> duracaoTotal;
//         std::vector<double> frequenciaTotal;
//         std::vector<std::vector<double> > duracaoTotalMatriz;
//         std::vector<std::vector<double> > frequenciaTotalMatriz;

    latenciaTotal= latencia(vetorPontos);
    duracaoTotal = duracaoCategoria(vetorPontos);
    frequenciaTotal = frequenciaCategorias(vetorPontos);
    duracaoTotalMatriz.push_back(duracaoTotal);
    frequenciaTotalMatriz.push_back(frequenciaTotal);
    duracaoTotal.clear();
    frequenciaTotal.clear();



    //para todos os vetores de pontos
    // SAIDA.
    for(int cVePon=0; cVePon <vetorPontosSegmentadosMatriz.size(); cVePon++){
        duracaoTotal = duracaoCategoria(vetorPontosSegmentadosMatriz[cVePon]);
        frequenciaTotal = frequenciaCategorias(vetorPontosSegmentadosMatriz[cVePon]);
        duracaoTotalMatriz.push_back(duracaoTotal);
        frequenciaTotalMatriz.push_back(frequenciaTotal);
        duracaoTotal.clear();
        frequenciaTotal.clear();
    }
}

void telaSegementacao::on_pbTotalRes_clicked()
{
    // esse é o contador que contem o tamanho cViSeg
    //encontra os pontos iniciais e finais



    if(chTCCon){
        // esse é o contador que contem o tamanho cViSeg
        //vi1 = valor inicial primeiro

         vetorPontos = [](int q_processamento, int q_final, analiseEtografica *etografia ){

            std::vector<int> catego_por_quadro;

            bool chUnde=true;
            for(int rl= q_processamento; rl< q_final ; rl++){

                //tem que testar pra todas os pontos

                //para cada transcrição lida
                for(int rj=0;rj<etografia->frameInicial.size();rj++){

                    if((rl>=etografia->frameInicial[rj])&&(rl<etografia->frameFinal[rj])){

//                        qDebug() <<" frame" << rl << etografia->id[rj] << "e a transcrição é a " << rj;

                        catego_por_quadro.push_back(etografia->id[rj]);
//                        quadrosPontos.push_back(rl);
                        chUnde=false;

                    }


                }



                if(chUnde==true){
                    //se não enocntrou nenhuma classificao é undefinido
                    //é caracterizado como menos 1

                    catego_por_quadro.push_back(-1);
                }else{

                    chUnde=true;
                }



            }

            return catego_por_quadro;

        }(videoLido->frameProce, videoLido->frameFinal, etografiaLida );


       // double framesTotaisAnalise = videoLido->frameFinal - videoLido->frameProce;


//        bool chUnde=true;
//        //para cada quadro do v´deio

//        for(int rl=videoLido->frameProce; rl< videoLido->frameFinal ; rl++){

//            //tem que testar pra todas os pontos

//            //para cada transcrição lida
//            for(int rj=0;rj<etografiaLida->frameInicial.size();rj++){

//               if((rl>=etografiaLida->frameInicial[rj])&&(rl<etografiaLida->frameFinal[rj])){

//                   qDebug() <<" frame" << rl << etografiaLida->id[rj] << "e a transcrição é a " << rj;

//                   vetorPontos.push_back(etografiaLida->id[rj]);
//                   quadrosPontos.push_back(rl);
//                   chUnde=false;

//            }else{
//                   //não categorizado

////                vetorPontos.push_back(-1);
////                quadrosPontos.push_back(rl);



//               }


//            }



//            if(chUnde==true){
//                //se não enocntrou nenhuma classificao é undefinido
//                //é caracterizado como menos 1

//                vetorPontos.push_back(-1);
//            }else{

//                chUnde=true;
//            }



//        }

//        chUnde=true;

//        for(int rj=0;rj<etografiaLida->frameInicial.size();rj++){

//           if((videoLido->frameFinal==etografiaLida->frameFinal[rj])){

//               qDebug() <<" frame" << videoLido->frameFinal << etografiaLida->id[rj] << "e a transcrição é a " << rj;

//               vetorPontos.push_back(etografiaLida->id[rj]);
//               quadrosPontos.push_back(videoLido->frameFinal);
//               chUnde=false;

//        }else{
//               //não categorizado

////            vetorPontos.push_back(-1);
////            quadrosPontos.push_back(videoLido->frameFinal);




//           }


//        }

//        if(chUnde==true){
//            //se não enocntrou nenhuma classificao é undefinido
//            //é caracterizado como menos 1

//            vetorPontos.push_back(-1);
//        }else{

//            chUnde=true;
//        }

          auto gera_lista_segmentos = [](double tamanho, double fps, int q_inicial, int q_final, bool r_vetor_entrada){
              std::vector<double> vetor_saida;

              double varia = tamanho * fps; //frames
              double frameInico = q_inicial;

              do{
                  if(r_vetor_entrada){
                      vetor_saida.push_back(frameInico);


                  }else{
                      vetor_saida.push_back(frameInico+varia);
                  }

                  frameInico= frameInico+varia;

              }while (frameInico<=q_final);

              return vetor_saida;
         };

          double tamanho_janela =ui->lieTime->text().toDouble(); //frames

          inicioPeriodo = gera_lista_segmentos(tamanho_janela, videoLido->fps,  videoLido->frameProce,videoLido->frameFinal , true);
          fimPeriodo = gera_lista_segmentos(tamanho_janela, videoLido->fps,  videoLido->frameProce, videoLido->frameFinal , false);


        //fim de encontrar os pontos do vídeo
        //agora tem que segmentar pelo tempo

//         double varia =ui->lieTime->text().toDouble() * videoLido->fps; //frames
//         double frameInico = videoLido->frameProce;
//         do{

//             inicioPeriodo.push_back(frameInico);
//             fimPeriodo.push_back(frameInico+varia);

//             frameInico= frameInico+varia;

//         }while (frameInico<=videoLido->frameFinal);


         //tenho todos os peridos agora tem que fazer os vetores de cada periodo
            //para depois contabilizar

         //para todos os segmentoss
         auto gera_lista_contendo_segmentos = [](int q_inicial, int q_final, std::vector<double> inicioPeriodo, std::vector<double> fimPeriodo,  std::vector<int> vetorPontos){
             std::vector<int> s_vetorPontosSegmentados;
             std::vector<std::vector<int> > s_vetorPontosSegmentadosMatriz;

             for(int ka=0; ka<fimPeriodo.size(); ka++){

                 //para todos os quadros
                 for(int kb=q_inicial; kb<q_final;kb++){

                     //vou testar se esta dentro da segmentação
                     //se estiver dentro da segmentação ele pega o valor de pontos
                     if((kb>=inicioPeriodo[ka]) && (kb<fimPeriodo[ka])){

                        s_vetorPontosSegmentados.push_back(vetorPontos[kb-q_inicial]);

                     }

                     //para quando ser o ultimo frma ele estar incluso dentro dos pontos segmentados
                     if(kb==q_final){

                         s_vetorPontosSegmentados.push_back(vetorPontos[kb-q_inicial]);

                         qDebug() << "ultimo frame colocado dentro do vetor de segmentação";
                     }






                 }//fim dos testes dos quadros

                 s_vetorPontosSegmentadosMatriz.push_back(s_vetorPontosSegmentados);
                 s_vetorPontosSegmentados.clear();


             }


            return s_vetorPontosSegmentadosMatriz;
         };

        // parei por aqui.
        vetorPontosSegmentadosMatriz = gera_lista_contendo_segmentos(videoLido->frameProce, videoLido->frameFinal,
                                                                     inicioPeriodo, fimPeriodo, vetorPontos);




//         std::vector<double> latenciaTotal;
//         std::vector<double> duracaoTotal;
//         std::vector<double> frequenciaTotal;
//         std::vector<std::vector<double> > duracaoTotalMatriz;
//         std::vector<std::vector<double> > frequenciaTotalMatriz;

         latenciaTotal= latencia(vetorPontos);
         duracaoTotal = duracaoCategoria(vetorPontos);
         frequenciaTotal = frequenciaCategorias(vetorPontos);
         duracaoTotalMatriz.push_back(duracaoTotal);
         frequenciaTotalMatriz.push_back(frequenciaTotal);
         duracaoTotal.clear();
         frequenciaTotal.clear();



         //para todos os vetores de pontos
         // SAIDA.
         for(int cVePon=0; cVePon <vetorPontosSegmentadosMatriz.size(); cVePon++){
             duracaoTotal = duracaoCategoria(vetorPontosSegmentadosMatriz[cVePon]);
             frequenciaTotal = frequenciaCategorias(vetorPontosSegmentadosMatriz[cVePon]);
             duracaoTotalMatriz.push_back(duracaoTotal);
             frequenciaTotalMatriz.push_back(frequenciaTotal);
             duracaoTotal.clear();
             frequenciaTotal.clear();
         }




        ui->pbTotGravar->setVisible(true);
        ui->pbTotGravar->setEnabled(true);

//        qDebug() << " foi selecionado par afaze a segmentação do relatorio de TCC";

//       saida_texto_formada_csv = this->grava_csv();


       //        qDebug() << saida_texto;

    }else{

        double intervalo;

        intervalo =(double) parserTCCM->videoLido->frameFinal/parserTCCM->videoLido->fps - (double) parserTCCM->videoLido->frameProce/parserTCCM->videoLido->fps;
        cViSeg= intervalo/ ui->lieTime->text().toDouble();
        cViSegInteiro= intervalo/ ui->lieTime->text().toDouble(); // ta se utilizando do truncamento do inteiro

        if(cViSeg > cViSegInteiro){

            cViSeg++; //"isso serve para criar mais uma segmentacao;"
            chNumeroQuebrado=true;

        }

        double timeInicio= parserTCCM->videoLido->frameProce/parserTCCM->videoLido->fps;
        std::vector<double> framesSeg;

         double varia =ui->lieTime->text().toDouble() *parserTCCM->videoLido->fps;
         double frameInico = parserTCCM->videoLido->frameProce;
       do{

             //            double time= parserTCCM->videoLido->frameProce/parserTCCM->videoLido->fps;
             //            double frame = parserTCCM->videoLido->frameProce;

                         for(int k=0; k<parserTCCM->matrizReMorfo[0].frame.size(); k++ ){
                             if(((parserTCCM->matrizReMorfo[0].frame[k])>=frameInico)&& ((parserTCCM->matrizReMorfo[0].frame[k])< (frameInico+varia))  ){

                                // qDebug() << parserTCCM->matrizReMorfo[0].frame[k];
                                 framesSeg.push_back(parserTCCM->matrizReMorfo[0].frame[k]);


                             }else{

                                // break;
                             }

                         }


                         frameInico= frameInico +varia;

                         if(frameInico<parserTCCM->videoLido->frameFinal){
                             arvoreDeFrames.push_back(framesSeg);

                             framesSeg.clear();

                         }else{

                         }



         }while (frameInico<parserTCCM->videoLido->frameFinal);


        // framesSeg.push_back(parserTCCM->matrizReMorfo[0].frame[parserTCCM->matrizReMorfo[0].frame.size()-1]);
         arvoreDeFrames.push_back(framesSeg);

         framesSeg.clear();




          ui->pbGravarTCCM->setVisible(true);


        qDebug() << " foi selecionado par afaze a segmentação do relatorio de TCCM" << arvoreDeFrames.size();
    }


//    ui->pbTotalRes->

}

void telaSegementacao::on_pbTotGravar_clicked()
{
    //funcao para pegar o nome que sera gravado

    this->on_pbTotalRes_clicked();

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

//    std::vector<double> inicioPeriodo;
//    std::vector<double> fimPeriodo;
//    latenciaTotal= latencia(vetorPontos);
//    duracaoTotalMatriz.push_back(duracaoTotal);
//    frequenciaTotalMatriz.push_back(frequenciaTotal);
    //arrumar hoje

    stream.writeStartElement("sessao");
    stream.writeAttribute("id", QString::number(0));
    stream.writeAttribute("inicio",QString::number(videoLido->frameProce));
    stream.writeAttribute("fim",QString::number(videoLido->frameFinal));

    for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){
        stream.writeStartElement("categoria");
        stream.writeAttribute("idcat", QString::number(cat));
        stream.writeAttribute("name", catalagoLido->nome[cat]);
        stream.writeTextElement("duracao",QString::number(duracaoTotalMatriz[0][cat]*videoLido->fps));
        stream.writeTextElement("frequencia",QString::number(frequenciaTotalMatriz[0][cat]*videoLido->fps));
        stream.writeTextElement("latencia",QString::number(latenciaTotal[cat]*videoLido->fps));
        stream.writeEndElement(); //fecha categoria
    }
     stream.writeEndElement(); //fecha sessao

    //quantidade de segmentação de tempo
    for(int cSegTeg=0; cSegTeg<inicioPeriodo.size(); cSegTeg++ ){
        stream.writeStartElement("sessao");
        stream.writeAttribute("id", QString::number((cSegTeg)));
        stream.writeAttribute("inicio",QString::number(inicioPeriodo[cSegTeg]));

//        if(cSegTeg==(inicioPeriodo.size()-1)){
//            //no ultimo
//            stream.writeAttribute("fim",QString::number(fimPeriodo[cSegTeg]+1));
//            qDebug()<< "entrou no ultimo";
//        }else{
            stream.writeAttribute("fim",QString::number(fimPeriodo[cSegTeg]));
//        }



        for(int cat=0; cat<(catalagoLido->quantidadeDeCategorias);cat++){
            stream.writeStartElement("categoria");
            stream.writeAttribute("idcat", QString::number(cat));
            stream.writeAttribute("name", catalagoLido->nome[cat]);
            stream.writeTextElement("duracao",QString::number(duracaoTotalMatriz[cSegTeg+1][cat]*videoLido->fps));
            stream.writeTextElement("frequencia",QString::number(frequenciaTotalMatriz[cSegTeg+1][cat]));
            stream.writeTextElement("latencia",QString::number(0));
            stream.writeEndElement(); //fecha categoria
        }

        stream.writeEndElement(); //fecha sessao


    }


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

    stream.writeEndElement();


    //magica acontece cViSeg



    stream.writeEndElement(); //fecha totalSessao





    stream.writeEndElement(); //fecha analiseTotalSessao
    stream.writeEndDocument();



    Output.close();

//    parserxmltocsv
    int linha = 16;
    saida_segm = this->_gera_lis_segmetacao(linha);
    parser = new parserXMLtoCSV();


    parser->converteArquivo(nomeGravarCatalago, saida_segm);

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
                videoLido->fps= streamReader.readElementText().toDouble();

                videoLido->controle=false;
            }

        }

    }



    OutEtografia.close();


}

QList<Cell> telaSegementacao::_gera_lis_segmetacao(int linha_gap)
{
    QList<Cell> saida;
    int linha = linha_gap;
    linha += 2;




    int qnt_segmentos = inicioPeriodo.size();
    for(int tot=1; tot< qnt_segmentos+1; tot++){
        add_cell(&saida, "A"+QString::number(linha),"RESULTS FOR");
        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),"Segmentation initiated at " + QString::number( inicioPeriodo[tot-1]/videoLido->fps));
        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),
                 ";  Segmentation terminated at ;" + QString::number(fimPeriodo[tot-1]/videoLido->fps));

//        texto_saida = texto_saida + "\n RESULTS FOR \n Segmentation initiated at ;" + QString::number( inicioPeriodo[tot-1]/videoLido->fps) ;
//        texto_saida = texto_saida + ";  Segmentation terminated at ;" + QString::number(fimPeriodo[tot-1]/videoLido->fps) + "\n\n";
        linha += 1;
        add_cell(&saida, "A"+QString::number(linha),"Category");
        add_cell(&saida, "B"+QString::number(linha),"Duration(s)");
        add_cell(&saida, "C"+QString::number(linha),"Freq.");



//        texto_saida = texto_saida + "Category" + ";" + "Duration(s)" + ";" + "Freq." + "\n";
        int qnt_categorias = catalagoLido->nome.size();
        for(int fr=0; fr< qnt_categorias ; fr++){
            linha += 1;
            add_cell(&saida, "A"+QString::number(linha),catalagoLido->nome[fr]);
            add_cell(&saida, "B"+QString::number(linha),QString::number(duracaoTotalMatriz[tot][fr]), true);
            add_cell(&saida, "C"+QString::number(linha),QString::number(frequenciaTotalMatriz[tot][fr]), true);


//            texto_saida = texto_saida + catalagoLido->nome[fr] + ";" +
//                    QString::number(duracaoTotalMatriz[tot][fr])  + ";" +  ///videoLido->fps
//                    QString::number(frequenciaTotalMatriz[tot][fr]) + ";" ;

//                texto_saida = texto_saida + ";\n";


        }

    }
    return saida;
}

QString telaSegementacao::conPontoVirgula(double num)
{
    QByteArray numeroArray,numeroArraySaida;
    numeroArray = QByteArray::number(num);
    numeroArraySaida =numeroArray;


    numeroArraySaida.replace(QByteArray("."),QByteArray(","));
    return  QString::fromLatin1( numeroArraySaida);

}

std::vector<double> telaSegementacao::latencia(std::vector<int> entrada)
{

    //para cada categoria do catalogo
    std::vector<double> latenciaCateogrias;
    for(int cCat=0; cCat<catalagoLido->quantidadeDeCategorias;cCat++){

        double somLa=0;
        //para cada frame analisado
        for(int cFra=0; cFra<(entrada.size()); cFra++){

            if(entrada[cFra]!=cCat){

                somLa=somLa+ 1 ;

            }else{

                break;

            }


        }


        latenciaCateogrias.push_back(somLa/videoLido->fps);
        somLa=0;





    }



       return latenciaCateogrias;



}

std::vector<double> telaSegementacao::duracaoCategoria(std::vector<int> entrada)
{
    std::vector<double> duracaoCateogrias;

    double somLa=0;
    for(int cCat=0; cCat<catalagoLido->quantidadeDeCategorias;cCat++){

         for(int cFra=0; cFra<(entrada.size()); cFra++){

             if(entrada[cFra]==cCat){

                 somLa=somLa+ 1 ;

             }


         }

        duracaoCateogrias.push_back(somLa/videoLido->fps);
        somLa=0;
    }


    return duracaoCateogrias;

}

std::vector<double> telaSegementacao::frequenciaCategorias(std::vector<int> entrada)
{
    std::vector<double> frequenciaoCateogrias;
    bool cBSub  =false;
    bool cBDescida = true;

    double somLa=0;
    for(int cCat=0; cCat<catalagoLido->quantidadeDeCategorias;cCat++){

         for(int cFra=0; cFra<(entrada.size()); cFra++){

             if((entrada[cFra]==cCat)&&(cBDescida)){


                 cBSub = true;
                 somLa=somLa+ 1 ;
                 cBDescida =false;

             }

             if((cBSub)&&(entrada[cFra]!=cCat)){
                 cBSub=false;
                 cBDescida=true;

             }



         }

        frequenciaoCateogrias.push_back(somLa);
        somLa=0;
        cBSub  =false;
        cBDescida = true;
    }


    return frequenciaoCateogrias;
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

void telaSegementacao::on_pbTCCMfile_clicked()
{
//    fonteVideoETOXML = QFileDialog::getOpenFileName(
//                this,
//                tr("Open File"),
//                "C://Users//Bio//Desktop//videos//",
//                "Video Files (* .tkin)"
//                );


//    parserTCCM = new parserXML();
//    parserTCCM->readTCCM(fonteVideoETOXML);

//    chTCCon= false;

//    ui->lblFrameNome->setText(parserTCCM->videoLido->nome);
//    ui->lblFrameInicial->setText(QString::number(parserTCCM->videoLido->frameProce/parserTCCM->videoLido->fps));
//    ui->lblFrameFinal->setText(QString::number(parserTCCM->videoLido->frameFinal/parserTCCM->videoLido->fps));
//    ui->pbCaTotalSe->setEnabled(false);
//    ui->pbTCCMfile->setEnabled(false);
//    ui->pbTotalRes->setEnabled(true);
//    lerETOXML(fonteVideoETOXML);
}

void telaSegementacao::on_pbGravarTCCM_clicked()
{
//    ui->pbTotalRes->click();
//    connect(ui->pbGravarTCCM, SIGNAL(clicked()), this, SLOT(on_pbTotalRes_clicked()));
//    ui->pbTCCMfile->clicked();
//    this->on_pbTotalRes_clicked();


    QString teste2;

    teste2 = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                fonteVideoETOXML,
                "Video Files (*.csv)"
                );
    outGravador.setFileName(teste2);
    outGravador.open(QIODevice::WriteOnly | QIODevice::Text );

    QTextStream csvGravador(&outGravador);

    csvGravador <<"sep=; \n";
    csvGravador <<"EthoWatcher Open Source \n";
//    csvGravador <<"Observer" << experimentador.nome.toLatin1() << "\n";
//    csvGravador <<"Lab" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"Experiment" << "\n";
    csvGravador <<"Animal" << "\n";
    csvGravador <<"Weight" << "\n";
    csvGravador <<"sex" << "\n";
    csvGravador <<"Treatment/condition" << "\n";
    csvGravador <<"Other Info" << "\n";
    //csvGravador <<experimentador.nome.toLatin1() <<";" << experimentador.lab.toLatin1() << "\n";
    csvGravador <<"WARNING: in this version, decimals are separated by COMMA \n";
//    csvGravador <<"video file \n";

    csvGravador << "ETHOGRAPHY REPORT" << "\n";
////    csvGravador << "nome, fps, frame analisado inicial, frame analisado final \n";
    csvGravador << "video file is " << parserTCCM->videoLido->nome<< "\n";

    csvGravador << "Analysis initiated at " << conPontoVirgula( parserTCCM->videoLido->frameProce /parserTCCM->videoLido->fps)  << " (seconds) of the video file \n ";
    csvGravador << "Analysis terminated at " << conPontoVirgula(parserTCCM->videoLido->frameFinal / parserTCCM->videoLido->fps) << " (seconds) of the video file \n";
    csvGravador <<"\n";
//    csvGravador <<"informacoes do catalogo analisado: \n"
//    }
    csvGravador << "\n";
    csvGravador << "\n";
    csvGravador << "\n";

    double duracao=0;


    for(int ka1=0; ka1< arvoreDeFrames.size(); ka1++){ //para todas as segmentações


        csvGravador << "\n";
        csvGravador << "\n";
        csvGravador << "\n";
        double iniSeg;
        double fimSeg;

        if(ka1== arvoreDeFrames.size()){
            iniSeg = arvoreDeFrames[ka1][0];
            fimSeg = arvoreDeFrames[ka1][arvoreDeFrames[ka1].size()]+1;

        }else{
            iniSeg = arvoreDeFrames[ka1][0];
            fimSeg = arvoreDeFrames[ka1][arvoreDeFrames[ka1].size()-1];
        }

        qDebug() << fimSeg;


        csvGravador <<  "Results FOR;\n"      <<    "Segmentation initiated at;"    << conPontoVirgula(iniSeg/parserTCCM->videoLido->fps) << "Number of pixels;"     << "Area (in cm2);";
        csvGravador <<  "Segmentation initiated at;"    << conPontoVirgula(fimSeg/parserTCCM->videoLido->fps);
        csvGravador <<     "\n" ;

        csvGravador <<  ";"      <<    ";"    << "Number of pixels;"     << "Area (in cm2);";
        csvGravador <<  "Horizontal coordinate of the centroid;"      <<    "Vertical coordinate of the centroid;";
        csvGravador <<  "AA(in degrees);" <<"Height of the animal;" <<"width of the animal;" <<"Object Detected;" ;
        csvGravador << "Distance travelled by the centroid;" << "Distance travelled by the centroid;";
        csvGravador << "Variation of Area (from the former frame);";
        csvGravador << "Variation of Height of animal (from the former frame);";
        csvGravador << "Variation of width of animal (from the former frame);";
        csvGravador << "Variation of Angule of animal;";
        csvGravador << "Maximum variation distance travel by the centroid;" << "\n";


        //a area de intesse 0 é sempre a altura e largura da imagem original;

        csvGravador << "frames;" << "second;" << "of the animal's body;" << "of the animal's body;";
        csvGravador << "(in pixels, from" << "0 to "<< parserTCCM->areasDeInteresse.width[0] <<  " );" << "(in pixels, from " <<  "0 to " << parserTCCM->areasDeInteresse.heigth[0] << " );";
        csvGravador <<  "Angle between animal and Horizontal coordinate ;" << "in cm;" << "in cm;" <<"true or false;" ;
        csvGravador << "(in pixels);" << "(in cm);";
        csvGravador << "in cm2;";
        csvGravador << "in cm;";
        csvGravador << "in cm;";
        csvGravador << "in degrees;" ;
        csvGravador << "true or false" << "\n";



        for(int kj= 0; kj < parserTCCM->matrizReMorfo[0].frame.size(); kj++){ //para cada um dos frames processados no video

            int ki=0;

           if((parserTCCM-> matrizReMorfo[0].frame[kj]>= iniSeg)&&(parserTCCM-> matrizReMorfo[0].frame[kj] <= fimSeg)){


               csvGravador << parserTCCM-> matrizReMorfo[0].frame[kj] << ";"<< conPontoVirgula((parserTCCM->matrizReMorfo[0].frame[kj] ) / parserTCCM-> videoLido->fps) << ";" ;
               csvGravador << conPontoVirgula(parserTCCM->matrizReMorfo[ki].area[kj]) << ";" << conPontoVirgula(parserTCCM->matrizReMorfo[ki].area[kj]/(parserTCCM->videoLido->escala*parserTCCM->videoLido->escala))<< ";";
               csvGravador << conPontoVirgula(parserTCCM->matrizReMorfo[ki].centroidX[kj]) << ";" << conPontoVirgula(parserTCCM->matrizReMorfo[ki].centroidY[kj])<<";";
               csvGravador << conPontoVirgula(parserTCCM->matrizReMorfo[ki].anguloObj[kj]) << ";" ;
               csvGravador << conPontoVirgula(parserTCCM->matrizReMorfo[ki].altura[kj]/(parserTCCM->videoLido->escala)) << ";" ;
               csvGravador << conPontoVirgula(parserTCCM->matrizReMorfo[ki].largura[kj]/(parserTCCM->videoLido->escala)) << ";" ;
   //            reMorfo.tamanhoObj

              if(parserTCCM-> matrizReMorfo[ki].objetoEncontrado[kj]){
                  csvGravador << "true;";
              }else{
                  csvGravador << "false;";
              }
              csvGravador << conPontoVirgula(parserTCCM->matrizReCinema[ki].varDistancia[kj]) << ";" << conPontoVirgula(parserTCCM->matrizReCinema[ki].varDistancia[kj]/(parserTCCM->videoLido->escala))<< ";";
              csvGravador << conPontoVirgula(parserTCCM->matrizReCinema[ki].varArea[kj]/(parserTCCM->videoLido->escala*parserTCCM->videoLido->escala) ) << ";" ;
              csvGravador << conPontoVirgula(parserTCCM->matrizReCinema[ki].varAltura[kj]/(parserTCCM->videoLido->escala) ) << ";" ;
              csvGravador << conPontoVirgula(parserTCCM->matrizReCinema[ki].varLargura[kj]/(parserTCCM->videoLido->escala) ) << ";" ;
              csvGravador << conPontoVirgula(parserTCCM->matrizReCinema[ki].varAngular[kj] ) << ";" ;


              if(parserTCCM->matrizReCinema[ki].ruidoMaxVaria[kj] ){
                     csvGravador << "true;";
           }else{

                  csvGravador << "false;";

              }

              //reCinema.ruidoMaxVaria
   //reCinema.varTamObjeto
   //reCinema.varArea
              //

   //           reCinema.varAngular.push_back(streamReader.attributes().value("Van").toDouble());
   //           reCinema.varArea.push_back(streamReader.attributes().value("Var").toDouble());
   //           reCinema.varDistancia.push_back(streamReader.attributes().value("Vd").toDouble());
   //           reCinema.varTamObjeto.push_back(streamReader.attributes().value("VtoP").toDouble());



               csvGravador << "\n";

           }else{

             //  qDebug() << "fim da seção " <<ka1 << "do frame "<<parserTCCM-> matrizReMorfo[0].frame[kj] ;
           }






        }



    }


      outGravador.close();



}
