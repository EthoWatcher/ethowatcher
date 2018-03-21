#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tempoReal = new telaTempoReal();
//    tempoReal1 = new telaTempoReal();
//    tempoReal2 = new telaTempoReal();
}

MainWindow::~MainWindow()
{
    delete tempoReal;
//    delete tempoReal1;
//    delete tempoReal2;
//    for(int i=0; i<contTela;i++){

//    delete vetorTempoReal[i];
//        qDebug()<<i;
//    }

    delete ui;
}

void MainWindow::on_pushButton_clicked()
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
