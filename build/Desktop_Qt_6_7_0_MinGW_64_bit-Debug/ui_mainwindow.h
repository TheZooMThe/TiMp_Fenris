/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_Task_1;
    QPushButton *pushButton_Task_2;
    QPushButton *pushButton_Task_3;
    QPushButton *pushButton_Stat;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(248, 255, 243);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(30, 50, 190, 261));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_Task_1 = new QPushButton(verticalLayoutWidget);
        pushButton_Task_1->setObjectName("pushButton_Task_1");
        pushButton_Task_1->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_Task_1);

        pushButton_Task_2 = new QPushButton(verticalLayoutWidget);
        pushButton_Task_2->setObjectName("pushButton_Task_2");
        pushButton_Task_2->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_Task_2);

        pushButton_Task_3 = new QPushButton(verticalLayoutWidget);
        pushButton_Task_3->setObjectName("pushButton_Task_3");
        pushButton_Task_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_Task_3);

        pushButton_Stat = new QPushButton(verticalLayoutWidget);
        pushButton_Stat->setObjectName("pushButton_Stat");
        pushButton_Stat->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"color: rgb(255, 255, 255);\n"
"font: 9pt \"Segoe Print\";"));

        verticalLayout->addWidget(pushButton_Stat);

        pushButton_4 = new QPushButton(verticalLayoutWidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 94, 83);\n"
"font: 9pt \"Segoe Print\";\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(pushButton_4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_Task_1->setText(QCoreApplication::translate("MainWindow", "Task 1 - Chord Method", nullptr));
        pushButton_Task_2->setText(QCoreApplication::translate("MainWindow", "Task 2", nullptr));
        pushButton_Task_3->setText(QCoreApplication::translate("MainWindow", "Task 3", nullptr));
        pushButton_Stat->setText(QCoreApplication::translate("MainWindow", "Stat", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
