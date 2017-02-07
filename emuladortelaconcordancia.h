#ifndef EMULADORTELACONCORDANCIA_H
#define EMULADORTELACONCORDANCIA_H

#include <QWidget>
#include "teaconcordancia.h"
namespace Ui {
class EmuladorTelaConcordancia;
}

class EmuladorTelaConcordancia : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorTelaConcordancia(QWidget *parent = 0);
    ~EmuladorTelaConcordancia();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorTelaConcordancia *ui;
    teaConcordancia *concordancia;
};

#endif // EMULADORTELACONCORDANCIA_H
