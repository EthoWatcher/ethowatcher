#ifndef EMULADORMATIZTRANSICAO_H
#define EMULADORMATIZTRANSICAO_H

#include <QWidget>
#include <telamatriztransicao.h>

namespace Ui {
class EmuladorMatizTransicao;
}

class EmuladorMatizTransicao : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorMatizTransicao(QWidget *parent = 0);
    ~EmuladorMatizTransicao();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorMatizTransicao *ui;
    telaMatrizTransicao *matrizTransicao;
};

#endif // EMULADORMATIZTRANSICAO_H
