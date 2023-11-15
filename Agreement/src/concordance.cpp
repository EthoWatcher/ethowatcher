#include "concordance.h"
#include <numeric>
#include <math.h>
Concordance_Cohen::Concordance_Cohen()
{
}

QString Concordance_Cohen::carrega_etografia(Etografia eto1, Etografia eto2)
{
    // Função utilizada para carregar as etografias pelo objeto.
    this->eto1 = eto1;
    this->eto2 = eto2;

    this->catalogo_id = eto1.catalogo->id;
    this->catalogo_id.push_back( (int) catalogo_id.size());


    this->lista_eto1 = _constroi_lista_quadros(eto1);
    this->lista_eto2 = _constroi_lista_quadros(eto2);

    this->catalogo_categorias_nomes = eto1.catalogo->nome;
    this->catalogo_categorias_nomes.push_back("Undefined (frames that are not marked)");



    this->calculo_concordancia();
    return this->text_csv_concordancia();

}



void Concordance_Cohen::calculo_concordancia()
{
    auto conta_quantidade_quadros = [&](std::vector<std::vector<int> > matriz_concordancia) -> int {
            int contador_dados = 0;
            for (auto linha: matriz_concordancia){
                for(auto elemento: linha){

                    contador_dados = contador_dados +elemento;
                }
            }

            return contador_dados;
            };

    auto conta_quantidade_linha = [&](std::vector<std::vector<int> > matriz_concordancia) -> std::vector<float> {
        int qnt_elementos =conta_quantidade_quadros(matriz_concordancia);
        std::vector<float> qnt_linha;
        for (auto linha: matriz_concordancia){
            float qnt_elementos_linha=0;
            qnt_elementos_linha = accumulate(linha.begin(), linha.end(), qnt_elementos_linha);
            qnt_linha.push_back(qnt_elementos_linha/qnt_elementos);
        }
       return qnt_linha;

    };

    auto conta_quantidade_coluna = [&](std::vector<std::vector<int> > matriz_concordancia) -> std::vector<float>{
       int qnt_elementos = conta_quantidade_quadros(matriz_concordancia);
       std::vector<float> qnt_coluna;

       int i_coluna = 0;
        for (auto linha: matriz_concordancia){
            float soma_coluna = 0;
            for(auto linha:matriz_concordancia){
                soma_coluna = soma_coluna + linha[i_coluna];
            }
          qnt_coluna.push_back(soma_coluna/ qnt_elementos);
          i_coluna++;
        }


      return qnt_coluna;
    };




    matrix_concordance_nn = constroi_matrix_concordancia_cohen(this->lista_eto1, this->lista_eto2, this->catalogo_id);
    soma_linha = conta_quantidade_linha(matrix_concordance_nn);
    soma_coluna =  conta_quantidade_coluna(matrix_concordance_nn);

    // implementar as funções de calculo de concordancia.
    this->concordancia_acaso = calcula_concordancia_acaso(matrix_concordance_nn);
    this->concordancia_observada = calcula_concordancia_observada(matrix_concordance_nn);
    this->kappa_medio = calcula_kappa_medio(matrix_concordance_nn);


    for(int i=0; i< this->catalogo_id.size(); i++){
        confiabilidade_categoria conf_cate;
        conf_cate.nome = this->catalogo_categorias_nomes[i];
        //TODO: verificar se ambas as etografias tem o mesmo catalogo;

        conf_cate.matrix = gera_matrix_22_pela_categoria(this->lista_eto1, this->lista_eto2, this->catalogo_id, i);
        conf_cate.concordancia_observada = calcula_concordancia_observada(conf_cate.matrix);
        conf_cate.concordancia_acaso = calcula_concordancia_acaso(conf_cate.matrix);
        conf_cate.viez = calculo_vies_categoria(conf_cate.matrix);
        conf_cate.prevalencia = calculo_prevalencia_categoria(conf_cate.matrix);
        conf_cate.kappa = calcula_kappa_medio(conf_cate.matrix);


        conf_cate.matrix_max  = arruma_matrix_kappa_maximo(conf_cate.matrix);
        conf_cate.concordancia_observada_max = calcula_concordancia_observada(conf_cate.matrix_max);
        conf_cate.concordancia_acaso_max = calcula_concordancia_acaso(conf_cate.matrix_max);
        conf_cate.viez_max = calculo_vies_categoria(conf_cate.matrix_max);
        conf_cate.prevalencia_max = calculo_prevalencia_categoria(conf_cate.matrix_max);
        conf_cate.kappa_max = calcula_kappa_medio(conf_cate.matrix_max);

     list_confiabilidade.push_back(conf_cate);
    }

    qDebug() << ";";
}



// Funções auxiliares.
std::vector< std::vector<int> > constroi_matrix_concordancia_cohen(std::vector<int> etografia_1, std::vector<int> etografia_2 , std::vector<int> catalogo ){

      int matrix_size = catalogo.size();
      std::vector< std::vector<int> > matriz_concordancia = std::vector<std::vector<int>>(matrix_size, std::vector<int>(matrix_size));

    for(int quadro_da_analise = 0; quadro_da_analise < etografia_1.size(); quadro_da_analise++){
        int  marcacao_1 = etografia_1[quadro_da_analise];
        int  marcacao_2 = etografia_2[quadro_da_analise];

        bool r_marcacao_1 = marcacao_1 == -1;
        bool r_marcacao_2 = marcacao_2 == -1;

        if(r_marcacao_1){
            marcacao_1 = matrix_size -1;
        }
        if(r_marcacao_2){
            marcacao_2 = matrix_size -1;
        }

        matriz_concordancia[marcacao_2][marcacao_1] = matriz_concordancia[marcacao_2][marcacao_1] +1;

    }

    return matriz_concordancia;


}

float calcula_concordancia_observada(std::vector<std::vector<int> > matriz_concordancia)
{

    auto conta_quantidade_quadros = [&]() -> int {
            int contador_dados = 0;
            for (auto linha: matriz_concordancia){
                for(auto elemento: linha){

                    contador_dados = contador_dados +elemento;
                }
            }

            return contador_dados;
            };

    auto conta_quadros_concordante= [&]() -> int {
            int contador_pos_linha = 0;
            int qnt_quadros_concordante = 0;
            for (auto linha: matriz_concordancia){
                int contador_pos_coluna = 0;
                for(auto elemento: linha){
                    bool r_diagonal = contador_pos_coluna == contador_pos_linha;

                    if(r_diagonal){
                        qnt_quadros_concordante = qnt_quadros_concordante + elemento;
                    }

                contador_pos_coluna++;
                }

            contador_pos_linha++;
            }

            return qnt_quadros_concordante;
        };


    int quant_quadros_marcados = conta_quantidade_quadros();
    int quant_quadros_concordante =conta_quadros_concordante() ;

    float proporcao_concordancia_observada = (float) quant_quadros_concordante/ (float) quant_quadros_marcados;
    return proporcao_concordancia_observada;
}

float calcula_concordancia_acaso(std::vector<std::vector<int> > matriz_concordancia){

    auto conta_quantidade_quadros = [](std::vector<std::vector<int> > matriz_concordancia ) -> int {
            int contador_dados = 0;
            for (auto linha: matriz_concordancia){
                for(auto elemento: linha){

                    contador_dados = contador_dados + elemento;
                }
            }

                return contador_dados;
            };

    auto conta_quantidade_coluna = [&]() -> std::vector<float> {
        int qnt_elementos =conta_quantidade_quadros(matriz_concordancia);
        std::vector<float> qnt_linha;
        for (auto linha: matriz_concordancia){
            float qnt_elementos_linha=0;
            qnt_elementos_linha = accumulate(linha.begin(), linha.end(), qnt_elementos_linha);
            qnt_linha.push_back(qnt_elementos_linha/qnt_elementos);
        }
       return qnt_linha;

    };

    auto conta_quantidade_linha = [&]() -> std::vector<float>{
       int qnt_elementos = conta_quantidade_quadros(matriz_concordancia);
       std::vector<float> qnt_coluna;

       int i_coluna = 0;
        for (auto linha: matriz_concordancia){
            float soma_coluna = 0;
            for(auto linha:matriz_concordancia){
                soma_coluna = soma_coluna + linha[i_coluna];
            }
          qnt_coluna.push_back(soma_coluna/ qnt_elementos);
          i_coluna++;
        }


      return qnt_coluna;
    };

//    int quant_quadros_marcados = conta_quantidade_quadros();
    std::vector<float> soma_linha = conta_quantidade_linha();
    std::vector<float> soma_coluna = conta_quantidade_coluna();
    float concordancia_ao_acaso =0;
    for(int i=0; i< soma_coluna.size(); i++){
       float n1 = soma_linha[i];
       float n2 = soma_coluna[i];
       concordancia_ao_acaso = concordancia_ao_acaso + (n1* n2);

    }



    return concordancia_ao_acaso;

}

float calcula_kappa_medio(std::vector<std::vector<int> > matriz_concordancia){
    // Gian implementar o calculo do kappa medio

    float acaso = calcula_concordancia_acaso(matriz_concordancia);
    float concordancia = calcula_concordancia_observada(matriz_concordancia);
    float kappa = (concordancia - acaso)/(1 - acaso);

    return kappa;
}

//

// matriz de confusão nxn e temos que converter numa matriz de confusão 2x2
// do comportamento e diferente do comportamento
// calular o kappa por categoria
// calcular a prevalencia por categoria - OK
// calcular o vies por categoria - OK
// calcular o kappa maximo. - OK
// the Kappa Statistic in Reliability Studies: Use, Interpretation, and Sample Size Requirements
float calculo_por_categoria(std::vector<std::vector<int> > matriz_concordancia_22)// apenas para matrizes 2x2
{
    float n_1 = matriz_concordancia_22[0][0] + matriz_concordancia_22[0][1] + matriz_concordancia_22[1][0];
    float n_2 = matriz_concordancia_22[1][1] + matriz_concordancia_22[0][1] + matriz_concordancia_22[1][0];
    float dividendo_1 = matriz_concordancia_22[0][0];
    float dividendo_2 = matriz_concordancia_22[1][1];


    float agreement_1 = (float) dividendo_1/n_1;
    float agreement_2 = (float) dividendo_2/n_2;
    //qual dos dois retorna ?

}

float calculo_vies_categoria(std::vector<std::vector<int> > matriz_concordancia_22)
{
    float n = matriz_concordancia_22[0][0] + matriz_concordancia_22[0][1] + matriz_concordancia_22[1][0] + matriz_concordancia_22[1][1];
    float dividendo = fabs(matriz_concordancia_22[0][1] - matriz_concordancia_22[1][0]);
    float vies = (float) dividendo/n;
    return vies;
}

float calculo_prevalencia_categoria(std::vector<std::vector<int> > matriz_concordancia_22)
{
    float n = matriz_concordancia_22[0][0] + matriz_concordancia_22[0][1] + matriz_concordancia_22[1][0] + matriz_concordancia_22[1][1];
    float dividendo = fabs(matriz_concordancia_22[0][0] - matriz_concordancia_22[1][1]);
    float prevalencia = (float) dividendo/n;
    return prevalencia;
}



std::vector< std::vector<int> > arruma_matrix_kappa_maximo(std::vector<std::vector<int> > matriz_concordancia_22)
{
    std::vector< std::vector<int> > matriz_concordancia_22_saida = {{0,0}, {0,0}};

    int soma_linha_1 = 0;
    int soma_coluna_1 = 0;
    soma_linha_1 = matriz_concordancia_22[0][0] + matriz_concordancia_22[1][0];
    soma_coluna_1= matriz_concordancia_22[0][0] + matriz_concordancia_22[0][1];
    std::vector<int> soma_linha_coluna_1 = {soma_linha_1, soma_coluna_1};

    int soma_linha_2 = 0;
    int soma_coluna_2 = 0;

    soma_linha_2 = matriz_concordancia_22[0][1] + matriz_concordancia_22[1][1];
    soma_coluna_2 = matriz_concordancia_22[1][0] + matriz_concordancia_22[1][1];
    std::vector<int> soma_linha_coluna_2 = {soma_linha_2, soma_coluna_2};

    auto encontra_menor_valor = [](std::vector<int> entrada){

        sort(entrada.begin(), entrada.end());
        return entrada;

//        int min = entrada[0];
//        for(int i = 0; i < entrada.size(); i++){
//                if(entrada[i] < min){
//                    min = entrada[i];
//                }
//            }
//        return min;
    };
    std::vector<int> ord_linha_1 = encontra_menor_valor(soma_linha_coluna_1);
    std::vector<int> ord_linha_2 = encontra_menor_valor(soma_linha_coluna_2);


    matriz_concordancia_22_saida[0][0] = ord_linha_1[0];
    matriz_concordancia_22_saida[1][1] = ord_linha_2[0];

   matriz_concordancia_22_saida[0][1] = soma_linha_coluna_1[1] - matriz_concordancia_22_saida[0][0];
   matriz_concordancia_22_saida[1][0] = soma_linha_coluna_2[1] - matriz_concordancia_22_saida[1][1];


   return matriz_concordancia_22_saida;

//    float n = matriz_concordancia_22[0][0] + matriz_concordancia_22[0][1] + matriz_concordancia_22[1][0] + matriz_concordancia_22[1][1];
//    float dividendo = matriz_concordancia_22[0][0] + matriz_concordancia_22[1][1];
//    float kappa_maximo = (float) dividendo/n;
//    return kappa_maximo;
}


float transforma_matris_nn_22()
{

}

// Gravar XML da analise
void Concordance_Cohen::grava_xml_analise(QString caminho_arquivo)
{

    QString nomeGravarCatalago = QFileDialog::getSaveFileName(nullptr,
                "C://",
                "Fless Kappa Files (*.fkf)"
                );

     QFile Output;
     Output.setFileName(nomeGravarCatalago);


     Output.open(QIODevice::WriteOnly);

     QXmlStreamWriter stream(&Output); //passa o endereço
     stream.setAutoFormatting(true);
//     stream.writeStartDocument();//começa o documento

//     stream.writeStartElement("analiseTotalSessao");

//     stream.writeStartElement("dadosAnalisador");
//     stream.writeTextElement("nomeAnalisador","joao antonio Marcolan");
//     stream.writeTextElement("laboratorio","iebUFSC");
//     stream.writeEndElement(); //fecha dadosAnalisador


 //    stream.writeStartElement("dadosAnaliseEtografica");

 //    stream.writeStartElement("dadosVideosUsados");
 //    stream.writeTextElement("caminhoVideo",videoLido->nome);
 //    stream.writeTextElement("frameInicial",QString::number( videoLido->frameInicial));
 //    stream.writeTextElement("frameFinal",QString::number(videoLido->frameFinal));
 //    stream.writeTextElement("fps",QString::number(videoLido->fps));



 //    stream.writeEndElement(); //fecha dadosVideoUsados



 //    stream.writeStartElement("dadosCatalagoUsado");
 //    stream.writeTextElement("caminhoCatalago",catalagoLido->caminhoArquivo);
 //    stream.writeStartElement("Categorias");
 //    int contador=0;

 //    int ia;
 //    for(ia=0;ia<catalagoLido->quantidadeDeCategorias;ia++){

 //       stream.writeStartElement("categoria");
 //       stream.writeAttribute("id", QString::number(ia));
 //       stream.writeAttribute("nome",catalagoLido->nome[ia]);
 //       stream.writeEndElement();

 //       }


 //    stream.writeEndElement(); //fecha categorias

 //    stream.writeEndElement(); //fecha dadosCatalagos

 //    stream.writeStartElement("analises");

 //    for(int qdv=0;qdv<quantidadeDeVideo;qdv++){

 //        stream.writeStartElement("categoria");
 //        stream.writeAttribute("id", QString::number(qdv));
 //        stream.writeAttribute("tipo",catalagoKoho[qdv].tipoAnalise);
 //        stream.writeTextElement("caminhoAnalis"
 //                                "eEto",caminhoAnalise[qdv]);
 //        stream.writeEndElement();

 //    }




 //    stream.writeEndElement(); //fecha analises

 //    stream.writeEndElement(); //fecha dadosAnaliseEtografia

 //    stream.writeStartElement("analiseFleissKappa");


 //    stream.writeStartElement("tabelaConcordante");

 //    stream.writeStartElement("analise");
 //    for(int f3=0;f3<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f3++){

 //        stream.writeStartElement("aFr");
 //        stream.writeAttribute("num",QString::number(f3));

 //        for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){

 //            stream.writeStartElement("con");
 //           // stream.writeAttribute("idt", QString::number(c5));
 //            stream.writeAttribute("q",QString::number(frameFleisTabela[f3][c5]));

 //            stream.writeEndElement();


 //        }



 //        stream.writeEndElement();//fecha afr

 //    }


 //    stream.writeEndElement();


 //    stream.writeStartElement("resultadoFinal");



 //    stream.writeTextElement("Pe",QString::number(pEntrada.Pe) );
 //    stream.writeTextElement("P",QString::number(pEntrada.P_medio));
 //    stream.writeTextElement("indiceFleissKappa",QString::number(pEntrada.Kappa));

 //    stream.writeEndElement(); //fecha 0 pi



 //    stream.writeEndElement(); //fecha a tabelaConcordante



 //    stream.writeEndElement(); //fecha o analiseFleissKappa



 //    stream.writeEndElement(); //fecha dadosAnaliseEtografica
 //    stream.writeEndDocument();

 //    Output.close();

}

// Le XML da analise de concordancia
void Concordance_Cohen::le_xml_analise(QString caminho_arquivo)
{
    QFile OutEtografia;
    OutEtografia.setFileName(caminho_arquivo);
    OutEtografia.open(QIODevice::ReadOnly);

    QXmlStreamReader streamReader(&OutEtografia); //passa o endereço

    QString conversor;

    while(!streamReader.atEnd() && !streamReader.hasError()){

        streamReader.readNext();

        if(streamReader.name().toString() == "analise"){


        }

    }



}

// Grava CSV a partir de um documento XML

void Concordance_Cohen::gravar_csv(QString path_eto, QString t_saida)
{
    QFile outGravador_csv;
    outGravador_csv.setFileName(path_eto);
    outGravador_csv.open(QIODevice::WriteOnly | QIODevice::Text );
    QTextStream csvGravador(&outGravador_csv);


    csvGravador << t_saida;
    outGravador_csv.close();
}

QString Concordance_Cohen::text_csv_concordancia()
{
    QString texto_saida = "sep=;\n";

    auto gera_user_info = [&](){
        QString saida = "The user information\n";
        saida = saida + "Researcher;"+ "Laboratory;\n";
        saida = saida + "Placeholder;"+ "Placeholder;\n";

        return saida;
    }();


    QString gera_info_video  = [&](){
        QString saida = "Information about the analysed video:\n";
        saida = saida + "Name;"+ " Frames per second (fps);" + "Frame started the analysis;" + "Frame finished the analysis \n";
        saida = saida + this->eto1.video->nome +";"
        + QString::number(this->eto1.video->fps) + ";"
        + QString::number(this->eto1.video->frameProce) +";"
        + QString::number(this->eto1.video->frameFinal) + "\n";


        return saida;
    }();

    QString gera_info_eto  = [&](){
        QString saida = "The ethographys analised:\n";
        saida = saida + "Id;"+ "Path;" + " Type;\n";

        saida = saida + "0" +";" + this->eto1.registro->caminho_etografia  + ";" + this->eto1.registro->tipoDeAnalise + "\n";
        saida = saida + "1" +";"+ this->eto2.registro->caminho_etografia  + ";" +this->eto2.registro->tipoDeAnalise + "\n";





        return saida;
    }();

    QString gera_info_catalogo  = [&](){
        catalago * catalogo_usado = this->eto1.catalogo;

        QString saida = "Information of the catalog:\n";
        saida = saida + "Path of the used catalog are in: ;" + catalogo_usado->caminhoArquivo + "\n";

        saida = saida + "Categorie name;\n";

        for(int i=0; i <  catalogo_usado->nome.size(); i++){
            saida = saida +  catalogo_usado->nome[i] + "\n";
        }


        return saida;
    }();

    auto gera_matriz_concordancia_all = [&](){
        QString saida = "";

        QString titulos = ";";

        for(int i=0; i< (int) this->catalogo_categorias_nomes.size(); i++){
            titulos = titulos + this->catalogo_categorias_nomes[i] + ";";

        }
        titulos =  titulos + ";" +"marginal totals";
        saida = saida + titulos+ "\n";

        for(int i=0; i< (int) matrix_concordance_nn.size(); i++){
            std::vector<int> linha = matrix_concordance_nn[i];
            saida = saida + this->catalogo_categorias_nomes[i] +";";
            for(int j=0; j< (int) linha.size(); j++){
              saida = saida + QString::number(linha[j])+";";
            }
            saida = saida + QString::number(this->soma_linha[i]) + ";";

            saida = saida + "\n";
        }

        saida = saida + ";";
        for(int i=0; i< (int) this->catalogo_categorias_nomes.size(); i++){
            saida = saida + QString::number(this->soma_coluna[i]) + ";";

        }
        saida = saida + "\n";



        return saida;

    }();

    QString gera_resumo_analise  = [&](){
        QString saida = "The final result are\n";
        saida = saida + "The agreement porcentage by change (p) are:;" + QString::number(this->concordancia_acaso) + ";\n";
        saida = saida + "The mean agreement pocentage (pe) are:;" + QString::number(this->concordancia_observada) + ";\n";
        saida = saida + "The Cohen Kappa:;" + QString::number(this->kappa_medio)+ ";\n";
        return saida;

    }();

    QString gera_valores_por_categoria = [&](){
        QString texto_categ = "";
        auto gera_resumo_categoria_text = [&](confiabilidade_categoria conf_cat){
            QString saida ="";
            saida = saida + "The agreement porcentage by change (p) are:;" + "The mean agreement pocentage (pe) are:;"
            + "The bias are:;" + "The prevalence are:;" + "The Cohen Kappa off the categorie are:;" + "The max agreement porcentage by change (p) are:;"
            + "The max mean agreement pocentage (pe) are:;" + "The max bias are:;" + "The max prevalence are:;"+ "The max Cohen Kappa off the categorie are:;\n";

            saida = saida +  QString::number(conf_cat.concordancia_acaso) + ";";
            saida = saida  + QString::number(conf_cat.concordancia_observada) + ";";
            saida = saida + QString::number(conf_cat.viez) + ";";
            saida = saida  + QString::number(conf_cat.prevalencia) + ";";
            saida = saida  + QString::number(conf_cat.kappa)+ ";";

            saida = saida  + QString::number(conf_cat.concordancia_acaso_max) + ";";
            saida = saida  + QString::number(conf_cat.concordancia_observada_max) + ";";
            saida = saida  + QString::number(conf_cat.viez_max) + ";";
            saida = saida  + QString::number(conf_cat.prevalencia_max) + ";";
            saida = saida  + QString::number(conf_cat.kappa_max)+ ";\n";
            return saida;
        };
        auto gera_matrix_categoria_text = [&](confiabilidade_categoria conf_cat){
            QString saida = "";
            saida = saida + conf_cat.nome + ";not " + conf_cat.nome +";;;";
            saida = saida + "max " + conf_cat.nome + ";max not " + conf_cat.nome + "\n";

            for(int i =0; i< conf_cat.matrix.size(); i++){
//                for(j=0; j< conf_cat.matrix.size(); j++){
                saida = saida  + QString::number(conf_cat.matrix[i][0]) +";" +QString::number(conf_cat.matrix[i][1]) +";;;";
                saida = saida  + QString::number(conf_cat.matrix_max[i][0]) +";" +QString::number(conf_cat.matrix_max[i][1]) +"\n";
//            }
            };

            return saida;
        };


        for(int i=0; i< catalogo_id.size();i++){
            texto_categ = texto_categ + "\n\nThe resume of the categorie:" + list_confiabilidade[i].nome +" are\n";
            texto_categ = texto_categ + gera_matrix_categoria_text(list_confiabilidade[i]);
            texto_categ = texto_categ + gera_resumo_categoria_text(list_confiabilidade[i]);
        }

        return texto_categ;
    }();

    texto_saida = texto_saida + gera_user_info
            +"\n\n" + gera_info_video
            +"\n\n" + gera_info_eto
            +"\n\n" + gera_info_catalogo
            +"\n\n" + gera_resumo_analise
            +"\n\n" + gera_matriz_concordancia_all
            +"\n\n" + gera_valores_por_categoria;


    return  texto_saida;

}





// Calculo de concordancia Fleiss
Concordance_Fleiss::Concordance_Fleiss()
{
    quantidadeDeVideo=0;

}

void Concordance_Fleiss::add_arquivos_etografia(Etografia eto_grafia)
{

//    etografiaLida = new analiseEtografica();
//    catalagoLido = new catalago();
//    videoLido = new dadosVideo();


    dadosDosVideos.push_back(eto_grafia.video); //forma pratica de fazer um vetor com varios videos lidos
    etografiaDosVideos.push_back(eto_grafia.registro); // forma pratica de fazer um vetor com varias analises etogrificas
    catalagoDosVideos.push_back(eto_grafia.catalogo); //forma pratica de fazer um vetor de alguma variavel

    quantidadeDeVideo++;


//    list_etografias.push_back(eto_grafia);



    qDebug () << "adicionado arquivos";

}

QString Concordance_Fleiss::text_fleiss_concordancia()
{

    int quantCate= 0;

    //nao serve para nada
    etografiaKoho = etografiaDosVideos;
    videosKoho = dadosDosVideos;
    catalagoKoho = catalagoDosVideos;

//    for(int j=0; j<quantidadeDeVideo;j++){

//        *(etografiaKoho + j) = etografiaDosVideos[j]; //aponta para o seu respectivo vetor
//        *(videosKoho +j)    =  dadosDosVideos[j];
//        *(catalagoKoho+j)   = catalagoDosVideos[j];

//    }


    //conversão dos ponto
    int qDPontos=0;
    int pontos=0;
    //bool entrou= false;
    int v=0;
    int lido;

    std::vector<std::vector<int> > frameVideo; // saiiiiiiiiiiidaaaaaaaaaaaa
    std::vector<int> frameInfo;  //é uma linha dinahmica
    std::vector<double> fInicial;
    std::vector<double> fFinal;


    for(v=0; v<quantidadeDeVideo; v++){
//    //m é giaul ao id do catalago 3 pq são 3 no catalgo
    for(int m=0; m<catalagoKoho[0]->quantidadeDeCategorias; m++){

////        std::vector<double> fInicial;
////        std::vector<double> fFinal;
        fInicial.clear();
        fFinal.clear();
        frameInfo.clear();
        pontos=0;
        //encontra as regioões de determinada categoria do catalago
        //encontra de acordo com o valor de m
        for(qDPontos=0; qDPontos<etografiaKoho[v]->quantidadeDePontos; qDPontos++){


            if(etografiaKoho[v]->id[qDPontos] ==m){
                fInicial.push_back(etografiaKoho[v]->frameInicial[qDPontos]);
                fFinal.push_back(etografiaKoho[v]->frameFinal[qDPontos]);
                pontos++;
            }



        }


        //----------------------------------------------

        //qDPontos é o numero de pontos postos
    bool entrou= false;
//            //gera um for com um valor inicial igual ao frame inicial do video
//            //gera umf or com um valor final de acordo com o valor final do video
           for(int frame= videosKoho[v]->frameInicial; frame < videosKoho[v]->frameFinal; frame++){
//            //para cada frame do video lido
//                //o video lido é de acorodo com valor v
           for(int geraVetor=0; geraVetor<pontos; geraVetor++){

               // ele testa o frame para cada intervalo de pontos lido
               // se encontrar ele coloca um  ponto com o valor do id da categoria
               if(((frame>=fInicial[geraVetor])&&(frame<=fFinal[geraVetor]))){

                   frameInfo.push_back(m);
                   entrou= true;
               }

           }
//           //se o frame nao estiver dentro do intervalo o programa coloca o valor de -1
//           //-1 porque os id do catalago são sempre valores positivos

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

    // começa o calcula para a categoria não definida, para quadros que nao foram marcardos
        std::vector<int> claUndefinida;
        quantCate = catalagoKoho[0]->quantidadeDeCategorias;

        bool entra=false;

        //tal
           for(int p=0; p< (videosKoho[0]->frameFinal - videosKoho[0]->frameProce);
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

           //ISTO É A SAIDA ?
           anaEtoDosVideos.push_back(frameVideo);
           frameVideo.clear();

    }


    // calcula o fleiss

    //    std::vector< std::vector<int> > frameFleisTabela;
    //    std::vector<int> frameFleisLinha;

        std::vector<int> zerador;
        for(int zera=0;zera<(catalagoKoho[0]->quantidadeDeCategorias+1);zera++){
            zerador.push_back(0);

        }




        //para cada frame do video
       for(int f1=0; (f1<videosKoho[0]->frameFinal - videosKoho[0]->frameProce);f1++){

           frameFleisLinha.clear();
           frameFleisLinha= zerador; //zera


        for(int ca2=0; ca2<(catalagoKoho[0]->quantidadeDeCategorias+1);ca2++ ){

            for(int qv=0; qv<quantidadeDeVideo;qv++){

                for(int ca1=0; ca1<(catalagoKoho[0]->quantidadeDeCategorias+1);ca1++){

    //            for(int qv=0; qv<quantidadeDeVideo;qv++){



                    if(anaEtoDosVideos[qv][ca1][f1]==ca2){


                        frameFleisLinha[ca2]= frameFleisLinha[ca2]+1;


                    }


                }

            }

        }

        //TABELA DO FLEISS
        frameFleisTabela.push_back(frameFleisLinha);


       }

       for(int cQua=0; cQua<= frameFleisTabela.size(); cQua++ ){


           PIcalculados.push_back(calcularPI(   frameFleisTabela[cQua], quantidadeDeVideo));


       }


       std::vector<int> linha;
       //quantidade de categorias
       for(int ti=0; ti<frameFleisTabela[0].size(); ti++){

           //quantidade de quadros
           for(int tj=0; tj<frameFleisTabela.size(); tj++){

               linha.push_back(frameFleisTabela[tj][ti]);
           }


           PJcalculados.push_back(calcularPJ(linha, quantidadeDeVideo, frameFleisTabela.size() ));

           linha.clear();

       }

       Pe=0;
       for(int cSom=0; cSom<PJcalculados.size();cSom++){

           Pe= (PJcalculados[cSom] *PJcalculados[cSom] )+ Pe;
       }

       qDebug()<<"Concordancia por acaso Pe" << Pe;


       P_medio =0;
       for(int cSom=0; cSom<PIcalculados.size();cSom++){

           P_medio = PIcalculados[cSom] + P_medio;
       }

//       pEntrada.n=quantidadeDeVideo;
//       pEntrada.N=frameFleisTabela.size();
//       pEntrada.k=frameFleisTabela[0].size();

//       qDebug() << "a quantidade de TCC" << pEntrada.n <<
//                   "a quantidade de Quadros" << pEntrada.N <<
//                   "a quantidade de Categorias" << pEntrada.n;



       P_medio = P_medio/frameFleisTabela.size();
       qDebug()<<"Média de concordancia " << P_medio;
       Kappa = (P_medio - Pe)/(1- Pe);
       qDebug()<<"Kapppa médio " << Kappa;


       auto gera_csv = [&](){
            QString texto_saida ="";
            QString gera_cabecalho  = [&](){
                QString saida = "sep=;\n";
                saida = saida + "The user information\n";
                saida = saida + "Researcher;"+ "Laboratory;\n";
                saida = saida + "Placeholder;"+ "Placeholder;\n";
                return saida;
            }();




            QString gera_info_video  = [&](){
                QString saida = "Information about the analysed video:\n";
                saida = saida + "Name;"+ " Frames per second (fps);" + "Frame started the analysis;" + "Frame finished the analysis \n";
                saida = saida + videosKoho[0]->nome +";"
                + QString::number(videosKoho[0]->fps) + ";"
                + QString::number(videosKoho[0]->frameProce) +";"
                + QString::number(videosKoho[0]->frameFinal) + "\n";
                //TODO: CONFERIR O PROCESO DE LEITURA DO XML, o frame inicial é usado para outra coisa
                return saida;
            }();

            QString gera_info_catalogo  = [&](){
                catalago * catalogo_usado = catalagoKoho[0];

                QString saida = "Information of the catalog:\n";
                saida = saida + "Path of the used catalog are in: ;" + catalogo_usado->caminhoArquivo + "\n";

                saida = saida + "Categorie name;\n";

                for(int i=0; i <  catalogo_usado->nome.size(); i++){
                    saida = saida +  catalogo_usado->nome[i] + "\n";
                }


                return saida;
            }();


            QString gera_info_eto  = [&](){
                QString saida = "The ethographys analised:\n";
                saida = saida + "Id;"+ "Path;" + " Type;\n";
                for(int i=0; i< etografiaDosVideos.size(); i++){
                    saida = saida + QString::number(i) +";"+ etografiaDosVideos[i]->caminho_etografia + ";" + etografiaDosVideos[i]->tipoDeAnalise + "\n";

                }




                return saida;
            }();


            QString gera_resumo_analise  = [&](){
                QString saida = "The final result are\n";
                saida = saida + "The agreement porcentage by change (p) are:;" + QString::number(P_medio) + ";\n";
                saida = saida + "The mean agreement pocentage (pe) are:;" + QString::number(Pe) + ";\n";
                saida = saida + "The Fleiss Kappa:;" + QString::number(Kappa)+ ";\n";


                return saida;

            }();


            QString gera_matrix = [&](){
                QString saida = "The total of the Fleiss Kappa analysis\n";
                catalago *catalogo_lido =  catalagoKoho[0];
                saida = saida + "Frame;";
                for(int i=0; i< catalogo_lido->nome.size(); i++){
                    saida = saida + catalogo_lido->nome[i]+";";
                }
                saida = saida + "Undefined (frames that are not marked)\n";

                for(int i=0; i< frameFleisTabela.size(); i++){
                    std::vector<int> linha = frameFleisTabela[i];
                    saida = saida + QString::number(i) + ";";
                    for(int j=0; j< linha.size(); j++){
                        saida = saida + QString::number(linha[j]) +";";
                    }
                    saida = saida + "\n";
                }


                return saida;

            }();


            texto_saida = gera_cabecalho
                    +"\n\n" + gera_info_video
                    +"\n\n" + gera_info_catalogo
                    +"\n\n" + gera_info_eto
                    +"\n\n" + gera_resumo_analise
                    +"\n\n" + gera_matrix;

            return texto_saida;
       };


    return gera_csv();
}


void Concordance_Fleiss::gravar_csv(QString path_eto, QString t_saida){
    QFile outGravador_csv;
//    QStringList list1 = path_eto.split(".etoxml"); // nomeGravarEtografia
//    QString csv_path = list1[0] + "_csv.csv";
    outGravador_csv.setFileName(path_eto);
    outGravador_csv.open(QIODevice::WriteOnly | QIODevice::Text );
    QTextStream csvGravador(&outGravador_csv);


    csvGravador << t_saida;
    outGravador_csv.close();
}

double Concordance_Fleiss::calcularPJ(std::vector<int> entrada, double qntd_videos, double qnt_quadros)
{

    double mult = 1/(qntd_videos*qnt_quadros);
    double quadroSoma =0;

    //para cada quadro analisado
    for(int qCquadro=0;qCquadro < entrada.size(); qCquadro++){

        quadroSoma = entrada[qCquadro] + quadroSoma;

    }


    qDebug()<< "mult " << mult << "soma " << quadroSoma;


    return quadroSoma * mult;

}

double Concordance_Fleiss::calcularPI(std::vector<int> entrada, double qnt_de_TCC)
{

    double mult = 1/(qnt_de_TCC *(qnt_de_TCC -1));
    double quadroSoma =0;

    //para cada categoria analisada no quadro
    for(int qCat=0;qCat < entrada.size(); qCat++){

        quadroSoma= (entrada[qCat]*(entrada[qCat]-1)) +quadroSoma;
    }

    qDebug()<< "mult " << mult << "soma " << quadroSoma;

    return quadroSoma*mult;




}

void Concordance_Fleiss::calculo_concordancia()
{
//    //cria um vetor com alocação dinamica de memoria no qual ele tem o tamanho de quantidadeDeVideo
//        //quantidade de video é um contador que soma toda vez que adiciona um novo video
//        etografiaKoho = new analiseEtografica[quantidadeDeVideo];
//        videosKoho = new dadosVideo[quantidadeDeVideo];
//        catalagoKoho = new catalago[quantidadeDeVideo];
        int quantCate=0; //quantidade de categoria para fazer o vetor de categoria undefinida

//        for(int j=0; j<quantidadeDeVideo;j++){

//            *(etografiaKoho + j) = etografiaDosVideos[j]; //aponta para o seu respectivo vetor
//            *(videosKoho +j)    =  dadosDosVideos[j];
//            *(catalagoKoho+j)   = catalagoDosVideos[j];

//        }

//        //setando os nomes


//            ui->lblVideo1->setText(caminhoAnalise[0]);
//            ui->lblVideo2->setText(caminhoAnalise[1]);



//        //conversão dos ponto
//        int qDPontos=0;
//        int pontos=0;
//        //bool entrou= false;
//        int v=0;
//        int lido;
//    //    std::vector<int> frameInfo;  //é uma linha dinahmica


//        for(v=0; v<quantidadeDeVideo; v++){
//        //m é giaul ao id do catalago 3 pq são 3 no catalgo
//        for(int m=0; m<catalagoKoho[0].quantidadeDeCategorias; m++){

//    //        std::vector<double> fInicial;
//    //        std::vector<double> fFinal;
//            fInicial.clear();
//            fFinal.clear();
//            frameInfo.clear();
//            pontos=0;
//            //encontra as regioões de determinada categoria do catalago
//            //encontra de acordo com o valor de m
//            for(qDPontos=0; qDPontos<etografiaKoho[v].quantidadeDePontos; qDPontos++){


//                if(etografiaKoho[v].id[qDPontos] ==m){
//                    fInicial.push_back(etografiaKoho[v].frameInicial[qDPontos]);
//                    fFinal.push_back(etografiaKoho[v].frameFinal[qDPontos]);
//                    pontos++;
//                }



//            }
//            //qDPontos é o numero de pontos postos

//                //gera um for com um valor inicial igual ao frame inicial do video
//                //gera umf or com um valor final de acordo com o valor final do video
//               for(int frame= videosKoho[v].frameInicial; frame <
//                   videosKoho[v].frameFinal; frame++){
//                //para cada frame do video lido
//                    //o video lido é de acorodo com valor v
//               for(int geraVetor=0; geraVetor<pontos; geraVetor++){

//                   // ele testa o frame para cada intervalo de pontos lido
//                   // se encontrar ele coloca um  ponto com o valor do id da categoria
//                   if(((frame>=fInicial[geraVetor])&&(frame<=fFinal[geraVetor]))){

//                       frameInfo.push_back(m);
//                       entrou= true;
//                   }

//               }
//               //se o frame nao estiver dentro do intervalo o programa coloca o valor de -1
//               //-1 porque os id do catalago são sempre valores positivos

//                  if(!entrou){
//                       frameInfo.push_back(-1); //quer dissser que o usuario nao deixou precionado o botão

//                   }
//                   entrou= false;


//               }

//               //ao fim dos looping  de encontras os valores das categorias
//               //ele grava o vetor em uma matrix de pontos
//               frameVideo.push_back(frameInfo);
//               frameInfo.clear();
//               fInicial.clear();
//               fFinal.clear();

//           }


//        //e vai para a analise da categoria indefinida
//        std::vector<int> claUndefinida;
//        quantCate = catalagoKoho[0].quantidadeDeCategorias;


//     bool entra=false;

//     //tal
//        for(int p=0; p< (videosKoho[0].frameFinal-videosKoho[0].frameInicial);
//            p++){

//            //testa todas as  possibildiade de videos e de categorias do catalago
//            for(int z=0; z<quantCate;z++){
//                //for(int y=0; y<2; y++){

//                    //se alguma delas for diferente de vazio(-1) ele grava como vazio
//                    //vazio siginifica que não esta dentro da categoria testada
//                    //valor padrao
//                lido=frameVideo[z][p];
//                if((lido!=-1)&&(!entra)){

//                    claUndefinida.push_back(-1);
//                    entra=true;
//                   // break;

//                   // igualdade[y+z]=false;
//                    }
//                //}

//            }

//            if(!entra){
//                claUndefinida.push_back(quantCate); //o indefinido é classificado como ultimo

//            }
//            entra=false;



//        }
//        //ao fim ele grava o vetor em uma matriz
//        frameVideo.push_back(claUndefinida);


//        // e ao fim de todas as operações ele grava o valor da matriz em uma
//        //matriz de 3 dimensões
//        //um cubo de pontos que possui pra cada
//        //[a][b][c]
//          //[a] numero do video
//          //[b] categoria
//          //[c] qtd de frame.
//        //grava o [b] e [c] no [a]


//            anaEtoDosVideos.push_back(frameVideo);
//            frameVideo.clear();


//    }


//        //    std::vector< std::vector<int> > frameFleisTabela;
//        //    std::vector<int> frameFleisLinha;

//            std::vector<int> zerador;
//            for(int zera=0;zera<(catalagoKoho[0].quantidadeDeCategorias+1);zera++){
//                zerador.push_back(0);

//            }




//            //para cada frame do video
//           for(int f1=0; (f1<videosKoho[0].frameFinal- videosKoho[0].frameInicial);f1++){

//               frameFleisLinha.clear();
//               frameFleisLinha= zerador; //zera


//            for(int ca2=0; ca2<(catalagoKoho[0].quantidadeDeCategorias+1);ca2++ ){

//                for(int qv=0; qv<quantidadeDeVideo;qv++){

//                    for(int ca1=0; ca1<(catalagoKoho[0].quantidadeDeCategorias+1);ca1++){

//        //            for(int qv=0; qv<quantidadeDeVideo;qv++){



//                        if(anaEtoDosVideos[qv][ca1][f1]==ca2){


//                            frameFleisLinha[ca2]= frameFleisLinha[ca2]+1;


//                        }


//                    }

//                }

//            }

//            frameFleisTabela.push_back(frameFleisLinha);


//           }

//           //frameFleisTabela; essa variavel contem a tabela
//           //tem que calcular pj
//           //tem que calcular pi

//           pEntrada.n=quantidadeDeVideo;
//           pEntrada.N=frameFleisTabela.size();
//           pEntrada.k=frameFleisTabela[0].size();

//           qDebug() << "a quantidade de TCC" << pEntrada.n <<
//                       "a quantidade de Quadros" << pEntrada.N <<
//                       "a quantidade de Categorias" << pEntrada.n;

//           //calculando pi i=quadros
//           //para cada um dos quadros
//           for(int cQua=0; cQua<=frameFleisTabela.size(); cQua++ ){


//               PIcalculados.push_back(calcularPI(   frameFleisTabela[cQua]));


//           }
//           //calcular pj
//           //primeiro tem que fazer uma matriz transposta

//           std::vector<int> linha;
//           //quantidade de categorias
//           for(int ti=0; ti<frameFleisTabela[0].size(); ti++){

//               //quantidade de quadros
//               for(int tj=0; tj<frameFleisTabela.size(); tj++){

//                   linha.push_back(frameFleisTabela[tj][ti]);
//               }


//               PJcalculados.push_back(calcularPJ(linha));

//               linha.clear();

//           }

//           //encontrando Pe concordancia por acaso

//           for(int cSom=0; cSom<PJcalculados.size();cSom++){

//               pEntrada.Pe= (PJcalculados[cSom] *PJcalculados[cSom] )+ pEntrada.Pe;
//           }

//           qDebug()<<"Concordancia por acaso Pe" << pEntrada.Pe;



//           for(int cSom=0; cSom<PIcalculados.size();cSom++){

//               pEntrada.P_medio= PIcalculados[cSom] +pEntrada.P_medio;
//           }

//           pEntrada.P_medio = pEntrada.P_medio/pEntrada.N;

//           qDebug()<<"Média de concordancia " << pEntrada.P_medio;

//           pEntrada.Kappa = (pEntrada.P_medio -pEntrada.Pe)/(1- pEntrada.Pe);

//           qDebug()<<"Kapppa médio " << pEntrada.Kappa;




//           ui->leFleKappa->setText(QString::number(pEntrada.Kappa*100));

//           ui->lePe->setText(QString::number(pEntrada.Pe * 100));
//           ui->leP->setText(QString::number(pEntrada.P_medio *100));








//            for(int k=0; k<catalagoKoho[0].quantidadeDeCategorias+1; k++){

//                 if(k<catalagoKoho[0].quantidadeDeCategorias){
//                     titulos << catalagoKoho[0].nome[k];
//                 }else{

//                     titulos << "Undefinido" ;//<< "Somatório";
//                 }



//            }


//            ui->tabFleKapp->setColumnCount(catalagoKoho[0].quantidadeDeCategorias+1);

//            ui->tabFleKapp->setHorizontalHeaderLabels(titulos);


//            for(int f2=0;f2<(videosKoho[0].frameFinal- videosKoho[0].frameInicial);f2++){
//                    ui->tabFleKapp->insertRow(ui->tabFleKapp->rowCount());
//                    //cria uma nova linha
//                    //categoria

//                    for(int c5=0; c5<(catalagoKoho[0].quantidadeDeCategorias+1); c5++){
//                        //no valor zero coloca
//                      ui->tabFleKapp->setItem(ui->tabFleKapp->rowCount()-1
//                                               ,c5,new QTableWidgetItem(
//                                                   QString::number(frameFleisTabela[f2][c5])));


//                    }
//            }




//    ui->swFleissKappa->setCurrentIndex(1);
}



std::vector<std::vector<int> > gera_matrix_22_pela_categoria(std::vector<int> etrografia_1, std::vector<int> etrografia_2, std::vector<int> catalogo, int id_categ)
{
    std::vector<std::vector<int> > matrix_nn = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);
//    std::vector<std::vector<int> > matrix_nn;

    auto get_columa_matrix = [](std::vector<std::vector<int> > matrix_nn, int id_coluna){
        std::vector<int> linha_trocar;
        for(int i=0; i< matrix_nn.size(); i++){
            for(int j=0; j< matrix_nn.size(); j++){
                bool r_linha_gravar = j == id_coluna;
                if(r_linha_gravar){
                    linha_trocar.push_back(matrix_nn[i][j]);
                 }
            }
        }
        return  linha_trocar;
    };
    auto get_arruma_linha = [](std::vector<int> primeira_linha, int id_original, int id_coluna){
        int valor_zero = primeira_linha[id_original];
        int valor_troca = primeira_linha[id_coluna];
        primeira_linha[id_original] = valor_troca;
        primeira_linha[id_coluna] = valor_zero;
        return primeira_linha;
    };


    auto arruma_matrix = [] (std::vector<std::vector<int> > matrix_nn, std::vector<int> primeira_linha,std::vector<int> linha_trocar , int id_cat)
    {
        auto iniciliaza_matriz_00 = [](std::vector<std::vector<int> > matrix){
            std::vector<std::vector<int> > matrix_0;
            for(int i=0; i< matrix.size(); i++){
                std::vector<int> linha;
                for(int j=0; j< matrix.size(); j++){
                    linha.push_back(0);

                }
                matrix_0.push_back(linha);
            }
            return matrix_0;
        };

        std::vector<std::vector<int> >  matrix_nn_arruma = iniciliaza_matriz_00(matrix_nn);

        for(int i=0; i< matrix_nn_arruma.size(); i++){
         for(int j=0; j< matrix_nn_arruma.size(); j++){
             bool r_coluna_0 = j==0;
             bool r_coluna_troca = j ==id_cat;
             bool r_outros = !r_coluna_troca && !r_coluna_0;

             if(r_coluna_0){
                matrix_nn_arruma[i][j] = linha_trocar[i];
             }

             if(r_coluna_troca){
                 matrix_nn_arruma[i][j] = primeira_linha[i];
             }

             if(r_outros){
                 matrix_nn_arruma[i][j] = matrix_nn[i][j];
             }

         }
        }


        return matrix_nn_arruma;

     };





    std::vector<int> primeira_linha = get_arruma_linha(get_columa_matrix(matrix_nn, 0), 0, id_categ);
    std::vector<int> linha_trocar= get_arruma_linha(get_columa_matrix(matrix_nn, id_categ), id_categ,0);

    std::vector<std::vector<int> > saida = arruma_matrix(matrix_nn, primeira_linha, linha_trocar, id_categ);



    std::vector<std::vector<int> > matrix_22 = gera_matrix_22(saida);


    int div = (int(catalogo.size()) -1);

    matrix_22[0][1] = int(matrix_22[0][1]/ div);
    matrix_22[1][0] = int(matrix_22[1][0]/ div);
    matrix_22[1][1] = int(matrix_22[1][1]/ div);


    return matrix_22;


}


std::vector<std::vector<int> > gera_matrix_22(std::vector<std::vector<int> > matrix_nn){
    //incializando o vetor de saida
    auto gera_matrix_inicial = [](std::vector<std::vector<int> > saida)
        {
            saida.push_back({0,0});
            saida.push_back({0,0});
            return saida;
        };

    auto gera_concordancia_a_a = [](std::vector<std::vector<int> > matrix_nn)
        {
            int a =0;
            a = matrix_nn[0][0];

            return a;
        };

    auto gera_concordancia_a_nota = [](std::vector<std::vector<int> > matrix_nn)
        {
        //somando a linha
            int soma =0;
            std::vector<int> linha= matrix_nn[0];
            for(int i=1; i < linha.size(); i++ ){
                soma = linha[i] + soma;

            }
            return soma;
        };

    auto gera_concordancia_nota_a = [](std::vector<std::vector<int> > matrix_nn)
        {

            std::vector<int> linha;
            //transversa, pega primeiro elemento da matrix menos da primeira
            for(int i=1; i < matrix_nn.size(); i++){
                linha.push_back(matrix_nn[i][0]);
            }



            int soma =0;
            for(int i=0; i < linha.size(); i++ ){
                soma = linha[i] + soma;

            }

            return soma;
        };

    auto gera_concordancia_nota_nota = [](std::vector<std::vector<int> > matrix_nn)
        {
            std::vector<int> linha;
            //transversa
            for(int i=1; i < matrix_nn.size(); i++){
                for(int j=1; j < matrix_nn.size(); j++){
                    bool r_centro = i == j;
                    if (r_centro){
                        linha.push_back(matrix_nn[i][j]);
                    }

                }
            }

            int soma =0;
            for(int i=0; i < linha.size(); i++ ){
                soma = linha[i] + soma;

            }

            return soma;
        };





    std::vector<std::vector<int> > saida;
    saida = gera_matrix_inicial(saida);
    saida[0][0] = gera_concordancia_a_a(matrix_nn);
    saida[0][1] = gera_concordancia_a_nota(matrix_nn);
    saida[1][0] = gera_concordancia_nota_a(matrix_nn);
    saida[1][1] = gera_concordancia_nota_nota(matrix_nn);

//    saida[0][0] =


    return saida;
}


std::vector<int> _constroi_lista_quadros(Etografia eto)
{
    std::vector<int> saida;
    auto testa_quadros_dentro = [](int qnt_inicial, int qnt_final, int q_testado){
        bool r_teste = qnt_inicial <= q_testado ;
        bool r_teste_2 = q_testado <= qnt_final;

        return r_teste && r_teste_2;
    };

    std::vector<int> vetor_quadros;
    for(int i=eto.video->frameProce; i< eto.video->frameFinal; i++){
        vetor_quadros.push_back(i);
    }

    auto encontra_quadros_gap = [&](){

        std::vector<int> list_quadros_gap;

        for(int i=0; i < (int) vetor_quadros.size(); i++){
            int q_teste = vetor_quadros[i];

            bool r_foi_marcado = false;
            for(int j=0; j< (int) eto.registro->frameInicial.size(); j++){
                bool r_dentro_range = testa_quadros_dentro(eto.registro->frameInicial[j],
                                                           eto.registro->frameFinal[j],
                                                           q_teste);


                if(r_dentro_range){
                    r_foi_marcado = true;
                    break;
                }

            }
            if(!r_foi_marcado){
                list_quadros_gap.push_back(q_teste);
            }
        }

        return list_quadros_gap;

    };



    std::vector<int> list_quadros_gap = encontra_quadros_gap();

    for(int i=0; i< (int) vetor_quadros.size(); i++){
        int q_teste = vetor_quadros[i];

        bool r_no_gap = true;
        for(int j=0; j< (int) list_quadros_gap.size(); j++){
            bool r_valor_gap = list_quadros_gap[j] == q_teste;
            if(r_valor_gap){
                r_no_gap = false;
                break;
            }
        }
        if(r_no_gap){
            for(int k=0; k< eto.registro->frameInicial.size(); k++){

                int q_inicial = eto.registro->frameInicial[k];
                int q_final = eto.registro->frameFinal[k];
                int id_cate = eto.registro->id[k];

                bool r_dentro_range = testa_quadros_dentro(q_inicial, q_final, q_teste);

                if(r_dentro_range){
                    saida.push_back(id_cate);
                    break;
                }
            }

        }else{
            saida.push_back(-1);
        }

    }

    return saida;
}


//       for(int i=0; i< eto.registro->frameInicial.size(); i++){


//           int q_inicial = eto.registro->frameInicial[i];
//           int q_final = eto.registro->frameFinal[i];
//           for(int j=0; j< q_final - q_inicial; j++ ){
//               saida.push_back(eto.registro->id[i]);
//           }

//       }

//       bool r_checa_se_todos_quadros_marcados = saida.size() == (eto.video->frameFinal - eto.video->frameProce);

//       if(r_checa_se_todos_quadros_marcados){
//          qDebug() << "Construiu o array corretamente";
//       }

int  get_soma_linha(std::vector<int> l_grid){
    int soma = 0;
    for(int i=0; i< l_grid.size(); i++){
        soma = soma + l_grid[i];
    }
    return soma;
}

std::vector<int>  transpose_linha(std::vector<std::vector<int> >grid, int linha){
    std::vector<int> saida = {};
    for(std::vector<int> l_grid: grid){
        saida.push_back(l_grid[linha]);
    }
    return saida;
}

std::vector<bool> transpose_linha_bool(std::vector<std::vector<bool> >grid, int linha){
    std::vector<bool> saida = {};
    for(std::vector<bool> l_grid: grid){
        saida.push_back(l_grid[linha]);
    }
    return saida;
}

Marginal get_colu_linha_soma(std::vector<std::vector<int> >grid, int linha){
    Marginal m = Marginal(0,0);
    m.linha = get_soma_linha(grid[linha]);
    m.colun = get_soma_linha(transpose_linha(grid, linha));
    return  m;
}
std::vector<int> get_all_marginal(std::vector<std::vector<int> > grid)
{
    std::vector<int> ls_marginal ={};

     for(int i=0; i < grid[0].size(); i++){
        ls_marginal.push_back(get_colu_linha_soma(grid, i).get_menor_valor());

    }
     return ls_marginal;

}

std::vector<Marginal> get_tuple_marginal(std::vector<std::vector<int> >grid){
    std::vector<Marginal> ls_marginal ={};

     for(int i=0; i< grid[0].size(); i++){
     ls_marginal.push_back(get_colu_linha_soma(grid, i));

     }

     return ls_marginal;

}

std::vector<std::vector<int> > generate_matriz_maxima(std::vector<std::vector<int> > grid)
{
    std::vector<int> ls_marginal = get_all_marginal(grid);
    std::vector<std::vector<int> > grid_novo ={};

    for(int coluna=0; coluna< ls_marginal.size(); coluna++){
        std::vector<int> col_nova = {};
        for(int linha=0; linha< ls_marginal.size(); linha++){
            bool r_centro = linha == coluna;
             if (r_centro){
                col_nova.push_back(ls_marginal[coluna]);
             }else{
                col_nova.push_back(0);
             }

        }
        grid_novo.push_back(col_nova);
    }
    return grid_novo;
}

std::vector<std::vector<bool> > generate_matriz_maxima_visitada(std::vector<std::vector<int> > grid)
{
    std::vector<int> ls_marginal = get_all_marginal(grid);
    std::vector<std::vector<bool> > grid_novo ={};

    for(int coluna=0; coluna< ls_marginal.size(); coluna++){
        std::vector<bool> col_nova = {};
        for(int linha=0; linha< ls_marginal.size(); linha++){
            bool r_centro = linha == coluna;
             if (r_centro){
                col_nova.push_back(ls_marginal[coluna]);
             }else{
                col_nova.push_back(0);
             }

        }
        grid_novo.push_back(col_nova);
    }
    return grid_novo;
}



std::tuple<bool, std::vector<std::vector<int> > > solver(std::vector<std::vector<int> > & grid_max,
            std::vector<std::vector<bool> > matrix_max_visitada,
            std::vector<Marginal> tuple_marginal){
    struct NextItem{
        int i;
        int j;
        bool existe;
    };

    auto get_next_item = [] (std::vector<std::vector<bool> > grid)
    {
        NextItem saida;
        for(int i=0; i< grid[0].size(); i++){
            for(int j=0; j< grid[i].size(); j++){
                bool r_vazia = grid[i][j] == false;
                if(r_vazia){
                    saida.i = i;
                    saida.j = j;
                    saida.existe = true;
                    return saida;
                }else{

                }
            }
        }
        saida.i = 0;
        saida.j = 0;
        saida.existe = false;
        return saida;


    };

    auto checa_valido = [] (
            std::vector<std::vector<int> > matrix,
            std::vector<std::vector<bool> >matrix_max_visitada,
            std::vector<Marginal> tuple_marginal,
            int linha,
            int coluna){

        auto soma_linha  = get_soma_linha(matrix[linha]);
        auto soma_coluna = get_colu_linha_soma(matrix, coluna).colun;

        auto valor_linha       = tuple_marginal[linha].linha;
        auto valor_colun       = tuple_marginal[coluna].colun;

        bool r_linha_completa = valor_linha == soma_linha;
        bool r_col_completa   = valor_colun == soma_coluna;



        auto linha_visitada = matrix_max_visitada[linha];
        std::vector<bool> linha_falsa;


        auto col_visitada = transpose_linha_bool(matrix_max_visitada, coluna);
        std::vector<bool> col_falsa;

        std::copy_if (linha_visitada.begin(), linha_visitada.end(), std::back_inserter(linha_falsa), [](bool i){return i== false;} );
        std::copy_if (col_visitada.begin(), col_visitada.end(), std::back_inserter(col_falsa), [](bool i){return i== false;} );

        int qnt_menos_linha = linha_falsa.size();
        int qnt_menos_col =  col_falsa.size();

        bool r_linha_toda_visitada = qnt_menos_linha == 0;
        bool r_coluna_toda_visitada = qnt_menos_col == 0;

//        int qnt_menos_linha =  len(list(filter(lambda x: x == False, matrix_max_visitada[linha])))


        if(r_linha_toda_visitada && r_coluna_toda_visitada ){
            if(r_linha_completa && r_col_completa){
                return true;
            }else{
                return false;
            }

        } else if (r_linha_toda_visitada){
            if(r_linha_completa){
                return true;
            }else{
                return false;
            }


        }else if(r_coluna_toda_visitada){
             if (r_col_completa){
                    return true;
              }else{
                    return false;
               }



        }else{
            auto r_linha_maior    = soma_linha  > valor_linha;
            auto r_col_maior      = soma_coluna > valor_colun;
            auto r_linha_menor    = soma_linha  < valor_linha;
            auto r_col_menor      = soma_coluna < valor_colun;
            if (r_linha_maior or r_col_maior){
                return false;
                // return 0 # aqui tem q voltar no backtracking
            }
            if(r_linha_menor || r_col_menor || r_linha_completa || r_col_completa ){
                return true;
            }

        }



        return false;
    };



    NextItem item = get_next_item(matrix_max_visitada);
    matrix_max_visitada[item.i][item.j] = true;

//    bool r_todos_certo = [&matrix_max_visitada] (){
//        for(auto linha: matrix_max_visitada){
//            for(auto celula: linha){
//                if(celula == false){
//                    return false;
//                }
//            }
//        }

//        return true;
//    }();

//std::tuple<bool, std::vector<std::vector<int> > >
    if(item.existe == false){
        return  std::make_tuple(true, grid_max);
    }else{
        auto max_valor_linha = tuple_marginal[item.i].get_diferenca();
        auto max_valor_colun   = tuple_marginal[item.j].get_diferenca();

        int valor_ate = max_valor_linha;
        if (max_valor_linha > max_valor_colun){ //vani
            valor_ate = max_valor_colun;
        }

        for(int i=0; i<= valor_ate; i++){
            grid_max[item.i][item.j] = i;
            bool r_valido = checa_valido(grid_max,
                                             matrix_max_visitada,
                                             tuple_marginal,
                                             item.i,
                                             item.j);

            if (r_valido){
                auto saida = solver(grid_max, matrix_max_visitada,  tuple_marginal);
//                grid_max = std::get<1>(saida);

                bool r_resolvido = std::get<0>(saida);
                if (r_resolvido){
                    return std::make_tuple(true, grid_max);

                }else{
                    grid_max = std::get<1>(saida);


                }
//                else{
//                    grid_max[item.i][item.j] = 0;

//                }




           }
        }
        matrix_max_visitada[item.i][item.j] = false;
        grid_max[item.i][item.j] = 0;
//        auto valor_ate = max_valor_linha;
        return std::make_tuple(false, grid_max);;

    }


}





std::tuple<bool, std::vector<std::vector<int> > > solver_nova_max(std::vector<std::vector<int> > & grid_max, std::vector<std::vector<bool> > matrix_max_visitada,
            std::vector<valor_visto_pos> ls_matriz,
            std::vector<Marginal> tuple_marginal){

    auto generate_next_element = [](std::vector<valor_visto_pos> ls_matriz){
        for(int i=0; i< ls_matriz.size(); i++){
            auto elemento = ls_matriz[i];

            if(elemento.visited == false){
                return i;
            }

        }

        return -1;


    };



    auto resolucao = solver(grid_max, matrix_max_visitada, tuple_marginal);
    std::vector<std::vector<int> > m_saida = std::get<1>(resolucao);
    bool r_saida_solucao = std::get<0>(resolucao);
    if(r_saida_solucao){
        return resolucao;
    }else{


        std::vector<valor_visto_pos> linha_faltando;

        std::copy_if (ls_matriz.begin(), ls_matriz.end(), std::back_inserter(linha_faltando), [](valor_visto_pos i){return i.visited == false;} );


        for(valor_visto_pos next_item : linha_faltando){
//            auto item_en = ls_matriz[pros_item_i];
//            ls_matriz[pros_item_i].visited = true;
            int valor_antigo = grid_max[next_item.pos][next_item.pos];
            grid_max[next_item.pos][next_item.pos] = next_item.valor_visto;

            auto resolucao = solver(grid_max, matrix_max_visitada, tuple_marginal);
            std::vector<std::vector<int> > m_saida = std::get<1>(resolucao);
            bool r_saida_solucao = std::get<0>(resolucao);
            if(r_saida_solucao){
                return resolucao;
            }

        }

        int pros_item_i = generate_next_element(ls_matriz);
        bool r_encontrou = pros_item_i != -1;
        if(r_encontrou == false){
            return resolucao;
        }else{
            auto item_en = ls_matriz[pros_item_i];
            ls_matriz[pros_item_i].visited = true;
            int valor_antigo = grid_max[item_en.pos][item_en.pos];
            grid_max[item_en.pos][item_en.pos] = item_en.valor_visto;
            auto saida = solver_nova_max(grid_max, matrix_max_visitada, ls_matriz, tuple_marginal );
            bool r_saida_solucao = std::get<0>(saida);
            if(r_saida_solucao){
                return saida;
            }else{
                grid_max[item_en.pos][item_en.pos] = valor_antigo;
                ls_matriz[pros_item_i].visited = false;
                return saida;
            }

        }

    }


}






std::tuple<bool, std::vector<std::vector<int> > > generate_matriz_maxima_correta(std::vector<std::vector<int> >grid, int qnt_simpl){
//    int qnt_simpl = 1;

    auto arruma_grid = [&grid] (int dive_por){
        std::vector<std::vector<int>> saida;

        for(auto linha: grid){
            std::vector<int> linha_add;
            for(auto celula: linha){
                linha_add.push_back( int(ceil( celula/dive_por)));
            }
            saida.push_back(linha_add);
        }

        return saida;

    }(qnt_simpl);

    grid = arruma_grid;
    std::vector<std::vector<int> > grid_max = generate_matriz_maxima(grid);
    std::vector<std::vector<bool> > matrix_max_visitada = generate_matriz_maxima_visitada(grid);
    std::vector<Marginal> tuple_marginal = get_tuple_marginal(grid);






    auto get_lista_max_visto = [] ( std::vector<std::vector<int> > grid,  std::vector<std::vector<int> > grid_max){
        struct max_visto{
          int visto;
          int max;
        };
        std::vector< max_visto> saida;
        for(int i=0; i< grid[0].size(); i++){
            for(int j=0; j< grid[0].size(); j++){
                bool r_centro = i == j;
                if(r_centro){
                    max_visto m;
                    m.visto = grid[i][j];
                    m.max = grid_max[i][j];

                    saida.push_back(m);
                }

            }
        }

        std::vector<std::vector<valor_visto_pos>> queue;

        auto lis_max = saida;
        for( max_visto i : lis_max){
        std::vector<valor_visto_pos> q;
            for(int linha = i.max; linha >= i.visto; linha--){
                valor_visto_pos s;
                s.pos = queue.size();
                s.valor_visto = linha;
                s.visited = false;

                q.push_back(s);
            }
            queue.push_back(q);
        }


        std::vector<valor_visto_pos> q_saida;

        for(auto linha: queue){
            for(auto ele: linha){
                q_saida.push_back(ele);
            }
        }




        return q_saida;

    };

    auto ls_matriz = get_lista_max_visto(grid, grid_max);

    auto saida = solver_nova_max(grid_max, matrix_max_visitada, ls_matriz, tuple_marginal);

//     auto saida = solver(grid_max, matrix_max_visitada, tuple_marginal);

     if(std::get<0>(saida) == false){
         qDebug() << "nao encontrou";

     }

     std::vector<std::vector<int>> sa = std::get<1>(saida);

     auto arruma_vetor = [](int qnt_simpl, std::vector<std::vector<int>> &vetor){
         for(int i=0; i< vetor.size(); i++){
             for(int j=0; j< vetor.size(); j++){
                 vetor[i][j] = vetor[i][j] * qnt_simpl;
             }
         }
         return qnt_simpl;
     }(qnt_simpl, std::get<1>(saida));





//    qDebug() <<"saida";
    return  saida;


}



Calculo_paper::Calculo_paper(std::vector<int> etrografia_1, std::vector<int> etrografia_2, std::vector<int> catalogo, int qnt_simpl,
                             int qnt_maxima_permutaca, QObject *parent): QThread(parent)
{
    //arrumar essa função para deixar ela generica e guardar todos os valores.
    // para depois poder aplicar a tecnica de bootstrap.
    et1 = etrografia_1;
    et2 = etrografia_2;
    this->etrografia_1 = etrografia_1;
    this->etrografia_2 = etrografia_2;
    this->catalogo = catalogo;
    this->qnt_simpl = qnt_simpl;
    this-> qnt_maxima_permutaca =  qnt_maxima_permutaca;

//    this->do_proces();

}

void Calculo_paper::do_proces()
{
    auto matriz_concordancia = constroi_matrix_concordancia_cohen(etrografia_1, etrografia_2, catalogo);

    catalogo_var.categoria = 0;
    catalogo_var.matriz_concordancia = matriz_concordancia;
    catalogo_var.acaso = calcula_concordancia_acaso(matriz_concordancia);
    catalogo_var.observada =calcula_concordancia_observada(matriz_concordancia);
    catalogo_var.kappa = calcula_kappa_medio(matriz_concordancia);
    catalogo_var.vies = calcula_vies_NN(matriz_concordancia, qnt_maxima_permutaca) ;
    catalogo_var.prevalencia = calcula_prevalencia_NN(matriz_concordancia, qnt_maxima_permutaca);

    auto resolucao = generate_matriz_maxima_correta(catalogo_var.matriz_concordancia, qnt_simpl);

    bool encontrou = std::get<0>(resolucao); // nunca testei se quando nao encontra resolução volta um false, nem sei se é possivel nao ter solução.
    std::vector<std::vector<int> > m_saida = std::get<1>(resolucao);

    catalogo_var_max.categoria = 0;
    catalogo_var_max.matriz_concordancia = m_saida;
    catalogo_var_max.acaso = calcula_concordancia_acaso(catalogo_var_max.matriz_concordancia);
    catalogo_var_max.observada =calcula_concordancia_observada(catalogo_var_max.matriz_concordancia);
    catalogo_var_max.kappa = calcula_kappa_medio(catalogo_var_max.matriz_concordancia);
    catalogo_var_max.vies = calcula_vies_NN(catalogo_var_max.matriz_concordancia);
    catalogo_var_max.prevalencia = calcula_prevalencia_NN(catalogo_var_max.matriz_concordancia);



//    float concordancia_acaso_catalogo = calcula_concordancia_acaso(matriz_concordancia);
//    float concordancia_observada_catalogo = calcula_concordancia_observada(matriz_concordancia);
//    float kappa_catalogo = calcula_kappa_medio(matriz_concordancia);
//    qDebug() << "Concordancia Cohone catalogo "<< matriz_concordancia << "concordancia acaso: " << concordancia_acaso_catalogo << "concordancia observada: " << concordancia_observada_catalogo << "Kappa: " << kappa_catalogo;


    for(int cat : catalogo){
        Calculo_paper::Concordancia kappa_categoria;
        kappa_categoria.categoria = cat;
        kappa_categoria.matriz_concordancia = gera_matrix_22_pela_categoria(etrografia_1, etrografia_2, catalogo, cat);
        kappa_categoria.acaso = calcula_concordancia_acaso(kappa_categoria.matriz_concordancia);
        kappa_categoria.observada = calcula_concordancia_observada(kappa_categoria.matriz_concordancia);
        kappa_categoria.kappa = calcula_kappa_medio(kappa_categoria.matriz_concordancia);
        kappa_categoria.vies = calculo_vies_categoria(kappa_categoria.matriz_concordancia);
        kappa_categoria.prevalencia = calculo_prevalencia_categoria(kappa_categoria.matriz_concordancia);
        list_kappa_cat.push_back(kappa_categoria);

        Calculo_paper::Concordancia kappa_categoria_max;
        kappa_categoria_max.categoria = cat;
        kappa_categoria_max.matriz_concordancia = arruma_matrix_kappa_maximo(kappa_categoria.matriz_concordancia);
        kappa_categoria_max.acaso = calcula_concordancia_acaso(kappa_categoria_max.matriz_concordancia);
        kappa_categoria_max.observada = calcula_concordancia_observada(kappa_categoria_max.matriz_concordancia);
        kappa_categoria_max.vies = calculo_vies_categoria(kappa_categoria_max.matriz_concordancia);
        kappa_categoria_max.kappa = calcula_kappa_medio(kappa_categoria_max.matriz_concordancia);
        kappa_categoria_max.prevalencia = calculo_prevalencia_categoria(kappa_categoria_max.matriz_concordancia);
        list_kappa_cat_max.push_back(kappa_categoria_max);

    }


//    std::vector<std::vector<int> > matrix_22_swimming = gera_matrix_22_pela_categoria(etrografia_1, etrografia_2, catalogo, 0);
//    float viez_swimming = calculo_vies_categoria(matrix_22_swimming);
//    float prevalencia_swimming = calculo_prevalencia_categoria(matrix_22_swimming);
//    float kappa_swimming = calcula_kappa_medio(matrix_22_swimming);
//    qDebug() << "Swimming \n" << matrix_22_swimming << "Vies: " << viez_swimming << "Prevalencia: " << prevalencia_swimming << "Kappa: " << kappa_swimming;

//    std::vector<std::vector<int>> kappa_maximo_matrix = arruma_matrix_kappa_maximo(matrix_22_swimming);
//    float viez_max_swimming = calculo_vies_categoria(kappa_maximo_matrix);
//    float prevalencia_max_swimming = calculo_prevalencia_categoria(kappa_maximo_matrix);
//    float kappa_max_swimming = calcula_kappa_medio(kappa_maximo_matrix);
//    qDebug() << "Swimming max \n" << kappa_maximo_matrix << "Vies: " << viez_max_swimming << "Prevalencia: " << prevalencia_max_swimming << "Kappa: " << kappa_max_swimming;


}




std::vector<float> rota_vetor(double teta, int celula)
{


    auto gera_matriz_rotacao = [](double teta){
        std::vector<std::vector<float>> mt_rotacao;
        mt_rotacao.push_back({
                                 float(cos(teta)),
                                 float(sin(teta))
                             });

        mt_rotacao.push_back({
                                 float(-sin(teta)),
                                 float(cos(teta))
                             });


        return mt_rotacao;
    };

    auto multipla_matriz = [](std::vector<float> v_entrada,
            std::vector<std::vector<float>> mt_rotada){

        std::vector<float> saida = {
                           mt_rotada[0][0]* v_entrada[0] + mt_rotada[0][1]* v_entrada[1],
                           mt_rotada[1][0]* v_entrada[0] + mt_rotada[1][1]* v_entrada[1]
                        };


        return  saida;

    };

    std::vector<float> vetor_entrada = {float(celula), 0};

    auto mt_ro =  gera_matriz_rotacao(teta * 3.14159265358979323846/180);
    auto saida = multipla_matriz(vetor_entrada, mt_ro);
    return saida;


}


float soma_vetor(std::vector<int> ls_celulas){

    float qnt_rotacao = 360 / ls_celulas.size();

    std::vector<std::vector<float>> ls_vetore;
    int i=0;
    for(auto ele : ls_celulas){

        ls_vetore.push_back( rota_vetor(qnt_rotacao*i, ele));
        i++;
    }

    float soma_x = 0;
    float soma_y = 0;
    for(int i=0; i< ls_vetore.size(); i++){
        for(int c=0; c< ls_vetore[i].size(); c++){
            if(c == 0){
                soma_x = soma_x + ls_vetore[i][c];

            }else if(c ==1 ){

                soma_y = soma_y + ls_vetore[i][c];
            }
        }
    }

    float norma = sqrt((soma_x * soma_x) + (soma_y * soma_y) );
    return norma;


}





float calcula_prevalencia_NN(std::vector<std::vector<int>> grid, int qnt_maxima){

    auto get_numero_frames =[&grid](){
        int saida = 0;
        for(int linha=0; linha < grid.size(); linha++){
            for(int col=0; col < grid.size(); col++){
                 saida = saida + grid[linha][col];
            }
        }
        return saida;
    }();

    auto get_linha_central =[&grid](){
        std::vector<int> saida;
        for(int linha=0; linha < grid.size(); linha++){
            for(int col=0; col < grid.size(); col++){
                bool r_linha_central = linha == col;
                if(r_linha_central){
                    saida.push_back(grid[linha][col]);
                }
            }
        }
        return saida;
    };


    auto l_centr = get_linha_central();

    std::sort(std::begin(l_centr), std::end(l_centr));

    auto a = realiza_permutacao(l_centr, qnt_maxima);

    return a/get_numero_frames;






}


float calcula_vies_NN(std::vector<std::vector<int>> grid, int qnt_maxima){


    auto get_numero_frames =[&grid](){
        int saida = 0;
        for(int linha=0; linha < grid.size(); linha++){
            for(int col=0; col < grid.size(); col++){
                 saida = saida + grid[linha][col];
            }
        }
        return saida;
    }();



    auto get_linha_central =[&grid](){
        std::vector<int> saida;
        for(int linha=0; linha < grid.size(); linha++){
            for(int col=0; col < grid.size(); col++){
                bool r_not_linha_central = linha != col;
                if(r_not_linha_central){
                    saida.push_back(grid[linha][col]);
                }
            }

        }
        return saida;
    };

    auto l_centr = get_linha_central();

//    std::vector<float> l_vetores;


    std::sort(std::begin(l_centr), std::end(l_centr));




//    auto a =  *std::max_element(l_vetores.begin(), l_vetores.end());
    auto a = realiza_permutacao(l_centr, qnt_maxima);

    return a/get_numero_frames;







}





float realiza_permutacao(std::vector<int> l_centr, int qnt_maxima)
{

    float maior = -1;
    int i =0;
    bool r_nao_chego_maximo = i < qnt_maxima;
    do {
        int soma_encontrada = soma_vetor(l_centr);
//        qDebug() << l_centr;
        bool r_bool_maior = soma_encontrada > maior;
        if(r_bool_maior){
            maior = soma_encontrada;
        }

        i++;

        r_nao_chego_maximo = i < qnt_maxima;


//        l_vetores.push_back(soma_vetor(l_centr));
    } while ((std::next_permutation(l_centr.begin(), l_centr.end()) && r_nao_chego_maximo));


//    auto a =  *std::max_element(l_vetores.begin(), l_vetores.end());
    auto a = maior;

    return a;


}
