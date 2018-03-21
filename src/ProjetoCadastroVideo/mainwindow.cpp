#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // cadastroVideo = new TelaCadastroVideo();

    cadastroFilme = new telaCadastroFilme();
}

MainWindow::~MainWindow()
{
    qDebug() <<"fechando0";
    //delete cadastroVideo;
    delete cadastroFilme;
    delete ui;
    qDebug() <<"fechando1";
}

void MainWindow::on_pushButton_clicked()
{
   // cadastroFilme = new telaCadastroFilme();

    cadastroFilme->show();
    //cadastroVideo->show();
}
