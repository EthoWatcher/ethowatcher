#ifndef EMULADORUNVEIL_H
#define EMULADORUNVEIL_H

#include <QWidget>
#include "telaunveil.h"
namespace Ui {
class EmuladorUnveil;
}

class EmuladorUnveil : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorUnveil(QWidget *parent = 0);
    ~EmuladorUnveil();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorUnveil *ui;
    telaUnveil* unveil;
};

#endif // EMULADORUNVEIL_H
