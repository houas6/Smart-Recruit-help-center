#include "collaboration.h"
#include <QMessageBox>
#include "exportexcelobject.h"
Collaboration::Collaboration(QString nom,QString adresse,QString mail,int num,int id,QDate date_s,QDate date_e,int left)
{
        this->id=id;
    this->nom=nom;
    this->adresse=adresse;
    this->mail=mail;
    this->num=num;
    this->date_s=date_s;
    this->date_e=date_e;
    this->left=left;

}
bool Collaboration ::ajouter()
{
    QSqlQuery query;
    QString res = QString :: number(id);
    query.prepare("insert into COLLABORATEUR(IDCO,NOMCENTRE,ADRESSE,NUM,MAIL,DATE_START,DATE_END,DAYS_LEFT) values(:id,:nom,:adresse,:num,:mail,:date_s,:date_e,:left)");
    //
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);
    query.bindValue(":date_s",date_s);
    query.bindValue(":date_e",date_e);
        query.bindValue(":left",left);


    return query.exec();
}

QSqlQueryModel * Collaboration :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT IDCO,NOMCENTRE,ADRESSE,NUM,MAIL,DATE_START,DATE_END,DAYS_LEFT from COLLABORATEUR");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

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

    query.prepare("UPDATE COLLABORATEUR SET IDCO=:id,NOMCENTRE=:nom,ADRESSE=:adresse,NUM=:num,MAIL=:mail,DATE_START=:date_s,DATE_END=:date_e,DAYS_LEFT=:left where IDCO=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);
    query.bindValue(":date_s",date_s);
    query.bindValue(":date_e",date_e);
            query.bindValue(":left",left);

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
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
            model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

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
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
            model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

   return model;

}
QSqlQueryModel* Collaboration::trileft()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from COLLABORATEUR order by DAYS_LEFT");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
            model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

   return model;

}
QSqlQueryModel* Collaboration::recherche(int id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
                QString res=QString ::number(id);
            model->setQuery("select * from COLLABORATEUR where IDCO='"+res+"'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
            model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

   return model;

}
QSqlQueryModel* Collaboration::recherche_nom(QString nom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from COLLABORATEUR where NOMCENTRE='"+nom+"'");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
            model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

   return model;

}
void Collaboration::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select NOMCENTRE from COLLABORATEUR");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
QSqlQueryModel* Collaboration::recherche_mail(QString mail)
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from COLLABORATEUR where MAIL='"+mail+"'");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("date start"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("date end"));
            model->setHeaderData(7,Qt::Horizontal,QObject::tr("days left"));

   return model;

}
