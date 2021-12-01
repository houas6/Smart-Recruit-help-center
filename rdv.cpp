#include "RDV.h"
#include <QMessageBox>
RDV::RDV(QString nom,QString mail,int num,int id,QDate date_s)
{
        this->id=id;
    this->nom=nom;
    this->mail=mail;
    this->num=num;
    this->date_s=date_s;

}
bool RDV ::ajouter()
{
    QSqlQuery query;
    QString res = QString :: number(id);
    query.prepare("insert into RDV(ID,NOM,NUM,MAIL,DATE_S) values(:id,:nom,:num,:mail,:date_s)");
    //
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);
    query.bindValue(":date_s",date_s);


    return query.exec();
}

QSqlQueryModel * RDV :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("SELECT ID,NOM,NUM,MAIL,DATE_S from RDV");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("date start"));


return model;
}
bool RDV ::supprimer(int id)
{
QSqlQuery query;
QString res=QString ::number(id);
query.prepare("delete from RDV where ID= :id");
query.bindValue(":id",res);
return query.exec();
}
bool RDV::modifier(int id)
{
    QSqlQuery query;
    QString res=QString ::number(id);

    query.prepare("UPDATE RDV SET ID=:id,NOM=:nom,NUM=:num,MAIL=:mail,DATE_S=:date_s where ID=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":num",num);
    query.bindValue(":mail",mail);
    query.bindValue(":date_s",date_s);

    return query.exec();
}
QSqlQueryModel* RDV::tri()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV order by ID");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("date start"));

   return model;

}
QSqlQueryModel* RDV::trinom()
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV order by NOM");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("date start"));

   return model;

}
QSqlQueryModel* RDV::recherche(int id)
{
    QSqlQueryModel *model=new QSqlQueryModel();
                QString res=QString ::number(id);
            model->setQuery("select * from RDV where ID='"+res+"'");
            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("date start"));
   return model;

}
QSqlQueryModel* RDV::recherche_nom(QString nom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
            model->setQuery("select * from RDV where NOM='"+nom+"'");

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("num"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("mail"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("date start"));


   return model;

}
void RDV::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select ID from RDV");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
void RDV::calendrier(QTextCharFormat f,QCalendarWidget * w)
  {
      QDate date;
      QSqlQuery query("SELECT date_s FROM rdv");
      while (query.next())
      {
          date=query.value(0).toDate();
          w->setDateTextFormat(date,f);
      }
      w->setDateTextFormat(date,f);
  }

