#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Calendar {
    kEastern,
    kTibetan,
    kZoroastrian
};

enum class Horoscope {
    kZodiac,
    kDruid
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void ChangeButtonsState(bool state);

private slots:

    void on_rb_eastern_toggled(bool );

    void on_rb_tibetan_toggled(bool );

    void on_rb_zoroastrian_toggled(bool );

    void on_cb_is_date_toggled(bool );

    void on_rb_zodiac_toggled(bool);

    void on_rb_druid_toggled(bool);

    void on_sb_day_valueChanged(int arg1);

    void on_cb_month_currentIndexChanged(int index);

    void on_le_year_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Calendar calendar_ = Calendar::kEastern;
    Horoscope horoscope_ = Horoscope::kZodiac;
    void UpdateCalendar(void);

    int year_ = 1;
    int day_ = 1;
    int month_ = 1;
    int calendar_type_ = 0; // Вид календаря
    bool activ_date_ = false; // ввод полной даты
    bool horoscope_type_ = 0; // Вид гороскопа

};
#endif // MAINWINDOW_H
