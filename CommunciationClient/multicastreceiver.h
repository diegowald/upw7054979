#ifndef MULTICASTRECEIVER_H
#define MULTICASTRECEIVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>


class MulticastReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MulticastReceiver(const QString &groupAddress, const int port, int id = -1, QObject *parent = nullptr);

    void disconnectNow();

signals:
    void multicastReceived(int id, const QString &payload);

private slots:
    void processPendingDatagrams();


private:
    QUdpSocket _udpSocket;
    QHostAddress _groupAddress;
    int _id;
};

#endif // MULTICASTRECEIVER_H
