#ifndef EMULADORTELAFLUXOCOMPORTAMENTAL_H
#define EMULADORTELAFLUXOCOMPORTAMENTAL_H

#include <QWidget>
#include "telafluxocomportamental.h"

namespace Ui {
class EmuladorTelaFluxoComportamental;
}

class EmuladorTelaFluxoComportamental : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorTelaFluxoComportamental(QWidget *parent = 0);
    ~EmuladorTelaFluxoComportamental();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorTelaFluxoComportamental *ui;
    telaFluxoComportamental *fluxoComportamental;
};

#endif // EMULADORTELAFLUXOCOMPORTAMENTAL_H
