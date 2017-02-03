#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "telatemporeal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    telaTempoReal *tempoReal;
    telaTempoReal *tempoReal1;
    telaTempoReal *tempoReal2;
    std::vector<telaTempoReal *> vetorTempoReal;
    int contTela=0;
};

#endif // MAINWINDOW_H
