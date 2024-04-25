#ifndef DATABASE_H
#define DATABASE_H
#include <QByteArray>
#include <QString>

class database
{
public:
    database();
    static QByteArray sendQuerry(QString text);
};

#endif // DATABASE_H
