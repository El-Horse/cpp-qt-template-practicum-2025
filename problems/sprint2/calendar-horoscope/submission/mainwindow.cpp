#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include "magic_horoscope.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui -> le_year -> setValidator(new QIntValidator(1,9999,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_le_year_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
        ui ->lbl_calendar -> setText("Введите год");
    else{
        year_ = arg1.toInt();
        UpdateCalendar();
    }
}


void MainWindow::on_rb_eastern_toggled(bool )
{
    calendar_type_ = 0;

    UpdateCalendar();
}


void MainWindow::on_rb_tibetan_toggled(bool )
{
    calendar_type_ = 1;
    UpdateCalendar();
}


void MainWindow::on_rb_zoroastrian_toggled(bool )
{
    calendar_type_ = 2;
    UpdateCalendar();
}

void MainWindow::on_rb_zodiac_toggled(bool )
{
    horoscope_type_ = 0;
    UpdateCalendar();
}


void MainWindow::on_rb_druid_toggled(bool )
{
    horoscope_type_ = 1;
    UpdateCalendar();
}

void MainWindow::on_sb_day_valueChanged(int arg1)
{
    day_ = arg1;
    UpdateCalendar();
}


void MainWindow::on_cb_month_currentIndexChanged(int index)
{
    month_ = 1 + index;
    UpdateCalendar();
}


void MainWindow::on_cb_is_date_toggled(bool is_active)
{
    ui -> wd_horoscope -> setEnabled(is_active);
    ui ->sb_day -> setEnabled(is_active);
    ui -> rb_druid -> setEnabled(is_active);
    ui -> rb_zodiac -> setEnabled(is_active);
    ui -> gb_horoscope -> setEnabled(is_active);
    if(is_active)
        activ_date_ = true;
    else{
        activ_date_ = false;
        ui -> lbl_horoscope -> setText("Ввод даты отключён");
    }
    UpdateCalendar();
}


void MainWindow::UpdateCalendar(){


    QString calendar_mask = "%1 — это год %2%3";
    QString year_type ="";
    QString year_element = "";
    switch (calendar_type_) {
    case 0:
        year_type = GetAnimalForEasternCalendar(year_);
        year_element = ". Стихия/цвет — " + GetElementForEasternCalendar(year_);
        break;
    case 1:
        year_type = GetAnimalForTibetanCalendar(year_);
        year_element ="";
        break;
    case 2:
        year_type = GetAnimalForZoroastrianCalendar(year_);
        year_element = "";
    default:
        break;
    }

    ui -> lbl_calendar -> setText(calendar_mask.arg(year_).arg(year_type, year_element));

    if(!activ_date_)
        return;

    QString horoscope_mask = "%1.%2 ";
    horoscope_mask = horoscope_mask.arg(day_,2,10,QChar('0')).arg(month_,2,10,QChar('0'));
    QString zodiac = "";



    if(horoscope_type_ == 0){
        zodiac = GetZodiac(day_, month_, year_);
        if (!zodiac.isEmpty())
        ui -> lbl_horoscope ->setText(horoscope_mask + "— ваш знак зодиака "
                                   +zodiac + " по зодиакальному гороскопу");
        else
                ui -> lbl_horoscope -> setText("Такой даты не существует");
    }
    else if (horoscope_type_ == 1){
        zodiac = GetTree(day_, month_, year_);
        if (!zodiac.isEmpty())
        ui -> lbl_horoscope ->setText(horoscope_mask + "— ваше тотемное дерево "
                                   +zodiac + " по гороскопу друидов");
        else
            ui -> lbl_horoscope -> setText("Такой даты не существует");
    }





}

