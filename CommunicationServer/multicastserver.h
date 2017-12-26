#ifndef MULTICASTSERVER_H
#define MULTICASTSERVER_H

#include <QObject>
#include <QtNetwork>


class MulticastServer : public QObject
{
    Q_OBJECT
public:
    explicit MulticastServer(QObject *parent = nullptr);

public slots:
    void doWork();

public slots:

private:
    QUdpSocket udpSocket;
    QTimer timer;
    QHostAddress groupAddress;

};

#endif // MULTICASTSERVER_H
