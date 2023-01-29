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
#include "teaconcordancia.h"
#include "ui_teaconcordancia.h"
#include "../Agreement/ui/Reliability.h"

teaConcordancia::teaConcordancia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teaConcordancia)
{
    ui->setupUi(this);
    ui->swPrincipal->setCurrentIndex(0);
    ui->swFleissKappa->setCurrentIndex(0);
    ui->swKohoneKappa->setCurrentIndex(0);

    ui->pbKohone1->setVisible(false);
}

teaConcordancia::~teaConcordancia()
{
    delete ui;
}

void teaConcordancia::on_pbKohone1_clicked()
{
    ui->swPrincipal->setCurrentIndex(1);
}

void teaConcordancia::on_pbFleissKappa_clicked()
{
    ui->swPrincipal->setCurrentIndex(2);
}

void teaConcordancia::on_pushButton_5_clicked()
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

    caminhoAnalise.push_back(fonteVideoETOXML);

    dadosDosVideos.push_back(*videoLido); //forma pratica de fazer um vetor com varios videos lidos

    etografiaDosVideos.push_back(*etografiaLida); // forma pratica de fazer um vetor com varias analises etogrificas

    catalagoDosVideos.push_back(*catalagoLido); //forma pratica de fazer um vetor de alguma variavel


    quantidadeDeVideo++;

    ui->tabDadCat->insertRow(ui->tabDadCat->rowCount());
    ui->tabDadCat->setItem(ui->tabDadCat->rowCount()-1,0,new QTableWidgetItem(fonteVideoETOXML));
   // ui->tabDadCat->setItem(ui->tabDadCat->rowCount()-1,1,new QTableWidgetItem(ui->leAtalho->text()));


    //configurando TableWidget
    ui->tabDadCat->resizeColumnsToContents();
    ui->tabDadCat->clearSelection();
    ui->tabDadCat->clearFocus();

    if(quantidadeDeVideo==2){

        ui->pushButton_5->setEnabled(false);
    }


}

void teaConcordancia::on_pushButton_6_clicked()
{
    //cria um vetor com alocação dinamica de memoria no qual ele tem o tamanho de quantidadeDeVideo
        //quantidade de video é um contador que soma toda vez que adiciona um novo video
        etografiaKoho = new analiseEtografica[quantidadeDeVideo];
        videosKoho = new dadosVideo[quantidadeDeVideo];
        catalagoKoho = new catalago[quantidadeDeVideo];
        int quantCate=0; //quantidade de categoria para fazer o vetor de categoria undefinida

        for(int j=0; j<quantidadeDeVideo;j++){

            *(etografiaKoho + j) = etografiaDosVideos[j]; //aponta para o seu respectivo vetor
            *(videosKoho +j)    =  dadosDosVideos[j];
            *(catalagoKoho+j)   = catalagoDosVideos[j];

        }

        //setando os nomes


            ui->lblVideo1->setText(caminhoAnalise[0]);
            ui->lblVideo2->setText(caminhoAnalise[1]);



        //conversão dos ponto
        int qDPontos=0;
        int pontos=0;
        //bool entrou= false;
        int v=0;
        int lido;
    //    std::vector<int> frameInfo;  //é uma linha dinahmica


        for(v=0; v<quantidadeDeVideo; v++){
        //m é giaul ao id do catalago 3 pq são 3 no catalgo
        for(int m=0; m<catalagoKoho[0].quantidadeDeCategorias; m++){

    //        std::vector<double> fInicial;
    //        std::vector<double> fFinal;
            fInicial.clear();
            fFinal.clear();
            frameInfo.clear();
            pontos=0;
            //encontra as regioões de determinada categoria do catalago
            //encontra de acordo com o valor de m
            for(qDPontos=0; qDPontos<etografiaKoho[v].quantidadeDePontos; qDPontos++){


                if(etografiaKoho[v].id[qDPontos] ==m){
                    fInicial.push_back(etografiaKoho[v].frameInicial[qDPontos]);
                    fFinal.push_back(etografiaKoho[v].frameFinal[qDPontos]);
                    pontos++;
                }



            }
            //qDPontos é o numero de pontos postos

                //gera um for com um valor inicial igual ao frame inicial do video
                //gera umf or com um valor final de acordo com o valor final do video
               for(int frame= videosKoho[v].frameInicial; frame <
                   videosKoho[v].frameFinal; frame++){
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
               frameVideo.push_back(frameInfo);
               frameInfo.clear();
               fInicial.clear();
               fFinal.clear();

           }


        //e vai para a analise da categoria indefinida
        std::vector<int> claUndefinida;
        quantCate = catalagoKoho[0].quantidadeDeCategorias;


     bool entra=false;

     //tal
        for(int p=0; p< (videosKoho[0].frameFinal-videosKoho[0].frameInicial);
            p++){

            //testa todas as  possibildiade de videos e de categorias do catalago
            for(int z=0; z<quantCate;z++){
                //for(int y=0; y<2; y++){

                    //se alguma delas for diferente de vazio(-1) ele grava como vazio
                    //vazio siginifica que não esta dentro da categoria testada
                    //valor padrao
                lido=frameVideo[z][p];
                if((lido!=-1)&&(!entra)){

                    claUndefinida.push_back(-1);
                    entra=true;
                   // break;

                   // igualdade[y+z]=false;
                    }
                //}

            }

            if(!entra){
                claUndefinida.push_back(quantCate); //o indefinido é classificado como ultimo

            }
            entra=false;



        }
        //ao fim ele grava o vetor em uma matriz
        frameVideo.push_back(claUndefinida);


        // e ao fim de todas as operações ele grava o valor da matriz em uma
        //matriz de 3 dimensões
        //um cubo de pontos que possui pra cada
        //[a][b][c]
          //[a] numero do video
          //[b] categoria
          //[c] qtd de frame.
        //grava o [b] e [c] no [a]


            anaEtoDosVideos.push_back(frameVideo);
            frameVideo.clear();


    }


        //nesse botão ele faz a analise da matriz cubica de pontos
        //    //quantidade de frames

        //matriz de acordo
        //primeiro ele cria um vetor de pontos com a quantidade total de pontos

        for(int j=0; j<(catalagoKoho[0].quantidadeDeCategorias+1); j++){
            for(int k=0; k<(catalagoKoho[0].quantidadeDeCategorias+1); k++){

            cohoKappa.push_back(0);
            }
        }

        int quantKappa=0;


        //encontrando a concordancia

                //para cada categoria do catalago mais a categoria indefinida
               for(int quantVideo=0; quantVideo<(catalagoKoho[0].quantidadeDeCategorias+1);quantVideo++){

                    //para cada frame do video
                   for(int qq=0; (qq<videosKoho[0].frameFinal- videosKoho[0].frameInicial)

                       ;qq++){

                        //para cada categoria do catalado
                    for(int m=0; m<(catalagoKoho[0].quantidadeDeCategorias+1); m++ ){

                            //o programa testa se o vator de pontos do video 2 é
                            //igual ao do video 1
                            //se forem ele adiciona 1 a qual categoria

                         if((anaEtoDosVideos[0][quantVideo][qq]==quantVideo)&&
                           (anaEtoDosVideos[1][m][qq]==m)){

                             cohoKappa[quantKappa+m]=cohoKappa[quantKappa+m]+1;


                      }



                   }


                }
                quantKappa += catalagoKoho[0].quantidadeDeCategorias+1;

             }

    //           std::vector<int> somatorioLinha;
                int soma=0;
                int sCategoria=0;
               for(int m=0; m<(catalagoKoho[0].quantidadeDeCategorias+1);m++){
                    soma=0;

                   for(int n=0; n<(catalagoKoho[0].quantidadeDeCategorias+1);n++){

                   soma= soma +cohoKappa[sCategoria+n];

                   }

                    sCategoria=sCategoria+ catalagoKoho[0].quantidadeDeCategorias+1;
                   somatorioLinha.push_back(soma);

               }


    //           std::vector<int> somatorioColuna;
                sCategoria=0;
               for(int m=0; m<(catalagoKoho[0].quantidadeDeCategorias+1);m++){
                    soma=0;

                   for(int n=0; n<((catalagoKoho[0].quantidadeDeCategorias+1)*
                                   (catalagoKoho[0].quantidadeDeCategorias+1))
                       ;n+=(catalagoKoho[0].quantidadeDeCategorias+1)){

                   soma= soma +cohoKappa[m+n];

                   }

                   somatorioColuna.push_back(soma);

               }

               //fim de encontrar a concordancia
               //encontrando os totais


               for(int q=0;q<(catalagoKoho[0].quantidadeDeCategorias+1);q++){
                   somatorioTotal=somatorioTotal+somatorioColuna[q];

               }





               //inicio de mostrar a tabela




               ui->tabCoKapp->setColumnCount(catalagoKoho[0].quantidadeDeCategorias+1+1);

               for(int k=0; k<catalagoKoho[0].quantidadeDeCategorias+1; k++){

                    if(k<catalagoKoho[0].quantidadeDeCategorias){
                        titulos << catalagoKoho[0].nome[k];
                    }else{

                        titulos << "Undefinido" << "Somatório";
                    }



               }

           //colocando os valores da tabela de concordando no GUI
               ui->tabCoKapp->setHorizontalHeaderLabels(titulos);

                        int loopContador=0;
                        int tabela;
                        tabela= catalagoKoho[0].quantidadeDeCategorias+1;

                        for(int k=0;k<(catalagoKoho[0].quantidadeDeCategorias+1);k++){
                                ui->tabCoKapp->insertRow(ui->tabCoKapp->rowCount());
                                //cria uma nova linha
                                //categoria

                                int ja;
                                for(ja=0; ja<(catalagoKoho[0].quantidadeDeCategorias+1); ja++){
                                    //no valor zero coloca
                                  ui->tabCoKapp->setItem(ui->tabCoKapp->rowCount()-1
                                                           ,ja,new QTableWidgetItem(
                                                               QString::number(cohoKappa[loopContador])));

                                  loopContador++;
                                }



                                  ui->tabCoKapp->setItem(ui->tabCoKapp->rowCount()-1
                                                           ,tabela,new QTableWidgetItem(
                                                               QString::number(somatorioLinha[k])));



                                //escreve o ultimo valor que é a soma

                        }

                        int ma;
                        ui->tabCoKapp->insertRow(ui->tabCoKapp->rowCount());

                        for( ma=0;ma<(catalagoKoho[0].quantidadeDeCategorias+1);ma++)
                        {


                        ui->tabCoKapp->setItem(ui->tabCoKapp->rowCount()-1
                                                 ,ma,new QTableWidgetItem(
                                                     QString::number(somatorioColuna[ma])));

                        }


                        ui->tabCoKapp->setItem(ui->tabCoKapp->rowCount()-1
                                                 ,tabela,new QTableWidgetItem(
                                                     QString::number(somatorioTotal)));




                         ui->tabCoKapp->setVerticalHeaderLabels(titulos);


    //    int a=frameVideo[2][2];
    //    ui->label->setText(QString::number(a));

                         //    std::vector< std::vector<float> > porcentageTabela;
                         //    std::vector<float> porcentagemLinha;

                             //encontra a tabela de porcentagem
                             //+1 por causa da clase indefinida
                             int somaAjuda=0;
                             float grava;
                             for(int l1=0;l1<(catalagoKoho[0].quantidadeDeCategorias+1);l1++){

                                 porcentagemLinha.clear();

                                 for(int c1=0;c1<(catalagoKoho[0].quantidadeDeCategorias+1);c1++){


                                      grava= (float) cohoKappa[c1+somaAjuda]/somatorioTotal;


                                     porcentagemLinha.push_back(grava);

                                 }

                                  somaAjuda+=catalagoKoho[0].quantidadeDeCategorias+1;

                                 porcentageTabela.push_back(porcentagemLinha);

                             }

                             //até aqui enconrta a tabela de porcentagem apenas da tabela falta do somatorio

                             float grava2;
                             for(int l2=0;l2<(catalagoKoho[0].quantidadeDeCategorias+1);l2++){

                                  porcentagemLinha.clear();
                                  porcentagemLinha=porcentageTabela[l2];

                                  grava2= (float)somatorioLinha[l2]/somatorioTotal;

                                  porcentagemLinha.push_back(grava2);


                                  porcentageTabela[l2]=porcentagemLinha;
                             }

                             //cria a ultima linha da tabela de porcentagem
                             //que é a linha do somatorio


                             float grava3;
                             porcentagemLinha.clear();

                             for(int l3=0;l3<(catalagoKoho[0].quantidadeDeCategorias+1);l3++){


                                 grava3= (float)somatorioColuna[l3]/somatorioTotal;

                                 porcentagemLinha.push_back(grava3);


                             }

                             grava3= (float) somatorioTotal/somatorioTotal;


                             porcentagemLinha.push_back(grava3);
                             porcentageTabela.push_back(porcentagemLinha);


                             //mostra a tabela;

                             ui->tabPoKapp->setColumnCount(catalagoKoho[0].quantidadeDeCategorias+1+1);

                             ui->tabPoKapp->setHorizontalHeaderLabels(titulos);


                             for(int l4=0;l4<(catalagoKoho[0].quantidadeDeCategorias+1+1);l4++){
                                     ui->tabPoKapp->insertRow(ui->tabPoKapp->rowCount());
                                     //cria uma nova linha
                                     //categoria

                                     for(int c4=0; c4<(catalagoKoho[0].quantidadeDeCategorias+1+1); c4++){
                                         //no valor zero coloca
                                       ui->tabPoKapp->setItem(ui->tabPoKapp->rowCount()-1
                                                                ,c4,new QTableWidgetItem(
                                                                    QString::number(porcentageTabela[l4][c4])));


                                     }
                             }


                             ui->tabPoKapp->setVerticalHeaderLabels(titulos);

                             //gerou a ultima linha de porcentagem;

                             int novoContador=0;
                              for(int l5=0;l5<(catalagoKoho[0].quantidadeDeCategorias+1);l5++){

                                  cohoK1= (float) cohoKappa[l5+novoContador]+cohoK1;

                                  novoContador += catalagoKoho[0].quantidadeDeCategorias+1;
                              }

                              cohoK1= (float) cohoK1/somatorioTotal;

                              ui->leK1->setText(QString::number(cohoK1));


                              int ultimaPosicao= (catalagoKoho[0].quantidadeDeCategorias+1);


                              for(int cont=0; cont<(catalagoKoho[0].quantidadeDeCategorias+1);cont++ ){

                                  cohoK2= (float)cohoK2 + porcentageTabela[ultimaPosicao][cont] * porcentageTabela[cont][ultimaPosicao];

                              }

                              ui->leK2->setText(QString::number(cohoK2));


                              cohoKappaResultado= (float) (cohoK1-cohoK2)/(1-cohoK2);

                              ui->leCKappa->setText(QString::number(cohoKappaResultado));



               ui->swKohoneKappa->setCurrentIndex(1);
}

void teaConcordancia::on_pbCohenGravar_clicked()
{
    //funcao para pegar o nome que sera gravado

    nomeGravarCatalago = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Kohone Kappa Files (*.kkf)"
               );

    Output.setFileName(nomeGravarCatalago);



    Output.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&Output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento
//    if(ui->cbTKohone->isChecked()){

//       Output.write("\n<?xml-stylesheet type=\"text/xsl\" href=\"analiseKohoneEstilo.xsl\"?>");
//        ui->wAlertTotal2->setVisible(true);
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

    int ia;
    for(ia=0;ia<catalagoLido->quantidadeDeCategorias;ia++){

       stream.writeStartElement("categoria");
       stream.writeAttribute("id", QString::number(ia));
       stream.writeAttribute("nome",catalagoLido->nome[ia]);
       stream.writeEndElement();

       }
    stream.writeStartElement("categoria");
    stream.writeAttribute("id", QString::number(ia));
    stream.writeAttribute("nome","Não Categorisado");
    stream.writeEndElement();

    stream.writeStartElement("categoria");
    stream.writeAttribute("id", QString::number(ia+1));
    stream.writeAttribute("nome","Somatório");
    stream.writeEndElement();


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
        //caminhoAnalise
        //quantidadeDeVideo

    for(int qdv=0;qdv<quantidadeDeVideo;qdv++){

        stream.writeStartElement("categoriaKK");
        stream.writeAttribute("id", 0);
        stream.writeAttribute("tipo",catalagoKoho[qdv].tipoAnalise);
        stream.writeTextElement("caminhoAnalis"
                                "eEto",caminhoAnalise[qdv]);
        stream.writeEndElement();

    }




    stream.writeEndElement(); //fecha analises


    stream.writeEndElement(); //fecha dadosAnaliseEtografica



    stream.writeStartElement("analiseKohoneKappa");

    // stream.writeStartElement("sessoes");

     //analiseSequencial.dados
//    for(int se2=0;se2<cViSeg;se2++){
        stream.writeStartElement("tabelaConcordancia");
//        stream.writeAttribute("id", QString::number(0));

        int contadorQuant=0;
        int cata=0;
        int cat=0;
        for(cat=0; cat<(catalagoLido->quantidadeDeCategorias+1);cat++){

            stream.writeStartElement("categoriaKK");
            stream.writeAttribute("idcat", QString::number(cat));
            if(cat<catalagoLido->quantidadeDeCategorias){
               stream.writeAttribute("nome", catalagoKoho[0].nome[cat]);
            }else{

                 stream.writeAttribute("nome", "Não Categorizado");
            }





            for(cata=0; cata<(catalagoLido->quantidadeDeCategorias+1);cata++){
                //cohoKappa
                stream.writeStartElement("caAnaSeg");
                stream.writeAttribute("idcat", QString::number(cata));
                stream.writeAttribute("quant", QString::number(cohoKappa[cata+contadorQuant]));
                stream.writeEndElement(); //fecha sessao
            }


            stream.writeStartElement("caAnaSeg");
            stream.writeAttribute("idcat", QString::number(cata));
            stream.writeAttribute("quant", QString::number(somatorioLinha[cat]));
            stream.writeEndElement(); //fecha sessao

            stream.writeEndElement(); //fecha categoria
            contadorQuant+=catalagoLido->quantidadeDeCategorias+1;

        }

     //   stream.writeEndElement(); //fecha

//somatorio

        stream.writeStartElement("categoriaKK");
        stream.writeAttribute("idcat", QString::number(cat));
        stream.writeAttribute("nome", "Somatorio");

        for(cata=0; cata<(catalagoLido->quantidadeDeCategorias+1);cata++){
            //cohoKappa
            stream.writeStartElement("caAnaSeg");
            stream.writeAttribute("idcat", QString::number(cata));
            stream.writeAttribute("quant", QString::number(somatorioColuna[cata]));
            stream.writeEndElement(); //fecha sessao
        }

        stream.writeStartElement("caAnaSeg");
        stream.writeAttribute("idcat", QString::number(cata));
        stream.writeAttribute("quant", QString::number(somatorioTotal));

        stream.writeEndElement(); //fecha sessao

        stream.writeEndElement(); //fecha tabela concordancia

        stream.writeEndElement(); //fecha tabela concordancia a mais

        stream.writeStartElement("tabelaPorcentagem");

        for(int c10=0;c10<(catalagoKoho[0].quantidadeDeCategorias+1+1);c10++){


            stream.writeStartElement("categoriaKK");
            stream.writeAttribute("idcat", QString::number(c10));
            if(c10<catalagoLido->quantidadeDeCategorias){
               stream.writeAttribute("nome", catalagoKoho[0].nome[c10]);
            }else if(c10==(catalagoLido->quantidadeDeCategorias+1)){

                 stream.writeAttribute("nome", "Não Categorizado");
            }else if(c10<(catalagoLido->quantidadeDeCategorias+1)){

                stream.writeAttribute("nome", "Somatorio");

            }


            for(int c11=0;c11<(catalagoKoho[0].quantidadeDeCategorias+1+1);c11++){

                stream.writeStartElement("caAnaSeg");
                stream.writeAttribute("idcat", QString::number(c11));
                stream.writeAttribute("porcent", QString::number(porcentageTabela[c10][c11]));
                stream.writeEndElement();//fecha categoria

            }

            stream.writeEndElement();//fecha categoria

        }

        //stream.writeTextElement("nome","lalalalal");


        stream.writeEndElement();//fecha tabelaPorcentagem

            stream.writeStartElement("resultadoFinal");

            stream.writeTextElement("k1",QString::number(cohoK1));
            stream.writeTextElement("k2",QString::number(cohoK2));
            stream.writeTextElement("indiceKohoneKappa",QString::number(cohoKappaResultado));


            stream.writeEndElement(); //fechaResultadoFinal

 //       stream.writeEndElement(); //fecha
    stream.writeEndElement();//fecha analise KohoneKappa

    stream.writeEndElement(); //fecha analiseTotalSessao
    stream.writeEndDocument();



    Output.close();
    parser = new parserXMLtoCSV();

//    TA DANDO PROBLEMA
//    QList<Cell> saida;
//    parser->converteArquivo(nomeGravarCatalago, saida);
}

void teaConcordancia::on_pbCarregarFleis_clicked()
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

    caminhoAnalise.push_back(fonteVideoETOXML);

    dadosDosVideos.push_back(*videoLido); //forma pratica de fazer um vetor com varios videos lidos

    etografiaDosVideos.push_back(*etografiaLida); // forma pratica de fazer um vetor com varias analises etogrificas

    catalagoDosVideos.push_back(*catalagoLido); //forma pratica de fazer um vetor de alguma variavel


    quantidadeDeVideo++;

    ui->tabDadCat_2->insertRow(ui->tabDadCat_2->rowCount());
    ui->tabDadCat_2->setItem(ui->tabDadCat_2->rowCount()-1,0,new QTableWidgetItem(fonteVideoETOXML));
   // ui->tabDadCat->setItem(ui->tabDadCat->rowCount()-1,1,new QTableWidgetItem(ui->leAtalho->text()));


    //configurando TableWidget
    ui->tabDadCat_2->resizeColumnsToContents();
    ui->tabDadCat_2->clearSelection();
    ui->tabDadCat_2->clearFocus();



}


//vou trabalhar
//tabFleKapp
void teaConcordancia::on_pbAnaFleissKappa_clicked()
{
    //cria um vetor com alocação dinamica de memoria no qual ele tem o tamanho de quantidadeDeVideo
        //quantidade de video é um contador que soma toda vez que adiciona um novo video
        etografiaKoho = new analiseEtografica[quantidadeDeVideo];
        videosKoho = new dadosVideo[quantidadeDeVideo];
        catalagoKoho = new catalago[quantidadeDeVideo];
        int quantCate=0; //quantidade de categoria para fazer o vetor de categoria undefinida

        for(int j=0; j<quantidadeDeVideo;j++){

            *(etografiaKoho + j) = etografiaDosVideos[j]; //aponta para o seu respectivo vetor
            *(videosKoho +j)    =  dadosDosVideos[j];
            *(catalagoKoho+j)   = catalagoDosVideos[j];

        }

        //setando os nomes


            ui->lblVideo1->setText(caminhoAnalise[0]);
            ui->lblVideo2->setText(caminhoAnalise[1]);



        //conversão dos ponto
        int qDPontos=0;
        int pontos=0;
        //bool entrou= false;
        int v=0;
        int lido;
    //    std::vector<int> frameInfo;  //é uma linha dinahmica


        for(v=0; v<quantidadeDeVideo; v++){
        //m é giaul ao id do catalago 3 pq são 3 no catalgo
        for(int m=0; m<catalagoKoho[0].quantidadeDeCategorias; m++){

    //        std::vector<double> fInicial;
    //        std::vector<double> fFinal;
            fInicial.clear();
            fFinal.clear();
            frameInfo.clear();
            pontos=0;
            //encontra as regioões de determinada categoria do catalago
            //encontra de acordo com o valor de m
            for(qDPontos=0; qDPontos<etografiaKoho[v].quantidadeDePontos; qDPontos++){


                if(etografiaKoho[v].id[qDPontos] ==m){
                    fInicial.push_back(etografiaKoho[v].frameInicial[qDPontos]);
                    fFinal.push_back(etografiaKoho[v].frameFinal[qDPontos]);
                    pontos++;
                }



            }
            //qDPontos é o numero de pontos postos

                //gera um for com um valor inicial igual ao frame inicial do video
                //gera umf or com um valor final de acordo com o valor final do video
               for(int frame= videosKoho[v].frameInicial; frame <
                   videosKoho[v].frameFinal; frame++){
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
               frameVideo.push_back(frameInfo);
               frameInfo.clear();
               fInicial.clear();
               fFinal.clear();

           }


        //e vai para a analise da categoria indefinida
        std::vector<int> claUndefinida;
        quantCate = catalagoKoho[0].quantidadeDeCategorias;


     bool entra=false;

     //tal
        for(int p=0; p< (videosKoho[0].frameFinal-videosKoho[0].frameInicial);
            p++){

            //testa todas as  possibildiade de videos e de categorias do catalago
            for(int z=0; z<quantCate;z++){
                //for(int y=0; y<2; y++){

                    //se alguma delas for diferente de vazio(-1) ele grava como vazio
                    //vazio siginifica que não esta dentro da categoria testada
                    //valor padrao
                lido=frameVideo[z][p];
                if((lido!=-1)&&(!entra)){

                    claUndefinida.push_back(-1);
                    entra=true;
                   // break;

                   // igualdade[y+z]=false;
                    }
                //}

            }

            if(!entra){
                claUndefinida.push_back(quantCate); //o indefinido é classificado como ultimo

            }
            entra=false;



        }
        //ao fim ele grava o vetor em uma matriz
        frameVideo.push_back(claUndefinida);


        // e ao fim de todas as operações ele grava o valor da matriz em uma
        //matriz de 3 dimensões
        //um cubo de pontos que possui pra cada
        //[a][b][c]
          //[a] numero do video
          //[b] categoria
          //[c] qtd de frame.
        //grava o [b] e [c] no [a]


            anaEtoDosVideos.push_back(frameVideo);
            frameVideo.clear();


    }


        //    std::vector< std::vector<int> > frameFleisTabela;
        //    std::vector<int> frameFleisLinha;

            std::vector<int> zerador;
            for(int zera=0;zera<(catalagoKoho[0].quantidadeDeCategorias+1);zera++){
                zerador.push_back(0);

            }




            //para cada frame do video
           for(int f1=0; (f1<videosKoho[0].frameFinal- videosKoho[0].frameInicial);f1++){

               frameFleisLinha.clear();
               frameFleisLinha= zerador; //zera


            for(int ca2=0; ca2<(catalagoKoho[0].quantidadeDeCategorias+1);ca2++ ){

                for(int qv=0; qv<quantidadeDeVideo;qv++){

                    for(int ca1=0; ca1<(catalagoKoho[0].quantidadeDeCategorias+1);ca1++){

        //            for(int qv=0; qv<quantidadeDeVideo;qv++){



                        if(anaEtoDosVideos[qv][ca1][f1]==ca2){


                            frameFleisLinha[ca2]= frameFleisLinha[ca2]+1;


                        }


                    }

                }

            }

            frameFleisTabela.push_back(frameFleisLinha);


           }

           //frameFleisTabela; essa variavel contem a tabela
           //tem que calcular pj
           //tem que calcular pi

           pEntrada.n=quantidadeDeVideo;
           pEntrada.N=frameFleisTabela.size();
           pEntrada.k=frameFleisTabela[0].size();

           qDebug() << "a quantidade de TCC" << pEntrada.n <<
                       "a quantidade de Quadros" << pEntrada.N <<
                       "a quantidade de Categorias" << pEntrada.n;

           //calculando pi i=quadros
           //para cada um dos quadros
           for(int cQua=0; cQua<=frameFleisTabela.size(); cQua++ ){


               PIcalculados.push_back(calcularPI(   frameFleisTabela[cQua]));


           }
           //calcular pj
           //primeiro tem que fazer uma matriz transposta

           std::vector<int> linha;
           //quantidade de categorias
           for(int ti=0; ti<frameFleisTabela[0].size(); ti++){

               //quantidade de quadros
               for(int tj=0; tj<frameFleisTabela.size(); tj++){

                   linha.push_back(frameFleisTabela[tj][ti]);
               }


               PJcalculados.push_back(calcularPJ(linha));

               linha.clear();

           }

           //encontrando Pe concordancia por acaso

           for(int cSom=0; cSom<PJcalculados.size();cSom++){

               pEntrada.Pe= (PJcalculados[cSom] *PJcalculados[cSom] )+ pEntrada.Pe;
           }

           qDebug()<<"Concordancia por acaso Pe" << pEntrada.Pe;



           for(int cSom=0; cSom<PIcalculados.size();cSom++){

               pEntrada.P_medio= PIcalculados[cSom] +pEntrada.P_medio;
           }

           pEntrada.P_medio = pEntrada.P_medio/pEntrada.N;

           qDebug()<<"Média de concordancia " << pEntrada.P_medio;

           pEntrada.Kappa = (pEntrada.P_medio -pEntrada.Pe)/(1- pEntrada.Pe);

           qDebug()<<"Kapppa médio " << pEntrada.Kappa;




           ui->leFleKappa->setText(QString::number(pEntrada.Kappa*100));

           ui->lePe->setText(QString::number(pEntrada.Pe * 100));
           ui->leP->setText(QString::number(pEntrada.P_medio *100));








            for(int k=0; k<catalagoKoho[0].quantidadeDeCategorias+1; k++){

                 if(k<catalagoKoho[0].quantidadeDeCategorias){
                     titulos << catalagoKoho[0].nome[k];
                 }else{

                     titulos << "Undefinido" ;//<< "Somatório";
                 }



            }


            ui->tabFleKapp->setColumnCount(catalagoKoho[0].quantidadeDeCategorias+1);

            ui->tabFleKapp->setHorizontalHeaderLabels(titulos);


            for(int f2=0;f2<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f2++){
                    ui->tabFleKapp->insertRow(ui->tabFleKapp->rowCount());
                    //cria uma nova linha
                    //categoria

                    for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){
                        //no valor zero coloca
                      ui->tabFleKapp->setItem(ui->tabFleKapp->rowCount()-1
                                               ,c5,new QTableWidgetItem(
                                                   QString::number(frameFleisTabela[f2][c5])));


                    }
            }


//           // ui->tabFleKapp->setVerticalHeaderLabels(titulos);

//            //somatorio das colunas

//         for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){


//            somatorioFleisColuna.push_back(0);

//         }


//          for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){

//            for(int f2=0;f2<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f2++){

//                somatorioFleisColuna[c5]= somatorioFleisColuna[c5] + frameFleisTabela[f2][c5];


//            }
//          }

//          ui->tabFleSoma->setColumnCount(catalagoKoho[0].quantidadeDeCategorias+1);
//          ui->tabFleSoma->setHorizontalHeaderLabels(titulos);
//          ui->tabFleSoma->insertRow(ui->tabFleSoma->rowCount());
//          //cria uma nova linha
//          //categoria

//          for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){
//              //no valor zero coloca
//            ui->tabFleSoma->setItem(ui->tabFleSoma->rowCount()-1
//                                     ,c5,new QTableWidgetItem(
//                                         QString::number(somatorioFleisColuna[c5])));


//          }


//          int totalFrames= videosKoho[0].frameFinal-videosKoho[0].frameInicial;

//          double constante= (double) 1/(totalFrames*(catalagoKoho[0].quantidadeDeCategorias+1));


//          ui->tabFleSoma->insertRow(ui->tabFleSoma->rowCount());
//          for(int c6=0;c6<(catalagoKoho[0].quantidadeDeCategorias+1);c6++){

//              somatorioProporcao.push_back((double)somatorioFleisColuna[c6]*constante);

//              ui->tabFleSoma->setItem(ui->tabFleSoma->rowCount()-1
//                                       ,c6,new QTableWidgetItem(
//                                           QString::number(somatorioProporcao[c6])));
//          }


//          QStringList titulos2;

//          titulos2<<" Somatório" << "Pi";
//          ui->tabFleSoma->setVerticalHeaderLabels(titulos2);


//          for(int c7=0;c7<(catalagoKoho[0].quantidadeDeCategorias+1);c7++){


//              proporcaoConcordancia= proporcaoConcordancia+ qPow(somatorioProporcao[c7],2);

//          }

//          ui->lePe->setText(QString::number(proporcaoConcordancia));



//          double valor=0;
//          double constante1;
//          double nConstante;
//          nConstante=catalagoKoho[0].quantidadeDeCategorias+1;
//          constante1= 1/(nConstante*(nConstante-1));


//           for(int f3=0;f3<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f3++){
//              valor=0;
//              for(int c10=0;c10<(catalagoKoho[0].quantidadeDeCategorias+1);c10++)
//              {

//                  valor= (double) valor+ frameFleisTabela[f3][c10]*(frameFleisTabela[f3][c10]-1);
//              }

//              pNumero.push_back(valor*constante1);
//          }


//           somatorioP=0;
//        for(int f4=0;f4<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f4++){

//            somatorioP=pNumero[f4]+ somatorioP;


//        }
//           somatorioP= (double) somatorioP/(videosKoho[0].frameFinal- videosKoho[0].frameInicial);


//           ui->leP->setText(QString::number(somatorioP));

//           fleKappa= (somatorioP-proporcaoConcordancia)/(1-proporcaoConcordancia);


//           ui->leFleKappa->setText(QString::number(fleKappa));

//        //  QString nome2;
//        //  nome2="Somatorio";
//        //    ui->tabFleSoma->setHorizontalHeaderLabels(nome2);



    ui->swFleissKappa->setCurrentIndex(1);
}

void teaConcordancia::on_pbGerarKappa_clicked()
{
    //funcao para pegar o nome que sera gravado

    nomeGravarCatalago = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Fless Kappa Files (*.fkf)"
               );

    Output.setFileName(nomeGravarCatalago);


    Output.open(QIODevice::WriteOnly);

    QXmlStreamWriter stream(&Output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento
//    if(ui->cbTFless->isChecked()){

//       Output.write("\n<?xml-stylesheet type=\"text/xsl\" href=\"analiseFlessEstilo.xsl\"?>");
//        ui->wAlertTotal3->setVisible(true);
//    }
    stream.writeStartElement("analiseTotalSessao");

    stream.writeStartElement("dadosAnalisador");
    stream.writeTextElement("nomeAnalisador","joao antonio Marcolan");
    stream.writeTextElement("laboratorio","iebUFSC");
    stream.writeEndElement(); //fecha dadosAnalisador


    stream.writeStartElement("dadosAnaliseEtografica");

    stream.writeStartElement("dadosVideosUsados");
    stream.writeTextElement("caminhoVideo",videoLido->nome);
    stream.writeTextElement("frameInicial",QString::number( videoLido->frameInicial));
    stream.writeTextElement("frameFinal",QString::number(videoLido->frameFinal));
    stream.writeTextElement("fps",QString::number(videoLido->fps));



    stream.writeEndElement(); //fecha dadosVideoUsados



    stream.writeStartElement("dadosCatalagoUsado");
    stream.writeTextElement("caminhoCatalago",catalagoLido->caminhoArquivo);
    stream.writeStartElement("Categorias");
    int contador=0;

    int ia;
    for(ia=0;ia<catalagoLido->quantidadeDeCategorias;ia++){

       stream.writeStartElement("categoria");
       stream.writeAttribute("id", QString::number(ia));
       stream.writeAttribute("nome",catalagoLido->nome[ia]);
       stream.writeEndElement();

       }


    stream.writeEndElement(); //fecha categorias

    stream.writeEndElement(); //fecha dadosCatalagos

    stream.writeStartElement("analises");

//    for(int i=0;i<catalagoLido->quantidadeDeCategorias;i++){
        //caminhoAnalise
        //quantidadeDeVideo

    for(int qdv=0;qdv<quantidadeDeVideo;qdv++){

        stream.writeStartElement("categoria");
        stream.writeAttribute("id", QString::number(qdv));
        stream.writeAttribute("tipo",catalagoKoho[qdv].tipoAnalise);
        stream.writeTextElement("caminhoAnalis"
                                "eEto",caminhoAnalise[qdv]);
        stream.writeEndElement();

    }




    stream.writeEndElement(); //fecha analises

    stream.writeEndElement(); //fecha dadosAnaliseEtografia

    stream.writeStartElement("analiseFleissKappa");

//    stream.writeStartElement("cabecalho");
//        for(int c12=0;c12<(catalagoKoho[0].quantidadeDeCategorias+1);c12++)
//        {
//            stream.writeStartElement("categoria");
//            stream.writeAttribute("id", QString::number(c12));
//            if(c12<(catalagoKoho[0].quantidadeDeCategorias)){
//               stream.writeAttribute("nome", catalagoKoho[0].nome[c12]);
//            }else{
//                stream.writeAttribute("nome", "Undeterminado");

//            }

//            stream.writeEndElement();

//        }


//    stream.writeEndElement();

    stream.writeStartElement("tabelaConcordante");

    stream.writeStartElement("analise");
    for(int f3=0;f3<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f3++){

        stream.writeStartElement("aFr");
        stream.writeAttribute("num",QString::number(f3));

        for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){

            stream.writeStartElement("con");
           // stream.writeAttribute("idt", QString::number(c5));
            stream.writeAttribute("q",QString::number(frameFleisTabela[f3][c5]));

            stream.writeEndElement();


        }



        stream.writeEndElement();//fecha afr

    }


    stream.writeEndElement();


//    std::vector<QString> nomeElem; //iniocuio

//    for(int kas=0; kas<(catalagoKoho[0].quantidadeDeCategorias+1);kas++){

//     nomeElem.push_back("c"+ QString::number(kas));
//    }


////    nomeLesk.push_back("c1");
////    nomeLesk.push_back("c2");
////    nomeLesk.push_back("c3");

//    for(int f2=0;f2<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f2++){
//            //ui->tabFleKapp->insertRow(ui->tabFleKapp->rowCount());
//        stream.writeStartElement("aFr");
//        stream.writeAttribute("num",QString::number(f2));

//            for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){

//                //stream.writeStartElement("cAna");
//               // stream.writeAttribute("idt", QString::number(c5));
//                stream.writeAttribute(nomeElem[c5],QString::number(frameFleisTabela[f2][c5]));

//               // stream.writeEndElement();


//            }


//             stream.writeEndElement(); //fecha a tabelaConcordante
//    }

//    stream.writeEndElement(); //fecha a tabelasomatorio a mais
//    stream.writeStartElement("tabelaSomatorio");

//    for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){
//         stream.writeStartElement("con");
//      stream.writeAttribute("q",QString::number(somatorioFleisColuna[c5]));
//        stream.writeEndElement(); //fecha a tabelasomatorio
//    }

//    stream.writeEndElement(); //fecha a tabelasomatorio


//    stream.writeStartElement("pi");

//    for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){
//    stream.writeStartElement("con");
//      stream.writeAttribute("q",QString::number(somatorioFleisColuna[c5]));
//       stream.writeEndElement(); //fecha a tabelasomatorio

//    }

//    stream.writeEndElement(); //fecha 0 pi


    stream.writeStartElement("resultadoFinal");

//    stream.writeTextElement("Pe",QString::number(proporcaoConcordancia) );
//    stream.writeTextElement("P",QString::number(somatorioP));
//    stream.writeTextElement("indiceFleissKappa",QString::number(fleKappa));

    stream.writeTextElement("Pe",QString::number(pEntrada.Pe) );
    stream.writeTextElement("P",QString::number(pEntrada.P_medio));
    stream.writeTextElement("indiceFleissKappa",QString::number(pEntrada.Kappa));

    stream.writeEndElement(); //fecha 0 pi
//    somatorioProporcao somatorioFleisColuna


    stream.writeEndElement(); //fecha a tabelaConcordante


//    stream.writeTextElement("hudahudas","HUASDHAUHSDhu");
    stream.writeEndElement(); //fecha o analiseFleissKappa



    stream.writeEndElement(); //fecha dadosAnaliseEtografica
    stream.writeEndDocument();

    Output.close();
    parser = new parserXMLtoCSV();
//   QList<Cell> saida;
//    parser->converteArquivo(nomeGravarCatalago, saida);
}

void teaConcordancia::lerETOXML(QString nomeArquivo)
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
              etografiaLida->frameFinal.push_back(streamReader.attributes().value("frameFinal").toDouble()-1);
             // etografiaLida->frameFinal.push_back(streamReader.attributes().value("frameFinal").toDouble());
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

          if(streamReader.name().toString() == "frameProces"){

              videoLido->frameInicial= streamReader.readElementText().toInt();

          }

          if(streamReader.name().toString() == "frameFinal"){
           videoLido->frameFinal= streamReader.readElementText().toInt();

            videoLido->controle=false;
        }
          if(streamReader.name().toString() == "fps"){
              videoLido->fps= streamReader.readElementText().toDouble();

              videoLido->controle=false;
          }


        }

    }

    //correção
    etografiaLida->frameFinal[etografiaLida->frameFinal.size()-1]++;

    OutEtografia.close();
}

double teaConcordancia::calcularPI(std::vector<int> entrada)
{

    double mult = 1/(pEntrada.n *(pEntrada.n -1));
    double quadroSoma =0;

    //para cada categoria analisada no quadro
    for(int qCat=0;qCat < entrada.size(); qCat++){

        quadroSoma= (entrada[qCat]*(entrada[qCat]-1)) +quadroSoma;
    }

    qDebug()<< "mult " << mult << "soma " << quadroSoma;

    return quadroSoma*mult;




}

double teaConcordancia::calcularPJ(std::vector<int> entrada)
{

    double mult = 1/(pEntrada.N*pEntrada.n);
    double quadroSoma =0;

    //para cada quadro analisado
    for(int qCquadro=0;qCquadro < entrada.size(); qCquadro++){

        quadroSoma = entrada[qCquadro] + quadroSoma;

    }


    qDebug()<< "mult " << mult << "soma " << quadroSoma;


    return quadroSoma * mult;

}

void teaConcordancia::on_pb_BootstrapCohen_clicked()
{
    Reliability *r = new Reliability();
    r->show();

}
