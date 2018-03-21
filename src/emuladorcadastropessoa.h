#ifndef EMULADORCADASTROPESSOA_H
#define EMULADORCADASTROPESSOA_H

#include <QWidget>
#include "telacadastropessoa.h"

namespace Ui {
class EmuladorCadastroPessoa;
}

class EmuladorCadastroPessoa : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorCadastroPessoa(QWidget *parent = 0);
    ~EmuladorCadastroPessoa();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorCadastroPessoa *ui;
    telaCadastroPessoa *cadastroPessoa;
};

#endif // EMULADORCADASTROPESSOA_H
