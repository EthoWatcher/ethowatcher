/*
EthoWatcher OS is a software to assist study of animal behavior.
Copyright (C) 2018  Universidade Federal de Santa Catarina.

EthoWatcher OS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef ITEMNOVASETA_H
#define ITEMNOVASETA_H

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


class itemNovaSeta: public QGraphicsItem
{
public:
    itemNovaSeta();
    itemNovaSeta(QGraphicsItem *cirBase, QGraphicsItem *cirPonta, qreal desl);
    qreal deslocamentoDo;
//    QGraphicsLineItem* linha;

    void  setItem(QGraphicsItem *cirBase, QGraphicsItem *cirPonta);

    QGraphicsItem *basePonto, *setaPonto;
    QPointF pointSeta;
    QPointF pointBase;


    QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setaLinha(qreal x1, qreal y1, qreal x2, qreal y2);
    void setTamanhoFlecha(qreal wid);

    void setTextPor(QString por);

    QString texPor;

    void atualiDese();
    qreal getWidth1();
    qreal getHeigh1();

    qreal wid,hei;

    qreal ang;
    QLine lin;
    QPolygonF poly;
    QRect ret;
    qreal tamanho;

    void getPosi();

    qreal posiXBase,posiYBase, posiXSeta, posiYSeta;
    QRectF  tamaBase;
    qreal baseWid,baseHei;
   // QRectF  tamaSeta;

private:

   // qreal x3,y3, x4,y4,l1,l2,angle;

};

#endif // ITEMNOVASETA_H
