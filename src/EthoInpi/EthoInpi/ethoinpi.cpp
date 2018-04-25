#include "ethoinpi.h"
#include "ui_ethoinpi.h"

EthoInpi::EthoInpi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EthoInpi)
{
    ui->setupUi(this);
}

EthoInpi::~EthoInpi()
{
    delete ui;
}
