#include "telacadastropessoa.h"
#include "ui_telacadastropessoa.h"
#include <QMessageBox>

telaCadastroPessoa::telaCadastroPessoa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaCadastroPessoa)
{
    ui->setupUi(this);

   QObject::connect(this,SIGNAL(fechouJanela()),this,SLOT(mudaLetra()));
   vezes=0;
   tutor=1;
   nomeArquivo="";



   controlWarnig = new ControladoWarningTutor(":/tutor/tutores/tutoresTelaCadastroPessoa.xml");
   seqInicial.append("tutorInicio");
   seqInicial.append("tutorSaida");

   connect(controlWarnig,SIGNAL(clicou(bool,QString)),this,SLOT(botaoClicado(bool,QString)));

}

void telaCadastroPessoa::setTutor(bool chTutor){
    if(chTutor){
        tutor=1;
    }else{
        tutor=0;
    }

}

bool telaCadastroPessoa::getTutor(){
    if(tutor == 1){
        return true;
    }else{
        return false;
    }
}

void telaCadastroPessoa::showInterface()
{
    this->show();

    controlWarnig->setLista(seqInicial);
    controlWarnig->nextList(true);

}

telaCadastroPessoa::~telaCadastroPessoa()
{
    qDebug() <<" tela cadastro pessoa fechou";
    controlWarnig->fechandoJanelas();
   // emit fechouJanela();
    if(nomeArquivo !=""){
        gravandoUserXML();
        qDebug() <<" gtravou o usuario apos o usuario ser destruido";
    }else{


    }
    delete ui;
}

void telaCadastroPessoa::gravandoUserXML(){

    QFile output(nomeArquivo);
    //output.open(stdout, );

    vezes++;
    output.open(QIODevice::WriteOnly);
//! [write output]
//! [start stream]
    QXmlStreamWriter stream(&output);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();//começa o documento

    stream.writeStartElement("experimentador"); //abre o experimentador
    //stream.writeStartElement(nome);
    stream.writeTextElement("nome", nome);
    stream.writeTextElement("laboratorio", lab);
    stream.writeTextElement("password", ui->lePass->text());
    stream.writeTextElement("vezes",  QString::number(vezes));
    stream.writeTextElement("tutor",  QString::number(tutor));


    //stream.writeTextElement("sexo", sexo);

    //stream.writeTextElement("idade", "20");

    //stream.writeStartElement("data");



    //stream.writeTextElement("dia", QString::number(data.day())  );
    //stream.writeTextElement("mes", QString::number(data.month())  );
    //stream.writeTextElement("dia", QString::number(data.year())  );
  //  stream.writeEndElement(); //fecha elemento data


    stream.writeEndElement(); // fecha o experimentador
    stream.writeEndDocument();
    output.close();
}



void telaCadastroPessoa::lendoXML(){

    QFile output(nomeArquivo);
    output.open(QIODevice::ReadOnly | QIODevice::Text);

    //QXmlS
    QXmlStreamReader xmlReader(&output);

    while(!xmlReader.atEnd() && !xmlReader.hasError()){


   // if(xmlReader.name() == "experimentador"){
    if(xmlReader.name() == "nome"){
      // qDebug() << xmlReader.readElementText();
       nome = xmlReader.readElementText();
       //adsa=true;
       }
    if(xmlReader.name() == "laboratorio"){
       //qDebug() << xmlReader.readElementText();
       lab = xmlReader.readElementText();
       //adsa=true;
       }

    if(xmlReader.name() == "vezes"){
       //qDebug() << xmlReader.readElementText();
       vezes = xmlReader.readElementText().toInt();
       //adsa=true;
       }
    if(xmlReader.name() == "idObservador"){
       qDebug() << xmlReader.readElementText();
       //adsa=true;
       }

    if(xmlReader.name() == "sexo"){
       qDebug() << xmlReader.readElementText();
       //adsa=true;
       }


    if(xmlReader.name() == "idade"){
       qDebug() << xmlReader.readElementText();
       //adsa=true;
       }



    xmlReader.readNext();

   }


}


//salvar

void telaCadastroPessoa::setLocalArquivo(){

    nomeArquivo = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "User files (*.uxml)"
               );
}

bool telaCadastroPessoa::loadUser(){

    nomeArquivo = QFileDialog::getOpenFileName(
                this,
                tr("Load File"),
                "C://",
               "User files (*.uxml)"
               );


    if(nomeArquivo == ""){

        return false;

    }else{
         lendoXML();
         emit this->fechouJanela();
         return true;
    }




}



void telaCadastroPessoa::on_pushButton_2_clicked()
{
    //abre uma janela para salvar

    setLocalArquivo();
    nome= ui->leNome->text();
    lab = ui->leLab->text();


    //pega as variaveis da janela
    //nomeArquivo= nomeArquivo;
    //extensao= ".uxml";
    //nomeExtensao = extensao.insert(0,nomeArquivo);

    gravandoUserXML();

    QMessageBox::information(this,tr("Message"),tr("Saved successfully"));

    emit this->fechouJanela();
    //emite um sinal para fechar a janela (fehca a janela)
    this->close();
    //deleta a janela (chama o destrutor);
//    delete this;

}

void telaCadastroPessoa::mudaLetra(){

    ui->label->setText("oii");
}

void telaCadastroPessoa::botaoClicado(bool, QString)
{

}
