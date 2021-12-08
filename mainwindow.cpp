#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include "QrCode.hpp"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQueryModel>
#include "chat.h"

candidat _c;
QString cCaptcha;
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
ui->dateStart->setDate(QDate::currentDate());
    ui->dateEnd->setDate(QDate::currentDate());
    ui->tableView->setModel(tabb.afficher());

    ui->id->setValidator(new QIntValidator(0,99,this));
        ui->id_supp->setValidator(new QIntValidator(0,99,this));
    ui->num->setValidator(new QIntValidator(00000000,99999999,this));

    //ui->Find_line->setValidator(new QIntValidator(0,99,this));
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    ui->mail->setValidator(new QRegularExpressionValidator(rx, this));


    popup = new Popup;



    setGeometry(QStyle::alignedRect(
                    Qt::RightToLeft,
                    Qt::AlignCenter,
                    size(),
                    qApp->desktop()->availableGeometry()));

    setWindowTitle("Window");
    ui->tab_entreprise ->setModel(Et.afficher());
      ui->leIdEn ->setValidator(new QIntValidator(0, 9999999, this));
      ui->lenumero ->setValidator(new QIntValidator(0, 99999999, this));
      ui->dateStart->setDate(QDate::currentDate());
          ui->tableView->setModel(tabb.afficher());

          ui->id->setValidator(new QIntValidator(0,99,this));
              ui->id_supp->setValidator(new QIntValidator(0,99,this));
          ui->num->setValidator(new QIntValidator(00000000,99999999,this));


//ROUA
          ui->tableView_4->setModel(ctmp.Afficher());

          Captcha cp;
          cp.randomize();
          cp.setDifficulty(0);
          /*cp.loadDictionary("dictionary.txt");
          cp.setTextGeneration(Captcha::TextGeneration_Dictionary);*/
          cp.generateText();
          cCaptcha = cp.captchaText();
          ui->captcha_label->setPixmap(QPixmap::fromImage(cp.captchaImage()));


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
    int cin=ui->lineEdit_cin_2->text().toInt();Employes E1;
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





void MainWindow::on_qrpushbutton_clicked()
{
    int tabeq=ui->tableView_2->currentIndex().row();
        QVariant cinn=ui->tableView_2->model()->data(ui->tableView_2->model()->index(tabeq,0));
        int cin= cinn.toInt();
        QSqlQuery qry;
        qry.prepare("select * from EMPLOYES where cin=:cin");
        qry.bindValue(":cin",cin);
        qry.exec();
        QString nom, prenom,cine;

        while(qry.next()){
            nom=qry.value(1).toString();
            prenom=qry.value(2).toString();

        }
         cine=int(cin);
         cine="cin: "+cine+"nom: "+nom+" prenom: "+prenom;
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
void MainWindow::on_pbajouter_clicked()
{
    int IdEn=ui->leIdEn->text().toInt();

    QString nom=ui->lenom->text();
    QString adresse=ui->ladresse->text();
    QString mail=ui->lemail->text();
     int numero=ui->lenumero->text().toInt();

 Entreprise E (IdEn,nom,adresse,mail,numero);
 bool test=E.ajouter();
 MainWindow w;
 if(test)
 {  ui->tab_entreprise ->setModel(E.afficher());
     QMessageBox::information(nullptr, QObject::tr("database is open"),
                 QObject::tr("ajout avec succes.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);

}
 else
     QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                 QObject::tr("echec d ajout.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_supprimer_clicked()
{
Entreprise E; E.setIdEn(ui->leidensupp->text().toInt());
bool test=E.supprimer(E.getIdEn());
MainWindow w;

QMessageBox msgBox;
if(test)
{
    w.show();
    {
    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("suppression avec succes.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
                 ui->tab_entreprise->setModel(E.afficher()) ;

                }

}
else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr("echec de suppression.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


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
    QString nom =ui->nom_supp->text();
    QString adresse=ui->adresse_supp->text();
    QString mail=ui->mail_supp->text();
    int num=ui->num_supp->text().toInt();
    QDate date_s =ui->dateStart_supp->date();
    QDate date_e =ui->dateEnd_supp->date();
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
            ui->nom_supp->clear();
            ui->adresse_supp->clear();
            ui->mail_supp->clear();
            ui->num_supp->clear();

    }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("try again.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
            ui->id_supp->clear();
            ui->nom_supp->clear();
            ui->adresse_supp->clear();
            ui->mail_supp->clear();
            ui->num_supp->clear();
        }
}



void MainWindow::on_tri_name_clicked()
{
    ui->tableView->setModel(tabb.trinom());
}

void MainWindow::on_Find_id_clicked()
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

        int id;bool test;
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
    if (test)
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
    }
}
void MainWindow::on_tri_jour_clicked()
{
    ui->tableView->setModel(tabb.trileft());
}

void MainWindow::on_Find_mail_clicked()
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


void MainWindow::on_pushButton_modifier_entreprise_clicked()
{
    Entreprise E ;
      int IdEn=ui->leIdEn->text().toInt();
     QString nom=ui->lenom->text();
     QString adresse=ui->ladresse->text();
     QString mail=ui->lemail->text();
     int numero=ui->lenumero->text().toInt();
     Entreprise E1(IdEn,nom,adresse,mail,numero);
     //bool test= E.modifier(,nom,adresse,fonction,date_naissance);
      bool test;
      test= E1.modifier(IdEn,nom,adresse,mail,numero );
     if (test)
         //[☺]
        {
         ui->tab_entreprise->setModel(E1.afficher());
         QMessageBox::information(nullptr, QObject::tr("MODIFIER"),
                                       QObject::tr("MODIFICATION avec succes .\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);

         }
                       else
                           QMessageBox::critical(nullptr, QObject::tr("MODIFIER"),
                                       QObject::tr("UPDATE failed.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_ajoutercollaborateur_clicked()
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
           ui->tableView_5->setModel(tabb1.afficher());
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

void MainWindow::on_Ajouter_clicked()
{
    int id=ui->id_rdv->text().toInt();
    QString nom =ui->nom_rdv->text();
    QString mail=ui->mail_rdv->text();
    int num =ui->num_rdv->text().toInt();
    QDate date_s =ui->dateStart_rdv->date();
    QDate actual_date=QDate::currentDate();
    //
    RDV c(nom,mail,num,id,date_s);
    //
    bool test=c.ajouter ();
    if (test)
    {
           ui->tableView_5->setModel(tabb1.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                     QObject ::tr("Ajout effectué\n"
                                  "click cancel to exit"),
                QMessageBox:: Cancel);
        ui->id_rdv->clear();
        ui->nom_rdv->clear();
        ui->mail_rdv->clear();
        ui->num_rdv->clear();
} else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                             QObject::tr("try again.\n"
                                         "click cancel to exit."),QMessageBox::Cancel);
        ui->id_rdv->clear();
        ui->nom_rdv->clear();
        ui->mail_rdv->clear();
        ui->num_rdv->clear();
    }
}

void MainWindow::on_tri_id_2_clicked()
{
    ui->tableView_5->setModel(tabb1.tri());

}

void MainWindow::on_tri_name_2_clicked()
{
    ui->tableView_5->setModel(tabb1.trinom());

}

void MainWindow::on_Find_id_2_clicked()
{
    int id=ui->Find_line_2->text().toInt();
    if (id==NULL) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a Number."));
        return;
    } else {
    ui->tableView->setModel(tabb1.recherche(id));
    }
}

void MainWindow::on_Find_nom_2_clicked()
{
    QString nom=ui->Find_line_2->text();
    if (nom.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a Name."));
        return;
    } else {
    ui->tableView_5->setModel(tabb1.recherche_nom(nom));
    }
}

void MainWindow::on_pb_pdf_clicked()
{
    QString strStream;
      QTextStream out(&strStream);

   const int rowCount = ui->tableView_5->model()->rowCount();
   const int columnCount = ui->tableView_5->model()->columnCount();
   out <<  "<html>\n"
           "<head>\n"
   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
   <<  QString("<title>%1</title>\n").arg("strTitle")
   <<  "</head>\n"
  "<body bgcolor=#ffffff link=#5000A0>\n"

  //     "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste Des RDV </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
   for (int column = 0; column < columnCount; column++)
   if (!ui->tableView_5->isColumnHidden(column))
       out << QString("<th>%1</th>").arg(ui->tableView_5->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

                                           // data table
           for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_5->isColumnHidden(column)) {
     QString data = ui->tableView_5->model()->data(ui->tableView_5->model()->index(row, column)).toString().simplified();
     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                   }
                                               }
                      out << "</tr>\n";
                                           }
                            out <<  "</table> </center>\n"
                                    "</body>\n"
                                  "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}

void MainWindow::on_Modifier_2_clicked()
{
    int id=ui->id_supp_rdv->text().toInt();
    QString nom =ui->nom_supp_rdv->text();
    QString mail=ui->mail_supp_rdv->text();
    int num=ui->num_supp_rdv->text().toInt();
    QDate date_s =ui->dateStart_supp_rdv->date();
    QDate actual_date=QDate::currentDate();
       RDV c(nom,mail,num,id,date_s);
        bool test=c.modifier(id);
        if (test)
        {
               ui->tableView_5->setModel(tabb1.afficher());
            QMessageBox :: information (nullptr, QObject ::tr("OK"),
                         QObject ::tr("modifier effectué\n"
                                      "click cancel to exit"),
                    QMessageBox:: Cancel);
            ui->id_supp_rdv->clear();
            ui->nom_supp_rdv->clear();
            ui->mail_supp_rdv->clear();
            ui->num_supp_rdv->clear();

    }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                 QObject::tr("try again.\n"
                                             "click cancel to exit."),QMessageBox::Cancel);
            ui->id_supp_rdv->clear();
            ui->nom_supp_rdv->clear();
            ui->mail_supp_rdv->clear();
            ui->num_supp_rdv->clear();
        }
}

void MainWindow::on_Supprimer_2_clicked()
{
    int id =ui->id_supp_rdv->text().toInt();
     bool test=tabb1.supprimer(id);
     if (test)
     {
         ui->tableView_5->setModel(tabb1.afficher());
        QMessageBox :: information (nullptr, QObject ::tr("OK"),
                      QObject ::tr("suppression effectué\n"
                                   "click cancel to exit"),
                 QMessageBox:: Cancel);
        ui->id_supp_rdv->clear();

    }
     else
     {
         QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
         ui->id_supp_rdv->clear();
     }
}

void MainWindow::on_tri_id_clicked()
{
    ui->tableView->setModel(tabb.tri());

}

void MainWindow::on_connecter_clicked()
{
    QStackedWidget stackedWidget;
            connect(ui->stackedWidget, SIGNAL(clicked()), this, SLOT(viewData));
            QString username=ui->lineEdit_username->text();
                    QString password = ui->lineEdit_password->text();
                    if(username == "aziz" && password == "aziz")
                    { QMessageBox::information(this, "Login", "Username and password is correct");
                   //connect(ui->MainWindow->page_3, SIGNAL(on_connecter_clicked()), this, SLOT(viewData));
                    ui->stackedWidget->setCurrentIndex(1);
                    }
                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                        else if(username == "soulaima" && password == "soulaima")
                    { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(2);
                    }
                            //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                            else if(username == "oussema" && password == "oussema")
                            { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(3);
                    }
                                //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                else if(username == "yassine" && password == "yassine")
                                { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(4);
                    }
                                    //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                    else if(username == "roua" && password == "roua")
                                    { QMessageBox::information(this, "Login", "Username and password is correct");
                       ui->stackedWidget->setCurrentIndex(5);
                    }

                                        //hide(); mainwindow = new MainWindow(this); mainwindow->show(); }
                                                else { QMessageBox::warning(this,"Login", "Username and password is not correct"); }
}
//candidats
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
            ui->tableView_4->setModel(ctmp.Afficher());

            QMessageBox::information(nullptr, QObject::tr("Succes"),
                        QObject::tr("Ajout successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tableView_4->setModel(ctmp.Afficher());

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                        QObject::tr("Ajout failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel); }
}

void MainWindow::on_butSupprimer_clicked()
{
    QString id_del=ui->tableView_4->model()->data(ui->tableView->model()->index(ui->tableView_4->currentIndex().row(),0)).toString();

    bool supp = ctmp.Supprimer(id_del);

    if(supp)
        {
        ui->tableView_4->setModel(ctmp.Afficher());
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Suppression avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Suppression échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }

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
        ui->tableView_4->setModel(ctmp.Afficher());
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Modification avec succés.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);

    }
        else
           { QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Modification échoué.\n"
                                    "Click Cancel to exit."), QMessageBox::Ok);
    }

}

void MainWindow::on_Search_clicked()
{
    if((ui->comboBox->currentText() == "")||(ui->lineRechercher->text() == "")){
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                QObject::tr("Veuillez selectez une paramètre.\n"), QMessageBox::Ok);
    }
    else {
        ui->tableView_4->setModel(ctmp.Rechercher(ui->lineRechercher->text(), ui->comboBox->currentIndex()));
    }
}

void MainWindow::on_butTrier_clicked()
{
    ui->tableView_4->setModel(ctmp.Tri(ui->comboBox_2->currentIndex(), ui->comboBox_3->currentIndex()));
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Captcha cp;
    cp.randomize();
    cp.setDifficulty(3);
    /*cp.loadDictionary("dictionary.txt");
    cp.setTextGeneration(Captcha::TextGeneration_Dictionary);*/
    cp.generateText();
    //painter.drawImage(30, 30, cp.captchaImage());
}
