#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    cego = new telaCego();
}

MainWindow::~MainWindow()
{
    delete cego;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    cego = new telaCego();
    cego->show();
}
