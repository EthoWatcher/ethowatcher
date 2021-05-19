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
#include "ethowatcher.h"
#include "mysplash.h"
#include <QApplication>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDialog>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ethoWatcher w;
//    QDialog teste;





//    QTimer::singleShot(5000, &w, SLOT(show()));

//    qDebug() << "fim";


    w.show();

    return a.exec();

//    QApplication a (argc, argv);
//    QPixmap pixmap(":/icons/image3710.png");
//    mySplash splash ;
//    splash.setPixmap(pixmap);

//    splash.show();
//    splash.showMessage(QObject::trUtf8("Initiating your program now..."), Qt::AlignLeft | Qt::AlignBottom, Qt::red);

//    a.processEvents();

//    ethoWatcher w;

//    w.show();
////    QTimer::singleShot(1000, &splash, SLOT(close()));
////    QTimer::singleShot(1000, &w, SLOT(show()));

//    //w.carregaImagens(":/icons/cabecalho.jpg");

//    return 0;


}
