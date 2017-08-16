#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection(QString str_server, QString str_database, QString str_username, QString str_password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(str_server);
    db.setDatabaseName(str_database);
    db.setUserName(str_username);
    db.setPassword(str_password);

    if (!db.open())
    {
       return false;
    }

    return true;
}

#endif // CONNECTION_H
