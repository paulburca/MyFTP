#include <QString>

QString Encrypt(QString& password)
{
    password = password + 1;
    QString value=password;
    return value;
}
