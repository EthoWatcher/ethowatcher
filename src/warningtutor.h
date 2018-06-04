#ifndef WARNINGTUTOR_H
#define WARNINGTUTOR_H

#include <QWidget>
#include <QDebug>
#include <QShortcut>
#include <QPushButton>

namespace Ui {
class WarningTutor;
}

class WarningTutor : public QWidget
{
    Q_OBJECT

public:
    explicit WarningTutor(QWidget *parent = 0);
    ~WarningTutor();
    void setTextDestaque(QString Text);
    void setTextTutor(QString Text);
    void setTextYes(QString Text);
    void setTextNo(QString Text);
    void setYesOn(bool chave);
    void setNoOn(bool chave);
    bool getId(QString textId);
//    void setButtonYes(QPushButton botao);

    void setId(QString text);
signals:
    void clickYes();
    void clickNo();
    void clicou(bool);

private slots:
    void on_pbYes_clicked();

    void on_pbNo_clicked();

private:
    Ui::WarningTutor *ui;
    QString tutorId;
};

#endif // WARNINGTUTOR_H
