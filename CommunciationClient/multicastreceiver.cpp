#include "multicastreceiver.h"

MulticastReceiver::MulticastReceiver(const QString &groupAddress, const int port, int id, QObject *parent) : QObject(parent),
    _groupAddress(groupAddress)
{
    _id = id;

    _udpSocket.bind(QHostAddress::AnyIPv4, 45454, QUdpSocket::ShareAddress);
    _udpSocket.joinMulticastGroup(_groupAddress);

    connect(&_udpSocket, &QUdpSocket::readyRead, this, &MulticastReceiver::processPendingDatagrams);
}

void MulticastReceiver::processPendingDatagrams()
{
    QByteArray datagram;
    while (_udpSocket.hasPendingDatagrams())
    {
        datagram.resize(int(_udpSocket.pendingDatagramSize()));
        _udpSocket.readDatagram(datagram.data(), datagram.size());
        emit multicastReceived(_id, QString::fromUtf8(datagram));
    }
}

void MulticastReceiver::disconnectNow()
{
    _udpSocket.disconnectFromHost();
}
