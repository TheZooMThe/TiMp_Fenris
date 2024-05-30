#ifndef FUNCTIONSFORSERVER_H
#define FUNCTIONSFORSERVER_H
#include <QString>
#include <QList>
#include <QCryptographicHash>
#include "database.h"
#include "vigenerecipher.h"
#include "methodchord.h"


   QByteArray reg(QString log, QString pass, QString mail);
   QByteArray auth(int socketDescr, QString log, QString pass);
   QByteArray parsing(int socketDescr, QString data_from_client);
   QByteArray stat(int socketDescr, QString login);
   QByteArray adminAuth(int socketDescr, QString log, QString pass);
   QByteArray check(int socketDescr, QStringList& data);
   QByteArray userStatistic(int socketDescr, QString login);
   QByteArray totalStatistic(int socketDescr,QString adminLogin);
   bool userDisconnect(int socketDescr);


    QByteArray const static_key = "dota";
#endif // FUNCTIONSFORSERVER_H
