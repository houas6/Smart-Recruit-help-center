#ifndef CANDIDAT_H
#define CANDIDAT_H


#include <QApplication>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPrinter>

class candidat
{
private:
    int ID;
    int CIN;
    QString Nom;
    QString Prenom;
    QString Mail;
    int Num;
    QString Sexe;

public:
    candidat();
    candidat(int, int, QString, QString, QString, int,QString);
    bool Ajouter();
    QSqlQueryModel * Afficher();
    int getHommes();
    int getFemmes();
    bool Modifier(QString);
    bool Supprimer(QString);
    QSqlQueryModel * Tri(int, int);
    QSqlQueryModel * Rechercher(QString , int );
    ~candidat();
    void pdf();


};

#endif // CANDIDAT_H
