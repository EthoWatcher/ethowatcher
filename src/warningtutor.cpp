#include "warningtutor.h"
#include "ui_warningtutor.h"

WarningTutor::WarningTutor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarningTutor)
{
    ui->setupUi(this);
    this->setNoOn(false);
    this->setYesOn(false);
    setWindowFlags(Qt::CustomizeWindowHint);
    //    connect(this,SIGNAL())

    //chute 1 para adicionar imagem
    //    QImage img(":/icons/cabecalho.jpg"); // todo: generate image in memory
    //    ui->textoTutor->document()->addResource(QTextDocument::ImageResource, QUrl("qrc:/icons/cabecalho.jpg" ), img);

    new QShortcut( Qt::Key_Y, this, SLOT(on_pbYes_clicked()));
    new QShortcut( Qt::Key_N, this, SLOT(on_pbNo_clicked()));

    tutorId="";
}

WarningTutor::~WarningTutor()
{
    delete ui;
}

void WarningTutor::setTextDestaque(QString Text)
{
    ui->lblDestaque->setText(Text);

}

void WarningTutor::setId(QString text){

    tutorId = text;
}

void WarningTutor::setTextTutor(QString Text)
{

    ui->textoTutor->setText(Text);
    //    ui->webView->load(QUrl("http://qt-project.org"));
    //webView->setUrl(QUrl(QStringLiteral("about:blank")));

}

//void WarningTutor::setButtonYes(QPushButton botao){

//    botao.click();

//}

void WarningTutor::setTextYes(QString Text)
{
    ui->pbYes->setText(Text);

    if(Text== ""){
        this->setYesOn(false);
    }else{
        this->setYesOn(true);
    }

}

void WarningTutor::setTextNo(QString Text)
{

    ui->pbNo->setText(Text);
    if(Text == ""){
        this->setNoOn(false);
    }else{
        this->setNoOn(true);
    }

}

void WarningTutor::setYesOn(bool chave)
{
    ui->pbYes->setEnabled(chave);
    ui->pbYes->setVisible(chave);

}

void WarningTutor::setNoOn(bool chave)
{
    ui->pbNo->setEnabled(chave);
    ui->pbNo->setVisible(chave);

}

bool WarningTutor::getId(QString textId)
{
    if (textId == tutorId){

        return true;
    }else{

        return false;
    }


}

void WarningTutor::on_pbYes_clicked()
{
    emit clickYes();

    emit clicou(true,tutorId);
    this->close();
}

void WarningTutor::on_pbNo_clicked()
{
    emit clickNo();
    emit clicou(false,tutorId);
    this->close();
}

void QWidget::closeEvent(QCloseEvent *){

    qDebug() << "isso fechou";

}

ControladoWarningTutor::ControladoWarningTutor(QString XML)
{

    //ja pega todos os tutores xml
    tutor.lerXml(XML);
    tutor.debugID();
    contador=0;

    chHabilitaTutor=true;

}
/**
 * @brief ControladoWarningTutor::setLista metodo para criar uma lista de interface de tutores
 * @param sequencia de tutores que quer
 */
void ControladoWarningTutor::setLista(QList<QString> sequencia)
{

    desconectandoListaTutores();
    contador=0;
    qDebug() << "================= 123123 12==========";
    this->sequenciaTutores = sequencia;


    criandoInterfaces();





}
void ControladoWarningTutor::criandoInterfaces(){

    //    QList<WarningTutor *> lista;


    for(int i=0; i< this->sequenciaTutores.size(); i++){
        qDebug() << this->sequenciaTutores[i];

        tutorAbs = new WarningTutor();
        tutorAbs->setTextDestaque(tutor.getTitulo(this->sequenciaTutores[i]));
        tutorAbs->setId(this->sequenciaTutores[i]);
        tutorAbs->setTextTutor( tutor.getTextoById(this->sequenciaTutores[i]));
        tutorAbs->setTextYes(tutor.getPbS(this->sequenciaTutores[i]));
        tutorAbs->setTextNo(tutor.getPbN(this->sequenciaTutores[i]));

        listaTutores.append(tutorAbs);


        connect(listaTutores[i],SIGNAL(clicou(bool,QString)),this,SLOT(wrapper(bool,QString)));

    }


}


void ControladoWarningTutor::desconectandoListaTutores(){

    qDebug() << "desconectando 1";
    for(int i=0; i<listaTutores.size();i++){
        disconnect(listaTutores[i],SIGNAL(clicou(bool,QString)),this,SLOT(wrapper(bool,QString)));
        listaTutores.pop_back();
    }
    qDebug() << "desconectando 2";


}



/**
 * @brief ControladoWarningTutor::wrapper para enviar se foi clicado o botao yes ou no
 * @param chBotao
 */
void ControladoWarningTutor::wrapper(bool chBotao, QString id){

    qDebug()<< "oi mundo 12312 ";
    emit clicou(chBotao,id);
}


void ControladoWarningTutor::nextById(QString id){

    for(int i=0; i<listaTutores.size();i++){
        if(listaTutores[i]->getId(id) ){

            if(chHabilitaTutor){
               listaTutores[i]->show();
               qDebug()<<"foi ligada a interface " << id;
            }

            break;
        }
    }
}

void ControladoWarningTutor::setTutor(bool chLigaTutor)
{
    this->chHabilitaTutor = chLigaTutor;
}

/**
 * @brief ControladoWarningTutor::nextList método para ir para o próximo da lista
 * @param chNext
 */
void ControladoWarningTutor::nextList(bool chNext)
{


    if(contador<listaTutores.size()){

        this->nextById(this->sequenciaTutores[contador]);

        if((chNext)){
            contador++;
        }

    }


}

