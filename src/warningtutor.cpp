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
    this->setYesOn(true);

}

void WarningTutor::setTextNo(QString Text)
{

    ui->pbNo->setText(Text);
    this->setNoOn(true);
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
    emit clicou(true);
    this->close();
}

void WarningTutor::on_pbNo_clicked()
{
    emit clickNo();
    emit clicou(false);
    this->close();
}

void QWidget::closeEvent(QCloseEvent *){

    qDebug() << "isso fechou";

}
