#include "task_one.h"
#include "ui_task_one.h"

#include "functionsforclient.h"
#include <singletonclient.h>

task_one::task_one(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::task_one)
{
    ui->setupUi(this);
    task_number=0;
    ui->lineEdit_answer->setPlaceholderText("Answer");
}

task_one::~task_one()
{
    delete ui;
}

void task_one::set_task_number(int i)
{
    if (i == 1)
    {
    this->task_number = i;
    ui->label_5->setText("Equation: x * x + 5 * x - 2");
    ui->label->setText("");
    ui->lineEdit_answer->setText("");
    ui->label_task->setText("Task "+ QString::number(task_number) + " chord");

    ui->label_first->setVisible(true);
    ui->label_second->setVisible(true);
    ui->label_accuracy->setVisible(true);
    ui->label_5->setVisible(true);
    ui->pushButton_send->setVisible(true);
    ui->lineEdit_answer->setVisible(true);
    ui->label->setVisible(true);

    int value1= QRandomGenerator::global()->bounded(-20, 0);
    QString aString1 = QString::number(value1);
    ui->label_first->setText("First guess: " + aString1);

    int value2= QRandomGenerator::global()->bounded(1, 20);
    QString aString2 = QString::number(value2);
    ui->label_second->setText("Second guess: " + aString2);
    ui->label_accuracy->setText("Accuracy (epsilon): 0.0001"); // treba este niekam pridat priklad ako taky, plus prerobit to na labels
    }

    else if (i == 2)
    {
        this->task_number = i;
        ui->label_task->setText("Task "+ QString::number(task_number));
        ui->label_first->setVisible(false);
        ui->label_second->setVisible(false);
        ui->label_accuracy->setVisible(false);
        ui->label_5->setVisible(false);
        ui->pushButton_send->setVisible(false);
        ui->lineEdit_answer->setVisible(false);
        ui->label->setVisible(false);
    }

    else if (i == 3)
    {
        this->task_number = i;
        ui->label_task->setText("Task "+ QString::number(task_number));
        ui->label_first->setVisible(false);
        ui->label_second->setVisible(false);
        ui->label_accuracy->setVisible(false);
        ui->label_5->setVisible(false);
        ui->pushButton_send->setVisible(false);
        ui->lineEdit_answer->setVisible(false);
        ui->label->setVisible(false);
    }
}

void task_one::set_task_stat()
{
    ui->label_task->setText("Statistics");
    ui->label_first->setVisible(false);
    ui->label_second->setVisible(false);
    ui->label_accuracy->setVisible(false);
    ui->label_5->setVisible(false);
    ui->pushButton_send->setVisible(false);
    ui->lineEdit_answer->setVisible(false);
    ui->label->setVisible(false);

}

void task_one::show_statistic(QString answer)
{
    QStringList parts = answer.split("&");
    ui->label_first->setVisible(true);
    ui->label_second->setVisible(true);
    ui->label_accuracy->setVisible(true);
    ui->label_first->setText("Task 1: " + parts[2] + "%");
    ui->label_second->setText("Task 2: " + parts[3] + "%");
    ui->label_accuracy->setText("Task 3: " + parts[4] + "%");

}


void task_one::on_pushButton_send_clicked()  // sem sa treba pozriet a preverit ako to funguje
{
    QString first = ui->label_first->text();
    QStringList fir = first.split(" ");
    QString first_guess = fir[2];
    QString second = ui->label_second->text();
    QStringList sec = second.split(" ");
    QString second_guess = sec[2];
    QString answer = ui->lineEdit_answer->text();
    QString task_to_text = QString::number(task_number);
    SingletonClient::getInstance()->send_msg_to_server_check(task_to_text, first_guess, second_guess, answer);
}

void task_one::on_pushButton_return_clicked()
{
    FunctionsForClient::return_to_menu();
}

void task_one::check_plus(int i)
{
    if (i == 1){
    ui->label->setText("Good boy!");
    }
    else
    {
    ui->label->setText("Try again!");
    }
}
