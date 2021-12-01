#ifndef COLLABORATION_H
#define COLLABORATION_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QMessageBox>
#include<QDate>


class Collaboration
{
    QString nom,adresse,mail;
    int num,id,left;
    QDate date_s,date_e;
public:
    Collaboration(){}
    Collaboration(QString,QString,QString,int,int,QDate,QDate,int);
    QString getnom(){return nom;}
        QString getadresse(){return adresse;}
        QString getmail (){return mail;}
        int  getnum(){return num;}
        int  getid(){return id;}
        int  getleft(){return left;}
        QDate  getdate_s(){return date_s;}
        QDate  getdate_e(){return date_e;}
        //
        void setnom(QString no){nom=no;}
        void setadresse(QString ad){adresse=ad;}
        void setmail(QString ml){mail=ml;}
        void setnum(int n){num=n;}
        void setid(int i){id=i;}
        void setdate_s(QDate ds){date_s=ds;}
        void setdate_e(QDate de){date_e=de;}
        void setleft(int l){left=l;}
        //
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer (int id);
        bool modifier(int id);
        QSqlQueryModel *tri();
        QSqlQueryModel *trinom();
        QSqlQueryModel *recherche(int);
        QSqlQueryModel *recherche_nom(QString);
        QSqlQueryModel *trileft();
        QSqlQueryModel *recherche_mail(QString mail);
        void statistique(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // COLLABORATION_H
