#include "ethowatcherinpi.h"
#include <QApplication>
#include "tutoretho.h"
#include "warningtutor.h"
#include <QPoint>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EthoWatcherInpi *w;

    w = new EthoWatcherInpi();
//existe uma possibilidade de mover o lugar que a tela abre
//    QPoint d;
//    d= w.pos();
//    qDebug() << " a " << d.x();


//    w.move(0,0);
//    w.show();
//    TutorEtho tutor;

//    tutor.lerXml(":/icons/tutores/tutoresTelaCego.xml");
//    WarningTutor tutor1;

//    screenWidth = w.width();
//    screenHeight = w.height();

//    x = (screenWidth - WIDTH) / 2;
//    y = (screenHeight - HEIGHT) / 2;

//    window.resize(WIDTH, HEIGHT);
//    window.move( x, y );
//    window.setWindowTitle("Center");
//    window.show();

//    tutor1.setTextDestaque("Oi eu serei seu tutor");
////    tutor1.setTextTutor(tutor.getTextoById("figura"));
//    tutor1.setTextTutor(tutor.getTextoById("macarao"));
////    tutor1.setButtonYes(w.getButon());
//    tutor1.setTextYes("okay");
//    tutor1.show();

    return a.exec();
}
