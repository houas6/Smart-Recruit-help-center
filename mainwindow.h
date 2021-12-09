#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "collaboration.h"
#include <QDateTime>
#include <popup.h>
#include "arduino.h"
#include <QMainWindow>

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

    void on_Ajouter_clicked();

    void on_Supprimer_clicked();

    void on_Modifier_clicked();

    void on_tri_id_clicked();

    void on_tri_name_clicked();

    void on_Find_id_clicked();

    void on_Find_nom_clicked();


    void on_update_clicked();

   // void on_tabWidget_currentChanged(int index);

    void on_export_2_clicked();

    void on_tri_jour_clicked();

    void on_Find_email_clicked();
    void update_label();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Collaboration tabb;
    Popup *popup;

    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
