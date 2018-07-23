#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QMessageBox>

class MusicPlayer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_selectMusic_clicked();


    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void errorLoading(QMediaPlayer::Error);
    void durationChanged(qint64);
    void positionChanged(qint64);

    void on_btnBack10_clicked();

    void on_btnForward10_clicked();

    void on_btnPlayPause_clicked();

    void on_btnStop_clicked();

    void on_reloadMusic_clicked();

private:
    QString currentSong;
    QMediaPlayer * player;

    MusicPlayer* musicPlayer;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
