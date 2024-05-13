#include <QCoreApplication>
#include "singletonclient.h"
#include <iostream>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SingletonClient::getInstance();
    std::string msg;
    std::cin>>msg;
    SingletonClient::getInstance()->
        send_msg_to_server(QString::fromStdString(msg));
    return a.exec();
}


