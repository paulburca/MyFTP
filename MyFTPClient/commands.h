#ifndef COMMANDS_H
#define COMMANDS_H
#include <unistd.h>
#include <mbedtls/sha512.h>
#include<QString>
bool login(int sd, QString name,QString password);
bool reg(int sd, QString name, QString password);
bool transfer_to(int sd, QString& nameC);
bool transfer_from(int sd, QString& nameS, QString& locationC);
bool create_dir(int sd, QString& name);
bool create_file(int sd,QString& name, QString& content);
bool deleter(int sd, QString& locationS);
bool cd(int sd, QString& loc);
bool bk(int sd);
#endif // COMMANDS_H
