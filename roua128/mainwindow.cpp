#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "candidat.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
 int id=ui->lineid->text().toInt();
   int cin=ui->linecin->text().toInt();
    QString nom=ui->linenom->text();
    QString prenom =ui->lineprenom->text();
    QString mail=ui->linemail->text();
    int num =ui->linenum->text().toInt();



candidat C(id,cin,nom,prenom,mail,num);

    bool test=C.ajouter_candidat();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("Succes"),
                    QObject::tr("Ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(ctmp.afficher_candidat());

}
    else
       { QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                    QObject::tr("Ajout failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel); }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableView->setModel(ctmp.afficher_candidat());
}

void MainWindow::on_pushButton_3_clicked()
{
    int i=ui->lineid->text().toInt();
    ctmp.supprimer(i);
    ui->tableView->setModel(ctmp.afficher_candidat());
}


void MainWindow::on_pushButton_4_clicked()
{
    int i=ui->lineid->text().toInt();
    int cin=ui->linecin->text().toInt();
     QString nom=ui->linenom->text();
     QString prenom =ui->lineprenom->text();
     QString mail=ui->linemail->text();
     int num =ui->linenum->text().toInt();
 candidat C(i,cin,nom,prenom,mail,num);
    C.modifier(i);
    ui->tableView->setModel(C.afficher_candidat());

}
