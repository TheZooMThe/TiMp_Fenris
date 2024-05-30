/********************************************************************************
** Form generated from reading UI file 'task_one.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK_ONE_H
#define UI_TASK_ONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_task_one
{
public:
    QLabel *label_task;
    QLabel *label;
    QPushButton *pushButton_return;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_first;
    QLabel *label_second;
    QLabel *label_accuracy;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_answer;
    QPushButton *pushButton_send;

    void setupUi(QWidget *task_one)
    {
        if (task_one->objectName().isEmpty())
            task_one->setObjectName("task_one");
        task_one->resize(600, 400);
        task_one->setStyleSheet(QString::fromUtf8("background-color: rgb(248, 255, 243);"));
        label_task = new QLabel(task_one);
        label_task->setObjectName("label_task");
        label_task->setGeometry(QRect(20, 10, 121, 21));
        label_task->setStyleSheet(QString::fromUtf8("\n"
"font: 12pt \"Segoe Print\";"));
        label = new QLabel(task_one);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 340, 141, 20));
        pushButton_return = new QPushButton(task_one);
        pushButton_return->setObjectName("pushButton_return");
        pushButton_return->setGeometry(QRect(10, 240, 121, 29));
        pushButton_return->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));
        verticalLayoutWidget = new QWidget(task_one);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 50, 281, 103));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);

        label_first = new QLabel(verticalLayoutWidget);
        label_first->setObjectName("label_first");

        verticalLayout->addWidget(label_first);

        label_second = new QLabel(verticalLayoutWidget);
        label_second->setObjectName("label_second");

        verticalLayout->addWidget(label_second);

        label_accuracy = new QLabel(verticalLayoutWidget);
        label_accuracy->setObjectName("label_accuracy");

        verticalLayout->addWidget(label_accuracy);

        horizontalLayoutWidget = new QWidget(task_one);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 150, 291, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_answer = new QLineEdit(horizontalLayoutWidget);
        lineEdit_answer->setObjectName("lineEdit_answer");
        lineEdit_answer->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"	border: 1px solid rgb(255,94,83);\n"
"	border-radius: 550px;\n"
"	background-color: rgb(255,255,255);\n"
"}"));

        horizontalLayout->addWidget(lineEdit_answer);

        pushButton_send = new QPushButton(horizontalLayoutWidget);
        pushButton_send->setObjectName("pushButton_send");
        pushButton_send->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        horizontalLayout->addWidget(pushButton_send);


        retranslateUi(task_one);

        QMetaObject::connectSlotsByName(task_one);
    } // setupUi

    void retranslateUi(QWidget *task_one)
    {
        task_one->setWindowTitle(QCoreApplication::translate("task_one", "Form", nullptr));
        label_task->setText(QCoreApplication::translate("task_one", "TextLabel", nullptr));
        label->setText(QString());
        pushButton_return->setText(QCoreApplication::translate("task_one", "Return to menu", nullptr));
        label_5->setText(QCoreApplication::translate("task_one", "equation", nullptr));
        label_first->setText(QCoreApplication::translate("task_one", "first", nullptr));
        label_second->setText(QCoreApplication::translate("task_one", "second", nullptr));
        label_accuracy->setText(QCoreApplication::translate("task_one", "accuracy", nullptr));
        pushButton_send->setText(QCoreApplication::translate("task_one", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class task_one: public Ui_task_one {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK_ONE_H
