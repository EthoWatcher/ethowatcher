#include "emuladorcadastrolistavideo.h"
#include "ui_emuladorcadastrolistavideo.h"

EmuladorCadastroListaVideo::EmuladorCadastroListaVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorCadastroListaVideo)
{
    ui->setupUi(this);
    cadastroListaFilme = new telaCadastroListaFilme();
}

EmuladorCadastroListaVideo::~EmuladorCadastroListaVideo()
{
    delete cadastroListaFilme;
    delete ui;
}

void EmuladorCadastroListaVideo::on_pushButton_clicked()
{
    cadastroListaFilme = new telaCadastroListaFilme();
    cadastroListaFilme->show();
}
