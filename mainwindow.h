#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include <QTableWidget>
#include <QTcpServer>
#include<QTcpSocket>
#include"chat.h"
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "QrCode.hpp"
#include "collaboration.h"
#include "entreprise.h"
#include "rdv.h"
#include "popup.h"
#include "QrCode.hpp"
#include"exportexcelobject.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    private slots:
    //employe
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();



    void on_pushButton_trie_clicked();

    void on_pushButton_Recherche_clicked();




    void on_qrpushbutton_clicked();

    void on_pushButton_clicked();
    bool launch_chat(chat&);
    //entreprise
    void on_pbajouter_clicked();
    void on_pushButton_modifier_entreprise_clicked();

        void on_pb_supprimer_clicked();
//collaboration

           void on_Supprimer_clicked();

           void on_Modifier_clicked();


           void on_tri_name_clicked();

           void on_Find_id_clicked();

           void on_Find_nom_clicked();


           void on_update_clicked();


           void on_pushButton_3_clicked();

           void on_tri_jour_clicked();

           void on_Find_mail_clicked();

           void on_pushButton_ajoutercollaborateur_clicked();

           void on_Ajouter_clicked();

           void on_tri_id_2_clicked();
           void on_tri_id_clicked();

           void on_tri_name_2_clicked();

           void on_Find_id_2_clicked();

           void on_Find_nom_2_clicked();

           void on_pb_pdf_clicked();

           void on_Modifier_2_clicked();

           void on_Supprimer_2_clicked();

private:
    Ui::MainWindow *ui;
    Employes Etmp;
    Entreprise E;
        Entreprise E1;
        Entreprise Et;
        Collaboration tabb;
            Popup *popup;
            RDV tabb1;

};
#endif // MAINWINDOW_H
