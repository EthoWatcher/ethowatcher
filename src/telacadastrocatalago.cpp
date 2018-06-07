#include "telacadastrocatalago.h"
#include "ui_telacadastrocatalago.h"

telaCadastroCatalago::telaCadastroCatalago(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaCadastroCatalago)
{
    ui->setupUi(this);

    this->move(100,100);


    this->show();

    controlWarnig = new ControladoWarningTutor(":/tutor/tutores/tutoresTelaCadastroCatalogo.xml",this);
    connect(controlWarnig,SIGNAL(clicou(bool,QString)),this,SLOT(botaoClicado(bool,QString)));

    seqInicial.append("tutorInicio");
    seqInicial.append("tutorPrenchaCamposNameCodeDescription");
    seqInicial.append("tutoCatalogUnits");
    seqInicial.append("tutorDele");
    seqInicial.append("tutorSalva");

    controlWarnig->setLista(seqInicial);

    controlWarnig->nextList(true);

    ui->groupBox_3->setVisible(false);




}

telaCadastroCatalago::~telaCadastroCatalago()
{
    delete ui;
}

void telaCadastroCatalago::closeEvent(QCloseEvent *event){

    qDebug()<< " a janela de cadastro de usuario foi fechada ";
}

void telaCadastroCatalago::on_pbAddCategoria_clicked()
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


    controlWarnig->nextList("tutoCatalogUnits");
}

void telaCadastroCatalago::on_pbClearItem_clicked()
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

void telaCadastroCatalago::on_pbCadastroCatalago_clicked()
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

    this->close();
    //deleta a janela (chama o destrutor);
    delete this;

    //para colocar as variaveis dentro da variavel cAnaEto
    //que sera usada para fazer a analise etografica

   // readCatalago();

    //ui->swPrincipal->setCurrentIndex(1);

//    if(!nomeGravarCatalago.isEmpty()){
//    ui->pbEtografia->setEnabled(true);
//    }


}

void telaCadastroCatalago::botaoClicado(bool clicado, QString id)
{

    if(id == "tutorInicio"){
        qDebug() <<"oi mundo ";
        if(clicado){
            controlWarnig->nextList(true);

        }else{

        }

    }

}
