#ifndef EMULADORCONVERSOR_H
#define EMULADORCONVERSOR_H

#include <QWidget>
#include "telaconversorxmlcsv.h"

namespace Ui {
class EmuladorConversor;
}

class EmuladorConversor : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorConversor(QWidget *parent = 0);
    ~EmuladorConversor();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorConversor *ui;
    telaConversorXmlCsv* conversorXmlCsv;
};

#endif // EMULADORCONVERSOR_H
