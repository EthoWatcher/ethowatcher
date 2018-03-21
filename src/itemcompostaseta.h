#ifndef ITEMCOMPOSTASETA_H
#define ITEMCOMPOSTASETA_H

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QtCore>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QGraphicsPolygonItem>
#include <QtMath>
#include "itemcirculo.h"
#include <QObject>



class itemCompostaSeta: public QGraphicsItem
{
public:
    itemCompostaSeta();
    itemCompostaSeta(QGraphicsItem *circ);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
     void getLinha(qreal x1, qreal y1, qreal raio);
     void setaLinha(qreal x1, qreal y1, qreal x2, qreal y2);
     void getPosi();
     void setText(QString quant);
     QString texQuant;

     QPolygonF poly;

     qreal posiX, posiY, tamFigu;
     qreal tamSeta,tamSetaDobr;

     qreal tamanho;
     QGraphicsItem * basePonto;
};

#endif // ITEMCOMPOSTASETA_H
