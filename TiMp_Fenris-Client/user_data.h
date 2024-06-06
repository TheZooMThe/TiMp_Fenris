#ifndef USER_DATA_H
#define USER_DATA_H

#include <QString>
#include <QDebug>

struct UserData {
    QString login;
    int task1Percentage;
    int task2Percentage;
    int task3Percentage;

    UserData() : login(""), task1Percentage(0), task2Percentage(0), task3Percentage(0) {}

    void setLogin(const QString& log) {
        login = log;
    }

    void setTask1Percentage(int percentage) {
        task1Percentage = percentage;
    }

    void setTask2Percentage(int percentage) {
        task2Percentage = percentage;
    }

    void setTask3Percentage(int percentage) {
        task3Percentage = percentage;
    }

    void print() const {
        qDebug() << "Login:" << login;
        qDebug() << "Task 1 Percentage:" << task1Percentage;
        qDebug() << "Task 2 Percentage:" << task2Percentage;
        qDebug() << "Task 3 Percentage:" << task3Percentage;
    }
};

#endif // USER_DATA_H
