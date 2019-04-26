#ifndef MYSPLASH_H
#define MYSPLASH_H

#include <QSplashScreen>

class mySplash : public QSplashScreen
{
    Q_OBJECT
public:
    mySplash(QWidget *parent = 0);
    bool eventFilter(QObject *target, QEvent *event);    
};

#endif // MYSPLASH_H
