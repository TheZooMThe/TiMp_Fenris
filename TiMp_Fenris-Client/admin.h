#ifndef ADMIN_H
#define ADMIN_H
#include <QTextEdit>

#include "user_data.h"

#include <QWidget>
#include <QtAlgorithms>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    void setup_statistic(QVector<UserData> users);
    void set_textEdit(QString text);

    static QVector<UserData> admin_users;
    ~admin();

private slots:
    void on_pushButton_filter_task_1_clicked();
    void on_pushButton_filter_task_2_clicked();
    void on_pushButton_filter_task_3_clicked();
    void on_pushButton_show_stat_clicked();


private:
    Ui::admin *ui;
    void sortUsersByTask1Percentage(QVector<UserData>& admin_users);
    void sortUsersByTask2Percentage(QVector<UserData>& admin_users);
    void sortUsersByTask3Percentage(QVector<UserData>& admin_users);
    void hoareSort(QVector<UserData>& arr, int low, int high, std::function<bool(const UserData&, const UserData&)> comparator);
    int hoarePartition(QVector<UserData>& arr, int low, int high, std::function<bool(const UserData&, const UserData&)> comparator);
};

#endif // ADMIN_H
