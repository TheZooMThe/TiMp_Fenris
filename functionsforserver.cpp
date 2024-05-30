#include "functionsforserver.h"

// Հաշվիչ ֆունկցիայի անունը
int hash_func_name(const QString& func_name) {
    if (func_name == "auth") return 0;
    if (func_name == "reg") return 1;
    if (func_name == "stat") return 2;
    if (func_name == "check") return 3;
    if (func_name == "adminAuth") return 4;
    if (func_name == "statistic") return 5;
    if (func_name == "totalStatistic") return 6;
    return -1; // անհայտ ֆունկցիա
}

// Ավելացնել սոկետի դեսկրիպտոր
QByteArray auth(int socketDescr, QString log, QString pass) {
    if((log == "") || (pass == "")) {
        return "auth-";
    }

    SHA384 hasher;
    QByteArray hashedPass = hasher.hash(pass.toUtf8());

    database *db = database::getInstance();
    return db -> auth(socketDescr, log, hashedPass);
}

// Գրանցման ֆունկցիա
QByteArray reg(QString log, QString pass, QString mail) {
    if((log == "") || (pass == "") || (mail == "")) {
        return "reg-";
    }

    SHA384 hasher;
    QByteArray hashedPass = hasher.hash(pass.toUtf8());

    database *db = database::getInstance();
    return db ->reg(log, hashedPass, mail);
}

// Վիճակագրության ֆունկցիա
QByteArray stat(int socketDescr, QString log) {
    database *db = database::getInstance();

    if (!db->isUserCorrect(log, socketDescr)) {
        return "stat-";
    }

    return db -> stat(socketDescr, log);
}

// Ադմինիստրատորի հաստատման ֆունկցիա
QByteArray adminAuth(int socketDescr, QString log, QString pass) {
    if((log == "") || (pass == "")) {
        return "adminAuth-";
    }

    SHA384 hasher;
    QByteArray hashedPass = hasher.hash(pass.toUtf8());

    database *db = database::getInstance();
    return db -> adminAuth(socketDescr, log, hashedPass);
}

// Ստուգման ֆունկցիա
QByteArray check(int socketDescr, QStringList& data) {
    QString taskNum = data[0];
    int taskNumInt = taskNum.toInt();

    if(taskNumInt == 1) {
    MethodChord chord;
    double x1Chord = data[1].toDouble();
    double x2Chord = data[2].toDouble();
    double userAnswerChord = data[3].toDouble();
    double trueAnswer = chord.chordMethod(x1Chord, x2Chord);

    qDebug() << "True answ: " << trueAnswer;
    qDebug() << "User answ: " << userAnswerChord;
    qDebug() << "True=user answ: " << (abs(trueAnswer-userAnswerChord) < 0.000001);
    database* db = database::getInstance();
    QString log = db->getLoginFromSocketDescr(socketDescr);  // Օգտագործողի մուտքագրումը
    if (abs(trueAnswer - userAnswerChord) < 0.000001) {

        if (!log.isEmpty()) {
            db->updateTask1Ap(log);  // Թարմացնել task_1_ap օգտվողի համար
        }
        return "check+&" + taskNum.toUtf8();
    }

    if (!log.isEmpty()) {
        db->updateTask1Try(log);  // Թարմացնել task_1_ap օգտվողի համար
    }
    return "check-&" + taskNum.toUtf8();
}
    else if(taskNumInt == 2) {
        // Максим Коваленко сюда свой код

    return "check-&" + taskNum.toUtf8();
    }

    else if(taskNumInt == 3) {
        // Константин Крот код сюда свой

    return "check-&" + taskNum.toUtf8();
    }

    return "check-&" + taskNum.toUtf8();
}

// Օգտվողի անջատման ֆունկցիա
bool userDisconnect(int socketDescr) {
    database *db = database::getInstance();
    return db ->userDisconnect(socketDescr);
}

// Օգտվողի վիճակագրության ֆունկցիա
QByteArray userStatistic(int socketDescr, QString log) {
    database *db = database::getInstance();

    if (!db->isUserCorrect(log, socketDescr)) {
        return "statistic-";
    }

    return db -> userStatistic(log);
}

// Ընդհանուր վիճակագրության ֆունկցիա
QByteArray totalStatistic(int socketDescr, QString adminLogin) {
    database *db = database::getInstance();

    if (!db->isUserCorrect(adminLogin, socketDescr)) {
        return "totalstatistic-";
    }

    return db -> totalStatistic(adminLogin);
}

// Տեքստի կոդավորման ֆունկցիա
QByteArray CipherForOut(QByteArray text, QByteArray DynamicKey) {
    VigenereCipher cipher(DynamicKey);
    QByteArray result = cipher.encrypt(text);
    cipher.setKey(static_key);
    result += "*" + cipher.encrypt(DynamicKey);
    return result;
}

// Տվյալների վերլուծության ֆունկցիա
QByteArray parsing(int socketDescr, QString data_from_client) {

    VigenereCipher cipher(static_key);
    int pos = data_from_client.lastIndexOf('*');
    if (pos == -1) {
        return CipherForOut("error", "error"); // եթե չկա '*' նշանը, վերադարձնել սխալ
    }

    QString dynamic_key_encrypted = data_from_client.mid(pos + 1);
    QString data_to_decrypt = data_from_client.left(pos);

    // Դինամիկ բանալիի վերծանում օգտագործելով ստատիկ բանալի
    QByteArray decrypted_dynamic_key = cipher.decrypt(dynamic_key_encrypted.toUtf8());
    QString dynamic_key = QString::fromUtf8(decrypted_dynamic_key);

    // Ստեղծել նոր ծածկագիր դինամիկ բանալիով
    VigenereCipher dynamicCipher(dynamic_key.toUtf8());

    // Տվյալների վերծանում օգտագործելով դինամիկ բանալի
    QByteArray decrypted_data = dynamicCipher.decrypt(data_to_decrypt.toUtf8());
    QString decrypted_string = QString::fromUtf8(decrypted_data);

    qDebug() << decrypted_string;

    // NameOfFunc&Param1&Param2&Param3 to NameOfFunc(param1,param2,param3)
    QStringList data_from_client_list = decrypted_string.split(QLatin1Char('&'));


    /*
    QStringList data_from_client_list = data_from_client.split(QLatin1Char('&'));
    VigenereCipher cipher(static_key);
    QString dynamic_key = "ab"; // Առանց կոդավորման */

    if (data_from_client_list.size() < 2) {
        return CipherForOut("error", "error");
    }

    QString func_name = data_from_client_list.first();
    data_from_client_list.removeFirst();

    cipher.setKey(dynamic_key.toUtf8());
    switch (hash_func_name(func_name)) {
    case 0: // auth
        if (data_from_client_list.size()!= 2) {
            return CipherForOut("auth-", "error");
        }
        return CipherForOut(auth(socketDescr,data_from_client_list.at(0), data_from_client_list.at(1).trimmed()), data_from_client_list.at(0).toUtf8());

    case 1: // reg
        if (data_from_client_list.size()!= 3) {
            return CipherForOut("reg-", "error");
        }
        return CipherForOut(reg(data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2).trimmed()), data_from_client_list.at(0).toUtf8());

    case 2: // stat
        if (data_from_client_list.size() != 1) {
            return CipherForOut("error", "error");
        }

        return CipherForOut(stat(socketDescr, data_from_client_list.at(0).trimmed()), data_from_client_list.at(0).toUtf8());

    case 3: // check
        if (data_from_client_list.size() != 4) {
            return CipherForOut("error", "error");
        }

        // qDebug() << "վերծանված սերվերի պատասխանը:" << CipherForOut(check(socketDescr, data_from_client_list.at(0), data_from_client_list.at(1), data_from_client_list.at(2), data_from_client_list.at(3).trimmed() ), data_from_client_list.at(0).toUtf8());;

        return CipherForOut(check(socketDescr,data_from_client_list), static_key);

    case 4: // adminAuth
        if (data_from_client_list.size()!= 2) {
            return CipherForOut("adminAuth-", "error");
        }
        return CipherForOut(adminAuth(socketDescr,data_from_client_list.at(0), data_from_client_list.at(1).trimmed()), data_from_client_list.at(0).toUtf8());
    case 5: // userStatistic
        if (data_from_client_list.size() != 1) {
            return CipherForOut("statistic-", "error");
        }
        return CipherForOut(userStatistic(socketDescr, data_from_client_list.at(0).trimmed()), data_from_client_list.at(0).toUtf8());
    case 6: // totalStatistic
        if (data_from_client_list.size() != 1) {
            return CipherForOut("totalStatistic-", "error");
        }
        return CipherForOut(totalStatistic(socketDescr, data_from_client_list.at(0).trimmed()), data_from_client_list.at(0).toUtf8());


    default:
        return CipherForOut("There is no command with that syntax", "error");
    }
}
