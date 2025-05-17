#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttons_ = {ui->pb_button_1, ui->pb_button_2, ui->pb_button_3, ui->pb_button_4};

    connect(setting_, &Setting::signalSetAction, this, &MainWindow::slotShowAction);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotShowAction(int num, QString action_name, std::function<void()> action) {
    // Сохраните действие, которое будет делать кнопка с номером num.
    // Действие находится в функциональном объекте action.
    // Поменяйте надпись на кнопке: установите текст action_name.


    switch (num){
    case 0:{
        button_action_[0] = action;
        ui ->pb_button_1 -> setText(action_name);
        break;
    }
    case 1:{
        button_action_[1] = action;
        ui ->pb_button_2 -> setText(action_name);
        break;
    }
    case 2:{
        button_action_[2] = action;
        ui ->pb_button_3 -> setText(action_name);
        break;
    }
    case 3:{
        button_action_[3] = action;
        ui ->pb_button_4 -> setText(action_name);
        break;
    }
    }

}

void MainWindow::on_pb_sett_1_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(0);
}

void MainWindow::on_pb_sett_2_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(1);
}

void MainWindow::on_pb_sett_3_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(2);
}

void MainWindow::on_pb_sett_4_clicked()
{
    setting_->show();
    setting_->SetButtonForSetting(3);
}

void MainWindow::on_pb_button_1_clicked()
{
    auto action = button_action_[0];
    action();

}


void MainWindow::on_pb_button_2_clicked()
{
    auto action = button_action_[1];
    action();
}


void MainWindow::on_pb_button_3_clicked()
{
    auto action = button_action_[2];
    action();
}


void MainWindow::on_pb_button_4_clicked()
{
    button_action_[3]();

}

