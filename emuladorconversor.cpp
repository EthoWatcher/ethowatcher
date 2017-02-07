#include "emuladorconversor.h"
#include "ui_emuladorconversor.h"

EmuladorConversor::EmuladorConversor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorConversor)
{
    ui->setupUi(this);
    conversorXmlCsv = new telaConversorXmlCsv();
}

EmuladorConversor::~EmuladorConversor()
{
    delete conversorXmlCsv;
    delete ui;
}

void EmuladorConversor::on_pushButton_clicked()
{
    conversorXmlCsv = new telaConversorXmlCsv();
    conversorXmlCsv->show();
}
