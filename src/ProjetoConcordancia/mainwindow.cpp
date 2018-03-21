#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     concordancia = new teaConcordancia();
}

MainWindow::~MainWindow()
{
    delete concordancia;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
   concordancia = new teaConcordancia();

   concordancia->show();
}
