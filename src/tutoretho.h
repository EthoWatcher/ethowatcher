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
    QString getPbS();
    QString getPbN();
    QString getTitulo();
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
/**
 * @brief The TutorEtho class
 * Essa classe le o texto xml e retira os parametros das interfaces
 */
class TutorEtho : public QObject
{
    Q_OBJECT
public:
    explicit TutorEtho(QObject *parent = 0);

    void lerXml(QString arquivo);

    void debugID();
    void debugTexto();
    QString getTextoById(QString id);
    QString getTitulo(QString id);
    QString getPbS(QString id);
    QString getPbN(QString id);

    QString getTextoByNumero(int numero);
    int getSize();

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
