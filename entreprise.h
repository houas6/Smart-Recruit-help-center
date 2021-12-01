 #ifndef ENTREPRISE_H
#define ENTREPRISE_H
#include <QString>
#include <QSqlQueryModel>
class Entreprise
{
public:
    //constructeurs
    Entreprise();
    Entreprise(int,QString,QString,QString,int);
    //getters
    int getIdEn();
    QString getnom();
    QString getadresse();
    QString getmail();
    int getnumero();
    void setIdEn(int);
    void setnom(QString);
    void setadresse(QString);
    void setmail(QString);
    void setnumero(int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);

    bool modifier(int , QString ,QString ,QString ,int );


private:
int IdEn;
QString nom;
QString adresse;
QString mail;
int numero;


};

#endif // ENTREPRISE_H
