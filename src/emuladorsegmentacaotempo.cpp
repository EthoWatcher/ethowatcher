#include "emuladorsegmentacaotempo.h"
#include "ui_emuladorsegmentacaotempo.h"

EmuladorSegmentacaoTempo::EmuladorSegmentacaoTempo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmuladorSegmentacaoTempo)
{
    ui->setupUi(this);
    segmentacao = new telaSegementacao();
}

EmuladorSegmentacaoTempo::~EmuladorSegmentacaoTempo()
{
    delete segmentacao;
    delete ui;
}

void EmuladorSegmentacaoTempo::on_pushButton_clicked()
{
    segmentacao = new telaSegementacao();
    segmentacao->show();
}
