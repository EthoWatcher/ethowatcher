#include "emuladorverdadeirorealtime.h"
#include "ui_emuladorverdadeirorealtime.h"

EmuladorVerdadeiroRealTime::EmuladorVerdadeiroRealTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorVerdadeiroRealTime)
{
    ui->setupUi(this);
    tempoReal = new telaTempoReal();
}

EmuladorVerdadeiroRealTime::~EmuladorVerdadeiroRealTime()
{
    delete tempoReal;
    delete ui;
}

void EmuladorVerdadeiroRealTime::on_pushButton_clicked()
{
    tempoReal = new telaTempoReal();
    //tempoReal1 = new telaTempoReal();
    //tempoReal2 = new telaTempoReal();

//    vetorTempoReal.push_back(tempoReal);
//    vetorTempoReal[contTela]->show();
//    contTela++;

        tempoReal->show();
       //tempoReal1->show();
       //tempoReal2->show();
}
