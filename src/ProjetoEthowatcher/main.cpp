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
//    QApplication a(argc, argv);
//    ethoWatcher w;
//    QDialog teste;





//    QTimer::singleShot(5000, &w, SLOT(show()));

//    qDebug() << "fim";


//    w.show();

//    return a.exec();

    QApplication a (argc, argv);
    QPixmap pixmap(":/icons/image3710.png");
    mySplash splash ;
    splash.setPixmap(pixmap);

    splash.show();
    splash.showMessage(QObject::trUtf8("Initiating your program now..."), Qt::AlignLeft | Qt::AlignBottom, Qt::red);

    a.processEvents();

    ethoWatcher w;

    QTimer::singleShot(5000, &splash, SLOT(close()));
    QTimer::singleShot(5000, &w, SLOT(show()));

    //w.carregaImagens(":/icons/cabecalho.jpg");

    return a.exec();


}
