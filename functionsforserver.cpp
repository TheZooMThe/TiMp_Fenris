    #include "functionsforserver.h"
#include <database.h>

/*
create table user_info(login varchar(20) NOT NULL,
                      pass varchar(64) NOT NULL,
                      mail varchar(64) NOT NULL,
                      stat_task1 int NOT NULL,
                      stat_task2 int NOT NULL,
                      id_conn int)

*/

int hash_func_name(const QString& func_name) {
    if (func_name == "auth") return 0;
    if (func_name == "reg") return 1;
    if (func_name == "stat") return 2;
    if (func_name == "check") return 3;
    return -1; // unknown function
}

// добавить сокет дескрипшн
QByteArray auth(int sockDescr, QString log, QString pass) {
    if((log == "") || (pass == "")) {
        return "auth-";
    }

    database *db = database::getInstance();

    // Проверка на существование пользователя
    QByteArray result = db->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});
    if (result.isEmpty()) {
        return "auth-";
    }

    // Хэширование пароля
    QCryptographicHash hash(QCryptographicHash::Sha384);
    hash.addData(pass.toUtf8());
    QByteArray hashedPass = hash.result();

    // Проверка пароля на совпадение
    result = db->sendQuerry("SELECT * FROM user_info WHERE login = ? AND pass = ?", {log, hashedPass});
    if (result.isEmpty()) {
        return "auth-";
    }

    qDebug() << log << " " << pass;

    db->sendQuerry(
        "UPDATE user_info set id_conn = ? where login = ?",
        {sockDescr, log}
        );

    return ("auth+&" + log).toUtf8();
}

QByteArray reg(QString log, QString pass, QString mail) {
    if((log == "") || (pass == "") || (mail == "")) {
        return "reg-";
    }

    database *db = database::getInstance();

    qDebug() << log << " " << pass << " " << mail;

    QByteArray result = db->sendQuerry(
        "SELECT * FROM user_info WHERE login = ?",
        {log}
        );

    if (!result.isEmpty()) {
        return "reg-";
    }

    QCryptographicHash hash(QCryptographicHash::Sha384);
    hash.addData(pass.toUtf8());
    QByteArray hashedPass = hash.result();

    db->sendQuerry(
        "INSERT INTO user_info (login,pass,mail,stat_task1,stat_task2,id_conn) VALUES (?, ?, ?, 0, 0, NULL) ",
        {log, hashedPass, mail}
        );

    return ("reg+&" + log).toUtf8();
}

QByteArray stat(int socketDescr) {

    return "topstatistic\r\n";
}
QByteArray check(int socketDescr, QString var, QString userAnsw) {

    return "check\r\n";
}

QByteArray parsing(int socketDescr, QString data_from_client) {
    // NameOfFunc&Param1&Param2&Param3 to NameOfFunc(param1,param2,param3)
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));

    if (data_from_client_list.size() < 2) {
        return "error";
    }

    QString func_name = data_from_client_list.first();
    data_from_client_list.removeFirst();

    switch (hash_func_name(func_name)) {
    case 0: // auth
        if (data_from_client_list.size()!= 2) {
            return "auth-";
        }
        return auth(socketDescr,data_from_client_list.at(0), data_from_client_list.at(1).trimmed());

    case 1: // reg
        if (data_from_client_list.size()!= 3) {
            return "reg-";
        }
        return reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2).trimmed());

    case 2: // stat
        if (data_from_client_list.size() != 0) {
            return "error";
        }

        return stat(socketDescr);

    case 3: // check
        if (data_from_client_list.size() != 2) {
            return "error";
        }

        return check(socketDescr, data_from_client_list.at(0), data_from_client_list.at(1).trimmed());

    default:
        return "There is no command with that syntax";
    }
}

