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
    mTcpSocket = mTcpServer->nextPendingConnection();
    int socketDescriptor = mTcpSocket->socketDescriptor();
    mSocketDescriptors[socketDescriptor] = mTcpSocket;
    mTcpSocket->write("Hello, World!!! I am echo server!\r\n");
    connect(mTcpSocket, &QTcpSocket::readyRead,this,&MyTcpServer::slotServerRead);
    connect(mTcpSocket,&QTcpSocket::disconnected,this,&MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        return;
    }

    QString res = "";
    while(socket->bytesAvailable()>0)
    {
        QByteArray array =socket->readAll();
        qDebug()<<array<<"\n";
        if(array=="\x01")
        {
            // mTcpSocket->write(parsing(QString(res.toUtf8())));
            socket->write(res.toUtf8());
            res = "";
        }
        else
            res.append(array);
    }
    socket->write(parsing(socket->socketDescriptor(), QString(res.toUtf8())));
}

void MyTcpServer::slotClientDisconnected(){
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        int socketDescriptor = mSocketDescriptors.key(socket);
        mSocketDescriptors.remove(socketDescriptor);
        socket->close();
        qDebug() << socketDescriptor;
        // qDebug() << stat(880, "Artem");
        userDisconnect(socketDescriptor);
    }
}
