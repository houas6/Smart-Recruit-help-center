#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QMainWindow>
#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QVideoFrame>
#include <QListWidget>
#include <QIcon>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QtSql>
#include <QSqlQuery>


namespace Ui {
class MEDIA_PLAYER;
}

class MEDIA_PLAYER : public QMainWindow
{
    Q_OBJECT

public:
    explicit MEDIA_PLAYER(const QString &Path ,QWidget *parent = nullptr);
    ~MEDIA_PLAYER();

private slots:
    void on_Pause_Media_triggered();

    void on_Play_Media_triggered();

    void on_Stop_Media_triggered();

private:
    Ui::MEDIA_PLAYER *ui;
    QString Path;

    QMediaPlayer *player ;
    QVideoWidget *vw;
    QSlider *slider;
    QSlider *progress_bar;
};

#endif // MEDIA_PLAYER_H
