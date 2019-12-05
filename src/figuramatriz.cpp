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
#include "figuramatriz.h"
#include "ui_figuramatriz.h"

figuraMatriz::figuraMatriz(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::figuraMatriz)
{
    ui->setupUi(this);



    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView-> setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


    scene = new QGraphicsScene(0,0,1000,1000,ui->graphicsView);
  //  scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);



    tempo= new QTimer();

    connect(tempo,SIGNAL(timeout()),this,SLOT(atualizaDesenho()));


}

figuraMatriz::~figuraMatriz()
{
    delete ui;
}

void figuraMatriz::setNovoCirculo(QString Nome)
{
      circulo = new itemCirculo();
      circulo->setName(Nome);

      listaCirc.push_back(circulo);

      scene->addItem(listaCirc[conTCirc]);

//      circulo2 = new itemCirculo();
//      circulo2->setName(Nome);

//      listaCirc.push_back(circulo);

//      circulo = new itemCirculo();
//      circulo->setName(Nome);

//      listaCirc.push_back(circulo);

//      listaCirc.push_back(circulo2);

//      scene->addItem(listaCirc[0]);
//      scene->addItem(listaCirc[1]);
//      scene->addItem(listaCirc[2]);

      conTCirc++;




}

void figuraMatriz::recebeDadosSeq(std::vector<double> dados)
{

    int soma=0;

    for(int c1=0 ;c1<conTCirc; c1++){
        dadoLinha.clear();
        logicaLinha.clear();

        for(int c2=0;c2<conTCirc; c2++){

            dadoLinha.push_back(dados[soma+c2]);
            logicaLinha.push_back(true);

        }
        soma=soma+conTCirc;

        logicaMat.push_back(logicaLinha);
        dadosMat.push_back(dadoLinha);


    }


}

void figuraMatriz::on_pbSave_clicked()
{
//    //ui->graphicsView->update();

//    tempo->stop();
//    QGraphicsScene *foto;

//    foto = new QGraphicsScene();


//    QList<QGraphicsItem*> iten;

//    iten = scene->items();


////    for(int k=0; k< iten.size(); k++){





////    }
//    //scene->clearSelection();
//    //foto->clearSelection();
//    foto = iten[0]->scene();
//   // foto = new QGraphicsScene();




//    //scene->update(0,0,1000,1000);
//    QImage image(foto->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
//    image.fill(Qt::transparent);                                              // Start all pixels transparent
//    QPainter painter(&image);


////    scene->render();

//     foto->render(&painter);
//     image.save("file_name4.png");


//   //  QPixmap pixMap = QPixmap::grabWidget(ui->graphicsView);
//    // pixMap.save("file_name2.png");

    QString nomeGravar;

    nomeGravar = QFileDialog::getSaveFileName(
                this,
                tr("Save File"),
                "C://",
               " (*.png)"
               );
    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);  // Create the image with the exact size of the shrunk scene
    image.fill(Qt::transparent);                                              // Start all pixels transparent

    QPainter painter(&image);
    scene->render(&painter);
    image.save(nomeGravar);


}

void figuraMatriz::on_pbZoomIn_clicked()
{
    ui->graphicsView->scale(1.1,1.1);
}

void figuraMatriz::on_pbZoomOut_clicked()
{


    ui->graphicsView->scale(0.9,0.9);
}

void figuraMatriz::on_pbAtualiza_clicked()
{
    int conCompSeta=0;
    int conNovaSeta=0;

    //0
    //1
    //2
    for(int c1=0; c1<conTCirc; c1++){


        for(int c2=0; c2<conTCirc; c2++){

            double aux= dadosMat[c1][c2];

            //se tem um valor apontando para a propria categoria
            if((aux!=0)&& ( c1==c2)){


                compostaSeta = new itemCompostaSeta(listaCirc[c1]);
                compostaSeta->setText(QString::number(aux));
                listaCompoSeta.push_back(compostaSeta);
                scene->addItem(listaCompoSeta[conCompSeta]);
                conCompSeta++;
            }

            bool auxBoolI = logicaMat[c1][c2];
            bool auxBoolJ = logicaMat[c2][c1];


            if((aux!=0) && (c1!=c2)){

                //ele ta vendo se ja pos a seta em algum das categorias
                if((auxBoolI)&&(auxBoolJ)){
                    seta= new itemNovaSeta(listaCirc[c1],listaCirc[c2],-10);
                    seta->setTextPor(QString::number(aux));

                    listaNovaSeta.push_back(seta);

                    scene->addItem(listaNovaSeta[conNovaSeta]);
                    conNovaSeta++;
                }else{



                    seta= new itemNovaSeta(listaCirc[c1],listaCirc[c2],10);
                    seta->setTextPor(QString::number(aux));
                    listaNovaSeta.push_back(seta);

                    scene->addItem(listaNovaSeta[conNovaSeta]);
                    conNovaSeta++;


                }

                logicaMat[c1][c2]=false;



            }



        }


    }




//    compostaSeta = new itemCompostaSeta(listaCirc[0]);
//      seta= new itemNovaSeta(listaCirc[0],listaCirc[1],-10);
//      seta1= new itemNovaSeta(listaCirc[1],listaCirc[0],10);
//      seta2= new itemNovaSeta(listaCirc[1],listaCirc[2],-10);

//    scene->addItem(compostaSeta);
//    scene->addItem(seta);
//    scene->addItem(seta1);
//    scene->addItem(seta2);


   tempo->start(200);
//    QPointF luga=listaCirc[0]->pos();

//    compostaSeta->getLinha(luga.x(),luga.y(),50);

//    scene->update(scene->sceneRect());
//    ui->graphicsView->setUpdatesEnabled(true);
//    ui->graphicsView->update();


   ui->pbSave->setEnabled(true);
//   ui->teTutor->setText("<p>Passo 2: Clique no botão 'Salvar' oara salvar o fluxograma da matriz"
//                        "de transição em uma imagem no formato .png <p/>");

}

void figuraMatriz::atualizaDesenho()
{
//    QPointF luga=listaCirc[0]->pos();

//    compostaSeta->getLinha(luga.x(),luga.y(),50);
    scene->update(scene->sceneRect());
    ui->graphicsView->setUpdatesEnabled(true);
    ui->graphicsView->update();

}

