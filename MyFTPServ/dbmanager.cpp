#include "dbmanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

int DbManager::connections = 0;
QString Encrypt(const QString& password)
{
    QString password1 = password + 1;
    QString value=password1;
    return value;
    //work in progress.
}

DbManager::DbManager( const char* path)
{
   //crearea unei baze de date de tip SQLite
   m_db = QSqlDatabase::addDatabase("QSQLITE",QString::number(connections));
   //legarea fisierului de baza de date creata
   m_db.setDatabaseName(path);
   //deschiderea bazei de date
   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

bool DbManager::NewUser(const char* name, const char* password)
{
    //bool cu rol de verificare
    //daca este deja inregistrat acel user
    bool already = false;
    //cream o variabila de tip query
    //pentru baza de date
    QSqlQuery query(m_db);
    //"pregatim" ce interogare
    //va trebui executata
    query.prepare("SELECT name FROM users WHERE name = :name");
    //punem in ":name" valoarea lui name
    query.bindValue(":name", name);
    //executam interogarea
    if(query.exec())
    {
        //trecem la primul element
        //rezultat din interogare
        if(query.next())
        {
            //daca exista user-ul
            already = true;
        }
    }
    //verificam daca exista user-ul sau nu
    if(!already){
        //"pregatim" ce interogare
        //va trebui executata
        query.prepare("INSERT INTO users VALUES (:name, :password, 0)");
        //punem in ":name" valoarea lui name
        query.bindValue(":name", name);
        //aici ar trebui prima data sa decriptam parola
        //si dupa sa o adaugam in interogare
        //punem in ":password" valoarea lui password
        query.bindValue(":password", password);
        //executam interogarea
        if(query.exec())
            //interogarea a reusit adaugarea unui user nou
            return true;
        else
            //interogarea nu a reusit
            qDebug() << "NewUser error:"
                     << query.lastError();
        return false;
    }
    else{
        //user-ul deja exista
        printf("User already exists");
        return false;
    }
}

bool DbManager::CheckUser(const char* name, const char* password)
{
    //cream o variabila de tip query
    //pentru baza de date
    QSqlQuery query(m_db);
    //"pregatim" ce interogare
    //va trebui executata
    query.prepare("SELECT * FROM users WHERE name = :name "
                  "AND password = :password AND blacklisted = 0");
    //punem in ":name" valoarea lui name
    query.bindValue(":name", name);
    //aici ar trebui prima data sa decriptam parola
    //si dupa sa o adaugam in interogare
    query.bindValue(":password", password);
    //executam interogarea
    if(query.exec())
        //trecem la primul element
        //rezultat din interogare
        if(query.next())
            //daca exista user-ul si toate
            //detalii de conectare sunt corecte
            return true;
    //nu exista user-ul sau a gresit parola
    return false;
}
