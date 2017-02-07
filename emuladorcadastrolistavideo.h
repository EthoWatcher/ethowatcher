#ifndef EMULADORCADASTROLISTAVIDEO_H
#define EMULADORCADASTROLISTAVIDEO_H

#include <QWidget>
#include "telacadastrolistafilme.h"

namespace Ui {
class EmuladorCadastroListaVideo;
}

class EmuladorCadastroListaVideo : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorCadastroListaVideo(QWidget *parent = 0);
    ~EmuladorCadastroListaVideo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorCadastroListaVideo *ui;
     telaCadastroListaFilme *cadastroListaFilme;
};

#endif // EMULADORCADASTROLISTAVIDEO_H
