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
protected:
    database() {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("C:\\works\\TiMp_Fenris\\sqlite.db");
        if (!db.open()) {
            qDebug() << "Error opening database: " << db.lastError().text();
        }
    }
    database(const database &);
    database &operator=(const database &);
    ~database() {}
    friend class databaseDestroyer;
public:
    static database *getInstance() {
        if (!p_instance) {
            p_instance = new database();
            destroyer.initialize(p_instance);
        }
        return p_instance;
    }
    QByteArray sendQuerry(const QString& text,const QVariantList& queryParams);
};

#endif // DATABASE_H
