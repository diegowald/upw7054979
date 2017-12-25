#include "server.h"
#include <QRegExp>
#include <QStringList>
#include <QCoreApplication>

#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

Server::Server(QObject *parent) : QObject(parent)
{
    QHttpServer *server = new QHttpServer(this);
    connect(server, SIGNAL(newRequest(QHttpRequest*, QHttpResponse*)),
            this, SLOT(handleRequest(QHttpRequest*, QHttpResponse*)));

    server->listen(QHostAddress::Any, 8080);
}

void Server::handleRequest(QHttpRequest *req, QHttpResponse *resp)
{
    qDebug() << req->path();
    bool found = false;
    foreach(QString regExp, _functors.keys())
    {
        QRegExp exp(regExp);
        if (exp.indexIn(req->path()) != -1)
        {
            found = _functors[regExp](req, resp, exp.capturedTexts());
            break;
        }
    }

    if (!found)
    {
        resp->writeHead(403);
        resp->end(QByteArray("You aren't allowed here!"));
    }
}


void Server::subscribe(const QString regExp, std::function<bool(QHttpRequest *, QHttpResponse *, const QStringList &params)> commandFunction)
{
    _functors[regExp] = commandFunction;
}
