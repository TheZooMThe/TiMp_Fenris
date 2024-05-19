#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include <QByteArray>
#include <QString>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>
#include <QCryptographicHash>
#include <sha384.h>

class database;

class databaseDestroyer
{
private:
    database *p_instance;
public:
    ~databaseDestroyer() { delete p_instance; }
    void initialize(database *p) { p_instance = p; }
};

class database
{
private:
    static database *p_instance;
    static databaseDestroyer destroyer;
    QSqlDatabase db;
    QStringList sendQuerry(const QString& text,const QVariantList& queryParams);
protected:
    database();
    database(const database &);
    database &operator=(const database &);
    ~database() {}
    friend class databaseDestroyer;
public:
    static database *getInstance();
    QByteArray reg(QString log, QString pass, QString mail);
    QByteArray auth(int sockDescr, QString log, QString pass);
    QByteArray stat(int socketDescr, QString log);
    bool userDisconnect(int sockDescr);
    bool isUserCorrect(QString log, int socketDescr);
};

#endif // DATABASE_H
