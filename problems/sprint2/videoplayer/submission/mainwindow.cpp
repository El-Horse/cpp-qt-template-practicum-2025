#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Присоедините аудио и видеовыходы к плееру.

    connect(&player_, &prac::QMediaPlayer::positionChanged, this, &MainWindow::on_position_changed);
    connect(&player_, &prac::QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_media_status_changed);
    connect(&player_, &prac::QMediaPlayer::playbackStateChanged, this, &MainWindow::on_playback_state_changed);

    player_.setAudioOutput(&audio_output_);
    player_.setVideoOutput(ui -> video_output);
    audio_output_.setVolume(1.f);
    ui -> btn_pause -> setText("||") ;
}

void MainWindow::on_position_changed(qint64 position) {
    position_changing_ = true;
    ui -> sld_pos -> setValue(position);
    ui -> lbl_current_pos -> setText(QString::number(position));
    position_changing_ = false;
}

void MainWindow::on_media_status_changed(QMediaPlayer::MediaStatus) {
    double duratio = player_.duration();
    ui -> sld_pos -> setMaximum(duratio);
    QString txt = QString::number(duratio);
    ui -> lbl_duration -> setText(txt);

}

void MainWindow::on_playback_state_changed(QMediaPlayer::PlaybackState new_state) {

}

void MainWindow::on_btn_choose_clicked() // выбор файла
{

    QString file_name = prac::QFileDialog::getOpenFileName(this, QString("Выбрать видео"), QDir::currentPath(),"*.mp4");
    player_.setSource(QUrl::fromLocalFile(file_name));
    player_.play();
    ui -> btn_pause -> setText("⏵") ;
}

void MainWindow::on_btn_pause_clicked()
{
    auto state = player_.playbackState();
    if (state == QMediaPlayer::PlaybackState::PausedState){ // на паузе
        player_.play();
        ui -> btn_pause -> setText("⏵") ;
}
    else if (state == QMediaPlayer::PlaybackState::StoppedState){ // остановлено
        player_.setPosition(0);
        player_.play();
        ui -> btn_pause -> setText("⏵") ;
}
    else if (state == QMediaPlayer::PlaybackState::PlayingState){ // проигрывание
        player_.pause();
        ui -> btn_pause -> setText("||") ;
}
}

void MainWindow::on_sld_volume_valueChanged(int value)
{
    audio_output_.setVolume(value/100.);
}

void MainWindow::on_sld_pos_valueChanged(int value)
{
    if (position_changing_)
        return;
    player_.setPosition(value);
}

MainWindow::~MainWindow()
{
    delete ui;
}
