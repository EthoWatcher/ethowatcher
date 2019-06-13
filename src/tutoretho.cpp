#include "tutoretho.h"

TutorEtho::TutorEtho(QObject *parent) : QObject(parent)
{




}

/**
 * @brief TutorEtho::lerXml ele le um arquivo xml que contem o conteudo do tutor
 * @param arquivo path do arquivo xml a ser lido
 */
void TutorEtho::lerXml(QString arquivo)
{
    QDomDocument xml;
    OutVideo.setFileName(arquivo);
    OutVideo.open(QIODevice::ReadOnly);

    if(OutVideo.isOpen()){
        xml.setContent(&OutVideo);

        Tutores tutorLido;

        QDomElement rootElement = xml.documentElement();
        qDebug("root element has %d childs", rootElement.childNodes().count());
        qDebug("root element is  %s ",  qPrintable(rootElement.nodeName()) );

        QDomNodeList a = rootElement.elementsByTagName("tutor");
        QDomNodeList b = rootElement.elementsByTagName("html");
        QDomNodeList c = rootElement.elementsByTagName("config");
        for (int i=0; i< a.length(); i ++) {

            QString aContent;

            QTextStream ts(&aContent);


            b.at(i).save(ts,0);

           // qDebug() << aContent;

//            tutorLido.texto = aContent;


            QDomNode itemNode= a.at(i);
            QDomElement itemEle = itemNode.toElement();

           // qDebug()<<"a primeira tab tem o atributo" << itemEle.attribute("id");

            tutorLido.addParamatros(itemEle.attribute("id"),
                                    aContent,
                                    itemEle.attribute("titulo"),
                                    itemEle.attribute("pbS"),
                                    itemEle.attribute("pbN"),
                                    itemEle.attribute("sizeHeight")
                                    );
//            tutorLido.id = itemEle.attribute("id");
//            tutorLido.titulo = itemEle.attribute("titulo");
//            tutorLido.pbN = itemEle.attribute("pbN");
//            tutorLido.pbS = itemEle.attribute("pbS");
//            qDebug() << itemEle.attribute("titulo");

            tutores.push_back(tutorLido);



        }


    }else{
        qDebug() << "nao encontrou/leu o arquivo xml";
    }



}
/**
 * @brief TutorEtho::debugID Mostra todos os id lidos no xml
 */
void TutorEtho::debugID()
{
    qDebug()<<"================================id=====================================";
    for(int i=0; i<tutores.size();i++){
         qDebug() << tutores[i].getId();
    }

}

/**
 * @brief TutorEtho::debugTexto mostra todos os textos lidos no xml
 */
void TutorEtho::debugTexto()
{
    qDebug()<<"================================texto=====================================";
    for(int i=0; i<tutores.size();i++){
        qDebug() << tutores[i].getTexto();

    }

}

/**
 * @brief TutorEtho::getTextoById retornar o texto do tutor a partir do id
 * @param id id do tutor a ser retorando
 * @return retorna uma QString contendo otexto, caso nao encontrar retorna nao encontrado
 */
QString TutorEtho::getTextoById(QString id)
{
    for(int i=0; i<tutores.size();i++){
        if(tutores[i].getId() == id){
            return tutores[i].getTexto();
        }

    }

    return "erro nao encontrou";
}

QString TutorEtho::getTitulo(QString id)
{
    for(int i=0; i<tutores.size();i++){
        if(tutores[i].getId() == id){
            return tutores[i].getTitulo();
        }

    }
    return "erro nao encontrou";
}

QString TutorEtho::getPbS(QString id)
{
    for(int i=0; i<tutores.size();i++){
        if(tutores[i].getId() == id){
            return tutores[i].getPbS();
        }

    }
    return "erro nao encontrou";
}

QString TutorEtho::getPbN(QString id)
{
    for(int i=0; i<tutores.size();i++){
        if(tutores[i].getId() == id){
            return tutores[i].getPbN();
        }

    }
    return "erro nao encontrou";
}

QString TutorEtho::getSizeHeight(QString id)
{
    for(int i=0; i<tutores.size();i++){
        if(tutores[i].getId() == id){
            return tutores[i].getSizeHeight();
        }

    }
    return "erro nao encontrou";

}

QString TutorEtho::getTextoByNumero(int numero)
{
    for(int i=0; i<tutores.size();i++){
        if(i == numero){
            return tutores[i].getTexto();
        }

    }

    return "erro nao encontrou";
}

int TutorEtho::getSize()
{
    return tutores.size();
}



Tutores::Tutores()
{
    chPbS= false;
    chPbN= false;
    qDebug() << "feito o primeiro leitor de tutor;";
}

void Tutores::addParamatros(QString id, QString texto, QString Titulo, QString pbS, QString pbN, QString sizeHeight)
{

    this->id=id;
    this->texto = texto;
    this->titulo = Titulo;
    this->pbN = pbN;
    this->pbS = pbS;
    this->sizeHeight = sizeHeight;


    if(this->pbN == ""){

        this->chPbN=false;
    }else{

        this->chPbN=true;
    }

    if(this->pbS == ""){

        this->chPbS=false;
    }else{

        this->chPbS=true;
    }
}

QString Tutores::getTexto()
{
    return this->texto;

}

QString Tutores::getId()
{
    return this->id;

}

QString Tutores::getPbS()
{
    return this->pbS;
}

QString Tutores::getPbN()
{

    return this->pbN;
}

QString Tutores::getTitulo()
{
    return this->titulo;
}

QString Tutores::getSizeHeight()
{
    return this->sizeHeight;
}
