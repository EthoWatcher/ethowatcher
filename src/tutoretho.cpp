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

            tutorLido.texto = aContent;


            QDomNode itemNode= a.at(i);
            QDomElement itemEle = itemNode.toElement();

           // qDebug()<<"a primeira tab tem o atributo" << itemEle.attribute("id");

            tutorLido.id = itemEle.attribute("id");
            qDebug() << itemEle.attribute("titulo");

            tutores.push_back(tutorLido);



        }

//    for (int i=0; i< c.length(); i ++) {
//    QString cContent="";

//    QTextStream tsC(&cContent);
//    c.at(i).save(tsC,0);
//    QDomNode itemNode= a.at(i);
//    QDomElement itemEle = itemNode.toElement();

//     qDebug() << cContent;



//    }

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
         qDebug() << tutores[i].id;
    }

}

/**
 * @brief TutorEtho::debugTexto mostra todos os textos lidos no xml
 */
void TutorEtho::debugTexto()
{
    qDebug()<<"================================texto=====================================";
    for(int i=0; i<tutores.size();i++){
        qDebug() << tutores[i].texto;

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
        if(tutores[i].id == id){
            return tutores[i].texto;
        }

    }

    return "erro nao encontrou";
}


