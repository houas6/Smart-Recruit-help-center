#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collaboration.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listView->setModel(ptmp.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_on_pushButton_ajouter_clicked_clicked()
{
    int num=ui->num->text().toInt();
    QString nom =ui->nom->text();
    QString typeor=ui->typeor->text();
    QString typec=ui->typec->text();
    //
    Collaboration c(nom,typeor,typec,num);
    //
    bool test=c.ajouter ();
    if (test)
    { QMessageBox :: information (nullptr, QObject ::tr("OK"),
                     QObject ::tr("Ajout effectué\n"
                                  "click cancel to exit"),
                QMessageBox:: Cancel);

}
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                             QObject::tr("try again.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
    }
}


