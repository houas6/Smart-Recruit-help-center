 #include "entreprise.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Entreprise::Entreprise()
{
IdEn=0; nom="";adresse="";mail=""; numero=0 ;
}

Entreprise::Entreprise(int IdEn, QString nom,QString adresse,QString mail,int numero)
{this->IdEn=IdEn;this->nom=nom;this->adresse=adresse;this->mail=mail;this->numero=numero; }
int Entreprise::getIdEn(){return IdEn;}
QString Entreprise::getnom(){return nom;}
QString Entreprise::getadresse(){return adresse;}
QString Entreprise:: getmail(){return mail;}
int Entreprise::getnumero(){return numero;}
void Entreprise::setIdEn(int IdEn){this->IdEn=IdEn;}
void Entreprise::setnom(QString nom){this->nom=nom;}
void Entreprise::setadresse(QString adresse){this->adresse=adresse;}
void Entreprise::setmail(QString mail){this->mail=mail;}
void Entreprise::setnumero(int numero){this->numero=numero;}
bool Entreprise::ajouter()
{

    QSqlQuery query;

    QString numero_string= QString::number(numero);
    QString IdEn_string= QString::number(IdEn);



    query.prepare("INSERT INTO entreprise(IDEN,NOM, ADRESSE, MAIL ,NUMERO) "
                  "VALUES (:IdEn, :name, :adress, :mail, :number)");
    query.bindValue(":IdEn",IdEn_string );
    query.bindValue(":name",nom );
    query.bindValue(":adress",adresse);
    query.bindValue(":mail", mail);
    query.bindValue(":number", numero_string);

        return query.exec();   // envoie la requete pourl'executer

}
bool Entreprise::supprimer(int IdEn)
{
     QSqlQuery query;
    query .prepare("Delete from entreprise where IdEn=:IdEn");
    query.bindValue(0,IdEn );
            return query.exec();

}
QSqlQueryModel * Entreprise::afficher()
{
  QSqlQueryModel * model=new QSqlQueryModel();
  model->setQuery("SELECT iden,nom,adresse,mail,numero  FROM entreprise");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("IdEn"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("Mail"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("Numero"));


  return model;
}
bool Entreprise ::modifier(int IdEn , QString nom , QString adresse, QString mail , int numero )
{

    QSqlQuery query ;
    QString IdEn_string = QString::number(IdEn);
    QString numero_string = QString::number(numero  );

    query.prepare("update ENTREPRISE set nom=:nom,adresse=:adresse,mail=:mail,numero=:numero where IdEn=:IdEn");
    query.bindValue(":IdEn",IdEn);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":mail",mail);
    query.bindValue(":numero",numero);
    return query.exec();

}


