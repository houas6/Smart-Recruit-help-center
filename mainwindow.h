#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QTcpServer>
#include<QTcpSocket>
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
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();



    void on_pushButton_trie_clicked();

    void on_pushButton_Recherche_clicked();
    void connexion_nueva();
    void leer_socket();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    Employes Etmp;
    QTcpServer*mServer;
    QTcpSocket*mSocket;
};
#endif // MAINWINDOW_H
