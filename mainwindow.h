#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "collaboration.h"

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
    void on_on_pushButton_ajouter_clicked_clicked();

private:
    Ui::MainWindow *ui;
    Collaboration ptmp;
};
#endif // MAINWINDOW_H
