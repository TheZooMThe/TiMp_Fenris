#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H
#include <QWidget>
#include "admin.h"


namespace Ui {
class AuthRegForm;
}

class AuthRegForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthRegForm(QWidget *parent = nullptr);
    ~AuthRegForm();

private slots:
    void on_pushButton_auth_clicked();

    void on_pushButton_email_clicked();

    void on_pushButton_registration_clicked();

    void on_pushButton_admin_clicked();

    void on_pushButton_adminlogin_clicked();


    void handleAuthResponse(const QString& response);

private:
    Ui::AuthRegForm *ui;
};

#endif // AUTHREGFORM_H
