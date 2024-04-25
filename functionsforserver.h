#ifndef FUNCTIONSFORSERVER_H
#define FUNCTIONSFORSERVER_H
#include <QString>
#include <QList>
#include <database.h>


   QByteArray reg(QString log, QString pass, QString mail);
   QByteArray auth(QString log, QString pass);
   QByteArray parsing(QString data_from_client);

#endif // FUNCTIONSFORSERVER_H
