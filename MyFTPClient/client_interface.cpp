#include "client_interface.h"
#include "ui_client_interface.h"
#include <QtCore>
#include <QtGui>
#include "commands.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <QDir>
#include <QList>
#include <dirent.h>
#include <sys/stat.h>
#define IP "192.168.1.103"
extern int errno;
int port = 8089;
bool conn(int* sd){
    // descriptorul de socket
    struct sockaddr_in server;	// structura folosita pentru conectare
    /* cream socketul */
    if ((*sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
      {
        perror ("Eroare la socket().\n");
      }
    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;

    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(IP);
    /* portul de conectare */
    server.sin_port = htons (port);
    /* ne conectam la server */
    if (connect (*sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
      {
        perror ("[client]Eroare la connect().\n");
        return false;
      }
    qDebug() << "connect ok";
    return true;
}
Client_interface::Client_interface(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client_interface)
{
    if(conn(&sd))
        ui->setupUi(this);
}

Client_interface::~Client_interface()
{
    delete ui;
}

void Client_interface::on_pushButton_clicked()
{//butonul de login este apasat
    //iau datele din casturele QLineEdit
    QString user = ui->username->text();
    QString password = ui->password->text();
    //execut comanda de login
    if(!login(sd,user, password))
        //daca nu reuseste sa se logheze
        perror("[login]");
    else
    {
        //pune numele fisierelor in treewidget
        displayTree(user);
        //schimbam pagina
        ui->stackedWidget->setCurrentWidget(ui->page2);
    }
}

void Client_interface::on_pushButton_2_clicked()
{//butonul de register este apasat
    //iau datele din casturele QLineEdit
    QString user = ui->username->text();
    QString password = ui->password->text();
    //execut comanda de register
    if(!reg(sd, user, password))
        //daca nu reuseste sa se inregistreze
        perror("[register]");
}

void Client_interface::on_pushButton_3_clicked()
{

}

void Client_interface::on_pushButton_4_clicked()
{

}

void Client_interface::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{

}

void Client_interface::on_treeWidget_2_itemClicked(QTreeWidgetItem *item, int column)
{

}

void Client_interface::on_pushButton_7_clicked()
{

}

void Client_interface::on_pushButton_5_clicked()
{

}

void Client_interface::on_pushButton_6_clicked()
{

}

void Client_interface::on_pushButton_8_clicked()
{

}

void fnd(char *path, char* name, QTreeWidgetItem* item)
{
    DIR *dir;
    struct dirent *de;
    struct stat st;
    stat(path, &st);
    QList<QString> list;
    if (S_ISDIR(st.st_mode))
    {
        if (NULL != (dir = opendir(path)))
        {
            while (NULL != (de = readdir(dir)))
            {
                if (strcmp(de->d_name, ".")&&strcmp(de->d_name, ".."))
                {
                    struct stat s;
                    char* newpath= new char[100];
                    sprintf(newpath,"%s/%s",path,de->d_name);
                    qDebug ("sarmale");
                    stat(newpath, &s);
                    QTreeWidgetItem* child = new QTreeWidgetItem;
                    child->setText(0,de->d_name);
                    child->setText(1,QString::number(s.st_size/1024));
                    item->addChild(child);

                    sprintf(newpath, "%s/%s", path, de->d_name);
                    fnd(newpath, (de->d_name), child);
                    //sprintf(name, "%s/%s", path, de->d_name);
                }
            }
            closedir(dir);
        }
    }

}

void Client_interface::displayTree(QString username)
{
    ui->treeWidget->setColumnCount(2);
    QStringList header;
    header << "Name" << "size";
    ui->treeWidget->setHeaderLabels(header);
    ui->treeWidget_2->setHeaderLabels(header);
    std::string text_current_path = (QDir::currentPath().toStdString()/*+'/'+username.toStdString()*/);
    const char* current_path = text_current_path.c_str();
    DIR *dir;
    struct dirent *de;
    struct stat st;
    stat(current_path, &st);
    if (S_ISDIR(st.st_mode))
    {
        if (NULL != (dir = opendir(current_path)))
        {
            while (NULL != (de = readdir(dir)))
            {
                if (strcmp(de->d_name, ".")&&strcmp(de->d_name, ".."))
                {
                    qDebug ("BRUH   ");
                    QTreeWidgetItem* nm = new QTreeWidgetItem;
                    nm->setText(0,de->d_name);
                    ui->treeWidget->addTopLevelItem(nm);
                    struct stat s;
                    char* newpath= new char[100];
                    sprintf(newpath,"%s/%s",current_path,de->d_name);
                    qDebug ("sarmale");
                    stat(newpath, &s);
                    nm->setText(1,QString::number(s.st_size/1024));
                    qDebug(de->d_name);
                    if(S_ISDIR(s.st_mode)){
                        qDebug(de->d_name);
                        fnd((char*)newpath, (char*)(de->d_name),nm);
                    }//sprintf(name, "%s/%s", path, de->d_name);
                    qDebug("asdasdads");
                }
            }
            closedir(dir);
        }
    }
}
