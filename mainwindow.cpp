#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collaboration.h"
#include <QtDebug>
#include <QMessageBox>
#include <QTableView>
#include <QAbstractItemView>
#include <QIntValidator>
#include "qcustomplot.h"
#include "exportexcelobject.h"
#include "popup.h"
using namespace std;
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateStart->setDate(QDate::currentDate());
    ui->dateEnd->setDate(QDate::currentDate());
    ui->tableView->setModel(tabb.afficher());

    ui->id->setValidator(new QIntValidator(0,99,this));
        ui->id_supp->setValidator(new QIntValidator(0,99,this));
    ui->num->setValidator(new QIntValidator(00000000,99999999,this));
    ui->num_2->setValidator(new QIntValidator(00000000,99999999,this));
    //ui->Find_line->setValidator(new QIntValidator(0,99,this));
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->mail->setValidator(new QRegularExpressionValidator(rx, this));
    ui->mail_2->setValidator(new QRegularExpressionValidator(rx, this));

    popup = new Popup;



    setGeometry(QStyle::alignedRect(
                    Qt::RightToLeft,
                    Qt::AlignCenter,
                    size(),
                    qApp->desktop()->availableGeometry()));

    setWindowTitle("Window");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    int id=ui->id->text().toInt();
    QString nom =ui->nom->text();
    QString adresse=ui->adresse->text();
    QString mail=ui->mail->text();
    int num =ui->num->text().toInt();
    QDate date_s =ui->dateStart->date();
    QDate date_e =ui->dateEnd->date();
    QDate actual_date=QDate::currentDate();
    int left=actual_date.daysTo(date_e);
    //
    Collaboration c(nom,adresse,mail,num,id,date_s,date_e,left);
    //
    bool test=c.ajouter ();
    if (test)
    {
           ui->tableView->setModel(tabb.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                     QObject ::tr("Ajout effectué\n"
                                  "click cancel to exit"),
                QMessageBox:: Cancel);
        ui->id->clear();
        ui->nom->clear();
        ui->adresse->clear();
        ui->mail->clear();
        ui->num->clear();

}
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                             QObject::tr("try again.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
        ui->id->clear();
        ui->nom->clear();
        ui->adresse->clear();
        ui->mail->clear();
        ui->num->clear();
    }
}





void MainWindow::on_Supprimer_clicked()
{
    int id =ui->id_supp->text().toInt();
     bool test=tabb.supprimer(id);
     if (test)
     {
         ui->tableView->setModel(tabb.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                      QObject ::tr("suppression effectué\n"
                                   "click cancel to exit"),
                 QMessageBox:: Cancel);
        ui->id_supp->clear();

    }
     else
     {
         QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
         ui->id_supp->clear();
     }
}

void MainWindow::on_Modifier_clicked()
{
    int id=ui->id_supp->text().toInt();
    QString nom =ui->nom_2->text();
    QString adresse=ui->adresse_2->text();
    QString mail=ui->mail_2->text();
    int num=ui->num_2->text().toInt();
    QDate date_s =ui->dateStart_2->date();
    QDate date_e =ui->dateEnd_2->date();
    QDate actual_date=QDate::currentDate();
    int left=actual_date.daysTo(date_e);
       Collaboration c(nom,adresse,mail,num,id,date_s,date_e,left);
        bool test=c.modifier(id);
        if (test)
        {
               ui->tableView->setModel(tabb.afficher());
            QMessageBox :: information (nullptr, QObject ::tr("OK"),
                         QObject ::tr("modifier effectué\n"
                                      "click cancel to exit"),
                    QMessageBox:: Cancel);
            ui->id_supp->clear();
            ui->nom_2->clear();
            ui->adresse_2->clear();
            ui->mail_2->clear();
            ui->num_2->clear();

    }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("try again.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
            ui->id_supp->clear();
            ui->nom_2->clear();
            ui->adresse_2->clear();
            ui->mail_2->clear();
            ui->num_2->clear();
        }
}

void MainWindow::on_pushButton_2_clicked()
{
        ui->tableView->setModel(tabb.tri());
}

void MainWindow::on_tri_name_clicked()
{
    ui->tableView->setModel(tabb.trinom());
}

void MainWindow::on_Find_clicked()
{
    int id=ui->Find_line->text().toInt();
    if (id==NULL) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a Number."));
        return;
    } else {
    ui->tableView->setModel(tabb.recherche(id));
    }
}

void MainWindow::on_Find_nom_clicked()
{
    QString nom=ui->Find_line->text();
    if (nom.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a Name."));
        return;
    } else {
    ui->tableView->setModel(tabb.recherche_nom(nom));
    }
}



void MainWindow::on_update_clicked()
{

        int id;
        QString title, description;
                QSqlQuery query;
     //   model->setQuery("SELECT * from COLLABORATEUR"  );
      //  int count= model->rowCount();
     //  qInfo() << count;
    //   for(i=1;i<=count;i++)
   //    {
           QSqlQuery q1("SELECT IDCO,DATE_END FROM COLLABORATEUR");
           while (q1.next())
           {
           id = q1.value(0).toInt();
           QDate actual_date=QDate::currentDate();
           QDate date_e = q1.value(1).toDate();
           int left=actual_date.daysTo(date_e);
           query.prepare("UPDATE COLLABORATEUR SET DAYS_LEFT=:left where IDCO=:id");

           query.bindValue(":id",id);
           query.bindValue(":left",left);
           query.exec();
           ui->tableView->setModel(tabb.afficher());
           QString res=QString ::number(id);
           if(left<=10){
               title="contract";
               description="ID:"+res+" contract is going to end in less than 10 days";
           popup->showPopup(title,description);
           }
           qInfo() << id;
           }

    //tabb.update(id);
   //    }
 /*   if (test)
    {
           ui->tableView->setModel(tabb.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                     QObject ::tr("modifier effectué\n"
                                  "click cancel to exit"),
                QMessageBox:: Cancel);

}
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                             QObject::tr("try again.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
    }*/
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
              amande->setName("jour rest");
              amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
              amande->setBrush(QColor(0, 168, 140));

               //axe des abscisses
              QVector<double> ticks;
              QVector<QString> labels;
              tabb.statistique(&ticks,&labels);

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

              // ajout des données  (statistiques de la quantité)//

              QVector<double> PlaceData;
              QSqlQuery q1("select DAYS_LEFT from COLLABORATEUR");
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
void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                       tr("Excel Files (*.xls)"));
            QString sheetName=ui->sheet->text();
    ExportExcelObject obj(fileName, sheetName, ui->tableView);
    obj.addField(0, tr("IDCO"), "int");
    obj.addField(1, tr("NOMCENTRE"), "char(20)");
    obj.addField(2, tr("ADRESSE"), "char(20)");
    obj.addField(3, tr("NUM"), "int");
    obj.addField(4, tr("MAIL"), "char(40)");
    obj.addField(5, tr("DATE_START"), "date");
    obj.addField(6, tr("DATE_END"), "date");
    obj.addField(7, tr("DAYS_LEFT"), "int");
 obj.export2Excel();

}




void MainWindow::on_pushButton_4_clicked()
{
    ui->tableView->setModel(tabb.trileft());
}

void MainWindow::on_Find_2_clicked()
{
    QString mail=ui->Find_line->text();
    if (mail.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a mail."));
        return;
    } else {
    ui->tableView->setModel(tabb.recherche_mail(mail));
    }
}
