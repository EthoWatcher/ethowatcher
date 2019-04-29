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
#include "telacadastropessoa.h"
#include "ui_telacadastropessoa.h"
#include <QMessageBox>

telaCadastroPessoa::telaCadastroPessoa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaCadastroPessoa)
{
    ui->setupUi(this);

   QObject::connect(this,SIGNAL(fechouJanela()),this,SLOT(mudaLetra()));
}

telaCadastroPessoa::~telaCadastroPessoa()
{
    qDebug() <<" tela cadastro pessoa fechou";
    emit fechouJanela();
    delete ui;
}

void telaCadastroPessoa::gravandoXML(){

    QFile output(nomeArquivo);
    //output.open(stdout, );
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

void telaCadastroPessoa::on_pushButton_2_clicked()
{
    //abre uma janela para salvar
    nomeArquivo = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               "Catalog files (*.uxml)"
               );

    nome= ui->leNome->text();
    lab = ui->leLab->text();


    //pega as variaveis da janela
    //nomeArquivo= nomeArquivo;
    //extensao= ".uxml";
    //nomeExtensao = extensao.insert(0,nomeArquivo);

    gravandoXML();

    QMessageBox::information(this,tr("Message"),tr("Saved successfully"));

    emit this->fechouJanela();
    //emite um sinal para fechar a janela (fehca a janela)
    this->close();
    //deleta a janela (chama o destrutor);
    delete this;

}

void telaCadastroPessoa::mudaLetra(){

    ui->label->setText("oii");
}
