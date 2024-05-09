#ifndef FUNCTIONSFORSERVER_H
#define FUNCTIONSFORSERVER_H
#include <QString>
#include <QList>
#include <QCryptographicHash>
#include <database.h>


   QByteArray reg(QString log, QString pass, QString mail);
   QByteArray auth(int sockDescr, QString log, QString pass);
   QByteArray parsing(int socketDescr, QString data_from_client);
   QByteArray stat(int socketDescr);
   QByteArray check(int socketDescr, QString var, QString userAnsw);

#endif // FUNCTIONSFORSERVER_H
