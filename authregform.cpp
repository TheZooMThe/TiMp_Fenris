#include "authregform.h"
#include "ui_authregform.h"

#include "functionsforclient.h"
#include <singletonclient.h>

AuthRegForm::AuthRegForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthRegForm)
{
    ui->setupUi(this);
    ui->label_email->setVisible(false);
    ui->lineEdit_email->setVisible(false);
    ui->pushButton_registration->setVisible(false);
}

AuthRegForm::~AuthRegForm()
{
    delete ui;
}

void AuthRegForm::on_pushButton_auth_clicked()
{
    QString username = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    SingletonClient::getInstance()->send_msg_to_server(username, password);
}

void AuthRegForm::on_pushButton_registration_clicked()
{
    QString username = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    QString email = ui->lineEdit_email->text();
    SingletonClient::getInstance()->send_msg_to_server_reg(username, password, email);
}

void AuthRegForm::test_function()
{
    bool flag = ui->label_email->isVisible();


    ui->label_email->setVisible(!flag);
    ui->lineEdit_email->setVisible(!flag);
    ui->pushButton_registration->setVisible(!flag);
    ui->pushButton_auth->setVisible(flag);
}


void AuthRegForm::on_pushButton_email_clicked()
{
    bool flag = ui->label_email->isVisible();


    ui->label_email->setVisible(!flag);
    ui->lineEdit_email->setVisible(!flag);
    ui->pushButton_registration->setVisible(!flag);
    ui->pushButton_auth->setVisible(flag);

}
