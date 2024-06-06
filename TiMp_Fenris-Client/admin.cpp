#include "admin.h"
#include "ui_admin.h"

#include "functionsforclient.h"
#include <singletonclient.h>

#include "user_data.h"

#include <QVector>

admin::admin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::admin)
{
    ui->setupUi(this);
}

admin::~admin()
{
    delete ui;
}

QVector<UserData> admin::admin_users;

void admin::on_pushButton_show_stat_clicked()
{
    QString log = FunctionsForClient::return_login();
    qDebug() << "log: " << log;
    SingletonClient::getInstance()->send_msg_to_server_total_statistic(log);
    qDebug() << "---------------------------------admin: "<< admin_users.size();
    // qDebug() << FunctionsForClient::return_user().size();
    admin::setup_statistic(admin_users);



    //ui->pushButton_get_statistics->setVisible(false);
}

void admin::on_pushButton_filter_task_1_clicked()
{
    QString log = FunctionsForClient::return_login();
    qDebug() << "log: " << log;
    SingletonClient::getInstance()->send_msg_to_server_total_statistic(log);
    qDebug() << "---------------------------------admin: "<< admin_users.size();
    // qDebug() << FunctionsForClient::return_user().size();
    sortUsersByTask1Percentage(admin_users);
    admin::setup_statistic(admin_users);



    //ui->pushButton_get_statistics->setVisible(false);
}

void admin::on_pushButton_filter_task_2_clicked()
{
    QString log = FunctionsForClient::return_login();
    qDebug() << "log: " << log;
    SingletonClient::getInstance()->send_msg_to_server_total_statistic(log);
    qDebug() << "---------------------------------admin: "<< admin_users.size();
    // qDebug() << FunctionsForClient::return_user().size();
    sortUsersByTask2Percentage(admin_users);
    admin::setup_statistic(admin_users);



    //ui->pushButton_get_statistics->setVisible(false);
}

void admin::on_pushButton_filter_task_3_clicked()
{
    QString log = FunctionsForClient::return_login();
    qDebug() << "log: " << log;
    SingletonClient::getInstance()->send_msg_to_server_total_statistic(log);
    qDebug() << "---------------------------------admin: "<< admin_users.size();
    // qDebug() << FunctionsForClient::return_user().size();
    sortUsersByTask3Percentage(admin_users);
    admin::setup_statistic(admin_users);

    //ui->pushButton_get_statistics->setVisible(false);
}

void admin::set_textEdit(QString text)
{
    ui->textEdit->setPlainText(text);
}

void admin::setup_statistic(QVector<UserData> users)
{
    QString statistics;
    for (const UserData& user : users) {
        statistics += QString("Login: %1\nTask 1 Percentage: %2\nTask 2 Percentage: %3\nTask 3 Percentage: %4\n\n")
                          .arg(user.login)
                          .arg(user.task1Percentage)
                          .arg(user.task2Percentage)
                          .arg(user.task3Percentage);
    }
    ui->textEdit -> setPlainText(statistics);
    admin_users.clear();

}

/*
void admin::sortUsersByTask1Percentage(QVector<UserData>& admin_users) {
    std::sort(admin_users.begin(), admin_users.end(), [](const UserData &a, const UserData &b) {
        return a.task1Percentage > b.task1Percentage;
    });
}

void admin::sortUsersByTask2Percentage(QVector<UserData>& admin_users) {
    std::sort(admin_users.begin(), admin_users.end(), [](const UserData &a, const UserData &b) {
        return a.task2Percentage > b.task2Percentage;
    });
}

void admin::sortUsersByTask3Percentage(QVector<UserData>& admin_users) {
    std::sort(admin_users.begin(), admin_users.end(), [](const UserData &a, const UserData &b) {
        return a.task3Percentage > b.task3Percentage;
    });
}*/


void admin::sortUsersByTask1Percentage(QVector<UserData>& admin_users) {
    hoareSort(admin_users, 0, admin_users.size() - 1, [](const UserData& a, const UserData& b) {
        return a.task1Percentage > b.task1Percentage;
    });
}

void admin::sortUsersByTask2Percentage(QVector<UserData>& admin_users) {
    hoareSort(admin_users, 0, admin_users.size() - 1, [](const UserData& a, const UserData& b) {
        return a.task2Percentage > b.task2Percentage;
    });
}

void admin::sortUsersByTask3Percentage(QVector<UserData>& admin_users) {
    hoareSort(admin_users, 0, admin_users.size() - 1, [](const UserData& a, const UserData& b) {
        return a.task3Percentage > b.task3Percentage;
    });
}

void admin::hoareSort(QVector<UserData>& arr, int low, int high, std::function<bool(const UserData&, const UserData&)> comparator) {
    if (low < high) {
        int p = hoarePartition(arr, low, high, comparator);
        hoareSort(arr, low, p, comparator);
        hoareSort(arr, p + 1, high, comparator);
    }
}

int admin::hoarePartition(QVector<UserData>& arr, int low, int high, std::function<bool(const UserData&, const UserData&)> comparator) {
    UserData pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (comparator(arr[i], pivot));
        do {
            j--;
        } while (comparator(pivot, arr[j]));
        if (i >= j) {
            return j;
        }
        UserData temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}



