#include "telatempoteal.h"
#include "ui_telatempoteal.h"

telaTempoTeal::telaTempoTeal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::telaTempoTeal)
{
    ui->setupUi(this);
}

telaTempoTeal::~telaTempoTeal()
{
    delete ui;
}
