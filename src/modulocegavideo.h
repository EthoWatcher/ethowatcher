#ifndef MODULOCEGAVIDEO_H
#define MODULOCEGAVIDEO_H

#include <QObject>
//opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDate>


//funcionar o aleatorio
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QString>
#include <QThread>
#include <QDebug>

//gravando
#include <QXmlStreamWriter>
#include "modulorsa.h"



class moduloCegaVideo : public QObject
{
    Q_OBJECT
public:
    explicit moduloCegaVideo(QObject *parent = 0);

signals:

public slots:
};

#endif // MODULOCEGAVIDEO_H
