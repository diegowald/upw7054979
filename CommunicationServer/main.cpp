#include <QCoreApplication>
#include "server.h"
#include <qhttpserver.h>
#include <qhttprequest.h>
#include <qhttpresponse.h>
#include "db.h"
#include "multicastserver.h"
#include <QThread>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;

    QThread workerThread;
    MulticastServer *multicastServer = new MulticastServer();
    multicastServer->moveToThread(&workerThread);
    QObject::connect(&workerThread, &QThread::finished, multicastServer, &MulticastServer::deleteLater);
    workerThread.start();
    multicastServer->doWork();

    server.subscribe("^/list/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        DB db;
        QString name = params[1];

        QStringList res = db.listUsers();

        resp->end(res.join(";").toUtf8());
        return true;
    });


    server.subscribe("^/add/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        DB db;
        QString name = params[1];
        bool res = db.addUser(name);

        resp->end(QString(res ? "OK" : "ERR").toUtf8());
        return res;
    });

    server.subscribe("^/block/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        DB db;
        QString name = params[1];
        bool res = db.blockUser(name);

        resp->end(QString(res ? "OK" : "ERR").toUtf8());
        return res;
    });

    server.subscribe("^/unblock/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        DB db;
        QString name = params[1];
        bool res = db.unblockUser(name);

        resp->end(QString(res ? "OK" : "ERR").toUtf8());
        return res;
    });

    server.subscribe("^/content/([a-z]+)$", [](QHttpRequest *req, QHttpResponse *resp, const QStringList &params) -> bool
    {
        resp->setHeader("Content-Type", "text/html");
        resp->writeHead(200);

        QString name = params[1];
        DB db;
        if (!db.isBlocked(name))
        {
            QString body = QObject::tr("<html><head><title>Greeting App</title></head><body><h1>Hello %1!</h1></body></html>");
            resp->end(body.arg(name).toUtf8());
            return true;
        }
        else
            return false;
    });

    int res = a.exec();
    workerThread.quit();
    workerThread.wait();

    return res;
}

