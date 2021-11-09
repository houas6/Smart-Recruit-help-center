#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source");
db.setUserName("roua128");//inserer nom de l'utilisateur
db.setPassword("roua128");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}
