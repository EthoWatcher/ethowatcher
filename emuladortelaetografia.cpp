#include "emuladortelaetografia.h"
#include "ui_emuladortelaetografia.h"

EmuladorTelaEtografia::EmuladorTelaEtografia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorTelaEtografia)
{
    ui->setupUi(this);
    etoPro= new telaEtografiaProce();
}

EmuladorTelaEtografia::~EmuladorTelaEtografia()
{
    delete etoPro;
    delete ui;
}

void EmuladorTelaEtografia::on_pushButton_clicked()
{
     delete etoPro;
    etoPro= new telaEtografiaProce();
    etoPro->show();
}
