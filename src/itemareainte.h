#ifndef ITEMAREAINTE_H
#define ITEMAREAINTE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QDebug>

class itemAreaInte: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    itemAreaInte();
    itemAreaInte(bool fomra);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool precionado;
    qreal wid,hei,raio;
    bool formaFigura;
    bool selecionado;
    bool permitidoDoubleClick;
    qreal ajustX, ajustY;
    int contador;
   // qreal extra;


    void setRaio(qreal raio1);
    void setWidHei(qreal hei1, qreal wid1);
    void setWid(qreal wid1);
    void setHei(qreal hei1);

    QString texto;

    void setTextFig(QString strin);
    void setSelecionado(bool sele1);

signals:

    void atualizoImage();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ITEMAREAINTE_H
