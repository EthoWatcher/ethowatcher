#ifndef ETHOINPI_H
#define ETHOINPI_H

#include <QMainWindow>

#include "botoesinterfaces.h"
#include "telacadastrocatalago.h"
#include "telacadastrofilme.h"
#include "QVBoxLayout"
#include "interfacedecisao.h"


namespace Ui {
class EthoInpi;
}

class EthoInpi : public QMainWindow
{
    Q_OBJECT

public:
    explicit EthoInpi(QWidget *parent = 0);
    BotoesInterfaces* adicionaInterfaceNoBotao(QWidget *novaInterface);
    ~EthoInpi();

private slots:
    void on_pbLoadUser_clicked();

    void on_pbTranscrition_clicked();

private:
    Ui::EthoInpi *ui;
};

#endif // ETHOINPI_H
