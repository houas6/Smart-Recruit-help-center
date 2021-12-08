#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "candidat.h"
#include <string>
#include <ctime>
#include <qpixmap.h>

#include <QMessageBox>

#include "drilldownchart.h"
#include "drilldownslice.h"

#include <QtCore/QTime>
#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QPieSeries>
#include <QGridLayout>
#include "captcha.h"

candidat _c;
QString cCaptcha;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(ctmp.Afficher());

    Captcha cp;
    cp.randomize();
    cp.setDifficulty(0);
    /*cp.loadDictionary("dictionary.txt");
    cp.setTextGeneration(Captcha::TextGeneration_Dictionary);*/
    cp.generateText();
    cCaptcha = cp.captchaText();
    ui->captcha_label->setPixmap(QPixmap::fromImage(cp.captchaImage()));

    DrilldownChart *chart = new DrilldownChart();
  chart->setTheme(QChart::ChartThemeLight);
  chart->setAnimationOptions(QChart::AllAnimations);
  chart->legend()->setVisible(true);
  chart->legend()->setAlignment(Qt::AlignRight);

  QPieSeries *yearSeries = new QPieSeries(parent);
  yearSeries->setName("Sales by year - All");

  const QStringList months = {
      "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };
  const QStringList names = {
      "Jane", "John", "Axel", "Mary", "Susan", "Bob"
  };

  QPieSeries *series = new QPieSeries(parent);
  series->setName("Candidats par sexe");

  *series << new DrilldownSlice(_c.getFemmes(), "Femme", series);
  *series << new DrilldownSlice(_c.getHommes(), "Homme", series);





  chart->changeSeries(series);

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  QGridLayout *gridLayout = new QGridLayout;
  ui->customplot->setLayout(gridLayout);

  ui->customplot->layout()->addWidget(chartView);



    //QPixmap Map = ("C:\Users\ASUS\Desktop\Atelier_Connexion\Map.PNG");
    //ui->
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_butAjouter_clicked()
{
    int id=ui->lineid->text().toInt();
       int cin=ui->linecin->text().toInt();
        QString nom=ui->linenom->text();
        QString prenom =ui->lineprenom->text();
        QString mail=ui->linemail->text();
        int num =ui->linenum->text().toInt();
        QString sexe =ui->linesexe->text();



    candidat C(id,cin,nom,prenom,mail,num,sexe);

        bool test=C.Ajouter();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("Succes"),
                        QObject::tr("Ajout successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView->setModel(ctmp.Afficher());

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                        QObject::tr("Ajout failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel); }
    ui->tableView->setModel(ctmp.Afficher());
}

void MainWindow::on_butSupprimer_clicked()
{
    QString id_del=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toString();

    bool supp = ctmp.Supprimer(id_del);

    if(supp)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Suppression avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Suppression échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }
    ui->tableView->setModel(ctmp.Afficher());
}

void MainWindow::on_butModifier_clicked()
{
    int id_mod=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
    int cin=ui->linecin->text().toInt();
     QString nom=ui->linenom->text();
     QString prenom =ui->lineprenom->text();
     QString mail=ui->linemail->text();
     int num =ui->linenum->text().toInt();
     QString sexe=ui->linesexe->text();

    candidat C(id_mod,cin,nom,prenom,mail,num,sexe);
    QString id_prov = (QString) id_mod;
    bool test = C.Modifier(id_prov);

    if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Modification avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Modification échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }
    ui->tableView->setModel(ctmp.Afficher());
}

void MainWindow::on_Search_clicked()
{
    if((ui->comboBox->currentText() == "")||(ui->lineRechercher->text() == "")){
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("Veuillez selectez une paramètre.\n"), QMessageBox::Ok);
    }
    else {
        ui->tableView->setModel(ctmp.Rechercher(ui->lineRechercher->text(), ui->comboBox->currentIndex()));
    }
}

void MainWindow::on_butTrier_clicked()
{
    ui->tableView->setModel(ctmp.Tri(ui->comboBox_2->currentIndex(), ui->comboBox_3->currentIndex()));
}

void MainWindow::on_butAjouter_2_clicked()
{

}

void MainWindow::on_butRechercher_clicked()
{

}

