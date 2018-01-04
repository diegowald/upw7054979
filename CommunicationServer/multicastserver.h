#ifndef MULTICASTSERVER_H
#define MULTICASTSERVER_H

#include <QObject>
#include <QtNetwork>


/*
TTL     Scope
----------------------------------------------------------------------
   0    Restricted to the same host. Won't be output by any interface.
   1    Restricted to the same subnet. Won't be forwarded by a router.
 <32         Restricted to the same site, organization or department.
 <64 Restricted to the same region.
<128 Restricted to the same continent.
<255 Unrestricted in scope. Global.
*/

class MulticastServer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief MulticastServer
     * @param groupAddress: please see https://en.wikipedia.org/wiki/Multicast_address to find the most suitable value for this.
     * @param TTL http://www.tldp.org/HOWTO/Multicast-HOWTO-2.html
     * @param parent
     */
    explicit MulticastServer(const QString &groupAddress = "239.255.43.21", int TTL = 1,int port = 45454,  QObject *parent = nullptr);

public slots:
    void doWork();

public slots:

private:
    QUdpSocket _udpSocket;
    QTimer _timer;
    QHostAddress _groupAddress;
    int _port;

};

#endif // MULTICASTSERVER_H
