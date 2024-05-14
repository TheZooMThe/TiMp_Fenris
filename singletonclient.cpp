#include "singletonclient.h"
#include <functionsforclient.h>
#include "ui_authregform.h"



SingletonClient *SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;


SingletonClient::SingletonClient(QObject *parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
}


SingletonClient* SingletonClient::getInstance()
{
    if (!p_instance)
    {
        p_instance = new SingletonClient();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

void SingletonClient::send_msg_to_server(QString log, QString pass)
{
    QString query = "auth&" + log + "&" + pass;
    mTcpSocket->write(query.toUtf8());
}

void SingletonClient::send_msg_to_server_reg(QString log, QString pass, QString email)
{
    QString query = "reg&" + log + "&" + pass + "&" + email;
    mTcpSocket->write(query.toUtf8());
}

void SingletonClient::slotServerRead()   // tu sa treba s artemom porozpravat ako posiela odpoved a preverit ako funguje is_auth
{
    //qDebug() << "slot\n";
    QString response = "";
    while(mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        response.append(array);
    }

    QStringList parts = response.split("&");
    if (parts.size() >= 2 && parts[0] == "auth+" )
    {

        QString log = parts[1];
        FunctionsForClient::is_auth();  //pravdepodobne on len posle correct alebo false, a podla toho bud vyzveme funkciu is_auth alebo nie

    }

 //   else if (parts.size() >= 2 && parts[0] == "reg+" )
 //   {

//    }

    else
    {
        qDebug() << "Invalid authentication response from server";
    }
    qDebug()<< response;
    emit message_from_server(response);
}
