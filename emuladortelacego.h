#ifndef EMULADORTELACEGO_H
#define EMULADORTELACEGO_H

#include <QWidget>
#include "telacego.h"

//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
class EmuladorTelaCego;
}

class EmuladorTelaCego : public QWidget
{
    Q_OBJECT

public:
    explicit EmuladorTelaCego(QWidget *parent = 0);
    ~EmuladorTelaCego();

private slots:
    void on_pushButton_clicked();

private:
    Ui::EmuladorTelaCego *ui;
    telaCego* cego;
};

#endif // EMULADORTELACEGO_H
