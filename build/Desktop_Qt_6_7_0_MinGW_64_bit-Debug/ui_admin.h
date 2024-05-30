/********************************************************************************
** Form generated from reading UI file 'admin.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMIN_H
#define UI_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_admin
{
public:
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QPushButton *pushButton_filter_task_1;
    QPushButton *pushButton_filter_task_2;
    QPushButton *pushButton_filter_task_3;
    QTextEdit *textEdit;
    QPushButton *pushButton_show_stat;

    void setupUi(QWidget *admin)
    {
        if (admin->objectName().isEmpty())
            admin->setObjectName("admin");
        admin->resize(600, 400);
        admin->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 255, 243);"));
        label = new QLabel(admin);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 261, 20));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe Print\";"));
        verticalLayoutWidget = new QWidget(admin);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(390, 70, 168, 163));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe Print\";"));

        verticalLayout->addWidget(label_2);

        pushButton_filter_task_1 = new QPushButton(verticalLayoutWidget);
        pushButton_filter_task_1->setObjectName("pushButton_filter_task_1");
        pushButton_filter_task_1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_filter_task_1);

        pushButton_filter_task_2 = new QPushButton(verticalLayoutWidget);
        pushButton_filter_task_2->setObjectName("pushButton_filter_task_2");
        pushButton_filter_task_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_filter_task_2);

        pushButton_filter_task_3 = new QPushButton(verticalLayoutWidget);
        pushButton_filter_task_3->setObjectName("pushButton_filter_task_3");
        pushButton_filter_task_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_filter_task_3);

        textEdit = new QTextEdit(admin);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(40, 80, 311, 291));
        pushButton_show_stat = new QPushButton(admin);
        pushButton_show_stat->setObjectName("pushButton_show_stat");
        pushButton_show_stat->setGeometry(QRect(390, 250, 166, 35));
        pushButton_show_stat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        retranslateUi(admin);

        QMetaObject::connectSlotsByName(admin);
    } // setupUi

    void retranslateUi(QWidget *admin)
    {
        admin->setWindowTitle(QCoreApplication::translate("admin", "Form", nullptr));
        label->setText(QCoreApplication::translate("admin", "Administrator interface", nullptr));
        label_2->setText(QCoreApplication::translate("admin", "       Filter", nullptr));
        pushButton_filter_task_1->setText(QCoreApplication::translate("admin", "Task 1", nullptr));
        pushButton_filter_task_2->setText(QCoreApplication::translate("admin", "Task 2", nullptr));
        pushButton_filter_task_3->setText(QCoreApplication::translate("admin", "Task 3", nullptr));
        pushButton_show_stat->setText(QCoreApplication::translate("admin", "SHOW STAT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class admin: public Ui_admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMIN_H
