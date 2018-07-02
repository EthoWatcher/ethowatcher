#ifndef CONTROLADORINTERFACES_H
#define CONTROLADORINTERFACES_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QRect>
#include <QPoint>

class MovimentaInterface {
public:
    virtual void movimenta(QWidget *widget) =0;
    virtual void setRef(QWidget *widgetPai)=0;
protected:
    QWidget *widget;
    QRect rect;
    QPoint point;


};

class MovimentaInterfaceLadoDireito: public MovimentaInterface {
public:
    MovimentaInterfaceLadoDireito();
    void setRef(QWidget *widgetPai);

    void movimenta(QWidget *widget);
protected:
    QWidget *widgetPai;
     void getPos();

};


class MovimentaInterfaceCentro: public MovimentaInterfaceLadoDireito {
public:
    MovimentaInterfaceCentro();
    void movimenta(QWidget *widget);


};



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
//    ControladorInterfaces(QObject *parent, MovimentaInterface *base);
    void setContInterfaces(MovimentaInterface *base);
private:
    MovimentaInterface *_pbase;
    MovimentaInterfaceLadoDireito *mInterface;

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






#endif // CONTROLADORINTERFACES_H
