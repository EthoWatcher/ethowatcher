#include "emuladormatiztransicao.h"
#include "ui_emuladormatiztransicao.h"

EmuladorMatizTransicao::EmuladorMatizTransicao(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorMatizTransicao)
{
    ui->setupUi(this);
    matrizTransicao = new telaMatrizTransicao();
}

EmuladorMatizTransicao::~EmuladorMatizTransicao()
{
    delete matrizTransicao;
    delete ui;
}

void EmuladorMatizTransicao::on_pushButton_clicked()
{
    matrizTransicao = new telaMatrizTransicao();

    matrizTransicao->show();
}
