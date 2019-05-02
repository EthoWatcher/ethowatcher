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
#ifndef ITEMAREAINTE_H
#define ITEMAREAINTE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QObject>
#include <QDebug>

class itemAreaInte: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    itemAreaInte();
    itemAreaInte(bool fomra);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool precionado;
    qreal wid,hei,raio;
    bool formaFigura;
    bool selecionado;
    bool permitidoDoubleClick;
    qreal ajustX, ajustY;
    int contador=0;
   // qreal extra;


    void setRaio(qreal raio1);
    void setWidHei(qreal hei1, qreal wid1);
    void setWid(qreal wid1);
    void setHei(qreal hei1);

    QString texto;

    void setTextFig(QString strin);
    void setSelecionado(bool sele1);

signals:

    void atualizoImage();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ITEMAREAINTE_H
