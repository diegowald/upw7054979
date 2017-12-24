#include <QCoreApplication>
#include "server.h"
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;

    server.subscribe("^/user/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
        return true;
    });

    server.subscribe("^/list/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
        return true;
    });


    server.subscribe("^/listConnected/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
        return true;
    });

    server.subscribe("^/add/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
        return true;
    });

    server.subscribe("^/block/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
        return true;
    });

    server.subscribe("^/content/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
        resp->end(body.arg(name).toUtf8());
        return true;
    });
    return a.exec();
}

