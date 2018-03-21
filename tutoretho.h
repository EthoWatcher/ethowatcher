#ifndef TUTORETHO_H
#define TUTORETHO_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QDomElement>


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

    struct Tutores{
        QString texto;
        QString id;
    };
    QList<Tutores> tutores;


    QFile OutVideo;
//    QList<QString> tutores;
//    QList<QString> dici;
//    QString Tutores;

signals:

public slots:
};

#endif // TUTORETHO_H
