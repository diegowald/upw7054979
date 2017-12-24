#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include "qhttpserverfwd.h"
#include <functional>
#include <QMap>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    typedef std::function<bool(QHttpRequest *, QHttpResponse *, const QStringList&)> command;
    void subscribe(const QString regExp, command commandFunction);

public slots:
    void handleRequest(QHttpRequest *req, QHttpResponse *resp);

private:
    QMap<QString, command> _functors;
};

#endif // SERVER_H
