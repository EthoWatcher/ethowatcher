#include "telacadastrolistafilme.h"
#include "ui_telacadastrolistafilme.h"

telaCadastroListaFilme::telaCadastroListaFilme(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaCadastroListaFilme)
{
    ui->setupUi(this);
    palavras= new QString[1];
    item= new QListWidget();
    ui->pbDeletar->setVisible(false);

}

telaCadastroListaFilme::~telaCadastroListaFilme()
{
    delete ui;
}

void telaCadastroListaFilme::on_pbOpenXml_clicked()
{


    nomeArquivo= QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                   "Video Files (*.vxml)"
                    );


    ui->lblNome->setText(separandoNome(nomeArquivo));
    ui->lblCaminho->setText(separandoCaminho(nomeArquivo));
    ui->lblExtensao->setText(separandoExt(nomeArquivo));

    ui->pbAddVideo->setEnabled(true);
    // count++;

  //  std::string fernando;
   // fernando = ui->leTexto->text().toStdString();

   // joao.push_back(fernando);
   // nome.push_back(nomeArquivo);
   // maisPalavra= new QString[count];

  //  palavras= maisPalavra;
   // video = new videoLocal();
    //cada vez que entra aqui o contador soma mais 1

  //  std::vector<int> v;
    //e realocado mais memoria
   // more_numbers = (int*) realloc (numbers, count * sizeof(int));
   // maisPalavras =(std::string*) realloc(palavras, count * sizeof(std::string));

    //é passado isso para o
   // numbers=more_numbers;



    //é pegado o valor
    //numbers[count-1]=ui->leNumero->text().toInt();
   // *(palavras+count-1)="a";

}

void telaCadastroListaFilme::on_pbAddVideo_clicked()
{

    //adiciona mais um string a lista
    nome.push_back(nomeArquivo);


   // item->addItem(nomeArquivo);

    //ui->listWidget->addItem();
    //for (int n=0;n<count;n++){
       // qDebug() << numbers[n];
    //  qDebug() << QString::fromStdString(joao[n]);
        ui->listWidget->addItem(nome[count]);
      // qDebug() << nome[n];
   // }
        count++;

        ui->pbAddVideo->setEnabled(false);

//ui->listWidget->setCurrentItem(0);

}

void telaCadastroListaFilme::on_pbDeletar_clicked()
{


    //ui->listWidget->currentItem()->setHidden(true);

  // ui->leTexto->text()= QString::number(ui->listWidget->currentRow());
    //ui->listWidget->currentItem()->setHidden(false);


   // ui->listWidget->setCurrentRow(1);

//int a=ui->listWidget->row(); // = ui->listWidget->count();
//ui->listWidget->addItem("kasdkalsd");

  //  itm->r

}

QString telaCadastroListaFilme::separandoCaminho(QString nomeArq){

    QByteArray fonteVideoBit,fonteVideoBitExtInv,fonteVideoBitExt,fonteVideoBitCaminhoArquivo,fonteVideoBitNomeArquivo;
    QString arquivoCaminho;
    QString arquivoNome;
    QString arquivoExt;

    if(!nomeArq.isNull())
{
        fonteVideoBit = nomeArq.toLatin1();


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

    //encontrar a ultima barra antes do nome
    int k=0;
    int ultimaPosicaoDaBarra=0;

    while(fonteVideoBit[k] != 0) //enquanto não tem string nula ou seja não é o fim do arquivo
    {

        if(fonteVideoBit[k] == 47){ //47 esta relacionado com a barra

            ultimaPosicaoDaBarra = k;

        }
        k++;


    }


    //assim pode-se encontar o nome do arquivo
    int contadorNome=ultimaPosicaoDaBarra+1;
    int contadorNome2=0;

    for(contadorNome;
        contadorNome <(fonteVideoBit.length()-j);
        contadorNome++)
    {

        fonteVideoBitNomeArquivo[contadorNome2]= fonteVideoBit[contadorNome];
        contadorNome2++;
    }

    //assim pode-se encontrar o caminho do arquivo
    int contadorCaminho=0;


    for(contadorCaminho;
        contadorCaminho < ultimaPosicaoDaBarra;
        contadorCaminho++)
    {

        fonteVideoBitCaminhoArquivo[contadorCaminho]= fonteVideoBit[contadorCaminho];

    }

    arquivoExt= QString::fromLatin1(fonteVideoBitExt);
    arquivoNome= QString::fromLatin1(fonteVideoBitNomeArquivo);
    arquivoCaminho = QString::fromLatin1(fonteVideoBitCaminhoArquivo);

    return arquivoCaminho;


}
}

QString telaCadastroListaFilme::separandoNome(QString nomeArq){

        QByteArray fonteVideoBit,fonteVideoBitExtInv,fonteVideoBitExt,fonteVideoBitCaminhoArquivo,fonteVideoBitNomeArquivo;
        QString arquivoCaminho;
        QString arquivoNome;
        QString arquivoExt;

        if(!nomeArq.isNull())
    {
            fonteVideoBit = nomeArq.toLatin1();


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

        //encontrar a ultima barra antes do nome
        int k=0;
        int ultimaPosicaoDaBarra=0;

        while(fonteVideoBit[k] != 0) //enquanto não tem string nula ou seja não é o fim do arquivo
        {

            if(fonteVideoBit[k] == 47){ //47 esta relacionado com a barra

                ultimaPosicaoDaBarra = k;

            }
            k++;


        }


        //assim pode-se encontar o nome do arquivo
        int contadorNome=ultimaPosicaoDaBarra+1;
        int contadorNome2=0;

        for(contadorNome;
            contadorNome <(fonteVideoBit.length()-j);
            contadorNome++)
        {

            fonteVideoBitNomeArquivo[contadorNome2]= fonteVideoBit[contadorNome];
            contadorNome2++;
        }

        //assim pode-se encontrar o caminho do arquivo
        int contadorCaminho=0;


        for(contadorCaminho;
            contadorCaminho < ultimaPosicaoDaBarra;
            contadorCaminho++)
        {

            fonteVideoBitCaminhoArquivo[contadorCaminho]= fonteVideoBit[contadorCaminho];

        }

        arquivoExt= QString::fromLatin1(fonteVideoBitExt);
        arquivoNome= QString::fromLatin1(fonteVideoBitNomeArquivo);
        arquivoCaminho = QString::fromLatin1(fonteVideoBitCaminhoArquivo);

    return arquivoNome;


    }


 }

QString telaCadastroListaFilme::separandoExt(QString nomeArq){

        QByteArray fonteVideoBit,fonteVideoBitExtInv,fonteVideoBitExt,fonteVideoBitCaminhoArquivo,fonteVideoBitNomeArquivo;
        QString arquivoCaminho;
        QString arquivoNome;
        QString arquivoExt;

        if(!nomeArq.isNull())
    {
            fonteVideoBit = nomeArq.toLatin1();


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

        //encontrar a ultima barra antes do nome
        int k=0;
        int ultimaPosicaoDaBarra=0;

        while(fonteVideoBit[k] != 0) //enquanto não tem string nula ou seja não é o fim do arquivo
        {

            if(fonteVideoBit[k] == 47){ //47 esta relacionado com a barra

                ultimaPosicaoDaBarra = k;

            }
            k++;


        }


        //assim pode-se encontar o nome do arquivo
        int contadorNome=ultimaPosicaoDaBarra+1;
        int contadorNome2=0;

        for(contadorNome;
            contadorNome <(fonteVideoBit.length()-j);
            contadorNome++)
        {

            fonteVideoBitNomeArquivo[contadorNome2]= fonteVideoBit[contadorNome];
            contadorNome2++;
        }

        //assim pode-se encontrar o caminho do arquivo
        int contadorCaminho=0;


        for(contadorCaminho;
            contadorCaminho < ultimaPosicaoDaBarra;
            contadorCaminho++)
        {

            fonteVideoBitCaminhoArquivo[contadorCaminho]= fonteVideoBit[contadorCaminho];

        }

        arquivoExt= QString::fromLatin1(fonteVideoBitExt);
        arquivoNome= QString::fromLatin1(fonteVideoBitNomeArquivo);
        arquivoCaminho = QString::fromLatin1(fonteVideoBitCaminhoArquivo);


    return arquivoExt;

    }


 }

void telaCadastroListaFilme::on_pbGravarXML_clicked()
{

    nomeGravarListaVideo = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Catalog files (*.lvxml)"
               );


    QFile output(nomeGravarListaVideo);
    //output.open(stdout, );
    output.open(QIODevice::WriteOnly);




    QXmlStreamWriter stream(&output); //passa o endereço
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento

    stream.writeStartElement("listaVideo");

    for(int i=0; i<count;i++){
    stream.writeStartElement("video");
    stream.writeAttribute("id", QString::number(i)); //escritor de atributos

        stream.writeTextElement("completo", nome[i]);
        stream.writeTextElement("caminho",separandoCaminho(nome[i]));
        stream.writeTextElement("nome",separandoNome(nome[i]));
        stream.writeTextElement("ext",separandoExt(nome[i]));

    stream.writeEndElement();

}


    stream.writeEndElement(); //abre o cadastroVideo
    stream.writeEndDocument(); //fecha o documento
    output.close(); //termina a gravacao

}
