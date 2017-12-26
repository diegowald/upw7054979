#ifndef MULTICASTRECEIVER_H
#define MULTICASTRECEIVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>


class MulticastReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MulticastReceiver(QObject *parent = nullptr);

signals:
    void multicastReceived(const QString &payload);

private slots:
    void processPendingDatagrams();


private:
    QUdpSocket udpSocket;
    QHostAddress groupAddress;
};

#endif // MULTICASTRECEIVER_H
