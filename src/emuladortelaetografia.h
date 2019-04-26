#ifndef EMULADORTELAETOGRAFIA_H
#define EMULADORTELAETOGRAFIA_H

#include <QWidget>
#include "telaetografia.h"
#include "telaetografiaproce.h"

namespace Ui {
class EmuladorTelaEtografia;
}

class EmuladorTelaEtografia : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorTelaEtografia(QWidget *parent = 0);
    ~EmuladorTelaEtografia();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorTelaEtografia *ui;
    telaEtografia* etografia;
    telaEtografiaProce *etoPro;
};

#endif // EMULADORTELAETOGRAFIA_H
