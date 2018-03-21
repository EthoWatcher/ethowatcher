#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    etoPro= new telaEtografiaProce();
}

MainWindow::~MainWindow()
{
    delete etoPro;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    etoPro= new telaEtografiaProce();
    etoPro->show();
    //etografia= new telaEtografia();
   // etografia->setExperimentador("Joao e ","UFSC BIOENGENHARIA");
    //etografia->show();
}

void MainWindow::on_pushButton_2_clicked()
{

}
