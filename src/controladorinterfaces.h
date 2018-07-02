#ifndef CONTROLADORINTERFACES_H
#define CONTROLADORINTERFACES_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QRect>
#include <QPoint>



class ControladorInterfaces : public QObject
{
    Q_OBJECT
public:
    explicit ControladorInterfaces(QObject *parent = 0);

    void addInterface(QWidget* widget);
//    void removeInterface(QWidget *widget);
    void deleteInterface(QWidget *widget);
    void mostraInterfaceAtiva(QWidget *widget);



    void fechaInterface(QWidget *widget);
private:

    QWidget *widgtReferencia;
    QRect rect;
    QPoint point;



protected:
     QList<QWidget*> listaQWidget;
     void moveInterface(QWidget *widget);

signals:

public slots:
};


class ControladorInterfacesTutor : public ControladorInterfaces
{
public:
    ControladorInterfacesTutor();
    void mostraInterfaceAtiva(QWidget *widget);
    void fechaTodas();

};


class MovimentaInterface {
public:
    virtual void movimenta(QWidget *widget) =0;
protected:
    QWidget *widget;
    QRect rect;
    QPoint point;


};

class MovimentaInterfaceLadoDireito: public MovimentaInterface {
public:
    MovimentaInterfaceLadoDireito(QWidget *widgetPai);

    void movimenta(QWidget *widget);
private:
    QWidget *widgetPai;
     void getPos();

};




#endif // CONTROLADORINTERFACES_H
