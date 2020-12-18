#include <QCoreApplication>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <dbmanager.h> // https://katecpp.github.io/sqlite-with-qt/
#include <qdebug.h>
#define PORT 8089
extern int errno;
struct thread_info{
    int client;
    DbManager* dbm;
};

void* thread_func(void* client_sock)
{
    //facem castare de la void* la int pentru client
    int client= (*(int*)client_sock);
    char name[30];
    char password[30];
    bool i=false, loggedin=false;
    int cmd_ID;
    //deschidem baza de date de fiecare data
    //un user se conecteaza
    DbManager dbm("MyDB");
    //incrementam id-ul conexiunii
    dbm.connections++;
    //verificam daca user-ul este logat sau nu
    while(!loggedin){
        //asteptam o comanda
        if(read(client, &cmd_ID, 4)<=0){
            //clientul s-a deconectat
            qDebug("Client disconnected");
            close(client);
            pthread_exit(NULL);
            //inchidem conexiunea si thread-ul
        }
        //verificam ce comanda este
        switch(cmd_ID)
        {
            case 1: //login
                //citim datele de la client
                read(client,&name, 30);
                read(client,&password, 30);
                //apelam functia de verificare
                //a userului in baza de date
                if(dbm.CheckUser(name,password))
                    i=true;
                //ii trimitem clientului raspunsul
                write(client, &i, 1);
                //resetam comanda
                cmd_ID=0;
                //user-ul este logat
                loggedin=i;
                break;
            case 2://register
                //citim datele de la client
                read(client,&name, 30);
                read(client,&password, 30);
                //apelam functia de verificare
                //a userului in baza de date
                if(dbm.NewUser(name,password))
                    i=true;
                //ii trimitem clientului raspunsul
                write(client, &i, 1);
                //resetam comanda
                cmd_ID=0;
                //asteptam sa le logheze
                break;
            default: //comanda care nu este in lista
            pthread_exit(NULL);
        }
    }
    /*while(1){
        if(read(client, &cmd_ID, 4)==-1){
            perror("come on");
            close(client);
            pthread_exit(NULL);
        }
        switch(cmd_ID){
            case 1: //login
                qDebug() << "test";
                read(client,&name, 30);
                qDebug() << "idk";
                read(client,&password, 30);
                qDebug() << "idk";
                if(dbm.CheckUser(name,password)){
                    i=true;
                    qDebug() << "test1";
                }
                write(client, &i, 1);
                cmd_ID=0;
                loggedin=true;
                break;
            case 2://register
                if(read(client,&name, 30)==-1){
                    perror("1idk");
                    pthread_exit(NULL);
                }

                if(read(client,&password, 30)==-1){
                    perror("1idk");
                    pthread_exit(NULL);
                }
                if(dbm.NewUser(name,password)){
                    qDebug() << "test2";
                    i=true;
                    qDebug() << "1";
                }
                qDebug() << "2";
                write(client, &i, 1);
                qDebug() << "3";
                cmd_ID=0;
                break;
        default: perror("please work");
        }qDebug() << "69";
    }*/
    close(client);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    struct sockaddr_in server;	// structura folosita de server
    struct sockaddr_in from;
    int sd;			//descriptorul de socket
   /* crearea unui socket */
   if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
   {
       perror ("[server]Eroare la socket().\n");
       return errno;
   }

   /* pregatirea structurilor de date */
   bzero (&server, sizeof (server));
   bzero (&from, sizeof (from));

   /* umplem -structura folosita de server */
   /* stabilirea familiei de socket-uri */
   server.sin_family = AF_INET;
   /* acceptam orice adresa */
   server.sin_addr.s_addr = htonl (INADDR_ANY);
   /* utilizam un port utilizator */
   server.sin_port = htons (PORT);

   /* atasam socketul */
   if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
   {
       perror ("[server]Eroare la bind().\n");
       return errno;
   }

   /* punem serverul sa asculte daca vin clienti sa se conecteze */
   if (listen (sd, 1) == -1)
   {
       perror ("[server]Eroare la listen().\n");
       return errno;
   }
    pthread_t t_id;//pregatim o variabila
    while(1)
    {
        int* client=new int;
        unsigned int length = sizeof (from);
        printf ("[server]Asteptam la portul %d...\n",PORT);
        fflush (stdout);
        //acceptam un client sa se conecteze la server
        *client = accept(sd, (struct sockaddr *) &from, &length);
        if (*client < 0)
            {
            perror ("[server]Eroare la accept().\n");
            continue;
            }
        //cream un thread pentru clientul conectat
        if(pthread_create(&t_id,NULL,thread_func,client)){
           perror ("[thread]Eroare la pthread_create()");
           continue;
        }
    }
    /* servim in mod concurent clientii... */
//   while (1)
//   {
//       int client;
//       unsigned int length = sizeof (from);

//       printf ("[server]Asteptam la portul %d...\n",PORT);
//       fflush (stdout);

//       /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
//       client = accept(sd, (struct sockaddr *) &from, &length);

//       /* eroare la acceptarea conexiunii de la un client */
//       if (client < 0)
//       {
//           perror ("[server]Eroare la accept().\n");
//           continue;
//       }

//       int pid;
//       if ((pid = fork()) == -1) {
//           close(client);
//           continue;
//       } else if (pid > 0) {
//           // parinte
//           close(client);
//           while(waitpid(-1,NULL,WNOHANG));
//           continue;
//       } else if (pid == 0) {
//           // copil
//           close(sd);

//           /* s-a realizat conexiunea, se astepta mesajul */
//           bzero (msg, 100);
//           printf ("[server]Asteptam mesajul...\n");
//           fflush (stdout);

//           /* citirea mesajului */
//           if (read (client, msg, 100) <= 0)
//           {
//               perror ("[server]Eroare la read() de la client.\n");
//               close (client);	/* inchidem conexiunea cu clientul */
//               continue;		/* continuam sa ascultam */
//           }

//           printf ("[server]Mesajul a fost receptionat...%s\n", msg);

//           /*pregatim mesajul de raspuns */
//           bzero(msgrasp,100);
//           strcat(msgrasp,"Hello ");
//           strcat(msgrasp,msg);

//           printf("[server]Trimitem mesajul inapoi...%s\n",msgrasp);


//           /* returnam mesajul clientului */
//           if (write (client, msgrasp, 100) <= 0)
//           {
//               perror ("[server]Eroare la write() catre client.\n");
//               continue;		/* continuam sa ascultam */
//           }
//           else
//               printf ("[server]Mesajul a fost trasmis cu succes.\n");

//           /* am terminat cu acest client, inchidem conexiunea */
//           close (client);
//           exit(0);
//       }

//   }
return(a.exec());
}
