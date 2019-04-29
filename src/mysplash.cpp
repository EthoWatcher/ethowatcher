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

