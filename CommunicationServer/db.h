#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql/QSqlDatabase>

class DB : public QObject
{
    Q_OBJECT
public:
    explicit DB(QObject *parent = nullptr);

    bool addUser(const QString &user);
    bool blockUser(const QString &user);
    bool unblockUser(const QString &user);
    QStringList listUsers();

    bool isBlocked(const QString &user);

private:
    QSqlDatabase getDB();

signals:

public slots:

private:
    QString _filename;
};

#endif // DB_H
