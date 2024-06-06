#ifndef TASK_ONE_H
#define TASK_ONE_H

#include <QWidget>

namespace Ui {
class task_one;
}

class task_one : public QWidget
{
    Q_OBJECT

public:
    explicit task_one(QWidget *parent = nullptr);
    ~task_one();
    void set_task_number(int i); // v podstate budeme len hladat cislo tasku a potom budeme ukazovat day text v sulade s zadanim
    void set_task_stat();
    void check_plus(int i);
    void show_statistic(QString answer);


private slots:
    void on_pushButton_send_clicked();
    void on_pushButton_return_clicked();

private:
    int task_number;
    Ui::task_one *ui;
};

#endif // TASK_ONE_H
