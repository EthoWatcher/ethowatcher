#ifndef ETHOINPI_H
#define ETHOINPI_H

#include <QMainWindow>

namespace Ui {
class EthoInpi;
}

class EthoInpi : public QMainWindow
{
    Q_OBJECT

public:
    explicit EthoInpi(QWidget *parent = 0);
    ~EthoInpi();

private:
    Ui::EthoInpi *ui;
};

#endif // ETHOINPI_H
