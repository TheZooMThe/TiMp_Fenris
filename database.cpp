#include "database.h"

/*
create table user_info(login varchar(20) NOT NULL,
                      pass varchar(64) NOT NULL,
                      mail varchar(64) NOT NULL,
                      stat_task1 int NOT NULL,
                      stat_task2 int NOT NULL,
                      id_conn int)

*/


database *database::p_instance = nullptr;
databaseDestroyer database::destroyer;



database::database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\works\\TiMp_Fenris\\sqlite.db");
    if (!db.open()) {
        qDebug() << "Error opening database: " << db.lastError().text();
    }
}

database* database::getInstance() {
    if (!p_instance) {
        p_instance = new database();
        destroyer.initialize(p_instance);
    }
    return p_instance;
}

QStringList database::sendQuerry(const QString& text, const QVariantList& queryParams)
{
    QSqlQuery query(db);
    query.prepare(text);

    for (int i = 0; i < queryParams.size(); ++i) {
        query.bindValue(i, queryParams.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return QStringList(  );
    }

    QStringList results;
    while (query.next()) {
        QStringList row;
        for (int i = 0; i < query.record().count(); i++) {
            row << query.value(i).toString();
        }
        results << row.join("\t");
    }
    return results;
}

bool database::userDisconnect(int socketDescr) {
    return p_instance->sendQuerry("UPDATE user_info set id_conn = NULL where id_conn = ?", {socketDescr}).isEmpty();
}

bool database::isUserCorrect(QString log, int socketDescr) {
    return !p_instance -> sendQuerry("SELECT 1 FROM user_info WHERE login = ? AND id_conn = ?", {log, socketDescr}).isEmpty();
}

QByteArray database::reg(QString log, QString pass, QString mail) {
    qDebug() << log << " " << pass << " " << mail;

    QStringList result = p_instance->sendQuerry(
        "SELECT * FROM user_info WHERE login = ?",
        {log}
        );

    if (!result.isEmpty()) {
        return "reg-";
    }

    QCryptographicHash hash(QCryptographicHash::Sha384);
    hash.addData(pass.toUtf8());
    QByteArray hashedPass = hash.result();

    p_instance->sendQuerry(
        "INSERT INTO user_info (login,pass,mail,stat_task1,stat_task2,id_conn) VALUES (?, ?, ?, 0, 0, NULL) ",
        {log, hashedPass, mail}
        );

    return ("reg+&" + log).toUtf8();


}
QByteArray database::auth(int socketDescr, QString log, QString pass) {

    // Проверка на существование пользователя
    QStringList result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});
    if (result.isEmpty()) {
        return "auth-";
    }

    // Хэширование пароля
    QCryptographicHash hash(QCryptographicHash::Sha384);
    hash.addData(pass.toUtf8());
    QByteArray hashedPass = hash.result();

    // Проверка пароля на совпадение
    result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ? AND pass = ?", {log, hashedPass});
    if (result.isEmpty()) {
        return "auth-";
    }

    qDebug() << log << " " << pass;

    p_instance->sendQuerry(
        "UPDATE user_info set id_conn = ? where login = ?",
        {socketDescr, log}
        );

    return ("auth+&" + log).toUtf8();
}


QByteArray database::stat(int socketDescr, QString log) {
    QStringList results = p_instance -> sendQuerry("SELECT stat_task1, stat_task2 FROM user_info WHERE login = ? AND id_conn = ?", {log, socketDescr});
    QStringList row = results.at(0).split("\t");
    int statTask1 = row.at(0).toInt();
    int statTask2 = row.at(1).toInt();

    return QString("stat&%1&%2").arg(statTask1).arg(statTask2).toUtf8();
}
