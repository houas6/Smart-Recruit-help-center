#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include <QMainWindow>
#include <QTableWidget>
#include <QTcpServer>
#include<QTcpSocket>
#include"chat.h"
#include "arduino.h"

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



    void on_tabWidget_currentChanged(int index);

    void on_qrpushbutton_clicked();

    void on_pushButton_clicked();
    bool launch_chat(chat&);
private:
    Ui::MainWindow *ui;
    Employes Etmp;

    QByteArray data;
    Arduino A;
};
#endif // MAINWINDOW_H
