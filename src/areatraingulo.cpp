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
#include "areatraingulo.h"

areaTraingulo::areaTraingulo()
{

    setFlag(QGraphicsItem::ItemIsMovable,true);
    wid=10;
    hei=10;
    red=false;
}

areaTraingulo::areaTraingulo(bool cor)
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    wid=10;
    hei=10;
    red= cor;
}

QRectF areaTraingulo::boundingRect() const
{
    return QRectF(0,0,wid,hei);

}

void areaTraingulo::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QVector<QPointF> vec;//c;
    QRectF retangulo = boundingRect();

    qreal x0 , x1, x2, y0 ,y1,y2;
    x1 = retangulo.x();//this->pos().x();// pos().x();
    y1 = retangulo.y();//this->pos().y();
    //;
   //
    x0= x1 + retangulo.height()/2;
    y0= y1 ;

    x1= 0;
    y1= retangulo.height();

    x2= retangulo.height();
    y2= retangulo.height();

    vec.push_back(QPointF(x0,y0));
    vec.push_back(QPointF(x1,y1));
    vec.push_back(QPointF(x2,y2));



     poly =QPolygonF(vec);


     if(!precionado){

         if(red){

             painter->setBrush(QBrush(Qt::red));

         }else{

             painter->setBrush(QBrush(Qt::blue));

         }



     }else{

         painter->setBrush(QBrush(Qt::yellow));

     }

     painter->drawPolygon(poly);


     emit atualizoImage();

//    painter->drawEllipse(0,0,wid,hei);





}

void areaTraingulo::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    precionado = true;
    update();

    QGraphicsItem::mousePressEvent(event);

}

void areaTraingulo::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    precionado = false;
    update();

    QGraphicsItem::mouseReleaseEvent(event);


}

void areaTraingulo::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
//    if(!selecionado){

//        setFlag(ItemIsMovable,true);
//        selecionado = true;
//        update();

//        QGraphicsItem::mouseDoubleClickEvent(event);


//    }else{
//        setFlag(ItemIsMovable,false);
//        selecionado = false;
//        update();

//        QGraphicsItem::mouseDoubleClickEvent(event);


//    }

}
