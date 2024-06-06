#include "functionsforclient.h"
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


MainWindow * FunctionsForClient::mainForm;
AuthRegForm * FunctionsForClient::authregForm;
task_one * FunctionsForClient::task;
admin * FunctionsForClient::Admin;
QString FunctionsForClient::login;

// QVector<UserData> FunctionsForClient::users;

FunctionsForClient::FunctionsForClient() {
    authregForm = new AuthRegForm();
    authregForm->show();
    mainForm = new MainWindow();
}

void FunctionsForClient::is_auth()
{
    //return client::sendmsg("auth&"+log+"&"+pass);

        authregForm->close();
        mainForm->show();


    //authregForm->showerr();

}

void FunctionsForClient::save_login(QString log)
{
    login = log;
}

QString FunctionsForClient::return_login()
{
    return login;
}

void FunctionsForClient::return_to_menu()
{
    task->hide();
    mainForm->show();
}

void FunctionsForClient::task_clicked(int i)
{
    mainForm->hide();
    if(task==nullptr)
        task =new task_one();
    task->set_task_number(i);
    task->show();
}

void FunctionsForClient::stat_clicked()
{
    mainForm->hide();
    if(task==nullptr)
        task =new task_one();
    task->set_task_stat();
    task->show();
}

void FunctionsForClient::send_clicked(int i)
{
    task->check_plus(i);
}

void FunctionsForClient::admin_Auth()
{
    authregForm->close();
    Admin = new admin;
    Admin->show();
}

void FunctionsForClient::statistic_received_user(QString answer)  // tato funkcia nemusi nic vracat, ale rovno spustime funkciu ktora berie nas vector ako parameter
{
    task->show_statistic(answer);
}


void FunctionsForClient::statistic_received(QString answer,QVector<UserData>& admin_users) {
    // Проверяем формат ответа
    if (!answer.startsWith("totalStatistic+&")) {
        qWarning() << "Unexpected format:" << answer;
        return;
    }

    // Удаляем префикс
    answer = answer.mid(QString("totalStatistic+&").length());

    // Разбиваем строку по символу '&'
    QStringList parts = answer.split('&');

    // Проходим по всем частям и добавляем данные о пользователях в вектор
    for (int i = 0; i + 3 < parts.size(); i += 4) {
        UserData userData;
        userData.login = parts.at(i);
        userData.task1Percentage = parts.at(i + 1).toInt();
        userData.task2Percentage = parts.at(i + 2).toInt();
        userData.task3Percentage = parts.at(i + 3).toInt();
        admin_users.append(userData);
        qDebug() << "user size: " << admin_users.size();
    }

    // Выводим данные о пользователях
    for (const auto &userData : admin_users) {
        qDebug() << "Login:" << userData.login;
        qDebug() << "Task 1 Percentage:" << userData.task1Percentage;
        qDebug() << "Task 2 Percentage:" << userData.task2Percentage;
        qDebug() << "Task 3 Percentage:" << userData.task3Percentage;
    }
}




