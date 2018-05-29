#include "ethowatcherinpi.h"
#include <QApplication>
#include "tutoretho.h"
#include "warningtutor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EthoWatcherInpi w;
//    w.show();
//    TutorEtho tutor;

//    tutor.lerXml(":/icons/tutores/tutoresTelaCego.xml");
//    WarningTutor tutor1;

//    tutor1.setTextDestaque("Oi eu serei seu tutor");
////    tutor1.setTextTutor(tutor.getTextoById("figura"));
//    tutor1.setTextTutor(tutor.getTextoById("macarao"));
////    tutor1.setButtonYes(w.getButon());
//    tutor1.setTextYes("okay");
//    tutor1.show();

    return a.exec();
}
