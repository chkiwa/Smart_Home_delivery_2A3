#include "connection.h"

connection::connection()
{

}

bool connection::createconnect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("mybase");
    db.setUserName("nour");
    db.setPassword("nour");

    if(db.open())
    return true;


    return false;
}

void connection::fermerconnexion()
{
      db.close();
}
