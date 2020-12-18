#include "commands.h"
#include <QDebug>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
bool login(int sd, QString name, QString password){
    bool i;
    int x=1;
    //transmitem codul comenzii la server
    write(sd,&x,4);
    //convertim textul de la QString la const char*
    std::string text_nume = (name.toStdString());
    std::string text_parola = (password.toStdString());
    const char* nume = text_nume.c_str();
    const char* parola = text_parola.c_str();
    //transmitem datele la server
    write(sd, (nume), 30);
    write(sd, (parola), 30);
    //primim raspuns de la server
    read(sd, &i, 1);
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
    const char* nume = text_nume.c_str();
    const char* parola = text_parola.c_str();
    //transmitem datele la server
    write(sd, (nume), 30);
    write(sd, (parola), 30);
    //primim raspuns de la server
    read(sd, &i, 1);
    //transmitem raspunsul catre functia principala
    return i;
}

void prepare_pg2(){

}
bool transfer_to(QString& data, QString& name, QString& location){

}

bool transfer_from(QString& data, QString& name, QString& location){

}
bool create_dir(QString& location){

}
bool create_file(QString& location){

}
