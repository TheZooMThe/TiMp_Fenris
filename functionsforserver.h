#ifndef FUNCTIONSFORSERVER_H
#define FUNCTIONSFORSERVER_H
#include <QString>
#include <QList>
#include <QCryptographicHash>
#include <database.h>


   QByteArray reg(QString log, QString pass, QString mail);
   QByteArray auth(int socketDescr, QString log, QString pass);
   QByteArray parsing(int socketDescr, QString data_from_client);
   QByteArray stat(int socketDescr, QString login);
   QByteArray check(int socketDescr, QString var, QString userAnsw);
   bool userDisconnect(int socketDescr);


#endif // FUNCTIONSFORSERVER_H
