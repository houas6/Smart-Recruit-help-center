#ifndef COLLABORATION_H
#define COLLABORATION_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QString>
#include<QMessageBox>


class Collaboration
{
    QString nom,adresse,mail;
    int num,id;
public:
    Collaboration(){}
    Collaboration(QString,QString,QString,int,int);
    QString getnom(){return nom;}
        QString getadresse(){return adresse;}
        QString getmail (){return mail;}
        int  getnum(){return num;}
        int  getid(){return id;}
        //
        void setnom(QString no){nom=no;}
        void setadresse(QString ad){adresse=ad;}
        void setmail(QString ml){mail=ml;}
        void setnum(int n){num=n;}
        void setid(int i){id=i;}
        //
        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer (int id);
        bool modifier(int id);
        QSqlQueryModel *tri();
        QSqlQueryModel *trinom();
};

#endif // COLLABORATION_H
