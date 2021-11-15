#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "QrCode.hpp"

class Employes
{
    //attribu
        int cin;
        QString nom;
        QString prenom;
        int age;
        int tel;
        QString adresse;
        QString departement;
public:
            Employes();
            Employes(int,QString,QString,int,int,QString,QString);
            int get_cin();
            QString get_nom();
            QString get_prenom();
            int get_age();
            int get_tel();
            QString get_adresse();
            QString get_departement();
            bool ajouter();
            QSqlQueryModel *afficher();
            bool supprimer(int);
            bool modifier(int,QString,QString,int,int,QString,QString);


            //
            QSqlQueryModel * trie_NOM();
            QSqlQueryModel * trie_PRENOM();
            QSqlQueryModel * trie_DEPARTEMENT();
            bool rech(int);
            QSqlQueryModel* rechercher(QString);
            bool rechnom(QString);
            QSqlQueryModel* recherchernom(QString);
            bool rechprenom(QString);
            QSqlQueryModel* rechercherprenom(QString);
            void statistique(QVector<double>* ticks,QVector<QString> *labels);




};

#endif // EMPLOYE_H
