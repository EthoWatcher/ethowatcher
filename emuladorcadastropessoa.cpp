#include "emuladorcadastropessoa.h"
#include "ui_emuladorcadastropessoa.h"

EmuladorCadastroPessoa::EmuladorCadastroPessoa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorCadastroPessoa)
{
    ui->setupUi(this);
    cadastroPessoa = new telaCadastroPessoa();
}

EmuladorCadastroPessoa::~EmuladorCadastroPessoa()
{
    delete cadastroPessoa;
    delete ui;
}

void EmuladorCadastroPessoa::on_pushButton_clicked()
{
    cadastroPessoa = new telaCadastroPessoa();

    cadastroPessoa->show();
}
