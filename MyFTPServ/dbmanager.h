#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QString>
#include <QSqlDatabase>
class DbManager
{
public:
    static int connections;
    DbManager(const char* path);
    bool NewUser(const char* name, const char* password);
    bool CheckUser( const char* name, const char* password);
private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
