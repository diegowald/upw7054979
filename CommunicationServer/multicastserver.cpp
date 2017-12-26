#include "multicastserver.h"

MulticastServer::MulticastServer(QObject *parent) : QObject(parent),
    groupAddress(QStringLiteral("239.255.43.21"))
{
    udpSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, 10);
}

void MulticastServer::doWork()
{
    int repetitions = 0;
    while (repetitions < 100000)
    {
        QByteArray datagram = "Message";
        udpSocket.writeDatagram(datagram, groupAddress, 45454);
        ++repetitions;
        QThread::sleep(1);
    }
}
