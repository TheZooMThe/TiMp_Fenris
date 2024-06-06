#include "database.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

/*
create table user_info(login varchar(20) NOT NULL,
                      pass varchar(64) NOT NULL,
                      mail varchar(64) NOT NULL,
                      stat_task1 int NOT NULL,
                      stat_task2 int NOT NULL,
                      id_conn int
                      is_admin integer
                      task_1_ap integer
                      task_2_ap integer
                      task_3_ap integer)

*/


database *database::p_instance = nullptr;
databaseDestroyer database::destroyer;

database::database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\Herten\\Desktop\\SERVER\\FINALSERVER\\sqlite.db");
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

QByteArray database::reg(QString log, QString hashedPass, QString mail) {
    // qDebug() << log << " " << pass << " " << mail;

    QStringList result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});

    if (!result.isEmpty()) {
        return "reg-";
    }

    //QCryptographicHash hash(QCryptographicHash::Sha384);
    //hash.addData(pass.toUtf8());
    //QByteArray hashedPass = hash.result(); - использовалось для сравнения результатов хеширования

    p_instance->sendQuerry(
        "INSERT INTO user_info (login,pass,mail,stat_task1,stat_task2,id_conn) VALUES (?, ?, ?, 0, 0, NULL) ",
        {log, hashedPass.toUtf8(), mail});

    return ("reg+&" + log).toUtf8();
}

QByteArray database::auth(int socketDescr, QString log, QString hashedPass) {

    // Проверка на существование пользователя
    QStringList result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});
    if (result.isEmpty()) {
        return "auth-";
    }

    //QCryptographicHash hash(QCryptographicHash::Sha384);
    //hash.addData(pass.toUtf8());
    //QByteArray hashedPass = hash.result();

    // Проверка пароля на совпадение
    result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ? AND pass = ?", {log, hashedPass.toUtf8()});
    if (result.isEmpty()) {
        return "auth-";
    }

    p_instance->sendQuerry(
        "UPDATE user_info set id_conn = ? where login = ?",
        {socketDescr, log}
        );

    return ("auth+&" + log).toUtf8();
}

QByteArray database::adminAuth(int socketDescr, QString log, QString hashedPass) {

    // Проверка на существование пользователя
    QStringList result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ?", {log});
    if (result.isEmpty()) {
        return "adminAuth-";
    }

    //QCryptographicHash hash(QCryptographicHash::Sha384);
    //hash.addData(pass.toUtf8());
    //QByteArray hashedPass = hash.result();

    // Проверка пароля на совпадение
    result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ? AND pass = ?", {log, hashedPass.toUtf8()});
    if (result.isEmpty()) {
        return "adminAuth-";
    }

    //ПРОВЕРКа НА КОЛОНКУ АДМИНКИ!!!!!!!!!!!!!
    result = p_instance->sendQuerry("SELECT * FROM user_info WHERE login = ? AND pass = ? AND is_admin = 1", {log, hashedPass.toUtf8()});
    if (result.isEmpty()) {
        return "adminAuth-";
    }


    p_instance->sendQuerry(
        "UPDATE user_info set id_conn = ? where login = ?",
        {socketDescr, log}
        );

    return ("adminAuth+&" + log).toUtf8();
}


QByteArray database::stat(int socketDescr, QString log) {
    QStringList results = p_instance -> sendQuerry("SELECT stat_task1, stat_task2 FROM user_info WHERE login = ? AND id_conn = ?", {log, socketDescr});
    QStringList row = results.at(0).split("\t");
    int statTask1 = row.at(0).toInt();
    int statTask2 = row.at(1).toInt();

    return QString("stat&%1&%2").arg(statTask1).arg(statTask2).toUtf8();
}

bool database::updateTask1Ap(const QString& log) {
    QString queryStr = "UPDATE user_info SET task_1_ap = task_1_ap + 1 WHERE login = ?";
    return !p_instance->sendQuerry(queryStr, {log}).isEmpty();
}

bool database::updateTask2Ap(const QString& log) {
    QString queryStr = "UPDATE user_info SET task_2_ap = task_2_ap + 1 WHERE login = ?";
    return !p_instance->sendQuerry(queryStr, {log}).isEmpty();
}

bool database::updateTask3Ap(const QString& log) {
    QString queryStr = "UPDATE user_info SET task_3_ap = task_3_ap + 1 WHERE login = ?";
    return !p_instance->sendQuerry(queryStr, {log}).isEmpty();
}

bool database::updateTask1Try(const QString& log) {
    QString queryStr = "UPDATE user_info SET Task1Try = Task1Try + 1 WHERE login = ?";
    return !p_instance->sendQuerry(queryStr, {log}).isEmpty();
}

bool database::updateTask2Try(const QString& log) {
    QString queryStr = "UPDATE user_info SET Task2Try = Task2Try + 1 WHERE login = ?";
    return !p_instance->sendQuerry(queryStr, {log}).isEmpty();
}

bool database::updateTask3Try(const QString& log) {
    QString queryStr = "UPDATE user_info SET Task3Try = Task3Try + 1 WHERE login = ?";
    return !p_instance->sendQuerry(queryStr, {log}).isEmpty();
}

QString database::getLoginFromSocketDescr(int socketDescr) {
    QStringList result = sendQuerry("SELECT login FROM user_info WHERE id_conn = ?", {socketDescr});
    if (result.isEmpty()) {
        return QString();
    }
    QStringList row = result.at(0).split("\t");
    return row.at(0);
}

QByteArray database::userStatistic(const QString& log) {
    QStringList results = sendQuerry(
        "SELECT task_1_ap, task_2_ap, task_3_ap, Task1Try, Task2Try, Task3Try FROM user_info WHERE login = ?", {log});

    if (results.isEmpty()) {
        return "statistic-";
    }

    QStringList row = results.at(0).split("\t");
    int task1Ap = row.at(0).toInt();
    int task2Ap = row.at(1).toInt();
    int task3Ap = row.at(2).toInt();
    int Task1Try = row.at(3).toInt();
    int Task2Try = row.at(4).toInt();
    int Task3Try = row.at(5).toInt();

    int task1Percentage = Task1Try != 0 ? (task1Ap * 100) / Task1Try : 0;
    int task2Percentage = Task2Try != 0 ? (task2Ap * 100) / Task2Try : 0;
    int task3Percentage = Task3Try != 0 ? (task3Ap * 100) / Task3Try : 0;

    return QString("statistic+&%1&%2&%3&%4")
        .arg(log)
        .arg(task1Percentage)
        .arg(task2Percentage)
        .arg(task3Percentage)
        .toUtf8();
}


QByteArray database::totalStatistic(const QString& adminLogin) {


    QStringList isAdmin = sendQuerry("SELECT is_admin FROM user_info WHERE login = ?", {adminLogin});
    if (isAdmin.isEmpty() || isAdmin.first() != "1") {
        return "totalStatistic-"; // Ошибка: пользователь не является администратором
    }

    QStringList results = sendQuerry(
        "SELECT login, task_1_ap, task_2_ap, task_3_ap, Task1Try, Task2Try, Task3Try FROM user_info", {});

    if (results.isEmpty()) {
        return "totalStatistic-";
    }

    QByteArray data;

    for (const QString& row : results) {
        QStringList columns = row.split("\t");
        QString login = columns.at(0);
        int task1Ap = columns.at(1).toInt();
        int task2Ap = columns.at(2).toInt();
        int task3Ap = columns.at(3).toInt();
        int Task1Try = columns.at(4).toInt();
        int Task2Try = columns.at(5).toInt();
        int Task3Try = columns.at(6).toInt();

        int task1Percentage = Task1Try != 0 ? (task1Ap * 100) / Task1Try : 0;
        int task2Percentage = Task2Try != 0 ? (task2Ap * 100) / Task2Try : 0;
        int task3Percentage = Task3Try != 0 ? (task3Ap * 100) / Task3Try : 0;

        data += QString("%1&%2&%3&%4&").arg(login).arg(task1Percentage).arg(task2Percentage).arg(task3Percentage).toUtf8();
    }

    return "totalStatistic+&" + data;
}
