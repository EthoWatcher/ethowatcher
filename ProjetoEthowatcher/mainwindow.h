#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "telacadastrovideo.h"
#include "telacadastrofilme.h"

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
    TelaCadastroVideo* cadastroVideo;
    telaCadastroFilme* cadastroFilme;

};

#endif // MAINWINDOW_H
