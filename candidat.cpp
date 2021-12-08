#include "candidat.h"
#include <QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include<QDebug>
#include<QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>
#include<QtNetwork/QNetworkRequest>
#include<QObject>

candidat::candidat()
{

}

candidat::candidat(int id, int cin, QString nom, QString prenom, QString mail, int num,QString sexe){
    ID = id;
    CIN = cin;
    Nom = nom;
    Prenom = prenom;
    Mail = mail;
    Num = num;
    Sexe = sexe;

}


/*QString candidat::ConvTracker(){
    QSqlQuery query;
    int row_count = 0;

    query.exec("SELECT COUNT(*) FROM candidat");
    if(query.first()){
        row_count = query.value(0).toInt();
    }
    QString track = QString::number(row_count);
    int diff = (int) 3 - track.length();
    for(int i = 0; i < diff; i++){
        track = "0" + track;
    }

    return track;
}*/

bool candidat::Ajouter(){
    QSqlQuery query;

    QString res1 = QString::number(ID);
    QString res2 = QString::number(CIN);
    QString res3 = QString::number(Num);
    //QString res4 = QString::number(Sexe);

    query.prepare("INSERT INTO candidat(ID, CIN, NOM, PRENOM, MAIL,NUM,SEXE)""VALUES (:ID, :CIN, :nom, :prenom, :mail, :num, :sexe)");
    query.bindValue(":ID", res1);
    query.bindValue(":CIN", res2);
    query.bindValue(":nom", Nom);
    query.bindValue(":prenom", Prenom);
    query.bindValue(":mail", Mail);
    query.bindValue(":num", res3);
    query.bindValue(":sexe", Sexe);



    bool res = query.exec();
    if(res)
    {
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        QNetworkRequest request;
        request.setUrl(QUrl("http://147.135.97.29:1212/sendsms?phone=" + res3 + "&text=Felicitations vous etes un candidat !"));
        manager->get(request);
    }
    return res;
}

QSqlQueryModel * candidat::Afficher(){
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID, CIN, NOM, PRENOM, MAIL, NUM,SEXE FROM candidat");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SEXE"));



    return model;
}

bool candidat::Supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM candidat WHERE ID= :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool candidat::Modifier(QString id){
    QSqlQuery query;

    QString res2 = QString::number(CIN);
    QString res3 = QString::number(Num);
    query.prepare("UPDATE candidat SET CIN=:CIN, NOM=:nom, PRENOM=:prenom, MAIL=:mail, NUM=:num+ WHERE ID=:id");
    query.bindValue(":id", id);
    query.bindValue(":CIN", res2);
    query.bindValue(":nom", Nom);
    query.bindValue(":prenom", Prenom);
    query.bindValue(":mail", Mail);
    query.bindValue(":num", res3);
    return query.exec();
}

QSqlQueryModel * candidat::Tri(int choix, int ordre){
        QSqlQueryModel * model = new QSqlQueryModel();
        QString k;
        if(ordre == 1){
            k = "DESC";
        }
        else {
            k = "ASC";
        }
        switch(choix){
            case 0:
                model->setQuery("SELECT ID, CIN, NOM, PRENOM, MAIL, NUM FROM candidat ORDER BY CIN " + k);
                break;
            case 1:
                model->setQuery("SELECT ID, CIN, NOM, PRENOM, MAIL, NUM FROM candidat ORDER BY NOM " + k);
                break;
            case 2:
                model->setQuery("SELECT ID_candidat, NOM, ETAT, TYPE, TICKET, USAGE_TOT, USAGE_MAINTENANCE, COORD_X, COORD_Y FROM candidat ORDER BY USAGE_TOT " + k);
                break;
            default:
                break;
        }
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM"));
        return model;
}

int candidat::getHommes()
{
    QSqlQuery qry("SELECT * FROM candidat WHERE SEXE='HOMME'");

    int numberOfRows = 0;
    if(qry.last())
    {
        numberOfRows =  qry.at() + 1;
        qry.first();
        qry.previous();
    }
    qDebug() << "nhommes = " << numberOfRows;
    return numberOfRows;
}

int candidat::getFemmes()
{
    QSqlQuery qry("SELECT * FROM candidat WHERE SEXE='FEMME'");

    int numberOfRows = 0;
    if(qry.last())
    {
        numberOfRows =  qry.at() + 1;
        qry.first();
        qry.previous();
    }
    return numberOfRows;
}

QSqlQueryModel * candidat::Rechercher(QString mot, int choix)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    switch(choix){
        case 1: //Rechereche nom
            model->setQuery("SELECT ID, CIN, NOM, PRENOM, MAIL, NUM FROM candidat WHERE CIN LIKE '" + mot + "%'");
            break;
        case 2:
            model->setQuery("SELECT ID, CIN, NOM, PRENOM, MAIL, NUM FROM candidat WHERE NOM LIKE '" "%"+ mot + "%'");
            break;

        default:
            break;
    }
    //model->setQuery("SELECT * FROM candidat WHERE NOM LIKE 'Ar%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM"));

    return model;
}

candidat::~candidat(){

}


void candidat :: pdf(){
    //QDateTime datecreation = date.currentDateTime();
                //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
                       QPdfWriter pdf("C:\\pdf\\file1.pdf");
                       QPainter painter(&pdf);
                      int i = 4000;
                           painter.setPen(Qt::blue);
                           painter.setFont(QFont("Arial", 30));
                           painter.drawText(1100,1200,"Liste Des candidats");
                           painter.setPen(Qt::black);
                           painter.setFont(QFont("Arial", 15));
                          // painter.drawText(1100,2000,afficheDC);
                           painter.drawRect(100,100,7300,2600);
                           //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                           painter.drawRect(0,3000,9600,500);
                           painter.setFont(QFont("Arial", 9));
                           painter.drawText(200,3300,"CIN");
                           painter.drawText(1200,3300,"nom");
                           painter.drawText(2200,3300,"prenom");
                           painter.drawText(3350,3300,"mail");
                           painter.drawText(3900,3300,"num");

                           QSqlQuery query;
                           query.prepare("select * from candidat");
                           query.exec();
                           while (query.next())
                           {
                               painter.drawText(200,i,query.value(0).toString());
                               painter.drawText(1300,i,query.value(1).toString());
                               painter.drawText(2200,i,query.value(2).toString());
                               painter.drawText(3200,i,query.value(3).toString());
                               painter.drawText(3900,i,query.value(4).toString());


                              i = i + 500;
                           }


        int reponse = QMessageBox::Yes;
            if (reponse == QMessageBox::Yes)
            {
                QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                notifyIcon->show();
                notifyIcon->setIcon(QIcon("icone.png"));

                notifyIcon->showMessage("GESTION candidat ","Liste des candidat prete dans PDF",QSystemTrayIcon::Information,15000);

                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }
}

