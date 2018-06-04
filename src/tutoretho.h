#ifndef TUTORETHO_H
#define TUTORETHO_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QDomElement>


class Tutores{

public:
    Tutores();
    void addParamatros(QString id,QString texto , QString Titulo,
                       QString pbS, QString pbN);


    QString getTexto();
    QString getId();
//    void addId();
//    void addTitulo();
//    void addPbS();
//    void addPbN();


private:
    QString texto;
    QString id;
    QString titulo;
    QString pbS;
    bool    chPbS;
    QString pbN;
    bool    chPbN;

};

class TutorEtho : public QObject
{
    Q_OBJECT
public:
    explicit TutorEtho(QObject *parent = 0);

    void lerXml(QString arquivo);
    void debugID();
    void debugTexto();
    QString getTextoById(QString id);

private:

    QList<Tutores> tutores;


    QFile OutVideo;
//    QList<QString> tutores;
//    QList<QString> dici;
//    QString Tutores;

signals:

public slots:
};




#endif // TUTORETHO_H
