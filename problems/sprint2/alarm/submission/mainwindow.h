#pragma once

#include <QMainWindow>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <prac/QDateTime>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    prac::QDateTime GetAlarmMoment() const {
        return alarm_moment_;
    }

private slots:
    void OnTimer();
    void SelectSound();

    // Тут объявите слоты.

    void on_pb_start_stop_clicked();

private:
    Ui::MainWindow *ui;
    prac::QDateTime alarm_moment_;
    prac::QTimer timer_;
    bool alarm_runing_ = false;

    void ProcessAlarm();
    prac::QMediaPlayer player_ {this};
    QAudioOutput audio_out_ {this};
};
