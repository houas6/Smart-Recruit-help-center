#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

ui->tableView_2->setModel(Etmp.afficher());
ui->lineEdit_cin->setValidator( new QIntValidator(0, 99999999, this) );
ui->lineEdit_age->setValidator( new QIntValidator(0, 99, this) );
ui->lineEdit_tel->setValidator( new QIntValidator(0, 99999999, this) );
mServer=new QTcpServer(this);
mServer->listen(QHostAddress::Any,2000);
mSocket=new QTcpSocket(this);

connect(mServer,SIGNAL(newConnection()),this,SLOT(connexion_nueva()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::connexion_nueva()
{
    mSocket=mServer->nextPendingConnection();
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(leer_socket()));
}
void MainWindow:: leer_socket()
{
    QByteArray buffer;
    buffer.resize(mSocket->bytesAvailable());
    mSocket->read(buffer.data(),buffer.size());
    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->appendPlainText(QString(buffer));
}
void MainWindow::on_pushButton_clicked()
{
    mSocket->write(ui->lineEdit->text().toLatin1().data(),ui->lineEdit->text().size());
    ui->plainTextEdit->appendPlainText(ui->lineEdit->text());
    ui->lineEdit->clear();
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
