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
#include <QtWidgets/QTextEdit>
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
    QLabel *label_9;
    QWidget *page2;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton4;
    QPushButton *pushButton3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton5;
    QLineEdit *lineEdit_3;
    QTextEdit *textEdit;
    QPushButton *pushButton6;
    QPushButton *pushButton7;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QTreeWidget *treeWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Client_interface)
    {
        if (Client_interface->objectName().isEmpty())
            Client_interface->setObjectName(QString::fromUtf8("Client_interface"));
        Client_interface->resize(1187, 631);
        Client_interface->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(Client_interface);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1191, 611));
        stackedWidget->setAutoFillBackground(false);
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
        label_9 = new QLabel(page1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(360, 200, 371, 16));
        stackedWidget->addWidget(page1);
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        pushButton1 = new QPushButton(page2);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setGeometry(QRect(320, 160, 41, 24));
        pushButton2 = new QPushButton(page2);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(320, 210, 41, 24));
        pushButton4 = new QPushButton(page2);
        pushButton4->setObjectName(QString::fromUtf8("pushButton4"));
        pushButton4->setGeometry(QRect(370, 260, 41, 24));
        pushButton3 = new QPushButton(page2);
        pushButton3->setObjectName(QString::fromUtf8("pushButton3"));
        pushButton3->setGeometry(QRect(320, 260, 41, 24));
        lineEdit = new QLineEdit(page2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(32, 160, 261, 24));
        lineEdit_2 = new QLineEdit(page2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(32, 210, 261, 24));
        label_3 = new QLabel(page2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 140, 58, 16));
        label_4 = new QLabel(page2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 190, 58, 16));
        label_5 = new QLabel(page2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(780, 100, 91, 16));
        pushButton5 = new QPushButton(page2);
        pushButton5->setObjectName(QString::fromUtf8("pushButton5"));
        pushButton5->setGeometry(QRect(420, 260, 41, 24));
        lineEdit_3 = new QLineEdit(page2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(30, 260, 261, 24));
        textEdit = new QTextEdit(page2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(30, 360, 431, 211));
        pushButton6 = new QPushButton(page2);
        pushButton6->setObjectName(QString::fromUtf8("pushButton6"));
        pushButton6->setGeometry(QRect(340, 300, 41, 24));
        pushButton7 = new QPushButton(page2);
        pushButton7->setObjectName(QString::fromUtf8("pushButton7"));
        pushButton7->setGeometry(QRect(390, 300, 41, 24));
        label_6 = new QLabel(page2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 40, 1131, 16));
        label_7 = new QLabel(page2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(50, 240, 58, 16));
        label_8 = new QLabel(page2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(50, 330, 58, 16));
        treeWidget = new QTreeWidget(page2);
        QFont font;
        font.setPointSize(10);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("File"));
        __qtreewidgetitem->setFont(0, font);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(520, 120, 631, 451));
        treeWidget->header()->setMinimumSectionSize(100);
        treeWidget->header()->setDefaultSectionSize(250);
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
        Client_interface->setWindowTitle(QCoreApplication::translate("Client_interface", "MyFileTransferProtocol", nullptr));
        pushButton->setText(QCoreApplication::translate("Client_interface", "Login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Client_interface", "Register", nullptr));
        label->setText(QCoreApplication::translate("Client_interface", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("Client_interface", "Password", nullptr));
        label_9->setText(QString());
        pushButton1->setText(QCoreApplication::translate("Client_interface", "->", nullptr));
        pushButton2->setText(QCoreApplication::translate("Client_interface", "<-", nullptr));
        pushButton4->setText(QCoreApplication::translate("Client_interface", "NF", nullptr));
        pushButton3->setText(QCoreApplication::translate("Client_interface", "ND", nullptr));
        label_3->setText(QCoreApplication::translate("Client_interface", "Client", nullptr));
        label_4->setText(QCoreApplication::translate("Client_interface", "Server", nullptr));
        label_5->setText(QCoreApplication::translate("Client_interface", "Server status", nullptr));
        pushButton5->setText(QCoreApplication::translate("Client_interface", "X", nullptr));
        pushButton6->setText(QCoreApplication::translate("Client_interface", "CD", nullptr));
        pushButton7->setText(QCoreApplication::translate("Client_interface", "Back", nullptr));
        label_6->setText(QCoreApplication::translate("Client_interface", "Location", nullptr));
        label_7->setText(QCoreApplication::translate("Client_interface", "Name", nullptr));
        label_8->setText(QCoreApplication::translate("Client_interface", "Content", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("Client_interface", "Size", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client_interface: public Ui_Client_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_INTERFACE_H
