#ifndef RDV_H
#define RDV_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QMessageBox>
#include<QDate>
#include<QTextCharFormat>
#include<QCalendarWidget>

class RDV
{
    QString nom,mail;
    int num,id;
    QDate date_s;
public:
    RDV(){}
    RDV(QString,QString,int,int,QDate);
    QString getnom(){return nom;}
        QString getmail (){return mail;}
        int  getnum(){return num;}
        int  getid(){return id;}
        QDate  getdate_s(){return date_s;}
        //
        void setnom(QString no){nom=no;}
        void setmail(QString ml){mail=ml;}
        void setnum(int n){num=n;}
        void setid(int i){id=i;}
        void setdate_s(QDate ds){date_s=ds;}
        //
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer (int id);
        bool modifier(int id);
        QSqlQueryModel *tri();
        QSqlQueryModel *trinom();
        QSqlQueryModel *recherche(int);
        QSqlQueryModel *recherche_nom(QString);
        void statistique(QVector<double>* ticks,QVector<QString> *labels);
        void calendrier(QTextCharFormat ,QCalendarWidget * );
};

#endif // RDV_H
