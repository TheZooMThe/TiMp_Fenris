#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "functionsforclient.h"
#include <singletonclient.h>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_Task_1_clicked()
{
    FunctionsForClient::task_clicked(1);
}

void MainWindow::on_pushButton_Task_2_clicked()
{
    FunctionsForClient::task_clicked(2);
}

void MainWindow::on_pushButton_Task_3_clicked()
{
    FunctionsForClient::task_clicked(3);
}

void MainWindow::on_pushButton_Stat_clicked()
{
    FunctionsForClient::stat_clicked();
    QString log = FunctionsForClient::return_login();
    SingletonClient::getInstance()->send_msg_to_server_stat(log);
}
