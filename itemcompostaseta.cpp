#include "itemcompostaseta.h"

itemCompostaSeta::itemCompostaSeta()
{

    tamFigu = 50;
    posiX = 0+tamFigu+tamFigu;
    posiY= 0+tamFigu;


}

itemCompostaSeta::itemCompostaSeta(QGraphicsItem *circ)
{
    basePonto = circ;

    QPointF posica1= basePonto->pos();
    QRectF  tamas1 = basePonto->boundingRect();

    tamFigu = tamas1.width()/2 ;//50;
    posiX =   posica1.x()+tamFigu+tamFigu;
    posiY= posica1.y()+ tamFigu;
    tamanho =1;
    texQuant="lal";
}

QRectF itemCompostaSeta::boundingRect() const
{

    return QRectF(0,0,200,200);

}

void itemCompostaSeta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QPen(QBrush(Qt::red),tamanho));
   // if(basePonto){

        getPosi();
  //  }

   // prepareGeometryChange();
    tamSeta = tamFigu;
    tamSetaDobr= tamSeta*2;

    painter->drawLine(posiX,posiY,
                      posiX+tamSeta,posiY);

    painter->drawLine(posiX+tamSeta,posiY,
                      posiX+tamSeta,posiY+tamSetaDobr);

    painter->drawLine(posiX+tamSeta,posiY+tamSetaDobr,
                      posiX-tamSeta,posiY+tamSetaDobr);

    painter->drawLine(posiX-tamSeta,posiY+tamSetaDobr,
                      posiX-tamSeta,posiY+tamSeta);

     setaLinha(posiX-tamSeta,posiY+tamSetaDobr,
               posiX-tamSeta,posiY+tamSeta);

    painter->drawPolygon(poly);

    QRectF retangulo= boundingRect();
    painter->setFont(QFont("Times", tamSeta/5, QFont::Bold));
    painter->drawText(posiX-tamSeta+10,posiY+tamSetaDobr,texQuant);


   // painter->drawLine()
}

void itemCompostaSeta::getLinha(qreal x1, qreal y1, qreal raio)
{
    tamFigu = raio;
//    posiX = x1 + raio+raio;
//    posiY= y1 + raio/2;

    posiX = x1+tamFigu+tamFigu;
    posiY= y1+tamFigu;

    prepareGeometryChange();
    update();


}

void itemCompostaSeta::setaLinha(qreal x1, qreal y1, qreal x2, qreal y2)
{
    //lin = QLine(x1,y1, x2,y2);

    QPointF final,linhax,linhay;
    double angParaX, angParaY, hip;
    double mr, ms, mang;
    double ladoE, ladoD;
    double razao;
    double xSeta,ySeta;
    double xPon,yPon;

    qreal x3,y3, x4,y4,angle;
    qreal l1,l2;

    float tamanhox;



    //encontra o angulo

    angle= 0.5;
    ms= (y2-y1)/(x2-x1);
    mr= -1/ms;

    l1=sqrt( qPow(y1 -y2,2) + qPow(x1 - x2,2));
    l2=20;

    x3= x2+  l2/l1*( ((x1-x2)*cos(angle)) + ((y1-y2)*sin(angle)));

    y3= y2+  l2/l1*( ((y1-y2)*cos(angle)) - ((x1-x2)*sin(angle)));

    x4= x2+  l2/l1*( ((x1-x2)*cos(angle)) - ((y1-y2)*sin(angle)));

    y4= y2+  l2/l1*( ((y1-y2)*cos(angle)) + ((x1-x2)*sin(angle)));


    final= QPointF(x2,y2);
    linhax= QPointF(x3,y3);
   linhay = QPointF(x4,y4);


    QVector<QPointF> vec;//c;

    vec.push_back(final);
    vec.push_back(linhax);
    vec.push_back(final);
    vec.push_back(linhay);

    poly =QPolygonF(vec);
   // wid = l1;
    // hei = l2;
}

void itemCompostaSeta::getPosi()
{
//    QPointF pointBase = mapFromItem(basePonto, 0, 0);

//    posiX = pointBase.x();
//    posiY = pointBase.y();

    QPointF posica1= basePonto->pos();
    QRectF  tamas1 = basePonto->boundingRect();

    tamFigu = tamas1.width()/2 ;//50;
    posiX =   posica1.x()+tamFigu+tamFigu;
    posiY= posica1.y()+ tamFigu;

}

void itemCompostaSeta::setText(QString quant)
{
  texQuant= quant;
}


//void itemCompostaSeta::setaLinha(qreal x1, qreal y1, qreal raio)
//{




//}
