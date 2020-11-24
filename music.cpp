#include "music.h"
#include "ui_music.h"
#include <QMediaPlayer>
#include <QFileDialog>
music::music(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::music)
{
    ui->setupUi(this);
    mMediaPlayer = new QMediaPlayer(this);
    connect(mMediaPlayer,&QMediaPlayer::positionChanged, [&](qint64 pos){
        ui->avance->setValue(pos);
    });
    connect(mMediaPlayer,&QMediaPlayer::durationChanged,[&](qint64 dur){
        ui->avance->setMaximum(dur);
    } );
}

music::~music()
{
    delete ui;
}



void music::on_pushButton_play_clicked()
{
mMediaPlayer->play();
}

void music::on_pushButton_pause_clicked()
{
mMediaPlayer->pause();
}

void music::on_pushButton_stop_clicked()
{
mMediaPlayer->stop();
}

void music::on_pushButton_choisir_clicked()
{ QString filename=QFileDialog::getOpenFileName(this,"choisir");
    if(filename.isEmpty())
    {return;}
    mMediaPlayer->setMedia(QUrl::fromLocalFile(filename));
    mMediaPlayer->setVolume(ui->volume->value());
    on_pushButton_play_clicked();
}

void music::on_volume_valueChanged(int value)
{
mMediaPlayer->setVolume(value);
}

void music::on_pushButton_mute_clicked()
{  if(ui->pushButton_mute->text()=="mute")
    {mMediaPlayer->setMuted(true);
    ui->pushButton_mute->setText("inmute");}
    else
    {
        mMediaPlayer->setMuted(false);
            ui->pushButton_mute->setText("mute");
    }
}
