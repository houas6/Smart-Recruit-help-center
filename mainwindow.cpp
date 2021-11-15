#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "QrCode.hpp"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQueryModel>
#include "chat.h"
using namespace qrcodegen;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

ui->tableView_2->setModel(Etmp.afficher());
ui->lineEdit_cin->setValidator( new QIntValidator(0, 99999999, this) );
ui->lineEdit_age->setValidator( new QIntValidator(0, 99, this) );
ui->lineEdit_tel->setValidator( new QIntValidator(0, 99999999, this) );


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    //recuperation des info dans les 7 champs
    int cin=ui->lineEdit_cin->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int age=ui->lineEdit_age->text().toInt();
    int tel=ui->lineEdit_tel->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    QString departement=ui->lineEdit_departement->text();
    Employes E(cin,nom,prenom,age, tel, adresse, departement);
    bool test=E.ajouter();//inserer employé e dans la table
    if (test)
    {
ui->tableView_2->setModel(E.afficher());

        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("ajout effectué \n"
                                             "Click Cancel to exist ."),QMessageBox::Cancel);

    }
    else
          QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                      QObject::tr("connection failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);




}


void MainWindow::on_pushButton_supprimer_clicked()
{
    //recuperation du cin
    int cin=ui->lineEdit_cin->text().toInt();Employes E1;
    bool test=E1.supprimer(cin);

    if (test)
    {
  ui->tableView_2->setModel(E1.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("suppression effectué \n"
                                             "Click Cancel to exist ."),QMessageBox::Cancel);

    }
    else
          QMessageBox::critical(nullptr, QObject::tr("no"),
                      QObject::tr("Suppression failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_modifier_clicked()
{
    int cin=ui->lineEdit_cin->text().toInt();Employes E1;
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int age=ui->lineEdit_age->text().toInt();
    int tel=ui->lineEdit_tel->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    QString departement=ui->lineEdit_departement->text();
    Employes E(cin,nom,prenom,age, tel, adresse, departement);
    bool test=E.modifier(cin,nom,prenom,age,tel,adresse,departement);//modifier employe
    if (test)
    {

ui->tableView_2->setModel(E1.afficher());
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Modification effectué \n"
                                             "Click Cancel to exist ."),QMessageBox::Cancel);

    }
    else
          QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                      QObject::tr("Modification failed.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pushButton_trie_clicked()
{

         Employes E;
         QString choix=ui->comboBox_tri->currentText();
         if (choix=="Nom")
         {
             ui->tableView_2->setModel(E.trie_NOM());
             ui->tableView_2->setModel(E.afficher());
             bool test=E.trie_NOM();//tri Nom
             if (test)
             {

         ui->tableView_2->setModel(E.trie_NOM());
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                                          QObject::tr("tri Nom effectué \n"
                                                      "Click Cancel to exist ."),QMessageBox::Cancel);

             }
             else
                   QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                               QObject::tr("tri Nom failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }
         if (choix=="Prenom")
         {
             ui->tableView_2->setModel(E.trie_PRENOM());
             ui->tableView_2->setModel(E.afficher());
             bool test=E.trie_PRENOM();//tri prenom
             if (test)
             {

         ui->tableView_2->setModel(E.trie_PRENOM());
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                                          QObject::tr("tri prenom effectué \n"
                                                      "Click Cancel to exist ."),QMessageBox::Cancel);

             }
             else
                   QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                               QObject::tr("tri prenom failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }
         if (choix=="Departement")
         {
             ui->tableView_2->setModel(E.trie_DEPARTEMENT());
             ui->tableView_2->setModel(E.afficher());
             bool test=E.trie_DEPARTEMENT();//tri produit
             if (test)
             {

         ui->tableView_2->setModel(E.trie_DEPARTEMENT());
                 QMessageBox::information(nullptr,QObject::tr("ok"),
                                          QObject::tr("tri departement effectué \n"
                                                      "Click Cancel to exist ."),QMessageBox::Cancel);

             }
             else
                   QMessageBox::critical(nullptr, QObject::tr("nonnnn"),
                               QObject::tr("tri departement failed.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
         }

    }


void MainWindow::on_pushButton_Recherche_clicked()
{
    Employes E;
       QString choix=ui->comboBox_chercher->currentText();

       if (choix=="Cin")
       {
           QString cin = ui->lineEdit_rech->text();
           ui->tableView_3->setModel(E.rechercher(cin));
       }
       if (choix=="Nom")
       {
           QString Nom = ui->lineEdit_rech->text();
           ui->tableView_3->setModel(E.recherchernom(Nom));
       }
       if (choix=="Prenom")
       {
           QString Prenom = ui->lineEdit_rech->text();
           ui->tableView_3->setModel(E.rechercherprenom(Prenom));
       }


    }


void MainWindow::on_tabWidget_currentChanged(int index)
{
    // background //
                  QLinearGradient gradient(0, 0, 0, 400);
                  gradient.setColorAt(0, QColor(90, 90, 90));
                  gradient.setColorAt(0.38, QColor(105, 105, 105));
                  gradient.setColorAt(1, QColor(70, 70, 70));
                  ui->plot->setBackground(QBrush(gradient));

                  QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
                  amande->setAntialiased(false);
                  amande->setStackingGap(1);
                   //couleurs
                  amande->setName("Repartition des EMPLOYES selon age ");
                  amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                  amande->setBrush(QColor(0, 168, 140));

                   //axe des abscisses
                  QVector<double> ticks;
                  QVector<QString> labels;
                  Etmp.statistique(&ticks,&labels);

                  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                  textTicker->addTicks(ticks, labels);
                  ui->plot->xAxis->setTicker(textTicker);
                  ui->plot->xAxis->setTickLabelRotation(60);
                  ui->plot->xAxis->setSubTicks(false);
                  ui->plot->xAxis->setTickLength(0, 4);
                  ui->plot->xAxis->setRange(0, 8);
                  ui->plot->xAxis->setBasePen(QPen(Qt::white));
                  ui->plot->xAxis->setTickPen(QPen(Qt::white));
                  ui->plot->xAxis->grid()->setVisible(true);
                  ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                  ui->plot->xAxis->setTickLabelColor(Qt::white);
                  ui->plot->xAxis->setLabelColor(Qt::white);

                  // axe des ordonnées
                  ui->plot->yAxis->setRange(0,10);
                  ui->plot->yAxis->setPadding(5);
                  ui->plot->yAxis->setLabel("Statistiques");
                  ui->plot->yAxis->setBasePen(QPen(Qt::white));
                  ui->plot->yAxis->setTickPen(QPen(Qt::white));
                  ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
                  ui->plot->yAxis->grid()->setSubGridVisible(true);
                  ui->plot->yAxis->setTickLabelColor(Qt::white);
                  ui->plot->yAxis->setLabelColor(Qt::white);
                  ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
                  ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

                  // ajout des données  (statistiques de l age)//

                  QVector<double> PlaceData;
                  QSqlQuery q1("select age from EMPLOYES");
                  while (q1.next()) {
                                int  nbr_fautee = q1.value(0).toInt();
                                PlaceData<< nbr_fautee;
                                  }
                  amande->setData(ticks, PlaceData);

                  ui->plot->legend->setVisible(true);
                  ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                  ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
                  ui->plot->legend->setBorderPen(Qt::NoPen);
                  QFont legendFont = font();
                  legendFont.setPointSize(5);
                  ui->plot->legend->setFont(legendFont);
                  ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}



void MainWindow::on_qrpushbutton_clicked()
{
    int tabeq=ui->tableView_2->currentIndex().row();
        QVariant cinn=ui->tableView_2->model()->data(ui->tableView_2->model()->index(tabeq,0));
        int cin= cinn.toInt();
        QSqlQuery qry;
        qry.prepare("select * from EMPLOYES where cin=:cin");
        qry.bindValue(":cin",cin);
        qry.exec();
        QString nom, prenom ,adresse,departement,cine;
        int age,tel;
        while(qry.next()){
            nom=qry.value(1).toString();
            prenom=qry.value(2).toString();
            adresse=qry.value(3).toString();
            departement=qry.value(4).toString();
        }
         cine=QString(cin);
         cine="cin: "+cine+"nom: "+nom+" prenom: "+prenom+"age:"+age+"tel:"+tel+" adresse: "+adresse+" departement : "+departement;
        QrCode qr = QrCode::encodeText(cine.toUtf8().constData(), QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(200,200);
        ui->qrlabel->setPixmap(QPixmap::fromImage(im));
        int i=0 ;
        for(i=0;i<100;i=i+0.1){
            i++;
            ui->progressBar->setValue(i);
        }
}

void MainWindow::on_pushButton_clicked()
{
    chat *chat_window= new chat(this);
        chat_window->setModal(true);
        chat_window->show();

        //qDebug()<< "Chat is running on " << QThread::currentThread();

        chat_window->exec();
}

bool MainWindow::launch_chat(chat &chat_window)
{
    chat_window.setModal(true);
    chat_window.show();

    qDebug()<< "Chat is running on " << QThread::currentThread();

    return chat_window.exec();
}
