/********************************************************************************
** Form generated from reading UI file 'client_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_INTERFACE_H
#define UI_CLIENT_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client_interface
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *username;
    QLineEdit *password;
    QWidget *page2;
    QTreeWidget *treeWidget;
    QTreeWidget *treeWidget_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client_interface)
    {
        if (Client_interface->objectName().isEmpty())
            Client_interface->setObjectName(QString::fromUtf8("Client_interface"));
        Client_interface->resize(1187, 631);
        centralwidget = new QWidget(Client_interface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1191, 611));
        page1 = new QWidget();
        page1->setObjectName(QString::fromUtf8("page1"));
        pushButton = new QPushButton(page1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 360, 80, 24));
        pushButton_2 = new QPushButton(page1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(610, 360, 80, 24));
        label = new QLabel(page1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(360, 230, 141, 31));
        label_2 = new QLabel(page1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(360, 300, 58, 16));
        username = new QLineEdit(page1);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(360, 260, 371, 24));
        password = new QLineEdit(page1);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(360, 320, 371, 24));
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        treeWidget = new QTreeWidget(page2);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(20, 100, 531, 401));
        treeWidget_2 = new QTreeWidget(page2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem);
        treeWidget_2->setObjectName(QString::fromUtf8("treeWidget_2"));
        treeWidget_2->setGeometry(QRect(610, 100, 551, 401));
        pushButton_3 = new QPushButton(page2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(510, 70, 41, 24));
        pushButton_4 = new QPushButton(page2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(610, 70, 41, 24));
        pushButton_5 = new QPushButton(page2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(460, 70, 41, 24));
        pushButton_6 = new QPushButton(page2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(660, 70, 41, 24));
        pushButton_7 = new QPushButton(page2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(410, 70, 41, 24));
        pushButton_8 = new QPushButton(page2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(710, 70, 41, 24));
        stackedWidget->addWidget(page2);
        Client_interface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Client_interface);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1187, 21));
        Client_interface->setMenuBar(menubar);
        statusbar = new QStatusBar(Client_interface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Client_interface->setStatusBar(statusbar);

        retranslateUi(Client_interface);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Client_interface);
    } // setupUi

    void retranslateUi(QMainWindow *Client_interface)
    {
        Client_interface->setWindowTitle(QCoreApplication::translate("Client_interface", "Client_interface", nullptr));
        pushButton->setText(QCoreApplication::translate("Client_interface", "Login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Client_interface", "Register", nullptr));
        label->setText(QCoreApplication::translate("Client_interface", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("Client_interface", "Password", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("Client_interface", "3", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("Client_interface", "2", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("Client_interface", "1", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_2->headerItem();
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("Client_interface", "3", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("Client_interface", "2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Client_interface", "->", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Client_interface", "<-", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Client_interface", "X", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Client_interface", "X", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Client_interface", "N", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Client_interface", "N", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client_interface: public Ui_Client_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_INTERFACE_H
