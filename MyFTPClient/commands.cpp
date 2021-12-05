#include "commands.h"
#include <QDebug>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
double powmod(double a, double b, double modd)// (a ^ b) % modd
{
    double p = a;
    for (int i = 1; i < b; i++)
    {
        a = fmod((a * p), modd);
    }
    return a;
}
std::string enc(std::string mesaj){//criptam datele
    std::string encv="";
    int e = 323;//cheia de criptare
    int n = 200099;//modulo
    //parcurgem mesajul si criptam fiecare caracter
    for (auto it = mesaj.begin(); it != mesaj.end(); it++)
    {
        double msg = *it;
        char ch[255] = "";

        // Encryption c = (msg ^ e) % n
        double c = powmod(msg, e, n);
        c = fmod(c, n);
        sprintf(ch,"%d",(int)c);
       // itoa((int)c, ch, 10);
        std::string chr=ch;
        encv = encv + chr + "|";
        //format: caracter_criptat1|caracter_criptat2|...
    }
    return encv;
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
bool login(int sd, QString name, QString password){
    bool i;
    int x=1;
    //transmitem codul comenzii la server
     write(sd,&x,4);
    //convertim textul de la QString la const char*
    std::string text_nume = (name.toStdString());
    std::string text_parola = (password.toStdString());
    //transmitem datele la server
    x=enc(text_nume).length();
    write(sd, &x,4);
    write(sd, enc(text_nume).c_str(),x);//trimitem numele criptat
    x=enc(text_parola).length();
    write(sd, &x,4);
    write(sd, enc(text_parola).c_str(),x);//trimitem parola criptata
    //primim raspuns de la server
    read(sd, &i, 1);//s-a reusit decriptarea si autentificarea
    //transmitem raspunsul catre functia principala
    return i;
}
bool reg(int sd,QString name, QString password){
    bool i;
    int x=2;
    //trimitem codul comenzii la server
    write(sd,&x,4);
    //convertim textul de la QString la const char*
    std::string text_nume = (name.toStdString());
    std::string text_parola = (password.toStdString());
    //transmitem datele la server
    x=enc(text_nume).length();
    write(sd, &x,4);
    write(sd, enc(text_nume).c_str(),x);
    x=enc(text_parola).length();
    write(sd, &x,4);
    write(sd, enc(text_parola).c_str(),x);
    //primim raspuns de la server
    read(sd, &i, 1);
    //transmitem raspunsul catre functia principala
    return i;
}


bool transfer_to(int sd, QString& nameC){
    bool i;
    int x=4;
    write(sd, &x, 4);//transmitem codul comenzii
    std::string text_nume = (nameC.toStdString());
    const char* file = text_nume.c_str();
    int len,l=0;;
    int fd=open(file,O_RDONLY);//deschidem fisierul de tranferat
    char content[PATH_MAX];
    char temp[strlen(file)];
    //extragem numele fisierului
    if(strrchr(file,'/'))
        strcpy(temp,strrchr(file,'/')+1);
    else strcpy(temp,file);
    len=strlen(temp);
    write(sd,&len,4);
    write(sd,temp,strlen(temp));
    //transmitem la server date din fisier in unitati de 4096 bytes
    memset(content,0,4096);
    if(!strrchr(file,'/')){
        sprintf(temp,"./Files/%s",file);
        fd=open(temp,O_RDONLY);//deschidem fisierul
    }
    else fd=open(file,O_RDONLY);
    l=read(fd,content,4096);
    write(sd, &l, 4);
    len=0;
    while(l==4096){
        sender(sd,4096,content);
        memset(content,0,4096);
        l=read(fd,content,4096);
        write(sd, &l, 4);
    }
    sender(sd,l,content);
    if(close(fd)==-1)//inchidem fisierul
        perror("[close]");
    else i=true;
    read(sd, &i, 1);
    return i;
}

bool transfer_from(int sd, QString& nameS, QString& locationC){
    bool i=false;
    int x=3;
    write(sd, &x, 4);//transmitem codul comenzii
    //castam de la QString la const char*
    std::string text_nume = (nameS.toStdString());
    std::string text_destination = (locationC.toStdString());
    const char* file = text_nume.c_str();
    const char* destination =text_destination.c_str();
    int len=strlen(file);
    if(!len)
        return 0;
    if(!strlen(destination))
        sprintf((char*)destination,"./Files");
    else if(!strcmp(destination,"."))
            sprintf((char*)destination,"./Files");
    write(sd,&len, 4);
    write(sd,file,strlen(file));//trimitem numele fisierului dorit
    read(sd,&i, 1);
    if(!i)
        return false;
    i=false;
    char content[PATH_MAX];
    char temp[strlen(destination)+strlen(file)+1];
    sprintf(temp,"%s/%s",destination,file);
    int fd;
    int l=0;
    //citim unitati de 4096 de la server si le scriem in fisier
    fd=open(temp,O_WRONLY | O_CREAT, 0777);
    read(sd,&l,4);
    len=0;
    while(l==4096){
        getter(sd,4096,content);
        write(fd,content,4096);
        memset(content,0,4096);
        read(sd,&l,4);
    }
    getter(sd,l,content);
    write(fd,content,l);
    if(close(fd)==-1)
        perror("[close]");
    else i=true;
    write(sd, &i, 1);//trimitem raspunsul la server
    return i;
}
bool create_dir(int sd, QString& name){
    bool i;
    int x=7;
    write(sd, &x, 4);//transmitem codul comenzii
    std::string text_nume = (name.toStdString());
    const char* file = text_nume.c_str();
    int l=strlen(file);
    if(!l)//verificam daca numele noului folder este nenul
        return false;
    write(sd,&l,4);
    write(sd,file,l);//transmitem numele noului director
    read(sd, &i,1);//primim raspuns de la server
    return i;
}
bool create_file(int sd, QString& name, QString& content){
    bool i;
    int x=6;
    write(sd, &x, 4);//transmitem codul comenzii
    std::string text_nume = (name.toStdString());
    std::string text_content = (content.toStdString());
    const char* file = text_nume.c_str();
    const char* data = text_content.c_str();
    int l=strlen(file);
    write(sd,&l,4);
    write(sd,file,l);//transmitem numele noului fisier
    char temp[PATH_MAX];
    //trimitem la server continutul noului fisier in unitati de 4096 biti
    memset(temp,0,4096);
    strncpy(temp,data,4096);
    l=strlen(temp);
    write(sd, &l, 4);//transmitem size-ul unitati de transmis
    while(l==4096){
        sender(sd, 4096,temp);
        memset(temp,0,4096);
        data+=l;//trecem la urmatorii 4096 biti dupa ce i-am transmis
        strncpy(temp,data,4096);
        l=strlen(temp);
        write(sd,&l,4);
    }
    sender(sd, l,data);
    read(sd,&i,1);//asteptam raspuns de la server
    return i;
}
bool deleter(int sd, QString& locationS){
    bool i;
    int x=5;
    write(sd, &x, 4);//transmitem codul comenzii
    std::string text_destination = (locationS.toStdString());
    const char* destination = text_destination.c_str();
    int l= strlen(destination);
    write(sd, &l, 4);
    write(sd, destination,l);//trimitem numele fisierului/folderului de sters
    read(sd,&i,1);//asteptam raspuns de la server
    return i;
}
bool cd(int sd, QString& loc){
    bool i;
    int x=8;
    write(sd, &x, 4);//transmitem codul comenzii
    std::string text_loc= (loc.toStdString());
    const char* next = text_loc.c_str();
    int l=strlen(next);
    write(sd,&l,4);
    write(sd,next,l);//tritem numele directorului pe care vrem sa-l accesam
    read(sd,&i,1);//asteptam raspuns de la server
    return i;
}
bool bk(int sd){
    bool i;
    int x=9;//transmitem codul comenzii
    write(sd, &x, 4);//trimitem codul respectiv comenzii
    read(sd,&i,1);
    return i;
}
