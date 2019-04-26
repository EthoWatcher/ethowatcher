#include "emuladortelaconcordancia.h"
#include "ui_emuladortelaconcordancia.h"

EmuladorTelaConcordancia::EmuladorTelaConcordancia(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorTelaConcordancia)
{
    ui->setupUi(this);
    concordancia = new teaConcordancia();

}

EmuladorTelaConcordancia::~EmuladorTelaConcordancia()
{
    delete concordancia;
    delete ui;
}

void EmuladorTelaConcordancia::on_pushButton_clicked()
{
    concordancia = new teaConcordancia();

    concordancia->show();
}
