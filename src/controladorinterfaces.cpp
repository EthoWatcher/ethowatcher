#include "controladorinterfaces.h"

ControladorInterfaces::ControladorInterfaces(QObject *parent) : QObject(parent)
{

    mInterface = new MovimentaInterfaceLadoDireito();
    _pbase = mInterface;



}

void ControladorInterfaces::addInterface(QWidget *widget)
{
    listaQWidget.append(widget);
//    rect =  listaQWidget[0]->rect();
    point= listaQWidget[0]->pos();
}

void ControladorInterfaces::fechaInterface(QWidget *widget){
    for(int i=0; i<listaQWidget.size();i++){

        if(listaQWidget[i]== widget ){

            listaQWidget[i]->close();

        }
    }
}

void ControladorInterfaces::deleteInterface(QWidget *widget)
{

    delete widget;
    for(int i=0; i<listaQWidget.size();i++){

        if(listaQWidget[i]== widget ){

            listaQWidget.removeAt(i);

        }
    }

}

void ControladorInterfaces::mostraInterfaceAtiva(QWidget *widget)
{
    for(int i=0; i< listaQWidget.size(); i++){

        if(listaQWidget[i]== widget ){
            moveInterface(listaQWidget[i]);
        }

    }

}

void ControladorInterfaces::moveInterface(QWidget *widget){

        if(widget==listaQWidget[0]){
            widget->show();
            rect =  listaQWidget[0]->rect();
            point= listaQWidget[0]->pos();
//            _pbase->setRef(listaQWidget[0]);
//            qDebug() <<"mocimnta1";
        }else if(listaQWidget.size() !=1){

//            qDebug() <<"mocimnta2";
//            _pbase->movimenta(widget);
            rect =  listaQWidget[0]->rect();
            point= listaQWidget[0]->pos();
            qDebug() << point.x() << point.y();
            qDebug() << rect.x() << rect.width() << rect.y() << rect.height();
            widget->move(point.x()+rect.width(), point.y() );
            widget->show();

        }else{


//            rect =  listaQWidget[0]->rect();
//            point= listaQWidget[0]->pos();
//            qDebug() << point.x() << point.y();
//            qDebug() << rect.x() << rect.width() << rect.y() << rect.height();
//            widget->move(point.x()+rect.width(), point.y() );
//            widget->show();
        }


}

ControladorInterfacesTutor::ControladorInterfacesTutor()
{

}

void ControladorInterfacesTutor::mostraInterfaceAtiva(QWidget *widget)
{
    fechaTodas();
    for(int i=0; i< listaQWidget.size(); i++){

        if(listaQWidget[i]== widget ){
            moveInterface(listaQWidget[i]);
        }

    }
}

void ControladorInterfacesTutor::fechaTodas()
{
    for(int i=1; i<listaQWidget.size();i++){


            listaQWidget[i]->close();

    }

}

MovimentaInterfaceLadoDireito::MovimentaInterfaceLadoDireito()
{

}

void MovimentaInterfaceLadoDireito::setRef(QWidget *widgetPai)
{
    this->widgetPai = widgetPai;
    this->getPos();
    qDebug() << "setado a tela de referencia ";
}


void MovimentaInterfaceLadoDireito::movimenta(QWidget *widget)
{
    this->getPos();
    qDebug() << point.x() << point.y();
    qDebug() << rect.x() << rect.width() << rect.y() << rect.height();
    widget->move(point.x()+rect.width(), point.y() );
        widget->show();
}

void MovimentaInterfaceLadoDireito::getPos()
{
    rect =  widgetPai->rect();
    point= widgetPai->pos();
}
