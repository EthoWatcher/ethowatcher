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
