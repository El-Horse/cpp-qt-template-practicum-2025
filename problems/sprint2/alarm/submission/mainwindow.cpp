#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>

QString TimeToString(QTime time) {
    return QString("%1:%2:%3").arg(time.hour(), 2, 10, QChar('0')).arg(time.minute(), 2, 10, QChar('0')).arg(time.second(), 2, 10, QChar('0'));
}

QString TimeToString(std::chrono::milliseconds ms) {
    return TimeToString(QTime::fromMSecsSinceStartOfDay(ms.count() + 500));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&timer_, &prac::QTimer::timeout, this, &MainWindow::OnTimer);
    connect(ui -> action_load_file, &QAction::triggered, this, &MainWindow::SelectSound);
    timer_.setSingleShot(true);
    timer_.start(1000);
    player_.setAudioOutput(&audio_out_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnTimer()
{
    QString time = prac::QTime::currentTime().toString();
    ui -> lbl_now -> setText(time);
    ProcessAlarm();
    timer_.start(1000);
}

void MainWindow::SelectSound()
{
    QString file_name = prac::QFileDialog::getOpenFileName
        (this, QString::fromUtf8("Открыть файл"), QDir::currentPath(), "*.wav;*.mp3");
    player_.setSource(file_name);
//    int mark = (file_name.lastIndexOf(QChar('/')));
    QStringList t = file_name.split('/');

    ui -> lbl_melody -> setText(t[t.size()-1]);
}

void MainWindow::on_pb_start_stop_clicked()
{
    if(!alarm_runing_){//кнопка "старт"
        auto now = prac::QDateTime::currentDateTime();
        auto alarm_time = QTime(ui -> sb_hour -> value(), ui -> sb_min -> value(), ui -> sb_sec -> value());
        alarm_moment_ = prac::QDateTime(now.date(), alarm_time);
        if (alarm_moment_ < now)
            alarm_moment_ = prac::QDateTime(now.date().addDays(1),alarm_time);
        ui -> pb_start_stop -> setText("Стоп");
        alarm_runing_ = true;
    }
    else{ // Будильник работает, кнопка "стоп"
        alarm_moment_ = prac::QDateTime{};
        player_.stop();
        ui -> pb_start_stop -> setText("Старт");
        alarm_runing_ = false;
    }
}

void MainWindow::ProcessAlarm()
{
    if(!alarm_runing_){
        ui -> lbl_timeout -> setText("Установите будильник");
    }
    else{
        auto now = prac::QDateTime::currentDateTime();
        auto time_to_alarm = TimeToString( alarm_moment_ - now);

        if(alarm_moment_ >= now)
            ui -> lbl_timeout -> setText(time_to_alarm);
        else{
            ui -> lbl_timeout -> setText("Пора вставать");
            if (player_.playbackState() != QMediaPlayer::PlaybackState::PlayingState)
                player_.play();
        }
    }
}

