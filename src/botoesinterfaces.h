#ifndef BOTOESINTERFACES_H
#define BOTOESINTERFACES_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDebug>


class BotoesInterfaces : public QPushButton
{
    Q_OBJECT

public:
   explicit BotoesInterfaces(QWidget *InterfaceEtho);

    QWidget *nova;
    QWidget *antigo;
public slots:
    void botaoClicado();


};

#endif // BOTOESINTERFACES_H
