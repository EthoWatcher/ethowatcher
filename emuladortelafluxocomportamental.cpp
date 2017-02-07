#include "emuladortelafluxocomportamental.h"
#include "ui_emuladortelafluxocomportamental.h"

EmuladorTelaFluxoComportamental::EmuladorTelaFluxoComportamental(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorTelaFluxoComportamental)
{
    ui->setupUi(this);
    fluxoComportamental = new telaFluxoComportamental();
}

EmuladorTelaFluxoComportamental::~EmuladorTelaFluxoComportamental()
{
    delete fluxoComportamental;
    delete ui;
}

void EmuladorTelaFluxoComportamental::on_pushButton_clicked()
{
    fluxoComportamental = new telaFluxoComportamental();
    fluxoComportamental->show();
}
