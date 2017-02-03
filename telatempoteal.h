#ifndef TELATEMPOTEAL_H
#define TELATEMPOTEAL_H

#include <QWidget>

namespace Ui {
class telaTempoTeal;
}

class telaTempoTeal : public QWidget
{
    Q_OBJECT

public:
    explicit telaTempoTeal(QWidget *parent = 0);
    ~telaTempoTeal();

private:
    Ui::telaTempoTeal *ui;
};

#endif // TELATEMPOTEAL_H
