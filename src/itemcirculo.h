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
