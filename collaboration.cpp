#include "collaboration.h"
#include <QMessageBox>

Collaboration::Collaboration(QString nom,QString adresse,QString mail,int num,int id)
{
        this->id=id;
    this->nom=nom;
    this->adresse=adresse;
    this->mail=mail;
    this->num=num;

}
bool Collaboration ::ajouter()
{
    QSqlQuery query;
    QString res = QString :: number(id);
    query.prepare("insert into COLLABORATEUR(IDCO,NOMCENTRE,ADRESSE,NUM,MAIL) values(:id,:nom,:adresse,:num,:mail)");
    //
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);


    return query.exec();
}

QSqlQueryModel * Collaboration :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT* from COLLABORATEUR");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
return model;
}
bool Collaboration ::supprimer(int id)
{
QSqlQuery query;
QString res=QString ::number(id);
query.prepare("delete from COLLABORATEUR where IDCO= :id");
query.bindValue(":id",res);
return query.exec();
}
bool Collaboration::modifier(int id)
{
    QSqlQuery query;
    QString res=QString ::number(id);

    query.prepare("UPDATE COLLABORATEUR SET IDCO=:id,NOMCENTRE=:nom,ADRESSE=:adresse,NUM=:num,MAIL=:mail where IDCO=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);

    return query.exec();
}
QSqlQueryModel* Collaboration::tri()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from COLLABORATEUR order by IDCO");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));

   return model;

}
QSqlQueryModel* Collaboration::trinom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from COLLABORATEUR order by NOMCENTRE");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));

   return model;

}
