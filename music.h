#ifndef MUSIC_H
#define MUSIC_H

#include <QDialog>

namespace Ui {
class music;
}
class QMediaPlayer;

class music : public QDialog
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = nullptr);
    ~music();

private slots:

    void on_pushButton_play_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_choisir_clicked();

    void on_volume_valueChanged(int value);

    void on_pushButton_mute_clicked();

private:
    Ui::music *ui;
    QMediaPlayer *mMediaPlayer;
};

#endif // MUSIC_H
