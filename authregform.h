#ifndef AUTHREGFORM_H
#define AUTHREGFORM_H
#include <QWidget>


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

    void test_function();

private:
    Ui::AuthRegForm *ui;
};

#endif // AUTHREGFORM_H
