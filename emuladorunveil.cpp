#include "emuladorunveil.h"
#include "ui_emuladorunveil.h"

EmuladorUnveil::EmuladorUnveil(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorUnveil)
{
    ui->setupUi(this);
    unveil = new telaUnveil();
}

EmuladorUnveil::~EmuladorUnveil()
{
    delete unveil;
    delete ui;
}

void EmuladorUnveil::on_pushButton_clicked()
{
    unveil = new telaUnveil();
    unveil->show();
}
