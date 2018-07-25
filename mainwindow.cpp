#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>


#include "musicPlayer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->songSlider->setRange(0,1000);
    ui->soundSlider->setRange(0,128);

    musicPlayer = new MusicPlayer(this);

    connect(musicPlayer, SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(musicPlayer, SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    connect(musicPlayer,SIGNAL(volumeChanged(int)),this,SLOT(volumeChanged(int)));

    connect(musicPlayer, &MusicPlayer::albumFound, [=](QString text){ ui->labelAlbumTip_2->setText(text);});
    connect(musicPlayer, &MusicPlayer::artistFound, [=](QString text){ui->labelArtist->setText(text);});
    connect(musicPlayer, &MusicPlayer::titleFound, [=](QString text){ui->labelTitle->setText(text);});
    connect(musicPlayer, &MusicPlayer::pictureFound, [=](QPixmap pic){
        QPixmap pic2 = pic.scaled(ui->labelPicture->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->labelPicture->setPixmap(pic2);}
    );

    musicPlayer->setNotifyInterval(1);

    AdjustingPos= false;
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_selectMusic_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Open", "F:/CloudMusic",
                                                      "Audio (*.mp3 *.wav *.aac *.mp4 *.ogg *.flac *.m4a);;All files (*.*)");

    if(files.size())
    {
        currentSong = files.first();

        ui->labelSong->setText(currentSong);
    }
}


void MainWindow::on_btnPlayPause_clicked()
{
    switch (musicPlayer->state()) {
    case MusicPlayer::PausedState:
    case MusicPlayer::StoppedState:
        musicPlayer->play();
        return;
    case MusicPlayer::PlayingState:
        musicPlayer->pause();
        return;
    default:
        return;
    }
}

void MainWindow::on_btnStop_clicked()
{
    musicPlayer->stop();
}

void MainWindow::durationChanged(qint64 duration)
{
    int ms = duration % 1000;
    duration = duration/1000;
    int s = duration % 60;
    int m = duration/60;

    QString timeLabel;
    timeLabel.sprintf("%.2d:%.2d.%.3d",m, s, ms);

    ui->label_tot_time->setText(timeLabel);

}

void MainWindow::positionChanged(qint64 position)
{
    int pecentOfThousand = int(1.0 * position / musicPlayer->duration() * 1000);

    if(!AdjustingPos)
        ui->songSlider->setValue(pecentOfThousand);

    int ms = position % 1000;
    position = position/1000;
    int s = position % 60;
    int m = position/60;

    QString timeLabel;
    timeLabel.sprintf("%.2d:%.2d.%.3d",m, s, ms);

    ui->label_cur_time->setText(timeLabel);



}

void MainWindow::volumeChanged(int volume)
{
     ui->soundSlider->setValue(volume);
}

void MainWindow::on_btnBack10_clicked()
{
    musicPlayer->backwardSeek(10000);
}

void MainWindow::on_btnForward10_clicked()
{
    musicPlayer->forwordSeek(10000);
}


void MainWindow::on_reloadMusic_clicked()
{
    if(currentSong != "")
    {
        musicPlayer->setMusicPath(currentSong);
        musicPlayer->reload();
    }
}

void MainWindow::on_soundSlider_valueChanged(int value)
{
    musicPlayer->setVolume(value);
}

void MainWindow::on_songSlider_sliderMoved(int position)
{
    posAdjust = musicPlayer->duration() * position / 1000;
}

void MainWindow::on_songSlider_sliderPressed()
{
    AdjustingPos = true;
}

void MainWindow::on_songSlider_sliderReleased()
{
    AdjustingPos = false;
    musicPlayer->seek(posAdjust);
}
