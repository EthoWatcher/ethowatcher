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
#ifndef ITEMCIRCULO_H
#define ITEMCIRCULO_H

//#include <QtCore>
#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QtMath>



class itemCirculo : public QGraphicsItem
{
public:
    itemCirculo();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRaio(int rad);
    int getRaio();
    void setName(QString name);
    void setPorc(QString porc);


    //qreal tamanho;
     bool pressed;
    //    QRectF rec;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:

    int raio;
    QString escrita;
    QString porcentage;




};

#endif // ITEMCIRCULO_H
