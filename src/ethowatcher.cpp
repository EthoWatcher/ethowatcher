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
#include "ethowatcher.h"
#include "ui_ethowatcher.h"

ethoWatcher::ethoWatcher(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ethoWatcher)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWiEthowatcher->setCurrentIndex(0);

    ui->tabWiEthowatcher->setEnabled(true);
    chLoadUser= false;
    cadastroFilme = new telaCadastroFilme();
    cego = new telablind();
    segment = new telaSegementacao();
    transi= new telaMatrizTransicao();
    concordancia= new teaConcordancia();
    etografaProce= new telaEtografiaProce();
    unveil = new telaUnveil();
    tempoReal = new telaTempoReal();
    fluxoComportamental = new telaFluxoComportamental();

    ui->pbConversorXMLCSV->setVisible(false);

    tutor_interface.lerXml("C:\\Users\\marcolan\\Desktop\\ENTREGAR\\ethowatcher\\src\\tutores\\ethowatcherInpi.xml");

    qDebug() << tutor_interface.getTextoById("ethoInicio");






    //ui->treeWidget->

    //cadastroPessoa = new telaCadastroPessoa(); //eh necessario para a alocacao da memoria
    //cadastroFilme = new telaCadastroFilme();
    //aquisicaoFilme = new telaAquisicaoFilme();
    //cadastroListaFilme = new telaCadastroListaFilme();
    //cadastroEtograma = new telaCadastroEtograma();

    //connect(cadastroPessoa,SIGNAL(fechouJanela()),this,SLOT(mudaTela()));

}

ethoWatcher::~ethoWatcher()
{
    //deletar tudo
  //  delete cadastroFilme;
   // delete cadastroPessoa;
   // delete aquisicaoFilme;
   // delete cadastroPessoa;
   // delete cadastroFilme;
  //  delete cadastroListaFilme;
    //telaCadastroEtograma *cadastroEtograma;
   // delete cego;
  //  delete etografia;
    delete tempoReal;
    delete unveil;
    delete cego;
    //foi arrumado com onovo sistema de destruição
    //delete cadastroFilme;
    //foi arrumado com o novo sistema de destruição
    // delete etografaProce;
    delete ui;



}


//stacked tela 1

void ethoWatcher::on_pbTela1No_clicked()
{
    //abir tela para cadastro cadastro da pessoa

    cadastroPessoa = new telaCadastroPessoa(); //eh necessario para a alocacao da memoria
    connect(cadastroPessoa,SIGNAL(fechouJanela()),this,SLOT(mudaTela()));
    cadastroPessoa->show();

    //ui->lb1->setText("oij");
}

void ethoWatcher::on_pbTela1Yes_clicked()
{
    cadastroPessoa = new telaCadastroPessoa(); //eh necessario para a alocacao da memoria
    connect(cadastroPessoa,SIGNAL(fechouJanela()),this,SLOT(mudaTela()));
    //abre arquivo cadastrado de usuario
    fonteUsuario= QFileDialog::getOpenFileName(
                    this,
                    tr("Open File"),
                    "C://",
                   "Video Files (*.uxml)"
                    );

      //Se a string capturada for vazia (casos: fechar ou cancelar janela de diálogo), sai da função
     // abrir video e não executa os códicos a seguir

     //  fonteUsuarioBit = fonteUsuario.toLatin1();
    if(fonteUsuario!=""){

                cadastroPessoa->nomeArquivo= fonteUsuario;
                 cadastroPessoa->lendoXML();


            // if(cadastroPessoa->nome !=""){

                 QString fraseInicial;
                 fraseInicial= "Hello " + cadastroPessoa->nome+
                         " do laboratorio " +cadastroPessoa->lab+
                         " escolha entre os botões a baixo o que você gostaria de fazer."+
                         "O programa conta com as opções de: \n "+
                         "1-Gravar um video apartir da webcam \n" +
                         "2-Cadastrar um video de seu banco de dados de videos para utilizar no ethowatcher \n"+
                         "3-Criar uma lista de videos cadastrados para ser utilizado na analise ethologica,cinematica,RNA\n"+
                         "4-Fazer uma analise ethologica com a opção de duplo cego.\n"+
                         "5-Fazer uma analise cinematica tanto de um video como de uma lista de videos \n"+
                         "6-Utilizar uma RNA para analisar seus experimentos ";

                 //ui->tePrimeiro->setText(fraseInicial);
                 //ui->stackedWidget->setCurrentIndex(1);
                 ui->tabWiEthowatcher->setEnabled(true);
                 //ui->widBotoCadas->setEnabled(false);
                 qDebug() << cadastroPessoa->nome + " lab " + cadastroPessoa->lab;
                 chLoadUser =true;
        }


}

//funcao que é chamado ao salvar novo usuario
void ethoWatcher::mudaTela(){

    if(cadastroPessoa->nome !=""){

        QString fraseInicial;
        fraseInicial= "Hello " + cadastroPessoa->nome+
                " do laboratorio " +cadastroPessoa->lab+
                " escolha entre os botões a baixo o que você gostaria de fazer."+
                "O programa conta com as opções de: \n "+
                "1-Gravar um video apartir da webcam \n" +
                "2-Cadastrar um video de seu banco de dados de videos para utilizar no ethowatcher \n"+
                "3-Criar uma lista de videos cadastrados para ser utilizado na analise ethologica,cinematica,RNA\n"+
                "4-Fazer uma analise ethologica com a opção de duplo cego.\n"+
                "5-Fazer uma analise cinematica tanto de um video como de uma lista de videos \n"+
                "6-Utilizar uma RNA para analisar seus experimentos ";

        qDebug() << cadastroPessoa->nome + " oi" + cadastroPessoa->lab;

        //ui->tePrimeiro->setText(fraseInicial);

    //ui->stackedWidget->setCurrentIndex(1);
    ui->tabWiEthowatcher->setEnabled(true);
    //ui->widBotoCadas->setEnabled(false);
   // ui->lb1->setText("oi");
    }

    cadastroPessoa->close();

}




//stacked tela 2
//abre janela para cadastrar filme
void ethoWatcher::on_pbTela2ListaVideo_clicked()
{
    cadastroFilme = new telaCadastroFilme();
    if(chLoadUser){
            cadastroFilme->setExperimentador(cadastroPessoa->nome,cadastroPessoa->lab);
    }

    cadastroFilme->show();


}


//abre janela para gravar video
//void ethoWatcher::on_pbTela2Gravar_clicked()
//{
//    //aquisicaoFilme = new telaAquisicaoFilme();

//    //aquisicaoFilme->show();
//}

void ethoWatcher::on_pbCadastrarListaVideo_clicked()
{
    cadastroListaFilme = new telaCadastroListaFilme();
    cadastroListaFilme->show();
}

void ethoWatcher::on_pbAnaliseEtograma_clicked()
{
    //tela de etografia.
    etografaProce= new telaEtografiaProce();
     if(chLoadUser){
        etografaProce->setExperimentador(cadastroPessoa->nome,cadastroPessoa->lab);
     }
    etografaProce->show();
    //etografia= new telaEtografia();
    //etografia->setExperimentador("Joao e ","UFSC BIOENGENHARIA");
   // etografia->show();
    //cadastroEtograma->show();
}

void ethoWatcher::on_pbDuploCego_clicked()
{
    cego = new telablind();
    cego->show();
}

void ethoWatcher::on_pbEstatistica_clicked()
{
    segment = new telaSegementacao();

    segment->show();
//    estatistica = new telaEstatistica();
//    estatistica->show();
}

void ethoWatcher::on_pbConversorXMLCSV_clicked()
{

    //conversorXmlCsv= new telaConversorXmlCsv();
    //conversorXmlCsv->show();

}

void ethoWatcher::on_actionAbout_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ethoWatcher::on_pbBackAbout_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

//void ethoWatcher::on_actionTips_triggered()
//{
//    //abre a janela de tips

//}

void ethoWatcher::on_actionLicense_agreement_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ethoWatcher::on_pbBackLicense_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void ethoWatcher::on_treeWidget_doubleClicked(const QModelIndex &index)
{


    QTreeWidgetItem *novo;
    novo = new QTreeWidgetItem();

    novo = ui->treeWidget->currentItem();

   resetaCorBotoes();


   // qDebug() <<" A coluna foi a " <<index.column() << " A linha foi " << index.row();
    qDebug() <<  ui->treeWidget->currentItem()->text(index.column());

    QString nome= ui->treeWidget->currentItem()->text(index.column());
    if(nome == "Cadastro Usuario"){
        qDebug() << "clicou no usuario Cadastrado";
        ui->pbTela1No->setStyleSheet("background-color: yellow");
       // ui->groupBox_2->setStyleSheet("background-color: yellow");

        //amarelo o que necessita para
        //verde o objeto na tela

    }
    if(nome == "Cadastro Video"){
    qDebug() << "clicou no Video Cadastrado";
        ui->pbTela2ListaVideo->setStyleSheet("font: bold;""background-color: #00ac00;"); //verde
        ui->pbTela1Yes->setStyleSheet("font: bold;""background-color: #076aff;");//azul
        ui->swidTutorBancoDados->setCurrentIndex(3);
    }

    if(nome == "Load User"){
    qDebug() << "clicou no Load User";
    ui->pbTela1Yes->setStyleSheet("font: bold;""background-color: #00ac00;"); //verde
    ui->pbTela1No->setStyleSheet("font: bold;" "background-color: red");
    ui->swidTutorBancoDados->setCurrentIndex(1);
    }

    //aqui mostra o que é necessario para pode usar a tela;
    //verde é o botão
    //amarelo os que precisa;
    //verde o botão
    //amarelo os opcionais
    //vermelho são os que precisam
    if(nome == "Cegar os Videos"){
    qDebug() << "clicou no Video Cadastrado";
    //        ui->pbTela2ListaVideo->setStyleSheet("background-color: red;");
        //ui->pbTela2ListaVideo->setStyleSheet("background-color: green");
        ui->pbDuploCego->setStyleSheet("font: bold;""background-color: #00ac00;"); //verde
        ui->pbCadastrarListaVideo->setStyleSheet("font: bold;""background-color: red;");
        ui->pbTela1No->setStyleSheet("font: bold;""background-color: red;");
        ui->swidTutorBancoDados->setCurrentIndex(5);
    }


}

void ethoWatcher::resetaCorBotoes()
{

    ui->pbDuploCego->setStyleSheet("font: ;""background-color: ;");
    ui->pbCadastrarListaVideo->setStyleSheet("font: ;""background-color: ;");
    ui->pbTela1No->setStyleSheet("font: ;""background-color: ;");
    ui->pbTela2ListaVideo->setStyleSheet("font: ;""background-color:");
    ui->pbTela1Yes->setStyleSheet("font: ;""background-color: ;");

//    ui->pbDuploCego->setStyleSheet("font:;""background-color:;");
//    ui->pbTela1No->setStyleSheet("background-color: ");
//    ui->pbTela2ListaVideo->setStyleSheet("background-color: ");


}

void ethoWatcher::on_pbRegisterCatalog_clicked()
{
    cadastroCatalogo = new telaCadastroCatalago();

    cadastroCatalogo->show();

}

void ethoWatcher::on_pbTransicao_clicked()
{
    transi= new telaMatrizTransicao();
    transi->show();

}

void ethoWatcher::on_pbConcordancia_clicked()
{
    concordancia= new teaConcordancia();
    concordancia->show();
}

void ethoWatcher::on_pbUnveil_clicked()
{

    unveil = new telaUnveil();
    unveil->show();
}

void ethoWatcher::on_pbRealTime_clicked()
{
    tempoReal = new telaTempoReal();
    tempoReal->show();
}

void ethoWatcher::on_pbBehaviorSample_clicked()
{
    fluxoComportamental = new telaFluxoComportamental();
    fluxoComportamental->show();
}
