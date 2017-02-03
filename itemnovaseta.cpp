#include "itemnovaseta.h"

itemNovaSeta::itemNovaSeta()
{
//    linha = new QGraphicsLineItem();

    posiXBase=10;

    posiYBase=10;

    posiXSeta=100;

    posiYSeta=100;
//    tamanho =1;
}

itemNovaSeta::itemNovaSeta(QGraphicsItem *cirBase, QGraphicsItem *cirPonta, qreal desl)
{
    basePonto = cirBase;
    setaPonto = cirPonta;
    deslocamentoDo=desl;
    tamanho=1;
    //update();
}

void itemNovaSeta::setItem(QGraphicsItem *cirBase, QGraphicsItem *cirPonta)
{
    basePonto = cirBase;
    setaPonto = cirPonta;
    tamanho=1;
    update();
}

QRectF itemNovaSeta::boundingRect() const
{
    return QRectF(0,0,500,500);
    //return QRectF(0,0,l1,l2);
}

void itemNovaSeta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    getPosi();

   // prepareGeometryChange();




    qreal ms;
    qreal xa1,ya1,xa2,ya2;
    xa2=posiXSeta+baseWid/2+deslocamentoDo;
    ya2=posiYSeta+baseWid/2+deslocamentoDo;

    xa1=posiXBase+baseWid/2+deslocamentoDo;
    ya1=posiYBase+baseWid/2+deslocamentoDo;


     ms= (ya2-ya1)/(xa2-xa1);

     ang= ms;

     qreal yEs,xEs;
     xEs = xa1+ (xa2-xa1)/2;
     yEs = (xEs - xa1)/ms + ya1;

     qreal yCir,xCir;
     qreal yCirS,xCirS;

//     qreal xPos,xNega;
//     qreal yPos, yNega;

     xCir= qPow(50,2)/((qPow(ms,2),2)+1);
     xCir= sqrt(xCir);
     yCir= ms* xCir;



//     xPos=xa1 + xCir;
//     xNega=xa1 -xCir;

//     yPos= ms* (xPos - xa1);
//     yNega= ms* (xNega - xa1);


     painter->setPen(QPen(QBrush(Qt::red),tamanho));


     if((ang>= -1.42 )&& (ang <=1.45)){

         if((xa2> xa1) && (ya1> ya2)){

            setaLinha(xa1+xCir,ya1+yCir, xa2 - xCir, ya2 - yCir);


         }

         if((xa2< xa1) && (ya1< ya2)){

            setaLinha(xa1 -xCir,ya1 -yCir, xa2 + xCir, ya2 + yCir);


         }


         if((xa2< xa1) && (ya1> ya2)){

            setaLinha(xa1 - xCir,ya1 - yCir, xa2 + xCir, ya2 + yCir);


         }


         if((xa2> xa1) && (ya1< ya2)){

            setaLinha(xa1 + xCir,ya1 + yCir, xa2 - xCir, ya2 - yCir);


         }



     }else{


        if((xa2> xa1) && (ya1> ya2)){

            setaLinha(xa1 ,ya1 - baseWid/2 , xa2 , ya2+baseWid/2);

        }


        if((xa2< xa1) && (ya1> ya2)){

            setaLinha(xa1 ,ya1 - baseWid/2 , xa2 , ya2+baseWid/2);

        }

        if((xa2 < xa1) && (ya1 < ya2)){

            setaLinha(xa1  ,ya1  + baseWid/2 , xa2  , ya2 - baseWid/2 );

        }

        if((xa2 > xa1) && (ya1 < ya2)){

            setaLinha(xa1  ,ya1  + baseWid/2 , xa2  , ya2 - baseWid/2 );

        }





     }






    // painter->drawEllipse(xCir+xa1,ya1+yCir,10,10);

     painter->drawLine(lin);



     painter->drawPolygon(poly);

     painter->setFont(QFont("Times", 10, QFont::Bold));



   // painter->drawText(xa1+(xa2-xa1)/2,ya1+(ya2-ya1)/2,"lalal");

   //  painter->drawText(xEs,yEs,"lalal");

     painter->drawText(xa1+(xa2-xa1)/2,ya1+(ya2-ya1)/2,texPor);

}

void itemNovaSeta::setaLinha(qreal x1, qreal y1, qreal x2, qreal y2)
{

   // x1= x1+ baseWid/2+deslocamentoDo;
   // x2= x2 + baseWid/2+deslocamentoDo;
   // y1= y1 + baseWid/2+deslocamentoDo;
   // y2= y2 + baseWid/2+deslocamentoDo;

    lin = QLine(x1 ,y1  ,
                x2 ,y2);
   //  baseHei = tamaBase.height();
//    lin = QLine(x1+ baseWid/2  ,y1 + baseWid/2 ,
//                x2 + baseWid/2 ,y2 + baseWid/2);
     //lin = QLine(x1 + baseWid/2 ,y1 + baseHei/2 , x2,y2);

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
     wid = l1;
     hei = l2;

    // update();


}

void itemNovaSeta::setTamanhoFlecha(qreal wid)
{
    tamanho= wid;
}

void itemNovaSeta::setTextPor(QString por)
{
    texPor =por;
}

void itemNovaSeta::atualiDese()
{
//    if (!basePonto || !setaPonto){

//    }else{
//    pointBase = mapFromItem(basePonto, 0, 0);
//    pointSeta = mapFromItem(setaPonto, 0, 0);

//    QRectF retangule = basePonto-> boundingRect();
//    QRectF retangule2 = setaPonto-> boundingRect();

//    setaLinha(basePonto->pos().x()+ retangule.width()/2, basePonto->pos().y() + retangule.height()/2,
//              pointSeta.x()+ retangule.width()/2, pointSeta.y()+retangule.height()/2);
//    update();

//    }
}

qreal itemNovaSeta::getWidth1()
{

}

qreal itemNovaSeta::getHeigh1()
{

}

void itemNovaSeta::getPosi()
{

    QPointF posica1= basePonto->pos();
    tamaBase = basePonto->boundingRect();
    QPointF posica2= setaPonto->pos();
    //tamaSeta = setaPonto->boundingRect();



     baseWid = tamaBase.width();
     posiXBase= posica1.x();
     posiYBase =posica1.y();
     posiXSeta = posica2.x();
     posiYSeta =posica2.y();
    //tamFigu = tamas1.width()/2 ;//50;
//    posiX =   posica1.x()+tamFigu+tamFigu;
//    posiY= posica1.y()+ tamFigu;
}
