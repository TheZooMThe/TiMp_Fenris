#include "mytcpserver.h"
#include <QDebug>
#include <QCoreApplication>
#include<QString>


MyTcpServer::~MyTcpServer()
{

    mTcpServer->close();
    //server_status=0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent){
    mTcpServer = new QTcpServer(this);
    // mfunctionsforserver = new functionsforserver();

    connect(mTcpServer, &QTcpServer::newConnection,
            this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 33333)){
        qDebug() << "server is not started";
    } else {
        //server_status=1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection(){
 //   if(server_status==1){
        mTcpSocket = mTcpServer->nextPendingConnection();
        mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
        connect(mTcpSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
        connect(mTcpSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
   // }
}

void MyTcpServer::slotServerRead(){
    QString res = "";
    while(mTcpSocket->bytesAvailable()>0)
    {
        QByteArray array =mTcpSocket->readAll();
        qDebug()<<array<<"\n";
        if(array=="\x01")
        {
            // mTcpSocket->write(parsing(QString(res.toUtf8())));
             mTcpSocket->write(res.toUtf8());
            res = "";
        }
        else
            res.append(array);
    }
    mTcpSocket->write(parsing(QString(res.toUtf8())));
    //mTcpSocket->write(res.toUtf8());

}

void MyTcpServer::slotClientDisconnected(){
    mTcpSocket->close();
}
