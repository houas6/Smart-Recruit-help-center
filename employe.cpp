#include "employe.h"
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QListView>
#include <QtDebug>
#include <QMessageBox>
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
    //prepare() prend la requete en parametre pour l'execution.

    query.prepare("INSERT INTO EMPLOYES (cin, nom, prenom, age, tel, adresse, departement) "
                        "VALUES (:cin, :nom, :prenom, :age, :tel, :adresse, :departement)");
    //creation des variables liees

    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    query.bindValue(":tel",tel);
    query.bindValue(":adresse",adresse);
    query.bindValue(":departement",departement);
    return    query.exec(); //exec() envoie de la requete pour l'executer.
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
query.bindValue(":cin", cin_string);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":age", age_string);
query.bindValue(":tel", tel_string);
query.bindValue(":adresse", adresse);
query.bindValue(":departement", departement);
return    query.exec();
}

QSqlQueryModel * Employes::trie_NOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYES ORDER BY nom ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    return model;
}
QSqlQueryModel * Employes::trie_PRENOM()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYES ORDER BY prenom ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    return model;
}
QSqlQueryModel * Employes::trie_DEPARTEMENT()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYES ORDER BY departement ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("tel"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse"));
    return model;
}
bool Employes::rech(int x){
    QSqlQuery query;
    query.prepare("select * from EMPLOYES where cin = :cin;");
    query.bindValue(":cin", x);
    return query.exec();
}

QSqlQueryModel* Employes::rechercher(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from EMPLOYES where cin ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("departement"));
            return model;
    }

bool Employes::rechnom(QString x){
    QSqlQuery query;
    query.prepare("select * from EMPLOYES where nom = :nom;");
    query.bindValue(":nom", x);
    return query.exec();}

QSqlQueryModel* Employes::recherchernom(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from EMPLOYES where nom ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("departement"));
            return model;
    }
bool Employes::rechprenom(QString x){
    QSqlQuery query;
    query.prepare("select * from EMPLOYES where prenom = :prenom;");
    query.bindValue(":prenom", x);
    return query.exec();
}
QSqlQueryModel* Employes::rechercherprenom(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from EMPLOYES where prenom ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("age"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("adresse"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("departement"));
            return model;
    }
void Employes::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select age from EMPLOYES");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
