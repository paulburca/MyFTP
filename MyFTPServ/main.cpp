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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <QDir>
#include <math.h>
#include <arpa/inet.h>
#define PORT 8089
extern int errno;
double powmod(double a, double b, double modd)
{
    double p = a;
    for (int i = 1; i < b; i++)
    {
        a = fmod((a * p), modd);
    }
    return a;
}
std::string dec(std::string mesaj){
    std::string decv="";
    int d = 43787;//cheie de decriptare
    int n = 200099;//modulo
    char* msg=&mesaj[0];
    char* cha = strtok(msg, "|");//mesaj=caracter_criptat1|caracter_criptat2|...
    while (cha)
    {
        double c = atof(cha);
        // Decryption m = (c ^ d) % n
        double m = powmod(c, d, n);
        m = fmod(m, n);

        char ch[2] = {(char)m};
        std::string chr=ch;
        decv = decv + chr;
        cha = strtok(NULL, "|");
    }
    qDebug("%s",decv.c_str());
    return decv;
}
void recfind(char *path, char* str)
{
    DIR *dir;
    struct dirent *de;
    char name[PATH_MAX];
    struct stat st;
    stat(path, &st);

    if (!S_ISDIR(st.st_mode))//nu e director
    {

        strcat(str,(const char*) (strrchr(path,'/')+1));
        strcat(str, "\n");
    }
    else //director
    {
        if (NULL != (dir = opendir(path)))//dechidem diectorul
        {
            while (NULL != (de = readdir(dir)))//citim fisierele din director
            {
                if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) // excludem "." si ".."
                {
                    char temp[1000];
                    sprintf(name, "%s", de->d_name);
                    sprintf(temp,"%s/%s",path,name);
                    strcat(str,(const char*) name);
                    strncat(str,"|",1);
                    stat(temp,&st);
                    int i = st.st_size;
                    if(!S_ISDIR(st.st_mode))
                        sprintf(temp,"%d",i);
                    else
                         sprintf(temp,"Dir");
                    strcat(str,temp);
                    strcat(str, "\n");
                    //fisier1|size\n fisier2|size\n director|Dir\n...
                }
            }
            closedir(dir);
        }
    }
}
void findfiles(int client, char loc[PATH_MAX]){//executam recfind si punem in loc rezultatul
    char str[PATH_MAX]="";
    int len=0;
    recfind(loc,str);//obstinem un string cu date despre fisierele si directoarele din fisierul actual
    len=strlen(str);
    if(write(client,&len,4)<=0)//trimitem lungimea string-ului
        perror("[srvlen]");
    write(client, str, len);//trimitem string-ul
}
void sender(int sd, int chunk, const char* data){
    int sent = 0;
    do{
        int value;
        value=write(sd,data+sent,chunk-sent);
        sent+=value;
    }while(sent < chunk);
}
void getter(int sd, int chunk, char* data){
    int sent = 0;
    do{
        int value;
        value=read(sd,data+sent,chunk-sent);
        sent+=value;
    }while(sent < chunk);
}
pthread_mutex_t lock;
void* thread_func(void* client_sock)
{
    //facem castare de la void* la int pentru client
    int client= (*(int*)client_sock);
    delete (int*)client_sock;
    char name[1000];
    char password[1000];
    char temp[PATH_MAX];
    bool i=false, loggedin=false;
    std::string ch;
    int cmd_ID,len=0;
    //deschidem baza de date de fiecare data
    //un user se conecteaza
    DbManager dbm("MyDB");
    //incrementam id-ul conexiunii
    pthread_mutex_lock(&lock);
    dbm.connections++;
    pthread_mutex_unlock(&lock);
    QDir dir;
    char loc[PATH_MAX]="";
    strcpy(loc,dir.absolutePath().toStdString().c_str());
    //verificam daca user-ul este logat sau nu
    while(!loggedin){
        //asteptam o comanda
        if(read(client, &cmd_ID, 4)<=0){
            //clientul s-a deconectat
            close(client);
            pthread_detach(pthread_self());
            pthread_exit(NULL);
            //inchidem conexiunea si thread-ul
        }
        i=false;
        //verificam ce comanda este
        switch(cmd_ID)
        {
            case 1: //login
                //citim datele de la client
                read(client,&len,4);
                read(client,&name, len);
                //decriptam numele
                ch=(dec(name)+'\0');
                strcpy(name,ch.c_str());
                read(client,&len,4);
                read(client,&password, len);
                //decriptam parola
                ch=(dec(password)+'\0');
                strcpy(password,ch.c_str());
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
                memset(name,0,1000);
                memset(password,0,1000);
                read(client,&len,4);
                read(client,&name, len);
                //decriptam numele
                ch=(dec(name)+'\0');
                strcpy(name,ch.c_str());
                read(client,&len,4);
                read(client,&password, len);
                //decriptam parola
                ch=(dec(password)+'\0');
                strcpy(password,ch.c_str());
                //apelam functia de verificare
                //a userului in baza de date
                if(dbm.NewUser(name,password)){
                    i=true;
                    sprintf(temp,"%s/Files/%s",loc,name);
                    mkdir(temp,0777);
                }
                //ii trimitem clientului raspunsul
                write(client, &i, 1);
                //resetam comanda
                cmd_ID=0;
                //asteptam sa le logheze
                break;
            default: //comanda care nu este in lista
            perror("Unknown command");
            pthread_detach(pthread_self());
            pthread_exit(NULL);
        }
    }
    //char str[PATH_MAX]="";
    sprintf(loc,"%s/Files/%s",loc,name);
    int l=0;
    char init_loc[PATH_MAX];
    strcpy(init_loc,loc);
    //init_loc salveaza locatia initiala - scop de a limita parcurgerea prin fisiere
    findfiles(client, loc);
    char location[PATH_MAX];
    char content[PATH_MAX];
    int fd;
    struct stat st;
    while(1){
        if(read(client, &cmd_ID, 4)<=0){
            //clientul s-a deconectat
            close(client);
            pthread_detach(pthread_self());
            pthread_exit(NULL);
            //inchidem conexiunea si thread-ul
        }
        i=false;
         switch(cmd_ID){
        case 3: //transfer server-client
            read(client, &len, 4);
            read(client,location, len);//obtinem numele fisierului de transferat
            location[len]='\0';
            sprintf(temp,"%s/%s",loc,location); //pune in temp adresa completa a fisierului

            if(stat(temp,&st)==0&&!S_ISDIR(st.st_mode))
                i=true;
            write(client,&i, 1);
            if(!i)
                break;
            i=false;
            fd=open(temp,O_RDONLY); //dechidem fisierul
            //citim in unitati de 4096 bytes fisierul si transmitem la client
            l=read(fd,content,4096);
            write(client, &l, 4);
            len=0;
            while(l==4096){
                sender(client, 4096, content);
                memset(content,0,4096);
                l=read(fd, content,4096);
                write(client,&l,4);
            }
            sender(client, l,content);
            if(close(fd)==-1)
                perror("[close]");
            else i=true;//true daca s-a reusit
            read(client, &i, 1);
            cmd_ID=0;
            break;
        case 4: //transfer client-server
            read(client,&len, 4);
            read(client,location,len);
            location[len]='\0';
            sprintf(temp,"%s/%s",loc,location);
            fd=open(temp,O_WRONLY | O_CREAT, 0777);
            //citim in unitati de 4096 bytes de la client si scriem in fisier
            read(client,&l,4);
            len=0;
            while(l==4096){
                getter(client,4096,content);
                write(fd,content,4096);
                memset(content,0,4096);
                read(client,&l,4);
            }
            getter(client,l,content);
            write(fd,content,l);
            if(close(fd)==-1)
                perror("[close]");
            else i=true;
            write(client, &i, 1);
            memset(content,0,4096);
            if(i)findfiles(client,loc);//actualizam lista cu fisiere
            cmd_ID=0;
            break;
        case 5: //delete server
            read(client, &len, 4);
            read(client, location,len);
            location[len]='\0';
            sprintf(temp,"%s/%s", loc, location);
            stat(temp,&st);
            //vedem daca fisierul este director sau nu si aplicam actiunile de stergere specifice
            if(S_ISDIR(st.st_mode)){
                if(!rmdir(temp))
                    i=true;
                else i=false;
            }
            else {
                if(!remove(temp))
                    i=true;
                else i=false;
            }
            write(client, &i, 1);//trimitem raspunsul la client
            if(i)findfiles(client, loc);//actualizam lista cu fisiere
            cmd_ID=0;
            break;
        case 6: //create file
            read(client, &len, 4);
            read(client, location,len);
            location[len]='\0';
            //temp = adresa completa a fisierului
            sprintf(temp,"%s/%s",loc,location);
            fd=open(temp,O_WRONLY | O_CREAT, 0777);
            //citim in unitati de 4096 bytes de la client si scriem in fisier
            read(client,&l,4);
            len=0;
            while(l==4096){
                getter(client,4096,content);
                write(fd,content,4096);
                memset(content,0,4096);
                read(client,&l,4);
            }
            getter(client,l,content);
            write(fd,content,l);
            if(close(fd)==-1)
                perror("[close]");
            else i=true;
            write(client, &i, 1);
            if(i)findfiles(client,loc);
            close(fd);
            cmd_ID=0;
            break;
        case 7: //create dir
            read(client, &len, 4);
            read(client, location,len);
            location[len]='\0';
            sprintf(temp,"%s/%s",loc, location);//pune in temp adresa completa a directorului
            if (stat(temp, &st) == -1){
                if(mkdir(temp, 0700))//cream directorul
                    i=false;
                else i=true;
            }
            write(client,&i, 1);//trimitem raspuns la client
            if(i)findfiles(client,loc);//actualizam lista de fisiere
            cmd_ID=0;
            break;
        case 8://cd
            read(client,&len,4);
            read(client,location,len);
            location[len]='\0';
            if((int)strlen(loc)+1!=sprintf(loc,"%s/%s",loc,location))//actualizam adresa
            {
                //veficam daca este intradevar director sau nu
                //in caz contrar, readucem adresa la pozitia initiala
                if(stat(loc,&st)==0&&S_ISDIR(st.st_mode))
                    i=true;
                else {
                    strcpy(strrchr(loc,'/'),"");
                }
            }
            write(client,&i,1);
            if(i)
                findfiles(client,loc);
            cmd_ID=0;
            break;
        case 9://back
            //verificam daca adresa actuala este cea initiala si nu continuam in acest caz
            if(strcmp(loc,init_loc)){
                if(strcpy(strrchr(loc,'/'),""))//aducem adresa la pozitia anterioara
                    i=true;
                write(client,&i,1);
                if(i)
                    findfiles(client,loc);//actualizam lista de fisiere
            }
            cmd_ID=0;
            break;
        default: perror("Unknown command");
        pthread_detach(pthread_self());
        pthread_exit(NULL);
    }qDebug() << "69";
    }
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
   int j = 1; /*setam pentru socket optiunea SO_REUSEADDR */
   if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &j, sizeof(int)) < 0)
   {
       perror("[server]optiunea SO_REUSEADDR");
   }
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
    pthread_mutex_init(&lock,NULL);//initializam mutex-ul
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
        char ip[20];
        //verificam daca ip-ul se afla pe banlist sau nu
        sprintf(ip,"%s",inet_ntoa(from.sin_addr));
        int fd;
        char s[PATH_MAX];
        fd=open("ban_list.txt",O_RDONLY);
        read(fd,s,PATH_MAX);
        char* str;
        str=strtok(s,"\n");
        bool i=true;
        while(str){
            if(!strcmp(ip,str))
                {
                    i=false;
                    break;
                }
            str=strtok(NULL,"\n");
        }
        close(fd);
        //cream un thread pentru clientul conectat
        write(*client,&i,1);
        if(i){
            if(pthread_create(&t_id,NULL,thread_func,client)){
                perror ("[thread]Eroare la pthread_create()");
                continue;
            }
        }
        else {
            close(*client);
            delete(client);
        }
    }
    pthread_mutex_destroy(&lock);
    return(a.exec());
}
