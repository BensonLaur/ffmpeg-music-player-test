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



    player = new QMediaPlayer(this);
    player->setNotifyInterval(1);

    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(player,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(errorLoading(QMediaPlayer::Error)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));


    musicPlayer = new MusicPlayer(this);

    connect(musicPlayer, SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64)));
    connect(musicPlayer, SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));

    connect(musicPlayer, &MusicPlayer::albumFound, [=](QString text){ ui->labelAlbumTip_2->setText(text);});
    connect(musicPlayer, &MusicPlayer::artistFound, [=](QString text){ui->labelArtist->setText(text);});
    connect(musicPlayer, &MusicPlayer::titleFound, [=](QString text){ui->labelTitle->setText(text);});
    connect(musicPlayer, &MusicPlayer::pictureFound, [=](QPixmap pic){
        QPixmap pic2 = pic.scaled(ui->labelPicture->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->labelPicture->setPixmap(pic2);}
    );
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

void MainWindow::mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    QMessageBox msgBox;

    switch (status) {
    case QMediaPlayer::MediaStatus::UnknownMediaStatus:
        msgBox.setText("UnknownMediaStatus.");
        msgBox.exec();
        break;
    case QMediaPlayer::MediaStatus::NoMedia:
        msgBox.setText("NoMedia.");
        msgBox.exec();
        break;
    case QMediaPlayer::MediaStatus::LoadingMedia:
        msgBox.setText("LoadingMedia.");
        msgBox.exec();
        break;
    case QMediaPlayer::MediaStatus::LoadedMedia:

        player->play();

        ui->labelSong->setText(currentSong);
        player->position();

        break;
    case QMediaPlayer::MediaStatus::StalledMedia:
        msgBox.setText("StalledMedia.");
        msgBox.exec();
        break;
    case QMediaPlayer::MediaStatus::BufferingMedia:
        msgBox.setText("BufferingMedia.");
        msgBox.exec();
        break;
    case QMediaPlayer::MediaStatus::EndOfMedia:
        msgBox.setText("EndOfMedia.");
        msgBox.exec();

        player->play();
        break;
    case QMediaPlayer::MediaStatus::InvalidMedia:
        msgBox.setText("InvalidMedia.");
        msgBox.exec();
        break;
    default:
        break;
    }


}

void MainWindow::errorLoading(QMediaPlayer::Error)
{
    QMessageBox msgBox;
    msgBox.setText("error.");
    msgBox.exec();
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
    ui->songSlider->setValue(pecentOfThousand);

    int ms = position % 1000;
    position = position/1000;
    int s = position % 60;
    int m = position/60;

    QString timeLabel;
    timeLabel.sprintf("%.2d:%.2d.%.3d",m, s, ms);

    ui->label_cur_time->setText(timeLabel);



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
