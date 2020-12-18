#ifndef COMMANDS_H
#define COMMANDS_H
#include <unistd.h>
#include<QString>
bool login(int sd, QString name,QString password);
bool reg(int sd, QString name, QString password);
bool transfer_to(QString& data, QString& name, QString& location);
bool transfer_from(QString& data, QString& name, QString& location);
bool create_dir(QString& location);
bool create_file(QString& location);
void prepare_pg2();

#endif // COMMANDS_H
