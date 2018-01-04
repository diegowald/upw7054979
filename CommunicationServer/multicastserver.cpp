#include "multicastserver.h"


MulticastServer::MulticastServer(const QString &groupAddress, int TTL, int port, QObject *parent) : QObject(parent),
    _groupAddress(groupAddress), _port(port)
{
    _udpSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, TTL);
}

void MulticastServer::doWork()
{
    int repetitions = 0;
    while (repetitions < 100000)
    {
        QString txt = "Message %1";
        QByteArray datagram = txt.arg(repetitions).toUtf8();
        _udpSocket.writeDatagram(datagram, _groupAddress, 45454);
        ++repetitions;
        QCoreApplication::processEvents();
        QThread::sleep(1);
    }
}
