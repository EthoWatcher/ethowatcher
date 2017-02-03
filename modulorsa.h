#ifndef MODULORSA_H
#define MODULORSA_H

#include <QObject>
#include <QDebug>

class moduloRsa : public QObject
{
    Q_OBJECT
public:
    explicit moduloRsa(QObject *parent = 0);

    struct chaveRSA{
    int p; //primeiro primo
    int q; //segundo primo
    int n;
    int d; //chave de decodificacao
    int e; //ou lambda
    int totiente;
    };
    chaveRSA chave;

    QString criptoRSAQstring(QString valorOriginalString);
    QString decriptoRSAQstring(QString valorCriptografadoString);

    int criptoRSA(int numeroASerCodificado);
    int decriptoRSA(int valorCriptografado);

    void valoresdeD();


    ///valores
    QString valorOriginalString;
    QByteArray valorOriginalBit;
  //  int valorDecrip[3];
   // int valorDecriptografar=0;





public slots:


signals:



private:







};

#endif // MODULORSA_H
