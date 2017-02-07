#include "emuladortelacego.h"
#include "ui_emuladortelacego.h"

EmuladorTelaCego::EmuladorTelaCego(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorTelaCego)
{
    ui->setupUi(this);
    cego = new telaCego();
}

EmuladorTelaCego::~EmuladorTelaCego()
{
    delete cego;
    delete ui;
}

void EmuladorTelaCego::on_pushButton_clicked()
{
    cego = new telaCego();
    cego->show();
}
