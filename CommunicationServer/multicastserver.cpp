#include "multicastserver.h"

MulticastServer::MulticastServer(QObject *parent) : QObject(parent),
    groupAddress(QStringLiteral("239.255.43.21"))
{
    udpSocket.setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
}

void MulticastServer::doWork()
{
    int repetitions = 0;
    while (repetitions < 100000)
    {
        QString txt = "Message %1";
        QByteArray datagram = txt.arg(repetitions).toUtf8();
        udpSocket.writeDatagram(datagram, groupAddress, 45454);
        ++repetitions;
        QCoreApplication::processEvents();
        QThread::sleep(1);
    }
}
