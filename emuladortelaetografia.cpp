#include "emuladortelaetografia.h"
#include "ui_emuladortelaetografia.h"

EmuladorTelaEtografia::EmuladorTelaEtografia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorTelaEtografia)
{
    ui->setupUi(this);
}

EmuladorTelaEtografia::~EmuladorTelaEtografia()
{
    delete ui;
}

void EmuladorTelaEtografia::on_pushButton_clicked()
{

}
