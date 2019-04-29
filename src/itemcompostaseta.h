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
