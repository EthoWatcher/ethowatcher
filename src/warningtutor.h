#ifndef WARNINGTUTOR_H
#define WARNINGTUTOR_H

#include <QWidget>
#include <QDebug>
#include <QShortcut>
#include <QPushButton>

#include <tutoretho.h>

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
    void clicou(bool,QString);

private slots:
    void on_pbYes_clicked();

    void on_pbNo_clicked();

private:
    Ui::WarningTutor *ui;
    QString tutorId;
};

class ControladoWarningTutor: public QObject{

    Q_OBJECT

    public:


    QList<WarningTutor *> listaTutores;

    TutorEtho tutor;

    WarningTutor *tutorAbs;





    QList<QString> sequenciaTutores;
    void setLista(QList<QString> sequencia);

    WarningTutor *getListaTutores();

    ControladoWarningTutor(QString XML);
    void nextList(bool chNext);
    void nextById(QString id);
    void setTutor(bool chLigaTutor);


public slots:
    void wrapper(bool chBotao, QString id);

signals:
    void clicou(bool,QString);
private:

    bool chHabilitaTutor;
    void criandoInterfaces();
    void desconectandoListaTutores();
    int contador;

};

#endif // WARNINGTUTOR_H
