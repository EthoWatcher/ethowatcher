#include "itemareainte.h"

itemAreaInte::itemAreaInte()
{
    precionado= false;
    wid=40;
    hei=40;
    raio=40;
   // extra = wid/2;
   // setFlag(ItemIsMovable);
    //setFlag(item);
    formaFigura = true;
    setFlag(ItemIsMovable,false);
    selecionado=false;
    permitidoDoubleClick=false;
}

itemAreaInte::itemAreaInte(bool fomra)
{
    precionado= false;
    wid=40;
    hei=40;
    raio=40;
    //extra = wid/2;
   // setFlag(ItemIsMovable);
    formaFigura= fomra;
    setFlag(ItemIsMovable,false);
    selecionado=false;
    permitidoDoubleClick=false;

}

QRectF itemAreaInte::boundingRect() const
{
    qreal extraX = wid/2;
    qreal extraY = hei/2;

    //ajustX= extraX;
   // ajustY= extraY;

    return QRectF(0,0,wid,hei).normalized().adjusted(-extraX,-extraY,extraX,extraY);
}

void itemAreaInte::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    contador++;

    qDebug() << contador << wid << hei << raio;

    //prepareGeometryChange();
    QRectF retangulo = boundingRect();
    //retangulo.setTop(wid/2);

    if(selecionado){

        // painter = new QPainter();
         if(precionado){

             //painter->setBrush(QBrush(Qt::red));

           painter->setPen(Qt::blue);



         }else{

             //painter->setBrush(QBrush(Qt::green));
             painter->setPen(Qt::green);

         }
    }else{

        painter->setPen(Qt::red);

    }




    if(formaFigura){ //if forma true igual retangulo


         painter->drawRect(0,0,wid,hei);


    }else{ //if forma false igual circulo
        painter->drawEllipse(QPoint(wid/2,hei/2),raio/2,raio/2);

       // painter->drawEllipse(0,0,wid,hei);

    }



    painter->setFont(QFont("Times", 10, QFont::Bold));
    painter->drawText(wid/2,hei/2,texto);
    //painter->drawText(retangulo,texto);

    emit atualizoImage();




}

void itemAreaInte::setRaio(qreal raio1)
{
    raio=raio1;
    hei=raio1;
    wid=raio1;

    update();
}

void itemAreaInte::setWidHei(qreal hei1, qreal wid1)
{
    hei= hei1;
    wid= wid1;
    raio=wid1;
    update();

}

void itemAreaInte::setWid(qreal wid1)
{
 wid=wid1;
 update();
}

void itemAreaInte::setHei(qreal hei1)
{
    hei= hei1;
    update();
}

void itemAreaInte::setTextFig(QString strin)
{
    texto= strin;
    update();
}

void itemAreaInte::setSelecionado(bool sele1)
{
    selecionado=sele1;
    if(sele1){

        setFlag(ItemIsMovable,true);
    }else{

        setFlag(ItemIsMovable,false);
    }

    update();
}

void itemAreaInte::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    precionado = true;
    update();

    QGraphicsItem::mousePressEvent(event);

}

void itemAreaInte::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //if(selecionado){

        precionado = false;
        update();

        QGraphicsItem::mouseReleaseEvent(event);

   // }

}

void itemAreaInte::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(permitidoDoubleClick){
        if(!selecionado){

            setFlag(ItemIsMovable,true);
            selecionado = true;
            update();

            QGraphicsItem::mouseDoubleClickEvent(event);


        }else{
            setFlag(ItemIsMovable,false);
            selecionado = false;
            update();

            QGraphicsItem::mouseDoubleClickEvent(event);


        }

    }




}
