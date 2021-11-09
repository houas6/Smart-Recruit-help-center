#include "candidat.h"
#include <QSqlQuery>
#include <QSqlQueryModel>

candidat::candidat()
{

}

candidat::candidat(int a ,int b ,QString c,QString d,QString e,int f)
{
id =a; cin=b; nom=c; prenom=d;mail=e;num=f;}

bool candidat:: ajouter_candidat()
{
    QSqlQuery query;
    QString res = QString::number(id);
    QString res1=QString::number(cin);
    QString res2=QString::number(num);
    query.prepare("INSERT INTO candidat(id,cin,nom,prenom,mail,num)""VALUES (:id,:cin,:nom,:prenom,:mail,:num)");
    query.bindValue(":id",res);
    query.bindValue(":cin",res1);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    query.bindValue(":num",res2);
    return query.exec();
}
QSqlQueryModel * candidat::afficher_candidat()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM candidat");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("num"));
    return model;
}
bool candidat::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("DELETE FROM candidat WHERE id= :id");
    query.bindValue(":id",res);
    return query.exec();
}
bool candidat::modifier(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString res1=QString::number(cin);
    QString res2=QString::number(num);
    query.prepare("UPDATE candidat SET cin=:cin,nom=:nom,prenom=:prenom,mail=:mail,num=:num WHERE id=:id");
    query.bindValue(":id",res);
    query.bindValue(":cin",res1);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",mail);
    query.bindValue(":num",res2);


    return query.exec();
}
