#include "functionsforserver.h"

QByteArray auth(QString log, QString pass) {
    database::sendQuerry("sha-256 hash или что тут писать пусть будет он");
    return "auth completed\r\n";
}

QByteArray reg(QString log, QString pass, QString mail) {

    return "reg completed\r\n";
}

QByteArray parsing(QString data_from_client) {
    // NameOfFunc&Param1&Param2&Param3 to NameOfFunc(param1,param2,param3)
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));

    if (data_from_client_list.size() < 2) {
        return "error\r\n";
    }

    QString func_name = data_from_client_list.first();
    data_from_client_list.removeFirst();

    if(func_name == "auth") {
        if (data_from_client_list.size() != 2) {
            return "error\r\n";
        }
        return auth(data_from_client_list.at(0), data_from_client_list.at(1));
    }

    else if(func_name == "reg") {
        if (data_from_client_list.size() != 3) {
            return "error\r\n";
        }
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2));
    }
    else {
        return "There is no command with that syntax\r\n";
    }

}
