#ifndef ETHOWATCHER_H
#define ETHOWATCHER_H

#include <QObject>

class EthoWatcher : public QObject
{
    Q_OBJECT
public:
    explicit EthoWatcher(QObject *parent = 0);

signals:

public slots:
};

#endif // ETHOWATCHER_H