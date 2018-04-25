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
public slots:
    void botaoClicado(bool clickado);


};

#endif // BOTOESINTERFACES_H
