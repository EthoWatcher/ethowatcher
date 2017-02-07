#ifndef EMULADROCADASTROVIDEO_H
#define EMULADROCADASTROVIDEO_H

#include <QWidget>
#include "telacadastrovideo.h"
#include "telacadastrofilme.h"

namespace Ui {
class EmuladroCadastroVideo;
}

class EmuladroCadastroVideo : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladroCadastroVideo(QWidget *parent = 0);
    ~EmuladroCadastroVideo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladroCadastroVideo *ui;
    TelaCadastroVideo* cadastroVideo;
    telaCadastroFilme* cadastroFilme;
};

#endif // EMULADROCADASTROVIDEO_H
