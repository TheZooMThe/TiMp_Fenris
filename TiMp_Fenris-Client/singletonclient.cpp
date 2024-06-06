#include "singletonclient.h"
#include <functionsforclient.h>
#include "functionsforclient.h"


SingletonClient *SingletonClient::p_instance = nullptr;
SingletonDestroyer SingletonClient::destroyer;


SingletonClient::SingletonClient(QObject *parent) : QObject(parent),cipher("")
{
    mTcpSocket = new QTcpSocket(this);
    mTcpSocket->connectToHost("127.0.0.1", 33333);

    connect(mTcpSocket, SIGNAL(readyRead()), this, SLOT(slotServerRead()));
    // FunctionsForClient functions;
    // mTcpSocket->waitForReadyRead();
    // slotServerRead();
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

    cipher.setKey(log.toUtf8()); // Устанавливаем ключ шифра логином

    QString query = "auth&" + log + "&" + pass;
    qDebug() << query;
    QByteArray encryptedQuery = cipher.encrypt(query.toUtf8());
    cipher.setKey(static_key); // Устанавливаем ключ шифра логином
    QByteArray encryptedDynamicKey = cipher.encrypt(log.toUtf8());
    qDebug() << "authSending to server (encrypted): " << encryptedQuery;
    mTcpSocket->write(encryptedQuery+ "*" + encryptedDynamicKey);
}


void SingletonClient::send_msg_to_server_reg(QString log, QString pass, QString email)
{
    cipher.setKey(log.toUtf8()); // Устанавливаем ключ шифра логином
    QString query = "reg&" + log + "&" + pass + "&" + email;
    QByteArray encryptedQuery = cipher.encrypt(query.toUtf8());
    cipher.setKey(static_key); // Устанавливаем ключ шифра логином
    QByteArray encryptedDynamicKey = cipher.encrypt(log.toUtf8());
    //qDebug() << "authSending to server (encrypted): " << encryptedQuery;
    mTcpSocket->write(encryptedQuery+ "*" + encryptedDynamicKey);
}

void SingletonClient::send_msg_to_server_check(QString task_number, QString first, QString second, QString answer)
{
    cipher.setKey(static_key); // Устанавливаем ключ шифра логином
    QString query = "check&" + task_number + "&" + first + "&" + second + "&" + answer;
    QByteArray encryptedQuery = cipher.encrypt(query.toUtf8());
    QByteArray encryptedDynamicKey = cipher.encrypt(static_key);
    //qDebug() << "authSending to server (encrypted): " << encryptedQuery;
    mTcpSocket->write(encryptedQuery+ "*" + encryptedDynamicKey);
}

void SingletonClient::send_msg_to_server_adminAuth(QString log, QString pass)
{

    cipher.setKey(log.toUtf8()); // Устанавливаем ключ шифра логином

    QString query = "adminAuth&" + log + "&" + pass;
    QByteArray encryptedQuery = cipher.encrypt(query.toUtf8());
    cipher.setKey(static_key); // Устанавливаем ключ шифра логином
    QByteArray encryptedDynamicKey = cipher.encrypt(log.toUtf8());
    qDebug() << "adminAuthSending to server (encrypted): " << encryptedQuery;
    mTcpSocket->write(encryptedQuery+ "*" + encryptedDynamicKey);
}

void SingletonClient::send_msg_to_server_stat(QString log)
{

    cipher.setKey(log.toUtf8()); // Устанавливаем ключ шифра логином
    QString query = "statistic&" + log;
    QByteArray encryptedQuery = cipher.encrypt(query.toUtf8());
    cipher.setKey(static_key); // Устанавливаем ключ шифра логином
    QByteArray encryptedDynamicKey = cipher.encrypt(log.toUtf8());
    //qDebug() << "authSending to server (encrypted): " << encryptedQuery;
    mTcpSocket->write(encryptedQuery+ "*" + encryptedDynamicKey);

}

void SingletonClient::send_msg_to_server_total_statistic(QString log)
{
    cipher.setKey(log.toUtf8()); // Устанавливаем ключ шифра логином
    QString query = "totalStatistic&" + log;
    qDebug() << query;
    QByteArray encryptedQuery = cipher.encrypt(query.toUtf8());
    cipher.setKey(static_key); // Устанавливаем ключ шифра логином
    QByteArray encryptedDynamicKey = cipher.encrypt(log.toUtf8());
    //qDebug() << "authSending to server (encrypted): " << encryptedQuery;
    mTcpSocket->write(encryptedQuery+ "*" + encryptedDynamicKey);
    mTcpSocket ->waitForReadyRead();
}

/*
QString SingletonClient::send_msg_to_server_check(QString task_number, QString first, QString second, QString answer)    // ked klikneme na task tak asi budeme potrebovat novu funkciu na poslanie
{                                                               // prosby na server task_number aby nam vygeneroval nejake random zadanie a vratil nam jeho parametre
    QString query = "check&" + task_number + "&" + first + "&" + second + "&" + answer;      // potom posielame check funkciu a pozerame ci dostaneme + alebo -
    mTcpSocket->write(query.toUtf8());      //okej, vyzera to tak ze generujeme random variant na kliente a posielame na back 3 argumenty + odpoved
    mTcpSocket->waitForReadyRead();
    return slotServerRead();
}
*/

QString SingletonClient::slotServerRead()
{
    //qDebug() << "slot\n";
    QString response = "";
    while(mTcpSocket->bytesAvailable() > 0)
    {
        QByteArray array = mTcpSocket->readAll();
        response.append(array);
    }


    qDebug() << "Сообщение до расшифровки"<< response;

    VigenereCipher cipher(static_key);
    int pos = response.lastIndexOf('*');


    QString dynamic_key_encrypted = response.mid(pos + 1);
    QString data_to_decrypt = response.left(pos);

    // Расшифровка динамического ключа с использованием статического ключа
    QByteArray decrypted_dynamic_key = cipher.decrypt(dynamic_key_encrypted.toUtf8());
    QString dynamic_key = QString::fromUtf8(decrypted_dynamic_key);

    // Создаем новый объект шифра с динамическим ключом
    VigenereCipher dynamicCipher(dynamic_key.toUtf8());

    // Расшифровка данных с использованием динамического ключа
    QByteArray decrypted_data = dynamicCipher.decrypt(data_to_decrypt.toUtf8());
    QString decrypted_string = QString::fromUtf8(decrypted_data);
    qDebug() << "MEssage: " << data_to_decrypt;

    qDebug() << "MEssage: " << decrypted_string;
    qDebug() << "Dynamic_key: " << decrypted_dynamic_key;







    emit message_from_server(decrypted_string);
    return decrypted_string;
    //emit message_from_server(response);
}
