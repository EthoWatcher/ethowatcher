#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conversorXmlCsv = new telaConversorXmlCsv();
}

MainWindow::~MainWindow()
{
    delete conversorXmlCsv;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    conversorXmlCsv = new telaConversorXmlCsv();
    conversorXmlCsv->show();
}
