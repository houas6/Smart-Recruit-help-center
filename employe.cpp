#include "employe.h"
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QListView>
Employes::Employes()
{
    cin=age=tel=0;
    nom=prenom=adresse=departement="";
}

Employes::Employes(int cin,QString nom,QString prenom,int age,int tel,QString adresse,QString departement)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->age=age;
    this->tel=tel;
    this->adresse=adresse;
    this->departement=departement;
}
//Getters
int Employes::get_cin(){return cin;}
QString Employes::get_nom(){return nom;}
QString Employes::get_prenom(){return prenom;}
int Employes::get_age(){return age;}
int Employes::get_tel(){return tel;}
QString Employes::get_adresse(){return adresse;}
QString Employes::get_departement(){return departement;}

bool Employes::ajouter()
{
    QSqlQuery query;
    QString cin_string =QString::number(cin);
    QString age_string =QString::number(age);
    QString tel_string =QString::number(tel);
    query.prepare("INSERT INTO EMPLOYES (cin, nom, prenom, age, tel, adresse, departement) "
                        "VALUES (:cin, :nom, :prenom, :age, :tel, :adresse, :departement)");
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    query.bindValue(":tel",tel);
    query.bindValue(":adresse",adresse);
    query.bindValue(":departement",departement);
    return    query.exec();
}




bool Employes::supprimer(int cin)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
query.prepare("Delete from EMPLOYES where cin=:cin");
query.bindValue(":cin",cin_string);
return    query.exec();
}


QSqlQueryModel * Employes::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EMPLOYES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("tel"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("departement"));
    return model;
    }




bool Employes::modifier(int cin,QString nom,QString prenom,int age,int tel,QString adresse,QString departement)
{
QSqlQuery query;
QString cin_string =QString::number(cin);
QString age_string =QString::number(age);
QString tel_string =QString::number(tel);
query.prepare("update EMPLOYES set nom=:nom,prenom=:prenom,age=:age,tel=:tel,adresse=:adresse,departement=:departement where cin=:cin");
query.bindValue(":cin", cin);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age", age);
query.bindValue(":tel", tel);
query.bindValue(":adresse", adresse);
query.bindValue(":departement", departement);
return    query.exec();
}
