#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QtNetwork>
#include <QByteArray>
#include <QDebug>

#include "functionsforserver.h"

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();
public slots:
    void slotNewConnection();
    void slotClientDisconnected();
    void slotServerRead();
private:
    QTcpServer * mTcpServer;
    // functionsforserver* mfunctionsforserver;
    QTcpSocket * mTcpSocket;
    //int server_status;
};
#endif // MYTCPSERVER_H







