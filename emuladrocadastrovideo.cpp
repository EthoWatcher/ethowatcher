#include "emuladrocadastrovideo.h"
#include "ui_emuladrocadastrovideo.h"

EmuladroCadastroVideo::EmuladroCadastroVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladroCadastroVideo)
{
    ui->setupUi(this);

    cadastroFilme = new telaCadastroFilme();
}

EmuladroCadastroVideo::~EmuladroCadastroVideo()
{
    delete cadastroFilme;
    delete ui;
}

void EmuladroCadastroVideo::on_pushButton_clicked()
{
    delete cadastroFilme;
    cadastroFilme = new telaCadastroFilme();
    cadastroFilme->show();
}
