#ifndef COLLABORATION_H
#define COLLABORATION_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QMessageBox>


class Collaboration
{
    QString nom,typeor,typec;
    int num;
public:
    Collaboration(){}
    Collaboration(QString,QString,QString,int);
    QString getnom(){return nom;}
        QString gettypeor(){return typeor;}
        QString gettypec (){return typec;}
        int  getnum(){return num;}
        //
        void setnom(QString no){nom=no;}
        void settypeor(QString tor){typeor=tor;}
        void settypec(QString tc){typec=tc;}
        void setnum(int n){num=n;}
        //
        bool ajouter();
        QSqlQueryModel * afficher();
};

#endif // COLLABORATION_H
