#ifndef EMULADORSEGMENTACAOTEMPO_H
#define EMULADORSEGMENTACAOTEMPO_H

#include <QWidget>
#include "telasegementacao.h"

namespace Ui {
class EmuladorSegmentacaoTempo;
}

class EmuladorSegmentacaoTempo : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorSegmentacaoTempo(QWidget *parent = 0);
    ~EmuladorSegmentacaoTempo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorSegmentacaoTempo *ui;
    telaSegementacao *segmentacao;
};

#endif // EMULADORSEGMENTACAOTEMPO_H
