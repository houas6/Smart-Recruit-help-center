#include "media_player.h"
#include "ui_media_player.h"

MEDIA_PLAYER::MEDIA_PLAYER(const QString& Path,QWidget *parent) :Path(Path),
    QMainWindow(parent),
    ui(new Ui::MEDIA_PLAYER)
{
    ui->setupUi(this);


    progress_bar =new QSlider();
    slider=new  QSlider();

    ui->toolBar->addWidget(progress_bar);
    ui->toolBar->addWidget(slider);

     progress_bar->setOrientation(Qt::Horizontal);


    player=new QMediaPlayer(this);
    vw=new QVideoWidget;

    player->setMedia(QUrl::fromLocalFile(this->Path));
    player->setVideoOutput(vw);
     vw->show();
   // this->setFixedSize(720,480);

    player->setVolume(50);
    slider->setValue(player->volume());

     connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setVolume);
     connect(player,&QMediaPlayer::durationChanged,progress_bar,&QSlider::setMaximum);
     connect(player,&QMediaPlayer::positionChanged,progress_bar,&QSlider::setValue);
     connect(progress_bar,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    this->setCentralWidget(vw);

    player->play();




}

MEDIA_PLAYER::~MEDIA_PLAYER()
{
    delete player;
    delete vw;
    delete ui;
}


void MEDIA_PLAYER::on_Pause_Media_triggered()
{
        player->pause();
}

void MEDIA_PLAYER::on_Play_Media_triggered()
{
    player->play();
}

void MEDIA_PLAYER::on_Stop_Media_triggered()
{
        player->stop();
}
