#ifndef FIGURAMATRIZ_H
#define FIGURAMATRIZ_H

#include <QWidget>

#include <QtCore>
#include <QtGui>
//#include "itemdesenho.h"
//#include "itemseta.h"
#include "itemcirculo.h"
#include "itemcompostaseta.h"
#include "itemnovaseta.h"
#include <QGraphicsLineItem>
#include <QTimer>
#include <QGraphicsPolygonItem>
#include <QImage>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QFileDialog>

namespace Ui {
class figuraMatriz;
}

class figuraMatriz : public QWidget
{
    Q_OBJECT

public:
    explicit figuraMatriz(QWidget *parent = 0);
    ~figuraMatriz();

    void setNovoCirculo(QString Nome);
    void recebeDadosSeq(std::vector<double> dados);

private slots:
    void on_pbSave_clicked();

    void on_pbZoomIn_clicked();

    void on_pbZoomOut_clicked();

    void on_pbAtualiza_clicked();

    void atualizaDesenho();

private:
    Ui::figuraMatriz *ui;

    QGraphicsScene *scene;
//    QGraphicsScene *scene1;
//    itemDesenho *mysquare;
//    itemDesenho *mysquare2;
    itemCirculo *circulo;
    itemCirculo *circulo1;
    itemCirculo *circulo2;

    itemNovaSeta *seta;
    itemNovaSeta *seta1;
    itemNovaSeta *seta2;
    itemCompostaSeta *compostaSeta;
    QList<QGraphicsItem*> ite1;

    QList<QGraphicsItem*> listaCirc;
    QList<QGraphicsItem*> listaCompoSeta;
    QList<QGraphicsItem*> listaNovaSeta;

    QTimer *tempo;
    int conTCirc=0;


    std::vector<double> dadoLinha;
    std::vector<bool> logicaLinha;
    std::vector<std::vector<double> > dadosMat;
    std::vector<std::vector<bool> > logicaMat;

//    QList<int> dadoLinha;
//    QList<bool> logicaLinha;
//    QList<QList<int> > dadosMat;
//    QList<QList<bool> > logicaMat;


};

#endif // FIGURAMATRIZ_H
