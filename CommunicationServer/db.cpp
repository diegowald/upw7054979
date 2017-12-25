#include "db.h"
#include <QDebug>

#include <QSqlError>
#include <QSqlQuery>


DB::DB(QObject *parent) : QObject(parent)
{
    _filename = "./db/users.db";
}

QSqlDatabase DB::getDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(_filename);
    bool opened = db.open();
    if (!opened)
    {
        qInfo() << db.lastError().text();
    }
    return db;
}

bool DB::addUser(const QString &user)
{
    QString SQL = "INSERT INTO users (username, blocked) VALUES (:username, 0);";

    QSqlDatabase db = getDB();

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":username", user);

    bool res = query.exec();
    qDebug() << query.lastError().text();

    return res;
}

bool DB::isBlocked(const QString &user)
{
    QString SQL = "SELECT blocked FROM users WHERE username = :username;";
    QSqlDatabase db = getDB();

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":username", user);

    query.exec();
    qDebug() << query.lastError().text();

    bool blocked = true;

    while (query.next())
    {
        blocked = query.value(0).toBool();
    }
    return blocked;
}

bool DB::blockUser(const QString &user)
{
    QString SQL = "UPDATE users SET blocked = 1 WHERE username = :username;";
    QSqlDatabase db = getDB();

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":username", user);

    query.exec();
    qDebug() << query.lastError().text();

    bool res = query.exec();
    qDebug() << query.lastError().text();

    return res;
}

bool DB::unblockUser(const QString &user)
{
    QString SQL = "UPDATE users SET blocked = 0 WHERE username = :username;";
    QSqlDatabase db = getDB();

    QSqlQuery query;
    query.prepare(SQL);
    query.bindValue(":username", user);

    query.exec();
    qDebug() << query.lastError().text();

    bool res = query.exec();
    qDebug() << query.lastError().text();

    return res;
}

QStringList DB::listUsers()
{
    QString SQL = "SELECT username, blocked from users;";
    QSqlDatabase db = getDB();

    QSqlQuery query;
    query.prepare(SQL);

    query.exec();
    qDebug() << query.lastError().text();

    QStringList users;
    while (query.next())
    {
        QString name = query.value(0).toString();
        QString blocked = query.value(1).toString();
        users << name + "," + blocked;
    }
    return users;
}
