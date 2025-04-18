#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

int DaysPerMonth(int month, int year)
{
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29; // February in a leap year.
        } else {
            return 28; // February in a non-leap year.
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30; // April, June, September, November have 30 days.
    } else {
        return 31; // All other months have 31 days.
    }
}

int CalculateDaysFromStartYear(int day, int month, int year)
{
    if(month == 0) {
        return 0;
    }
    int num_days = 0;
    for(size_t num_month = 1; num_month < static_cast<size_t>(month); ++num_month) {
        num_days += DaysPerMonth(num_month, year);
    }
    num_days += day;
    return num_days;
}

QString MainWindow::GetFormatType1(int day, int month, int year)
{
    // Реализуйте метод форматирования даты "дд.мм.гггг"
    QString format1 = "%1.%2.%3";
    //   QString formated1 = format1.arg(day).arg(month).arg(year);
    QString formated1 = format1.arg(day,2,10,QChar('0'))
                            .arg(month,2,10,QChar('0'))
                            .arg(year);
    return formated1;

}

QString MainWindow::GetFormatType2(int day, int month, int year)
{
    // Реализуйте метод форматирования даты "дд/мм/гггг"
    QString format2 = "%2/%1/%3";
    QString formated2 = format2.arg(day,2,10,QChar('0'))
                            .arg(month,2,10,QChar('0'))
                            .arg(year);
    return formated2;
}

QString MainWindow::GetFormatType3(int day, int month, int year)
{
    // Реализуйте метод форматирования даты "дд месяц гггг"
    QString format3 = "%1 %2 %3 года";
    QString month_text = MonthToText(month);
    QString formated3 = format3.arg(day,2,10,QChar('0'))
                            .arg(month_text)
                            .arg(year);
    return formated3;

}

QString MainWindow::GetStrNumDays(int num_days, int year) {
    // Метод должен возвращать текст о номере дня в году.
    QString format4 = "Это %1 день в %2 году";
    QString formated4 = format4.arg(num_days).arg(year);
    return formated4;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui -> le_day -> setValidator(new QIntValidator(1,31,this));
    ui -> le_month -> setValidator(new QIntValidator(1,12,this));
    ui -> le_year -> setValidator(new QIntValidator(1,9999, this));

    SetError("Некорректная дата");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowFormattedDate()
{


    // Отобразим результаты.
    // Используйте DaysPerMonth для определения количества дней в месяце.
    // Используйте CalculateDaysFromStartYear для определения номера дня в году.

    // Используйте GetFormatType1, GetFormatType2, GetFormatType3 и GetStrNumDays
    // для определения надписей, которые нужно вывести пользователю.
    // Эти методы реализуйте самостоятельно.
}

void MainWindow::SetError(const QString& err_text)
{
    ui->lbl_format_type1->clear();
    ui->lbl_format_type2->clear();
    ui->lbl_format_type3->clear();
    ui->lbl_message->setText(err_text);
}

void MainWindow::on_le_date_textChanged(const QString&)
{
    if(editing_now_)
        return;
    editing_now_ = true;

    auto arr = ui -> le_date -> text().split(".");
    if(arr.size() == 3){
        ui -> le_day -> setText(arr[0]);
        ui -> le_month -> setText(arr[1]);
        ui -> le_year -> setText(arr[2]);
        PrintDate (arr[0], arr[1], arr[2]);
    }
    CheckValidity(ui -> le_date);
    editing_now_ = false;
}

void MainWindow::on_le_day_textChanged(const QString&)
{
    if(editing_now_)
        return;
    editing_now_ = true;

    PrintDate(ui -> le_day -> text(), ui -> le_month -> text(), ui -> le_year -> text());
CheckValidity(ui -> le_day);
    editing_now_ = false;
}

void MainWindow::on_le_month_textChanged(const QString&)
{
    if(editing_now_)
        return;
    editing_now_ = true;

    PrintDate(ui -> le_day -> text(), ui -> le_month -> text(), ui -> le_year -> text());
CheckValidity(ui -> le_month);
    editing_now_ = false;   // Пользователь изменил месяц. Реализуйте слот.
}

void MainWindow::on_le_year_textChanged(const QString&)
{
    if(editing_now_)
        return;
    editing_now_ = true;

    PrintDate(ui -> le_day -> text(), ui -> le_month -> text(), ui -> le_year -> text());
CheckValidity(ui -> le_year);
    editing_now_ = false;    // Пользователь изменил год. Реализуйте слот.
}

void MainWindow::CheckValidity(QLineEdit *elem)
{
    if(!(elem->hasAcceptableInput())) {
//        SetError("Некорректная дата");
        elem -> setStyleSheet("border:1px solid red");

    }
    else
        elem -> setStyleSheet("border:1px solid transparent");
}

void MainWindow::PrintDate(const QString &d, const QString &m, const QString &y)
{
    int day = d.toInt();
    int month = m.toInt();
    int year = y.toInt();

    if (day == 0 || month == 0 || year == 0){
        SetError("Некорректная дата");
        return;
    }
    if(day < 1 || day > DaysPerMonth(month, year)
        || month < 1 || month > 12
        || year < 1 || year > 9999){
        SetError("Такой даты не существует");
        return;
    }

    ShowFormattedDate();
    QString t;
    t = GetFormatType1(day,month,year);
    ui -> le_date -> setText(t);
    ui -> lbl_format_type1 -> setText(t);
    ui -> lbl_format_type2 -> setText(GetFormatType2(day,month,year));
    ui -> lbl_format_type3 -> setText(GetFormatType3(day,month,year));
    ui -> lbl_message -> setText(GetStrNumDays(CalculateDaysFromStartYear(day,month,year), year));

}

QString MainWindow::MonthToText(int m){

    assert(m > 0);
    assert(m < 13);

    static const std::vector<QString> text = {
        QStringLiteral("января"), QStringLiteral("февраля"),
        QStringLiteral("марта"), QStringLiteral("апреля"),
        QStringLiteral("мая"), QStringLiteral("июня"),
        QStringLiteral("июля"), QStringLiteral("августа"),
        QStringLiteral("сентября"), QStringLiteral("октября"),
        QStringLiteral("ноября"), QStringLiteral("декабря")
    };
    return text[m-1];
}
