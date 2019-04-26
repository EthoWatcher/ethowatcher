#ifndef AREATRAINGULO_H
#define AREATRAINGULO_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class areaTraingulo : public QObject, public QGraphicsItem
{
    //Q_OBJECT

    Q_OBJECT

public:

    areaTraingulo();
    areaTraingulo(bool cor);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool precionado;
    qreal wid,hei;
    bool formaFigura;
    bool selecionado;

    bool red;


    QString texto;
    QPolygonF poly;

signals:

    void atualizoImage();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // AREATRAINGULO_H
