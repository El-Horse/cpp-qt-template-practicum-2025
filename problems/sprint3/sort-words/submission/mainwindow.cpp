#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rb_asc_clicked()
{
    // Ваш код.
    sort_a_to_z_ = true;
    SortText();
}

void MainWindow::on_rb_desc_clicked()
{
    // Ваш код.
    sort_a_to_z_ = false;
    SortText();
}

void MainWindow::on_cb_case_clicked()
{
    // Ваш код.
    sort_case_ = !sort_case_;
SortText();
}

void MainWindow::on_le_unsorted_textChanged(const QString&)
{
    SortText();
}

void MainWindow::SortText()
{   unsort_ = ui ->le_unsorted ->text();
    QStringList sorted_list = unsort_.split(' ');
    auto Case_az =[=, this](const QString& left, const QString& right){
        if (sort_case_)
            return QString::compare(left,right,Qt::CaseInsensitive) < 0;
        else
            return QString::compare(left,right,Qt::CaseSensitive) < 0;
    };
    auto Case_za =[=, this](const QString& left, const QString& right){
        if (sort_case_)
            return QString::compare(left,right,Qt::CaseInsensitive) > 0;
        else
            return QString::compare(left,right,Qt::CaseSensitive) > 0;
    };

    if(sort_a_to_z_){
        std::sort(sorted_list.begin(),sorted_list.end(),Case_az);
    }
    else{
        std::sort(sorted_list.begin(),sorted_list.end(),Case_za);
    }
    QString sorted;
    bool is_first = true;
    for (auto s : sorted_list){
        if (!is_first){
            sorted += ' ';

        }
        is_first = false;
        sorted +=s;
    }

    ui ->le_sorted -> setText(sorted);
}
