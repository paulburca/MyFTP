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
#include <string.h>
#define IP "192.168.1.102"
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
    bool i;
    if(conn(&sd)){
        read(sd,&i,1);
        ui->setupUi(this);
        if(!i){
            ui->label_9->setText("The IP you are using is blacklisted, sorry :(");
        }
    }
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
   else{
        strcpy(where,"~");
        ui->label_6->setText(where);
        //obtinem lista de fisiere din fisierul actual
        displayTree();
        //schimbam pagina
       ui->stackedWidget->setCurrentWidget(ui->page2);
            qDebug()<<"1";
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


void Client_interface::displayTree()
{
    int l=0;
    char str[PATH_MAX];
    if(read(sd,&l, 4)<=0)
        perror("[cliread]");
    read(sd,str,l);
    str[l]='\0';
    l=0;
    ui->treeWidget->clear();
    l=strlen(str);
    if (l)
    {
        char *q;
        q = strtok(str, "\n");
        while (q)//bucati de cod despartite de '\n'
        {
            QTreeWidgetItem* nm = new QTreeWidgetItem;
            char *p;
            p=strchr(q,'|');
            strncpy(p,"",1);
            //punem partea dinaintea lui "|" (numele fisierului)
            nm->setText(0,q);
            p=p+1;
            //punem partea de dupa "|" (size-ul fisierului / daca este director sau nu)
            nm->setText(1,p);
            ui->treeWidget->addTopLevelItem(nm);
            q=p;
            q = strtok(NULL, "\n");
        }
    }
}
void Client_interface::on_pushButton1_clicked()
{//transfer client-server
    QString client = ui->lineEdit->text();
    struct stat st;
    stat(client.toStdString().c_str(),&st);
    if(!S_ISDIR(st.st_mode)){
        if(!transfer_to(sd,client))//verificam daca s-a reusit transferul
            perror("[transfer_to]");
     else displayTree();//actualizam lista de fisiere
    }
}

void Client_interface::on_pushButton2_clicked()
{//transfer server-client
    QString client = ui->lineEdit->text();
    QString server = ui->lineEdit_2->text();
    if(!transfer_from(sd,server, client))//verificam daca s-a reusit transferul
            perror("[transfer_from]");
}

void Client_interface::on_pushButton3_clicked()
{//newfolder server
    QString name = ui->lineEdit_3->text();
    if(!create_dir(sd, name))//verificam daca s-a creat un folder
            perror("[newfolder]");
    else displayTree();//actualizam lista de fisiere
}

void Client_interface::on_pushButton4_clicked()
{//newfile server
    QString name = ui->lineEdit_3->text();
    QString content = ui->textEdit->toPlainText();
    if(!create_file(sd, name, content))//verificam daca s-a creat noul fisier
        perror("[newfile]");
    else displayTree();//actualizam lista de fisiere
}

void Client_interface::on_pushButton5_clicked()
{// delete
    QString server = ui->lineEdit_3->text();
    if(!deleter(sd,server))//verificam daca fisierul/documentul a fost sters
        perror("[deleter]");
    else displayTree();//actualizam lista de fisiere
}

void Client_interface::on_pushButton6_clicked()
{// cd
    QString loc = ui->lineEdit_3->text();
    if(!cd(sd,loc))
        perror("[cd]");
    else {
        sprintf(where,"%s/%s",where,loc.toStdString().c_str());//schimbam locatia actuala
        ui->label_6->setText(where);//punem noua locatie intr-un label
        displayTree();//actualizam lista de fisiere
    }
}

void Client_interface::on_pushButton7_clicked()
{// back
    if(strcmp(ui->label_6->text().toStdString().c_str(),"~")){
        if(!bk(sd))
            perror("[bk]");
        else {
            strcpy(strrchr(where,'/'),"");//trecem la locatia anterioara
            ui->label_6->setText(where);//punem noua locatie intr-un label
            displayTree();//actualizam lista de fisiere
        }
    }
}
