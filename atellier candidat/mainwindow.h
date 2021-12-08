#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "candidat.h"
#include <QVector>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_butAjouter_clicked();

    void on_butSupprimer_clicked();

    void on_butModifier_clicked();

    void on_butAjouter_2_clicked();

    void on_butRechercher_clicked();

    void on_Search_clicked();

    void on_butTrier_clicked();

private:
    Ui::MainWindow *ui;
    candidat ctmp;
};

#endif // MAINWINDOW_H
