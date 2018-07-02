#include "telacadastropessoa.h"
#include "ui_telacadastropessoa.h"
#include <QMessageBox>

telaCadastroPessoa::telaCadastroPessoa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaCadastroPessoa)
{
    ui->setupUi(this);

    ui->label_2->setVisible(false);
    ui->lePass->setVisible(false);


    QObject::connect(this,SIGNAL(fechouJanela()),this,SLOT(mudaLetra()));
    vezes=0;
    tutor=1;
    nomeArquivo="";

    tutores.tutorCadastroCatalogo=1;
    tutores.tutorCadastroUsuario=1;
    tutores.tutorEthoWatcherPrincipal=1;



//# configurando a janela de control warning
    controlWarnig = new ControladoWarningTutor(":/tutor/tutores/tutoresTelaCadastroPessoa.xml",this);
    seqInicial.append("tutorInicio");
    seqInicial.append("tutorPrenchaCampos");
    seqInicial.append("tutorSaida");

    connect(controlWarnig,SIGNAL(clicou(bool,QString)),this,SLOT(botaoClicado(bool,QString)));

    chCarregado=false;

}

void telaCadastroPessoa::closeEvent(QCloseEvent *){

    controlWarnig->fechandoJanelas();
}


void telaCadastroPessoa::setTutor(QString nomeTutor,bool chTutor){

    int chTu=1;
    if(chTutor){
        chTu=1;

    }else{
        chTu=0;
    }
    if(nomeTutor=="tutorCadastroCatalogo"){
        tutores.tutorCadastroCatalogo = chTu;

    }else if(nomeTutor=="tutorCadastroUsuario"){

        tutores.tutorCadastroUsuario = chTu;


    }else if(nomeTutor=="tutorEthoWatcherPrincipal"){
        tutores.tutorEthoWatcherPrincipal = chTu;

    }

}

bool telaCadastroPessoa::getTutor(QString nomeTutor){

    if(nomeTutor=="tutorCadastroCatalogo"){
        if(tutores.tutorCadastroCatalogo == 1){
            return true;
        }else{
            return false;
        }
    }else if(nomeTutor=="tutorCadastroUsuario"){

        if(tutores.tutorCadastroUsuario == 1){
            return true;
        }else{
            return false;
        }

    }else if(nomeTutor=="tutorEthoWatcherPrincipal"){
        if(tutores.tutorEthoWatcherPrincipal == 1){
            return true;
        }else{
            return false;
        }

    }


}

void telaCadastroPessoa::showInterface()
{
//    this->move(100,100);
    this->show();

    controlWarnig->setLista(seqInicial);
    controlWarnig->nextList(true);

}
//void telaCadastroPessoa::show(){
//    controlWarnig->setLista(seqInicial);
//    controlWarnig->nextList(true);

//   qDebug() << "asduhausdhu";
//}

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

    stream.writeStartElement("tutores");
    stream.writeTextElement("tutorCadastroCatalogo",  QString::number(tutores.tutorCadastroCatalogo));
    stream.writeTextElement("tutorCadastroUsuario",   QString::number(tutores.tutorCadastroUsuario));
    stream.writeTextElement("tutorEthoWatcherPrincipal",  QString::number(tutores.tutorEthoWatcherPrincipal));

    stream.writeEndElement(); // fecha o experimentado


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


        //lendo os tutores;
        if(xmlReader.name() == "tutorCadastroCatalogo"){
            QString b=xmlReader.readElementText();
            qDebug() << "tutorCadastroCatalogo" << b;
            int a= transformaEm1(b);
            tutores.tutorCadastroCatalogo = a;
            //adsa=true;
        }

        if(xmlReader.name() == "tutorCadastroUsuario"){
            QString b=xmlReader.readElementText();
            qDebug() << "tutorCadastroCatalogo" << b;
            int a= transformaEm1(b);
            tutores.tutorCadastroUsuario = a;
            //adsa=true;
        }

        if(xmlReader.name() == "tutorEthoWatcherPrincipal"){
            QString b=xmlReader.readElementText();
            qDebug() << "tutorCadastroCatalogo" << b;
            int a= transformaEm1(b);
            tutores.tutorEthoWatcherPrincipal = a;
            //adsa=true;
        }


        //ler o proximo elemento
        xmlReader.readNext();

    }


}

int telaCadastroPessoa::transformaEm1(QString snumero){

    if(snumero=="1"){

        return 1;
    }else{
        return 0;
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


bool telaCadastroPessoa::createdUser(){

    qDebug() << "foi retornado o arquivo" << chCarregado;
    return chCarregado;

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
    if(nomeArquivo != ""){
        gravandoUserXML();

        chCarregado = true;
        qDebug() << "foi gravado o arquivo" << chCarregado;

        QMessageBox::information(this,tr("Message"),tr("Saved successfully"));

        controlWarnig->fechandoJanelas();

        emit this->fechouJanela();

        //emite um sinal para fechar a janela (fehca a janela)
        this->close();

    }else{
        QMessageBox::information(this,tr("Message"),tr("Saved not successfully"));
        chCarregado = false;
    }

    //deleta a janela (chama o destrutor);
    //    delete this;

}

void telaCadastroPessoa::mudaLetra(){

    ui->label->setText("oii");
}

void telaCadastroPessoa::botaoClicado(bool, QString)
{

    controlWarnig->nextById("tutorPrenchaCampos");
}
