#ifndef INTERFACEDECISAO_H
#define INTERFACEDECISAO_H

#include <QWidget>
#include <botoesinterfaces.h>
#include <QList>

class InterfaceDecisao : public QWidget
{
    Q_OBJECT
public:
    explicit InterfaceDecisao(QWidget *parent = 0);
    void addBotoesInterface(BotoesInterfaces *novoBotoao);
//    void addInterfaces(QWidget *novaInterface);
    void mostraInterface();

private:
    QList<BotoesInterfaces*> todosBotoes;
//    QList<QWidget*> todasInterfaces;
signals:

public slots:

};

#endif // INTERFACEDECISAO_H
