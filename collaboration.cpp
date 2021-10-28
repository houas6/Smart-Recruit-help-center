#include "collaboration.h"
#include <QMessageBox>

Collaboration::Collaboration(QString nom,QString typeor,QString typec,int num)
{
    this->nom=nom;
    this->typeor=typeor;
    this->typec=typec;
    this->num=num;

}
bool Collaboration ::ajouter()
{
    QSqlQuery query;
    QString res = QString :: number(num);
    query.prepare("insert into place(num,etage,lettre,type,etat,tarif)""values(:num,:etage,:lettre,:type,:etat,:tarif)");
    //
    query.bindValue(":num",res);
    query.bindValue(":nom",nom);
    query.bindValue(":typeor",typeor);
    query.bindValue(":typec",typec);


    return query.exec();
}

QSqlQueryModel * Collaboration :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("selet * from place");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("typeor"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("typec"));
return model;
}

