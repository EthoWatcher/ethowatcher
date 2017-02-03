#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     fluxoComportamental = new telaFluxoComportamental();
}

MainWindow::~MainWindow()
{
    delete fluxoComportamental;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    fluxoComportamental = new telaFluxoComportamental();
    fluxoComportamental->show();
}
