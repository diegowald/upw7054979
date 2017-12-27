#include "multicastreceiver.h"

MulticastReceiver::MulticastReceiver(int id, QObject *parent) : QObject(parent),
    groupAddress(QStringLiteral("239.255.43.21"))
{
    _id = id;

    udpSocket.bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress);
    udpSocket.joinMulticastGroup(groupAddress);

    connect(&udpSocket, &QUdpSocket::readyRead, this, &MulticastReceiver::processPendingDatagrams);

//    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

void MulticastReceiver::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket.hasPendingDatagrams())
    {
        datagram.resize(int(udpSocket.pendingDatagramSize()));
        udpSocket.readDatagram(datagram.data(), datagram.size());
        emit multicastReceived(_id, QString::fromUtf8(datagram));
    }
}

void MulticastReceiver::disconnectNow()
{
    udpSocket.disconnectFromHost();
}
