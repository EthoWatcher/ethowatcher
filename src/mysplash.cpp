#include "mysplash.h"
#include <QEvent>

mySplash::mySplash(QWidget *parent):QSplashScreen(parent)
{
    this->installEventFilter(this);
}

bool mySplash::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::Paint)                          //não filtra pintura da tela
        return false;
    if(event->type() == QEvent::UpdateRequest)                  //não filtra escrita na tela
        return false;
    else
        return true;                                            //filtra todos os eventos
}

