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
#include "itemcirculo.h"

itemCirculo::itemCirculo()
{
    //pressed = false;
    setFlag(ItemIsMovable);
    escrita="";
    porcentage="";
    raio=100;
}

QRectF itemCirculo::boundingRect() const
{

   return QRectF(0,0,raio,raio);

}

void itemCirculo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //prepareGeometryChange();
    QRectF retangulo=boundingRect();



    painter->setBrush(Qt::white);
    painter->drawEllipse(0,0,raio,raio);

    retangulo.setY(raio/2-10);
    retangulo.setX(0);
    painter->setFont(QFont("Times", raio/10, QFont::Bold));
    painter->drawText(retangulo,escrita);
    retangulo.setY((raio/2-10)+raio/10);
    retangulo.setX(raio/2-10);
    painter->setFont(QFont("Times", raio/10, QFont::Bold));
    painter->drawText(retangulo,porcentage);

}

void itemCirculo::setRaio(int rad)
{

    raio = rad;
    update();
}

int itemCirculo::getRaio()
{
    return raio;
}

void itemCirculo::setName(QString name)
{
    escrita = name;
    update();

}

void itemCirculo::setPorc(QString porc)
{
    porcentage=porc;
    update();

}

void itemCirculo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   // pressed = true;
    update();

    QGraphicsItem::mousePressEvent(event);

}

void itemCirculo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //pressed = false;
     update();
     QGraphicsItem::mouseReleaseEvent(event);
}
